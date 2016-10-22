#ifndef __BASE_H_INCLUDED__
#define __BASE_H_INCLUDED__

#include <iostream>
#include <thread>
#include <map>

#if defined(_WIN32) || defined(_WIN64)

#include <winsock2.h>
#include <WS2tcpip.h>
#include <stdio.h>
#include <string>

#define VIENTO_WIN
#define SOCKET SOCKET
#define WSA_CLEANUP() \
 ( \
  (WSACleanup()), \
  (void)0 \
 )
#define CLOSE_SOCKET(SOCK) \
 ( \
  (closesocket((SOCK))), \
  (void)0 \
 )

#pragma comment(lib, "Ws2_32.lib")

#elif defined(__unix) || defined(__unix__) || defined(__linux__)

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <cstring>

#define VIENTO_UNIX
#define SOCKET int
#define WSA_CLEANUP()
#define CLOSE_SOCKET(SOCK) \
 ( \
  (close((SOCK))), \
 )

#endif

#define VIENTO_DEFAULT_PORT "27105"

namespace Viento {
	const int CLIENT = 0;
	const int SERVER = 1;
	const int INIT_FAILURE = 0;
	const int INIT_SUCCESS = 1;

	class Base {
	public:
		Base(void);

		int initialized(void);
		int socket_init(void);

	protected:
		int status;      // Used to set errors
		int init;        // Used to indicate instantiation success/failure
		int viento_type; // Used to indicate client or server setup

		SOCKET v_socket;
		const int SOCK_ERROR = SOCKET_ERROR;
	};
}


#endif // __BASE_H_INCLUDED__