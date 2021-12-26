#include <iostream>
#include "client_interface.h"

enum class CustomMsgTypes : uint16_t {
	ServerAccept,
	ServerDeny,
	ServerPing,
	MessageAll,
	ServerMessage,
};

class CustomClient {
public:
	void PingServer();
	void MessageAll();
};

int main() {
	CustomClient client;

	exit(true);
}