#ifndef __actor_h__
#define __actor_h__

#include <pistache/net.h>
#include <pistache/client.h>
#include <string>
class actor {
    public:
	actor(int id, Pistache::Address addr, int port)
		: id{ id }, addr{ addr }, port{ port }
	{
		client = new Pistache::Http::Client();
		client->init();
	}

	int get_id(void) const
	{
		return id;
	}

	void set_value(int value)
	{
		this->value = value;

		std::string page = "";
		if (value == -1)
			page = addr.host() + ":" + std::to_string(port) +
			       "/send" + "/-1/";
		else
			page = addr.host() + ":" + std::to_string(port) +
			       "/send" + "/1/";

		std::cout << "Host: " << addr.host() << " Port: " << port
			  << std::endl;

		client->post(page).send();
	}

	int get_value(void) const
	{
		return value;
	}

	~actor()
	{
		delete client;
	}
	actor(actor &&) = delete;

    private:
	int id;
	int value;
	Pistache::Address addr;
	Pistache::Http::Client *client;
	int port;
};

#endif
