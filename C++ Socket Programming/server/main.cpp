#include "net.h"

enum class MessageTypes : uint32_t {
    
};

int main() {
    try {
        net::Server<MessageTypes> server(8080);
        server.Start();
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << "\n";
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}
