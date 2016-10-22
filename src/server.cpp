#ifdef VIENTO_UNIX
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netdb.h>
#endif

#include "server.h"

using namespace Viento;

/* Public Member Functions */

Server::Server()
	: Base()
	, sock_id(0)
{

}

/* Private Member Functions */

int Server::socket_listen(void)
{
	if (listen(this->v_socket, SOMAXCONN) == -1) {
		WSA_CLEANUP();
		CLOSE_SOCKET(this->v_socket);
		return 1;
	}

	return 0;
}

int Server::socket_accept(void)
{
	std::thread([&]() {
		while (true) {
			auto client_socket = accept(this->v_socket, NULL, NULL);

			if (client_socket == SOCK_ERROR) {
				WSA_CLEANUP();
				CLOSE_SOCKET(this->v_socket);
				return 1;
			}

			this->sockets.insert(std::pair<int, SOCKET>(++this->sock_id, client_socket));
		}
	});

	return 0;
}