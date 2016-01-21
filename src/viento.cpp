#include "viento.h"

// Constructor
Viento::Viento(const int vt)
	: m_sock_id(0)
	, m_viento_type(vt)
{
#if defined(_WIN32) || defined(_WIN64)
	WSADATA wsaData;

	m_status = WSAStartup(MAKEWORD(2, 2), &wsaData);

	if (m_status != 0) {
		std::cout << "WSAStartup failed: " << m_status << std::endl;
		m_init = INIT_FAILURE;
	}
	else
		m_init = INIT_SUCCESS;
#elif __unix || __unix__ || __linux__
	m_init = INIT_SUCCESS;
#else
	std::cerr << "Your operating system is currently not supported" << std::endl;
	m_init = INIT_FAILURE;
#endif
}

/* Public Member Functions */

int Viento::initialized(void) 
{
	return m_init;
}

int Viento::socket_init(void)
{
	struct addrinfo hints;
	struct addrinfo *servinfo, *res;

	char yes = 1;

	memset(&hints, 0, sizeof hints);

	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	m_status = getaddrinfo(NULL, DEFAULT_PORT, &hints, &servinfo);

	if (m_status != 0) {
		std::cerr << "getaddrinfo failed: %i" << m_status << std::endl;
		if (WINDOWS) WSACleanup();
		return 1;
	}

	for (res = servinfo; res != NULL; res = res->ai_next) {
		if ((m_socket = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) == -1) {
			std::cerr << "NOT FATAL: server (socket)" << std::endl;
			continue;
		}

		if (setsockopt(m_socket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
			std::cerr << "server (setsockopt)" << std::endl;
			freeaddrinfo(servinfo);
#if defined(_WIN32) || defined(_WIN64)
			WSACleanup();
			closesocket(m_socket);
#else
			close(m_socket);
#endif
			return 1;
		}

		if (bind(m_socket, res->ai_addr, (int) res->ai_addrlen) == m_SOCK_ERROR) {
			std::cerr << "NOT FATAL: server (bind)" << std::endl;
#if defined(_WIN32) || defined(_WIN64)
			closesocket(m_socket);
#else
			close(m_socket)
#endif
			continue;
		}

		break;
	}

	freeaddrinfo(servinfo);

	if (res == NULL) {
		std::cerr << "Could not create socket" << std::endl;
#if defined(_WIN32) || defined(_WIN64)
		WSACleanup();
		closesocket(m_socket);
#else
		close(m_socket);
#endif
		return 1;
	}

	return 0;
}

/* Private Member Functions */

int Viento::socket_listen(void)
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

int Viento::socket_accept(void)
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