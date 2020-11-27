#include <iostream>
#include <thread>
#include <vector>
#include <getopt.h>

#include "api/sensor_api.h"
#include "api/actor_api.h"
#include "api/client_api.h"

#include <pistache/net.h>

#include <mysql++.h>

void actor_thread(std::string db, std::string host, std::string username,
		  std::string password, int db_port, int api_port)
{
	Pistache::Port port(api_port);

	Pistache::Address addr(Pistache::Ipv4::any(), port);

	mysqlpp::Connection conn;
	conn.connect(db.c_str(), host.c_str(), username.c_str(),
		     password.c_str(), db_port);

	actor_api actor_ap(addr, conn);
}

void sensor_thread(std::string db, std::string host, std::string username,
		   std::string password, int db_port, int api_port,
		   std::string location)
{
	mysqlpp::Connection conn;

	if (!conn.connect(db.c_str(), host.c_str(), username.c_str(),
			  password.c_str(), db_port)) {
		std::cout << "Could not connect to database" << std::endl;
	} else {
		std::cout << "Connected to database" << std::endl;
	}

	Pistache::Port port(api_port);

	Pistache::Address addr(Pistache::Ipv4::any(), port);

	sensor_api sensor(addr, conn, location);
}

void local_thread(std::string db, std::string host, std::string username,
		  std::string password, int db_port, int api_port)
{
	mysqlpp::Connection conn;
	conn.connect(db.c_str(), host.c_str(), username.c_str(),
		     password.c_str(), db_port);

	Pistache::Port port(api_port);

	Pistache::Address addr(Pistache::Ipv4::any(), port);

	local_client_api local_client(addr, conn);
}

static struct option long_options[] = {
	{ "local_port", required_argument, NULL, 'l' },
	{ "remote_port", required_argument, NULL, 'o' },
	{ "sensor_port", required_argument, NULL, 's' },
	{ "actor_port", required_argument, NULL, 'a' },
	{ "user", required_argument, NULL, 'u' },
	{ "port", required_argument, NULL, 'p' },
	{ "host", required_argument, NULL, 'h' },
	{ "db", required_argument, NULL, 'd' },
	{ "password", required_argument, NULL, 'P' },
	{ "location", required_argument, NULL, 'L' }
};

int main(int argc, char *argv[])
{
	int long_index = 0;
	int opt;

	int local_port = 3333;
	int remote_port = 11111;
	int sensor_port = 6666;
	int actor_port = 7777;

	std::string username;
	int port;
	std::string host;
	std::string db;
	std::string password;
	std::string location;

	while ((opt = getopt_long(argc, argv, "losauphdPL", long_options,
				  &long_index)) != -1) {
		switch (opt) {
		case 'l': {
			local_port = std::stoi(std::string{ optarg });
			break;
		}
		case 'o': {
			remote_port = std::stoi(std::string{ optarg });
			break;
		}
		case 's': {
			sensor_port = std::stoi(std::string{ optarg });
			break;
		}
		case 'a': {
			actor_port = std::stoi(std::string{ optarg });
			break;
		}
		case 'u': {
			username = optarg;
			break;
		}
		case 'p': {
			port = std::stoi(optarg);
			break;
		}
		case 'h': {
			host = optarg;
			break;
		}
		case 'd': {
			db = optarg;
			break;
		}
		case 'P': {
			password = optarg;
			break;
		}
		case 'L': {
			location = optarg;
			break;
		}
		}
	}

	std::thread sensor_api_thread(sensor_thread, db, host, username,
				      password, port, sensor_port, location);
	std::thread actor_api_thread(actor_thread, db, host, username, password,
				     port, actor_port);
	std::thread local_api_thread(local_thread, db, host, username, password,
				     port, local_port);

	Pistache::Port port2(remote_port);

	Pistache::Address addr2(Pistache::Ipv4::any(), port2);

	mysqlpp::Connection conn;
	conn.connect(db.c_str(), host.c_str(), username.c_str(),
		     password.c_str(), port);

	client_api client_ap(addr2, conn);

	return 0;
}
