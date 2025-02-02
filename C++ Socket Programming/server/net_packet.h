#pragma once

#include "net_common.h"

namespace net {
struct Test1 {
    char length[4];
    char code[7];
    char date[8];
};

class Test {
public:
    int length;
    std::string code;
    
    std::vector<char> serialize() const {
        std::vector<char> data(sizeof(int) + 1);
        
        std::memset(data.data(), 0x00, sizeof(data));
        std::memcpy(data.data(), std::to_string(length).c_str(), sizeof(int));
        std::memcpy(data.data() + sizeof(int), code.c_str(), code.length());
        
        return data;
    }
};

class Packet {
public:
    std::string message;
    
    std::vector<char> serialize() const {
        int size = static_cast<int>(message.size());
        std::vector<char> data(sizeof(int) + size + 1);
        
        std::memcpy(data.data(), &size, sizeof(int));
        std::memcpy(data.data() + sizeof(size_t), message.c_str(), size);
        data.data()[sizeof(int) + size] = 0x00;
        
        std::cout << data.data();
        
        return data;
    }
    
    void deserialize(const std::vector<char>& data) {
        int size;
        std::memcpy(&size, data.data(), sizeof(int));
        
        message = std::string(data.data() + sizeof(int), size);
    }
};
}
