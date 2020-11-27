#ifndef __actor_api_h__
#define __actor_api_h__

#include "rest_api.h"
#include "../actors.h"
#include "../db/dao.hpp"

#include <algorithm>
#include <pistache/http.h>
#include <pistache/mime.h>
#include <pistache/net.h>
#include <pistache/router.h>
#include <rapidjson/document.h>
#include <vector>

#include <pistache/thirdparty/serializer/rapidjson.h>
#include <rapidjson/rapidjson.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>
#include <mysql++.h>

class actor_api : public rest_api {
    public:
	explicit actor_api(Pistache::Address addr, mysqlpp::Connection &conn)
		: rest_api{ addr }, conn{ conn }
	{
		this->serve();
	}

    protected:
	void setup_routes() override
	{
		Pistache::Rest::Routes::Put(
			this->get_router(), "/register/:id/:sensor_id/",
			Pistache::Rest::Routes::bind(&actor_api::register_actor,
						     this));

		/*	Pistache::Rest::Routes::Post(
			this->get_router(), "/get/:id/:value",
			Pistache::Rest::Routes::bind(&actor_api::recieve_value,
						     this));*/
	}

    private:
	void register_actor(const Pistache::Rest::Request &request,
			    Pistache::Http::ResponseWriter response)
	{
		auto id = request.param(":id").as<int>();
		auto sensor_id = request.param(":sensor_id").as<int>();

		std::vector<int> a_list =
			actors::get_instance()->get_actor_id_list();
		if (std::find(a_list.begin(), a_list.end(), id) == a_list.end())
			actors::get_instance()->add_actor(
				id, request.address(),
				std::stoi(request.body()));

		dao<db::actor> dao_actor{ conn };

		//if not in database add to database
		std::vector<db::actor> actor_list = dao_actor.get_all_ids();
		std::vector<int> ids;
		for (auto s : actor_list) {
			ids.push_back(s.id);
		}

		if (std::find(ids.begin(), ids.end(), id) == ids.end()) {
			db::actor act;
			act.id = id;
			act.name = request.body();
			act.sensor_id = sensor_id;
			dao_actor.insert(act);

			std::cout << "Add actor to database" << std::endl;
		}

		//if( std::find(

		response.send(Pistache::Http::Code::Ok, "registered");
	}
	/*
	void recieve_value(const Pistache::Rest::Request &request,
			   Pistache::Http::ResponseWriter response)
	{
		auto id = request.param(":id").as<int>();
		auto value = request.param(":value").as<int>();
	}
	*/
	mysqlpp::Connection conn;
};

#endif
