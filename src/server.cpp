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
#if defined(_WIN32) || defined(_WIN64)
		std::cerr << "Listen failed with error: " << WSAGetLastError() << std::endl;
		closesocket(this->v_socket);
		WSACleanup();
		return 1;
#else
		std::cerr << "Listen failed for socket" << std::endl;
		close(m_socket);
		return 1;
#endif
	}

	return 0;
}

int Server::socket_accept(void)
{
	std::thread([&]() {
		while (true) {
			auto client_socket = accept(this->v_socket, NULL, NULL);

			if (client_socket == SOCK_ERROR) {
#if defined(_WIN32) || defined(_WIN64)
				std::cerr << "Accept failed: " << WSAGetLastError() << std::endl;
				closesocket(this->v_socket);
				WSACleanup();
#else
				std::cerr << "Accept failed" << std::endl;
				close(m_socket);
#endif
				return 1;
			}

#if defined(_WIN32) || defined(_WIN64)
			sockets.insert(std::pair<int, SOCKET>(++sock_id, client_socket));
#else
			m_sockets.insert(std::pair<int, int>(++m_sock_id, client_socket));
#endif
		}
	});

	return 0;
}