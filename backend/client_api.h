#ifndef __client_api_h__
#define __client_api_h__

#include "rest_api.h"
#include "actors.h"

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
			this->get_router(), "/set_sensor/:id/",
			Pistache::Rest::Routes::bind(
				&local_client_api::set_actor, this));
	}

    private:
	void set_actor(const Pistache::Rest::Request &request,
		       Pistache::Http::ResponseWriter response)
	{
		auto id = request.param(":id").as<int>();
		std::string value = request.body();
		actors::get_instance()->set_value_id(id, value);
	}
};

#endif
