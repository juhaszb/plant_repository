#include <iostream>
#include <thread>

#include "sensor_rest.h"
#include "actor_api.h"
#include "client_api.h"


#include <pistache/net.h>

void sensor_api1()
{
	Pistache::Port port(9999);

	Pistache::Address addr(Pistache::Ipv4::any(), port);

	actor_api sr(addr);
}

int main()
{
	std::thread sensor_api(sensor_api1);

	Pistache::Port port2(10000);

	Pistache::Address addr2(Pistache::Ipv4::any(), port2);

	client_api sr2(addr2);

	return 0;
}
