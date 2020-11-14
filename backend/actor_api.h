#ifndef __actor_api_h__
#define __actor_api_h__

#include "rest_api.h"
#include "actors.h"

#include <pistache/http.h>
#include <pistache/mime.h>
#include <pistache/net.h>
#include <pistache/router.h>
#include <rapidjson/document.h>

#include <pistache/thirdparty/serializer/rapidjson.h>
#include <rapidjson/rapidjson.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

class actor_api : public rest_api {
    public:
	explicit actor_api(Pistache::Address addr) : rest_api{ addr }
	{
		this->serve();
	}

    protected:
	void setup_routes() override
	{
		Pistache::Rest::Routes::Put(
			this->get_router(), "/register/:id",
			Pistache::Rest::Routes::bind(&actor_api::register_actor,
						     this));

		Pistache::Rest::Routes::Post(
			this->get_router(), "/get/:id/:value",
			Pistache::Rest::Routes::bind(&actor_api::recieve_value,
						     this));
	}

    private:
	void register_actor(const Pistache::Rest::Request &request,
			    Pistache::Http::ResponseWriter response)
	{
		auto id = request.param(":id").as<int>();
		actors::get_instance()->add_actor(id, request.address());
		response.send(Pistache::Http::Code::Ok, "registered");
	}

	void recieve_value(const Pistache::Rest::Request &request,
			   Pistache::Http::ResponseWriter response)
	{
		auto id = request.param(":id").as<int>();
		auto value = request.param(":value").as<int>();
	}
};

#endif
