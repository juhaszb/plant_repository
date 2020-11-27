#ifndef __client_api_h__
#define __client_api_h__

#define EXPAND_SSQLS_STATICS

#include "rest_api.h"
#include "../actors.h"

#include "../db/dao.hpp"
#include "../db/dbtables.h"

#include <map>
#include <pistache/net.h>

#include <rapidjson/rapidjson.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>
#include <rapidjson/document.h>
#include <string>
#include <mysql++.h>

class client_api : public rest_api {
    public:
	explicit client_api(Pistache::Address addr, mysqlpp::Connection &conn)
		: rest_api{ addr }, conn{ conn }
	{
		this->serve();
	}
	explicit client_api(Pistache::Address addr, mysqlpp::Connection &conn,
			    int dumm)
		: rest_api{ addr }, conn{ conn }
	{
	}

    protected:
	mysqlpp::Connection conn;
	virtual void setup_routes() override
	{
		Pistache::Rest::Routes::Get(
			this->get_router(), "/list_actors",
			Pistache::Rest::Routes::bind(&client_api::get_actors,
						     this));

		Pistache::Rest::Routes::Get(
			this->get_router(), "/list_sensors/",
			Pistache::Rest::Routes::bind(&client_api::list_sensors,
						     this));

		Pistache::Rest::Routes::Get(this->get_router(), "/list_plants/",
					    Pistache::Rest::Routes::bind(
						    &client_api::get_plant_list,
						    this));
	}

    private:
	//LOCALBA
	void get_actors(const Pistache::Rest::Request &request,
			Pistache::Http::ResponseWriter response)
	{
		auto mime = MIME(Application, Json);
		rapidjson::Document document;
		document.SetObject();
		rapidjson::Value v(rapidjson::kArrayType);
		rapidjson::Document::AllocatorType &allocator =
			document.GetAllocator();

		for (auto s : actors::get_instance()->get_actor_id_list())
			v.PushBack(s, allocator);
		document.AddMember("actors", v, allocator);

		rapidjson::StringBuffer buffer;
		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
		document.Accept(writer);

		response.send(Pistache::Http::Code::Ok, buffer.GetString(),
			      mime);
	}

	void list_sensors(const Pistache::Rest::Request &request,
			  Pistache::Http::ResponseWriter response)
	{
		auto mime = MIME(Application, Json);

		std::cout << "list sensors called" << std::endl;

		rapidjson::Document d;
		d.SetObject();

		rapidjson::Value sensor_list(rapidjson::kArrayType);

		dao<db::sensor_data> dao_sensor_data{ conn };
		dao<db::sensor> dao_sensor{ conn };

		std::vector<db::sensor_data> data_values =
			dao_sensor_data.get_all_ids();

		std::vector<db::sensor> sensor_ids = dao_sensor.get_all_ids();

		for (auto s : sensor_ids) {
			std::map<std::string, std::string> filter;
			filter.insert(
				std::pair("sensor_id", std::to_string(s.id)));
			std::vector<db::sensor_data> dt =
				dao_sensor_data.get(filter);
			if (dt.size() != 0) {
				std::sort(dt.begin(), dt.end(),
					  [](const db::sensor_data &a,
					     const db::sensor_data &b) -> bool {
						  return a.timestamp >
							 b.timestamp;
					  });
				rapidjson::Value data(rapidjson::kObjectType);
				data.AddMember("id", s.id, d.GetAllocator());

				db::sensor sens_name = dao_sensor.get(s.id);

				const std::string name = sens_name.name;

				rapidjson::Value name_value(
					rapidjson::kStringType);
				name_value.SetString(name.c_str(),
						     name.length(),
						     d.GetAllocator());

				data.AddMember("name", name_value,
					       d.GetAllocator());
				data.AddMember("data", dt[0].data,
					       d.GetAllocator());
				sensor_list.PushBack(data, d.GetAllocator());
			}
		}

		d.AddMember("sensors", sensor_list, d.GetAllocator());

		rapidjson::StringBuffer buffer;
		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
		d.Accept(writer);

		response.send(Pistache::Http::Code::Ok, buffer.GetString(),
			      mime);
	}
	void get_plant_list(const Pistache::Rest::Request &request,
			    Pistache::Http::ResponseWriter response)
	{
		auto mime = MIME(Application, Json);

		rapidjson::Document d;
		d.SetObject();
		rapidjson::Value plant_list(rapidjson::kArrayType);

		dao<db::plant> dao_plant{ conn };

		std::vector<db::plant> data_values = dao_plant.get_all_ids();

		for (auto s : data_values) {
			db::plant p = dao_plant.get(s.id);
			rapidjson::Value plant_single(rapidjson::kObjectType);
			plant_single.AddMember("id", s.id, d.GetAllocator());

			const std::string name = p.name;

			std::cout << "P.name is " << p.name << std::endl;
			rapidjson::Value string_value(rapidjson::kStringType);
			string_value.SetString(name.c_str(), name.length(),
					       d.GetAllocator());
			plant_single.AddMember("name", string_value,
					       d.GetAllocator());
			plant_single.AddMember("xcoord", p.gridx,
					       d.GetAllocator());
			plant_single.AddMember("ycoord", p.gridy,
					       d.GetAllocator());
			plant_list.PushBack(plant_single, d.GetAllocator());
		}

		d.AddMember("plants", plant_list, d.GetAllocator());

		rapidjson::StringBuffer buffer;
		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
		d.Accept(writer);

		std::cout << buffer.GetString() << std::endl;

		response.send(Pistache::Http::Code::Ok, buffer.GetString(),
			      mime);
	}
};

