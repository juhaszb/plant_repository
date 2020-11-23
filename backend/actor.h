#ifndef __actor_h__
#define __actor_h__

#include <pistache/net.h>
#include <pistache/client.h>
#include <string>
class actor
{
public:
	actor(int id, Pistache::Address addr, int port) : id{id}, addr{addr}, port{port} {}
	
	int get_id(void) const
	{
		return id;
	}

	void set_value(std::string value)
	{
		this->value = value;
		Pistache::Http::Client client;	
		std::string page = addr.host()+ ":" + std::to_string(port) + "/send";
		client.post(page).body(value);
	}

	std::string get_value(void) const 
	{
		return value;
	}

private:
	int id; 
	std::string value;
	Pistache::Address addr;
	int port;
};


#endif