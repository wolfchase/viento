// Standard libraries
#include <iostream>

// Local libraries
#include "server.h"

int main(void) {
	Viento::Server server = Viento::Server();

	if (server.initialized()) {
		std::cout << "Server successfully initialized" << std::endl;
	} 
	else {
		std::cout << "Server failed to initialize" << std::endl;
		return 1;
	}

	if (server.socket_init() != Viento::INIT_FAILURE) {
		std::cout << "Socket initialized" << std::endl;
	}
	else {
		std::cout << "Socket failed to initialize" << std::endl;
	}

	return 0;
}