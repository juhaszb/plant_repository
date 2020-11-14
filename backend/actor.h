#ifndef __actor_h__
#define __actor_h__

#include <pistache/net.h>
class actor
{
public:
	actor(int id, Pistache::Address addr) : id{id}, addr{addr} {}
	
	int get_id(void) const
	{
		return id;
	}

	void set_value(int value)
	{
		this->value = value;
	}

	int get_value(void) const 
	{
		return value;
	}

private:
	int id; 
	int value;
	Pistache::Address addr;
};


#endif