class local_client_api : public client_api {
    public:
	explicit local_client_api(Pistache::Address addr,
				  mysqlpp::Connection &conn)
		: client_api{ addr, conn, 1 }
	{
		this->serve();
	}

    protected:
	virtual void setup_routes() override
	{
		client_api::setup_routes();
		Pistache::Rest::Routes::Post(
			this->get_router(), "/set_actor/:id/",
			Pistache::Rest::Routes::bind(
				&local_client_api::set_actor, this));

		Pistache::Rest::Routes::Put(
			this->get_router(), "/add_plant/",
			Pistache::Rest::Routes::bind(
				&local_client_api::add_plant, this));

		Pistache::Rest::Routes::Put(
			this->get_router(), "/add_requirements/",
			Pistache::Rest::Routes::bind(
				&local_client_api::add_requirement, this));

		Pistache::Rest::Routes::Get(
			this->get_router(), "/list_requirements/",
			Pistache::Rest::Routes::bind(
				&local_client_api::get_requirements, this));
	}

    private:
	void set_actor(const Pistache::Rest::Request &request,
		       Pistache::Http::ResponseWriter response)
	{
		auto id = request.param(":id").as<int>();
		std::string value = request.body();
		//actors::get_instance()->set_value_id(id, value);

		response.send(Pistache::Http::Code::Ok, "set actor");
	}

	void add_plant(const Pistache::Rest::Request &request,
		       Pistache::Http::ResponseWriter response)
	{
		std::string body = request.body();

		std::cout << request.body() << std::endl;

		rapidjson::Document document;
		document.SetObject();
		rapidjson::StringStream s(body.c_str());
		document.ParseStream(s);

		dao<db::plant> dao_plant{ conn };

		std::vector<db::plant> plant_ids = dao_plant.get_all_ids();
		bool found = false;

		for (auto s : plant_ids) {
			db::plant p = dao_plant.get(s.id);
			if (p.gridx == document["xcoord"].GetInt() &&
			    p.gridy == document["ycoord"].GetInt())
				found = true;
		}

		if (!found) {
			db::plant new_plant;
			new_plant.id = 0;
			new_plant.name = document["name"].GetString();
			new_plant.gridx = document["xcoord"].GetInt();
			new_plant.gridy = document["ycoord"].GetInt();

			dao_plant.insert(new_plant);
		}

		response.send(Pistache::Http::Code::Ok, "sent");
	}

	void add_requirement(const Pistache::Rest::Request &request,
			     Pistache::Http::ResponseWriter response)
	{
		std::string body = request.body();
		rapidjson::Document document;

		rapidjson::StringStream s(body.c_str());
		document.ParseStream(s);

		dao<db::requirement> dao_requirement{ conn };

		db::requirement new_req;
		new_req.id = 0;
		new_req.plant_id = document["plant_id"].GetInt();
		new_req.sensor_id = document["sensor_id"].GetInt();
		new_req.min_value = document["min_value"].GetInt();
		new_req.max_value = document["max_value"].GetInt();

		dao_requirement.insert(new_req);

		response.send(Pistache::Http::Code::Ok, "OK");
	}

	void get_requirements(const Pistache::Rest::Request &request,
			      Pistache::Http::ResponseWriter response)
	{
		auto mime = MIME(Application, Json);

		dao<db::requirement> dao_requirements{ conn };
		rapidjson::Document d;
		d.SetObject();

		rapidjson::Value req_list(rapidjson::kArrayType);

		std::vector<db::requirement> reqs =
			dao_requirements.get_all_ids();

		for (auto s : reqs) {
			db::requirement req = dao_requirements.get(s.id);
			rapidjson::Value data(rapidjson::kObjectType);
			data.AddMember("id", req.id, d.GetAllocator());
			data.AddMember("plant_id", req.plant_id,
				       d.GetAllocator());
			data.AddMember("sensor_id", req.sensor_id,
				       d.GetAllocator());
			data.AddMember("min_value", req.min_value,
				       d.GetAllocator());
			data.AddMember("max_value", req.max_value,
				       d.GetAllocator());
			req_list.PushBack(data, d.GetAllocator());
		}

		d.AddMember("requirements", req_list, d.GetAllocator());
		rapidjson::StringBuffer buffer;
		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
		d.Accept(writer);
		response.send(Pistache::Http::Code::Ok, buffer.GetString(),
			      mime);
	}
};

#endif
