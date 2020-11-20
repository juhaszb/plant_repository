#ifndef __client_api_h__
#define __client_api_h__

#include "rest_api.h"
#include "actors.h"
#include "plants.h"
#include "plant.h"

#include <pistache/net.h>

#include <rapidjson/rapidjson.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>
#include <rapidjson/document.h>
#include <string>

class client_api : public rest_api {
    public:
	explicit client_api(Pistache::Address addr) : rest_api{ addr }
	{
		this->serve();
	}

    protected:
	virtual void setup_routes() override
	{
		Pistache::Rest::Routes::Get(
			this->get_router(), "/list_actors",
			Pistache::Rest::Routes::bind(&client_api::get_actors,
						     this));

		Pistache::Rest::Routes::Get(
			this->get_router(), "/sensor/:id/",
			Pistache::Rest::Routes::bind(
				&client_api::get_sensor_data, this));

		Pistache::Rest::Routes::Get(
			this->get_router(), "/list_sensors/",
			Pistache::Rest::Routes::bind(&client_api::list_sensors,
						     this));

		Pistache::Rest::Routes::Get(
			this->get_router(), "/get_plants/",
			Pistache::Rest::Routes::bind(
				&client_api::get_plant_list, this));
	}

    private:
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
		document.AddMember("List", v, allocator);

		rapidjson::StringBuffer buffer;
		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
		document.Accept(writer);

		response.send(Pistache::Http::Code::Ok, buffer.GetString(),
			      mime);
	}

	void get_sensor_data(const Pistache::Rest::Request &request,
			     Pistache::Http::ResponseWriter response)
	{
		//TODO: query sensor data from database and send back the appropriate one
		auto id = request.param(":id").as<int>();

		response.send(Pistache::Http::Code::Ok,
			      "put the value here as string");
	}

	void list_sensors(const Pistache::Rest::Request &request,
			  Pistache::Http::ResponseWriter response)
	{
		//TODO: query sensors list as a vector and then parse it into JSON
		response.send(Pistache::Http::Code::Ok,
			      "The JSON goes here as seen above");
	}
	void get_plant_list(const Pistache::Rest::Request &request,
			    Pistache::Http::ResponseWriter response)
	{
		auto mime = MIME(Application, Json);
		rapidjson::Document document;
		document.SetObject();

		rapidjson::Value names(rapidjson::kArrayType);
		rapidjson::Value xcoord(rapidjson::kArrayType);
		rapidjson::Value ycoord(rapidjson::kArrayType);

		rapidjson::Document::AllocatorType &allocator =
			document.GetAllocator();

		for (auto s : plants::get_instance()->get_plants()) {
			names.PushBack(s.get_name(), allocator);
			xcoord.PushBack(s.get_location().first, allocator);
			ycoord.PushBack(s.get_location().second, allocator);
		}
		document.AddMember("Names", names, allocator);
		document.AddMember("Xcoord", xcoord, allocator);
		document.AddMember("Ycoord", ycoord,
				   allocator); // Do I need multiple allocator?

		rapidjson::StringBuffer buffer;
		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
		document.Accept(writer);

		response.send(Pistache::Http::Code::Ok, buffer.GetString(),
			      mime);
	}
};

class local_client_api : public client_api {
    public:
	explicit local_client_api(Pistache::Address addr) : client_api{ addr }
	{
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
			this->get_router(), "/add_sensor/:name/",
			Pistache::Rest::Routes::bind(
				&local_client_api::add_sensor, this));

		Pistache::Rest::Routes::Put(
			this->get_router(), "/add_plant/",
			Pistache::Rest::Routes::bind(
				&local_client_api::add_plant, this));
	}

    private:
	void set_actor(const Pistache::Rest::Request &request,
		       Pistache::Http::ResponseWriter response)
	{
		auto id = request.param(":id").as<int>();
		std::string value = request.body();
		actors::get_instance()->set_value_id(id, value);

		response.send(Pistache::Http::Code::Ok, "set actor");
	}

	void add_sensor(const Pistache::Rest::Request &request,
			Pistache::Http::ResponseWriter response)
	{
		//auto id = request.param(":id").as<int>();
		auto name = request.param(":name").as<std::string>();
		//TODO: check if it exists if not then add

		response.send(Pistache::Http::Code::Ok, "added sensor");
	}

	void add_plant(const Pistache::Rest::Request &request,
		       Pistache::Http::ResponseWriter response)
	{
		//auto name = request.param(":name").as<std::string>();
		std::string body = request.body();
		rapidjson::Document document;

		//TODO check if not in database

		rapidjson::StringStream s(body.c_str());
		document.ParseStream(s);

		std::string name = document["name"].GetString();
		std::pair<int, int> location;
		location.first = document["gridx"].GetInt();
		location.second = document["gridy"].GetInt();
		unsigned int water_needs = document["water"].GetInt();
		std::pair<int, int> light_needs;
		light_needs.first = document["light_low"].GetInt();
		light_needs.second = document["light_high"].GetInt();
		std::pair<int, int> temp;
		temp.first = document["temp_low"].GetInt();
		temp.second = document["temp_high"].GetInt();
		std::pair<int, int> soil;
		soil.first = document["soil_low"].GetInt();
		soil.second = document["soil_high"].GetInt();

		//TODO generate id

		int sensor = document["sensor"].GetInt();

		plant p{ name, location, water_needs, light_needs,
			 temp, soil,	 0,	      sensor };
		plants::get_instance()->add_plant(p);

		//TODO add to databse
	}
};

#endif
