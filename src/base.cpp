#include "base.h"

using namespace Viento;

// Constructor
Base::Base()
{
#if defined(_WIN32) || defined(_WIN64)

	WSADATA wsaData;

	status = WSAStartup(MAKEWORD(2, 2), &wsaData);

	if (status != 0) {
		std::cout << "WSAStartup failed: " << status << std::endl;
		init = INIT_FAILURE;
	}
	else
		init = INIT_SUCCESS;
		
#elif defined(__unix) || defined(__unix__) || defined(__linux__)

	m_init = INIT_SUCCESS;
	
#endif
}

/* Public Member Functions */

int Base::initialized(void)
{
	return this->init;
}

int Base::socket_init(void)
{
	struct addrinfo hints;
	struct addrinfo *servinfo, *res;

	char yes = 1;

    std::memset(&hints, 0, sizeof hints);

	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	this->status = getaddrinfo(NULL, VIENTO_DEFAULT_PORT, &hints, &servinfo);

	if (status != 0) {
		std::cerr << "getaddrinfo failed: %i" << status << std::endl;
#ifdef VIENTO_WIN
		WSACleanup();
#endif
		return 1;
	}

	for (res = servinfo; res != NULL; res = res->ai_next) {
		if ((this->v_socket = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) == -1) {
			std::cerr << "NOT FATAL: server (socket)" << std::endl;
			continue;
		}

		if (setsockopt(this->v_socket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
			std::cerr << "server (setsockopt)" << std::endl;
			freeaddrinfo(servinfo);
#ifdef VIENTO_WIN
			WSACleanup();
			closesocket(this->v_socket);
#else
			close(m_socket);
#endif
			return 1;
		}

		if (bind(this->v_socket, res->ai_addr, (int) res->ai_addrlen) == SOCK_ERROR) {
			std::cerr << "NOT FATAL: server (bind)" << std::endl;
#ifdef VIENTO_WIN
			closesocket(this->v_socket);
#else
			close(m_socket);
#endif
			continue;
		}

		break;
	}

	freeaddrinfo(servinfo);

	if (res == NULL) {
		std::cerr << "Could not create socket" << std::endl;
#ifdef VIENTO_WIN
		WSACleanup();
		closesocket(this->v_socket);
#else
		close(m_socket);
#endif
		return 1;
	}

	return 0;
}

/* Private Member Functions */