#ifndef __BASE_H_INCLUDED__
#define __BASE_H_INCLUDED__

#include <iostream>
#include <thread>
#include <map>

#if defined(_WIN32) || defined(_WIN64)

#include <winsock2.h>
#include <WS2tcpip.h>
#include <stdio.h>

#define WINDOWS 1
#define UNIX 0

#pragma comment(lib, "Ws2_32.lib")

#elif defined(__unix) || defined(__unix__) || defined(__linux__)

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#define UNIX 1
#define WINDOWS 0

#endif

#define INIT_FAILURE 0
#define INIT_SUCCESS 1

#define DEFAULT_PORT "27015"

namespace Viento {

	class Base
	{
	public:
		Base();

		int initialized(void);
		int socket_init(void);
		//int start(void);

		static const int client = 0;
		static const int server = 1;

	protected:
		int m_status; // Used to set errors
		int m_init; // Used to indicate instantiation success/failure
		int m_viento_type; // Used to indicate client or server setup

						   // Socket information, won't need too much
						   // fiddling after socket initialization
#if defined(_WIN32) || defined(_WIN64)
		SOCKET m_socket;
		const int m_SOCK_ERROR = SOCKET_ERROR;
#else
		int m_socket;
		const int m_SOCK_ERROR = -1;
#endif
	};
}


#endif // __BASE_H_INCLUDED__