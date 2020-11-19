#ifndef __sensor_rest_api__
#define __sensor_rest_api__

#include <algorithm>
#include <string>

#include <iostream>
#include <pistache/http.h>
#include <pistache/net.h>
#include <pistache/router.h>
#include <pistache/endpoint.h>

#include "rest_api.h"
#include "plants.h"
/*
class sensor_rest
{
public:
	explicit sensor_rest(Pistache::Address addr) : endpoint{std::make_shared<Pistache::Http::Endpoint>(addr)} 
	{
		setup_routes();
		endpoint->setHandler(router.handler());
		endpoint->serve();
	}
private:

	void setup_routes()
	{
		Pistache::Rest::Routes::Post(router, "/record/:name/:value?", Pistache::Rest::Routes::bind(&sensor_rest::record_data, this));
	}
	
	void record_data(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response)
	{
		std::cout << "got record data" << std::endl;
		response.send(Pistache::Http::Code::Ok, "Recieved");
		
	}

	std::shared_ptr<Pistache::Http::Endpoint> endpoint;
	Pistache::Rest::Router router;

};
*/

class sensor_rest : public rest_api {
    public:
	explicit sensor_rest(Pistache::Address addr) : rest_api{ addr }
	{
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

		//TOOD: database

		std::cout << "Got record data with id: " << id << " and value: " << value <<std::endl;
		response.send(Pistache::Http::Code::Ok, "recieved");

		for(auto s: plants::get_instance()->get_plants())
		{
			if ( s.get_sensor() == id)
			{
				// if it is a sensor that is applicable for that plant
				//
				// 
			}
		}

	}
};

#endif
