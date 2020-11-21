#ifndef __sensor_rest_api__
#define __sensor_rest_api__


#define EXPAND_SSQLS_STATICS

#include <algorithm>
#include <string>

#include <iostream>
#include <pistache/http.h>
#include <pistache/net.h>
#include <pistache/router.h>
#include <pistache/endpoint.h>
#include <vector>
#include <mysql++.h>
#include <time.h>

#include "rest_api.h"
#include "../db/dao.hpp"
#include "../db/dbtables.h"
//#include "plants.h"
//#include "../db/dao.hpp"
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
	explicit sensor_rest(Pistache::Address addr, mysqlpp::Connection & conn ) : rest_api{ addr }, conn{conn} 
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
		
		dao<sensor> dao_sensor{conn};
		dao<sensor_data> dao_sensor_data{conn};

		std::vector<sensor> ids = dao_sensor.get_all_ids();
		
		if(std::find(ids.begin(), ids.end(), id) == ids.end())
		{
			std::cout<<"Couldnt find id, so insering it to data table"<< std::endl;
			sensor new_data;
			new_data.id = id;
			new_data.name = request.body();
			dao_sensor.insert(new_data);
		}

		sensor_data new_sensor_data;
		new_sensor_data.id = 0;
		new_sensor_data.sensor_id = id;
		new_sensor_data.timestamp =  (unsigned)time(NULL); // TODO get unix timestamp
		new_sensor_data.data = value;

		dao_sensor_data.insert(new_sensor_data);


		//TODO: query from requirements which plants use this sensor

//		dao<sensor_data> sensor_dao{conn};  
//		dao<sensor> 	
//		sensor_dao.insert({});
		//TOOD: database

		std::cout << "Got record data with id: " << id << " and value: " << value <<std::endl;
		response.send(Pistache::Http::Code::Ok, "recieved");

	/*	for(auto s: plants::get_instance()->get_plants())
		{
			if ( s.get_sensor() == id)
			{
				// if it is a sensor that is applicable for that plant
				//
				// 
			}
		}
	*/ 

	}
private:
	mysqlpp::Connection conn;

};

#endif
