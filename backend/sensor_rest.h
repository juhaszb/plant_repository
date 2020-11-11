#ifndef __sensor_rest_api__
#define __sensor_rest_api__

#include <algorithm>

#include <iostream>
#include <pistache/http.h>
#include <pistache/net.h>
#include <pistache/router.h>
#include <pistache/endpoint.h>

#include "rest_api.h"

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
			this->get_router(), "/record/:name/:value?",
			Pistache::Rest::Routes::bind(&sensor_rest::record_data,
						     this));
	}

	void record_data(const Pistache::Rest::Request &request,
			 Pistache::Http::ResponseWriter response) override
	{
		std::cout << "Got record data" << std::endl;
		response.send(Pistache::Http::Code::Ok, "recieved");
	}
	private:
	Pistache::Rest::Router router;
};

#endif
