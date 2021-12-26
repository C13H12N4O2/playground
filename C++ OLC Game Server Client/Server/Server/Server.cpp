#include <iostream>
#include "server_interface.h"

enum class CustomMsgTypes : uint16_t {
	ServerAccept,
	ServerDeny,
	ServerPing,
	MessageAll,
	ServerMessage,
};

class CustomServer : public server::server_interface<CustomMsgTypes> {
public:
	CustomServer(uint16_t nPort) : server::server_interface<CustomMsgTypes>(nPort) {

	}

protected:
	bool OnClientConnect();
	void OnClientDisconnect();

	virtual void OnMessage(std::shared_ptr<net::connection<CustomMsgTypes>> client, net::message<CustomMsgTypes>& msg) {
		char buff[1024];
		msg >> buff;
		std::cout << buff << "\n";
	}
};

int main() {
	CustomServer server(60000);
	server.Start();


	while (true) {
		server.Update();
	}

	exit(true);
}