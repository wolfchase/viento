// Standard libraries
#include <iostream>

// Local libraries
#include "viento.h"

int main(void) {
	Viento server = Viento(Viento::server);

	if (server.initialized()) {
		std::cout << "Server successfully initialized" << std::endl;
	} 
	else {
		std::cout << "Server failed to initialize" << std::endl;
		return 1;
	}

	if (server.socket_init() != 1) {
		std::cout << "Socket initialized" << std::endl;
	}
	else {
		std::cout << "Socket failed to initialize" << std::endl;
	}

	return 0;
}