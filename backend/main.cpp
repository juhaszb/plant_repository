#include <iostream>
#include <exception>
#include <sys/socket.h>
#include <sys/time.h>
#include <vector>
#include <algorithm>

#include "connection.h"

#ifndef byte
typedef unsigned char byte;
#endif

int main(int argc, char *argv[])
{
	if (argc < 2) {
		std::cout << "Portnumber argument is needed" << std::endl;
		exit(1);
	}

	int portnum = std::stoi(std::string(argv[1]));

	try {
		Connection master(portnum, INADDR_ANY);

		std::vector<std::shared_ptr<Connection> > clients;

		int max_sd;
		fd_set readfs;

		//	std::shared_ptr<Connection> client =master.Accept();
		while (true) {
			FD_ZERO(&readfs);

			FD_SET(master.getsocket(), &readfs);
			max_sd = master.getsocket();

			for (auto &s : clients) {
				int sd = s->getsocket();

				if (sd > 0)
					FD_SET(sd, &readfs);

				if (sd > max_sd)
					max_sd = sd;
			}

			int activity =
				select(max_sd + 1, &readfs, NULL, NULL, NULL);

			if ((activity < 0)) {
				std::cout << "Select Error" << std::endl;
			}

			if (FD_ISSET(master.getsocket(), &readfs)) {
				std::shared_ptr<Connection> newconn =
					master.Accept();

				clients.push_back(newconn);

				std::cout << "New connection" << std::endl;
			}

			for (auto &s : clients) {
				int sd = s->getsocket();

				if (FD_ISSET(sd, &readfs)) {
					char buffer[2048];
					if ((read(sd, buffer, 2047) == 0)) {
						//std::cout<<"Sorry cant delete things"<<std::endl;
						auto it = std::find(
							clients.begin(),
							clients.end(), s);
						//std::cout<<"Told ya"<<std::endl;
						clients.erase(it);

						std::cout << "Socket number "
							  << s->getsocket()
							  << " disconnected"
							  << std::endl;

					} else {
						// Itt kell lekezelni az üteneteket... feldolgozni stb...
					}
				}
			}
		}

	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
		std::cout << "caught exception" << std::endl;
	}
	return 0;
}
