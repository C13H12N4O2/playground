#pragma once

#include "net_common.h"

namespace net {
#if 0
template<typename T>
struct messageHeader {
    T id {};
    uint32_t size = 0;
};

template<typename T>
struct message {
    messageHeader<T> header {};
    std::vector<uint8_t> body;
    
    size_t size() const {
        return body.size();
    }
    
    friend std::ostream& operator << (std::ostream& os, const message<T>& msg) {
        os << "ID: " << static_cast<int>(msg.header.id) << " Size: " << msg.header.size;
        return os;
    }
    
    template<typename DataType>
    friend message<T>& operator << (message<T>& msg, const DataType& data) {
        static_assert(std::is_standard_layout<DataType>::value, "Data is too complex to be pushed into vector");
        size_t size = msg.body.size();
        msg.body.resize(msg.body.size() + sizeof(DataType));
        std::memcpy(msg.body.data() + size, &data, sizeof(DataType));
        msg.header.size = static_cast<unsigned int>(msg.size());
        return msg;
    }
    
    template<typename DataType>
    friend message<T>& operator >> (message<T>& msg, DataType& data) {
        static_assert(std::is_standard_layout<DataType>::value, "Data is too complex to be pulled from vertor");
        size_t size = msg.body.size() - sizeof(DataType);
        std::memcpy(&data, msg.body.data() + size, sizeof(DataType));
        msg.body.resize(size);
        msg.header.size = static_cast<unsigned int>(msg.size());
        return msg;
    }
};
#endif

struct Header {
    char length[4];
    char code[7];
    char date[8];
};

class Connection;
struct Message {
    std::shared_ptr<Connection> remote = nullptr;
    std::unique_ptr<char[]> data = std::make_unique<char[]>(1024);
};
}
