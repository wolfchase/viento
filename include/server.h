#ifndef __SERVER_H_INCLUDED__
#define __SERVER_H_INCLUDED__

#include <iostream>
#include <thread>
#include <map>

#include "base.h"

namespace Viento {

	class Server : public Base {
	public:
		Server();
		int start(void);

	private:
		std::map<int, SOCKET> sockets;

		int sock_id;

		int socket_listen(void);
		int socket_accept(void);
	};

}


#endif // __SERVER_H_INCLUDED__