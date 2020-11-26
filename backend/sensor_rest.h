#ifndef __sensor_rest_api__
#define __sensor_rest_api__

#include <exception>
#define EXPAND_SSQLS_STATICS

#include <algorithm>
#include <string>

#include <iostream>
#include <pistache/http.h>
#include <pistache/net.h>
#include <pistache/router.h>
#include <pistache/endpoint.h>
#include <vector>
#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>

#include <mysql++.h>
#include <time.h>

#include "actors.h"
#include "rest_api.h"
#include "../db/dao.hpp"
#include "../db/dbtables.h"

class sensor_rest : public rest_api {
    public:
	explicit sensor_rest(Pistache::Address addr, mysqlpp::Connection &conn,
			     std::string location)
		: rest_api{ addr }, conn{ conn }, location{ location }
	{
		client = std::make_shared<Pistache::Http::Client>();
		client->init();
		this->serve();
	}

    protected:
	void setup_routes() override
	{
		Pistache::Rest::Routes::Post(
			this->get_router(), "/sensor/:id/:value",
			Pistache::Rest::Routes::bind(&sensor_rest::record_data,
						     this));
	}

	void record_data(const Pistache::Rest::Request &request,
			 Pistache::Http::ResponseWriter response) override
	{
		auto id = request.param(":id").as<int>();
		auto value = request.param(":value").as<int>();

		dao<db::sensor> dao_sensor{ conn };
		dao<db::sensor_data> dao_sensor_data{ conn };

		std::vector<db::sensor> ids = dao_sensor.get_all_ids();
		std::vector<int> id_int;
		for (auto s : ids) {
			id_int.push_back(s.id);
		}

		if (std::find(id_int.begin(), id_int.end(), id) ==
		    id_int.end()) {
			std::cout
				<< "Couldnt find id, so insering it to data table"
				<< std::endl;
			db::sensor new_data;
			new_data.id = id;
			new_data.name = request.body();
			dao_sensor.insert(new_data);
		}

		db::sensor_data new_sensor_data;
		new_sensor_data.id = 0;
		new_sensor_data.sensor_id = id;
		new_sensor_data.timestamp = (unsigned)time(NULL);
		new_sensor_data.data = value;

		dao_sensor_data.insert(new_sensor_data);

		dao<db::requirement> dao_requirements{ conn };

		//std::string id_string = std::to_string(id);
		//std::string filter_string = "sensor_id";
		std::map<std::string, std::string> filter;
		filter.insert(std::pair("sensor_id", std::to_string(id)));

		std::vector<db::requirement> reqs =
			dao_requirements.get(filter);

		unsigned int not_matching = 0;

		for (auto s : reqs) {
			if (s.min_value > value || s.max_value < value) {
				not_matching++;
			}
		}

		dao<db::actor> dao_actor{ conn };
		std::map<std::string, std::string> actor_filter;
		actor_filter.insert(std::pair("sensor_id", std::to_string(id)));

		unsigned int less = 0;
		unsigned int more = 0;

		for (auto s : reqs) {
			if (s.min_value > value)
				less++;
			if (s.max_value < value)
				more++;
		}
		std::vector<db::actor> act = dao_actor.get(actor_filter);

		if (request.body().find("temperature") != std::string::npos) {
			std::string weather =
				"http://api.weatherapi.com/v1/current.json?key=c19d353e82c148919e8183238202611&q=" +
				location;

			std::cout << weather << location << std::endl;

			auto resp = client->get(weather).send();

			resp.then(
				[&](Pistache::Http::Response response) {
					rapidjson::Document d;
					std::string body = response.body();
					rapidjson::StringStream s(body.c_str());
					d.ParseStream(s);
					double temp_current =
						d["current"]["temp_c"]
							.GetDouble();
					std::cout << "Temp current"
						  << temp_current << std::endl;
					weather_act(temp_current, less, more,
						    reqs,act,value);	
				},
				[&](std::exception_ptr exc) { ; });

		} else {
			if ((less > (reqs.size() / 2)) && act.size() > 0) {
				actors::get_instance()->set_value_id(act[0].id,
								     1);
			} else if (more > (reqs.size() / 2)) {
				actors::get_instance()->set_value_id(act[0].id,
								     -1);
			}
		}
		std::cout << "Got record data with id: " << id
			  << " and value: " << value << std::endl;
		response.send(Pistache::Http::Code::Ok, "recieved");
	}

    private:
	std::shared_ptr<Pistache::Http::Client> client;
	mysqlpp::Connection conn;
	std::string location;

	void weather_act(double temp_current, unsigned int less,unsigned  int more, std::vector<db::requirement>&reqs, std::vector<db::actor>& act, int value)
	{
		if ((less > (reqs.size() / 2)) && act.size() > 0 &&
		    temp_current <  value + 5  ) {
			actors::get_instance()->set_value_id(act[0].id, 1);
		} else if (more > (reqs.size() / 2) && temp_current > value - 5 ) {
			actors::get_instance()->set_value_id(act[0].id, -1);
		}
	}
};

#endif
