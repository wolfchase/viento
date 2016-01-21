#include "server.h"

using namespace Viento;

/* Public Member Functions */

Server::Server()
	: Base()
	, m_sock_id(0)
{

}

/* Private Member Functions */

int Server::socket_listen(void)
{
	if (listen(m_socket, SOMAXCONN) == -1) {
#if defined(_WIN32) || defined(_WIN64)
		std::cerr << "Listen failed with error: " << WSAGetLastError() << std::endl;
		closesocket(m_socket);
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
			auto client_socket = accept(m_socket, NULL, NULL);

			if (client_socket == INVALID_SOCKET) {
				std::cerr << "Accept failed: " << WSAGetLastError() << std::endl;
				closesocket(m_socket);
				WSACleanup();
				return 1;
			}

			m_sockets.insert(std::pair<int, SOCKET>(++m_sock_id, client_socket));
		}
	});

	return 0;
}