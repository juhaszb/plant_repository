#include <iostream>

#include <pistache/net.h>

#include "sensor_rest.h"
#include <thread>


void sensor_api1()
{

	Pistache::Port port(9999);
	
	Pistache::Address addr(Pistache::Ipv4::any(), port);

	sensor_rest sr(addr);

}


int main()
{
	std::thread sensor_api(sensor_api1);

	Pistache::Port port2(10000);

	Pistache::Address addr2(Pistache::Ipv4::any(), port2);

	sensor_rest sr2(addr2);


	return 0;
}
