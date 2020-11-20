#include <iostream>
#include <thread>
#include <vector>

#include "sensor_rest.h"
#include "actor_api.h"
#include "client_api.h"
#include "plant.h"
#include "plants.h"

#include <pistache/net.h>

void sensor_api1()
{
	Pistache::Port port(9999);

	Pistache::Address addr(Pistache::Ipv4::any(), port);

	actor_api sr(addr);
}

int main()
{
	//TODO READ all plants from database.
	//When a new reading from a sensor comes in (responsibility of the sensor_api) query all plants. Whose id
	//matches (sensor_id) check if the values are in order (within acceptable ranges, if not then use the actors linked to the plant



	while(false) //TODO HERE GOES DATABASE READ for plants
	{
		
		//plants::get_instance()->add_plant(...)
	}

	



	std::thread sensor_api(sensor_api1);

	Pistache::Port port2(10000);

	Pistache::Address addr2(Pistache::Ipv4::any(), port2);

	client_api sr2(addr2);

	return 0;
}