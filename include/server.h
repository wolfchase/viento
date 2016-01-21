#ifndef __SERVER_H_INCLUDED__
#define __SERVER_H_INCLUDED__

#include <iostream>
#include <thread>
#include <map>

#include "base.h"

#define DEFAULT_PORT "27015"

namespace Viento {

	class Server : public Base
	{
	public:
		Server();
		int start(void);

	private:
	
#if defined(_WIN32) || defined(_WIN64)

		std::map<int, SOCKET> m_sockets;

#else

		std::map<int, int> m_sockets;
		
#endif

		int m_sock_id;

		int socket_listen(void);
		int socket_accept(void);
	};

}


#endif // __SERVER_H_INCLUDED__