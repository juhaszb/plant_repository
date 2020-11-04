#ifndef CONNECTION_H_
#define CONNECTION_H_

#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <memory>
#include <unistd.h>
#include <filesystem>
#include <iostream>

#include "exception.h"

#ifndef byte
typedef unsigned char byte;
#endif

class Connection {
    private:
	char buffer[256];
	struct sockaddr_in connection; // port and other network related stuff
	int sockfd; // socket file descriptor
	void setsocket(int sock)
	{
		sockfd = sock;
	}

    public:
	Connection() = default;

	Connection(unsigned int portnum, in_addr_t address)
	{
		bzero((char *)&connection, sizeof(connection));
		connection.sin_port = htons(portnum);
		connection.sin_addr.s_addr = address;
		sockfd = socket(AF_INET, SOCK_STREAM, 0);
		if (sockfd < 0)
			throw SockFdFailed();

		if (bind(sockfd, (struct sockaddr *)&connection,
			 sizeof(connection)) < 0)
			throw BindError();

		listen(sockfd, 5);
	}

	std::shared_ptr<Connection> Accept()
	{
		int addrlen = sizeof(connection);
		int socket = accept(sockfd, (struct sockaddr *)&connection,
				    (socklen_t *)&addrlen);
		if (socket < 0) {
			throw AcceptError();
		}
		std::shared_ptr<Connection> c = std::make_shared<Connection>();
		c->setsocket(socket);
		return c;
	}

	int getsocket()
	{
		return sockfd;
	}

	~Connection()
	{
		close(sockfd);
	}
};

#endif
