#pragma once

#include "net_common.h"
#include "net_tsqueue.h"
#include "net_message.h"

namespace net {
template<typename T>
class Connection {
public:
    Connection(int sockfd, int kqueue, tsqueue<std::shared_ptr<char[]>>& message) : m_sockfd(sockfd), m_kqueue(kqueue), m_timeout(0),  m_message(message) {
        struct kevent event;
        EV_SET(&event, sockfd, EVFILT_READ, EV_ADD, 0, 0, nullptr);
        kevent(m_kqueue, &event, 1, nullptr, 0, nullptr);
        
        SetTimeout();
    }
    
    ~Connection() {
        Disconnect();
    }
    
    int GetSocketFd() const {
        return m_sockfd;
    }
    
    void HandleEvent(const struct kevent &event) {
        if (event.filter == EVFILT_READ) {
            Receive();
        } else if (event.filter == EVFILT_TIMER) {
            std::cout << "EVFILT_TIMER\n";
            if (m_timeout == 6)
                throw std::runtime_error("Client disconnected");
            m_timeout++;
        }
        
        SetTimeout();
    }
    
    void Disconnect() {
        struct kevent event;
        EV_SET(&event, m_sockfd, EVFILT_READ, EV_DELETE, 0, 0, nullptr);
        if (kevent(m_kqueue, &event, 1, nullptr, 0, nullptr) < 0) {
            perror("Failed to remove socket event");
        }
        
        close(m_sockfd);
    }
    
    bool IsConnected() const {
        return fcntl(m_sockfd, F_GETFD) != -1;
    }
    
    void Send(const std::shared_ptr<char[]>& buffer) {
        ::send(m_sockfd, buffer.get(), sizeof(net::Test1), 0);
    }
    
private:
    void Receive() {
        auto buffer = std::make_unique<char[]>(128);
        std::memset(buffer.get(), 0x00, sizeof(buffer));
        
        ssize_t bytesRead = ::recv(m_sockfd, buffer.get(), sizeof(Test1), 0);
        if (bytesRead <= 0) {
            std::cerr << "Client disconnected: " << m_sockfd << "\n";
            throw std::runtime_error("Client disconnected");
        }
        
        m_message.emplace_back(std::move(buffer));
        
        struct kevent event;
        EV_SET(&event, SERVER_MSG_EVENT_IDENT, EVFILT_USER, 0, NOTE_TRIGGER, 0, nullptr);
        if (kevent(m_kqueue, &event, 1, nullptr, 0, nullptr) < 0) {
            perror("Failed to trigger server message event");
        }
        
        m_timeout = 0;
    }
    
#if 0
    void Test1() {
        auto buffer = std::make_unique<char[]>(128);
        Test1* packet = reinterpret_cast<net::Test1*>(buffer.get());
        
        std::memset(buffer.get(), 0x00, sizeof(buffer));
        std::memcpy(packet->length, "0019", 4);
        std::memcpy(packet->code, "0800200", 7);
        std::memcpy(packet->date, "20250201", 8);
        
        ::send(m_sockfd, buffer.get(), sizeof(net::Test1), 0);
    }
    
    void TestRcv() {
        std::vector<char> buffer(1024);
        ssize_t bytesRead = ::recv(m_sockfd, buffer.data(), buffer.size(), 0);
        if (bytesRead <= 0) {
            std::cerr << "Client disconnected: " << m_sockfd << "\n";
            throw std::runtime_error("Client disconnected");
        }
        
        std::cout << buffer.data() << "\n";
    }
#endif
    
    void SetTimeout() {
        struct kevent event;
        EV_SET(&event, m_sockfd, EVFILT_TIMER, EV_ADD | EV_ONESHOT, 0, 5000, nullptr);
        kevent(m_kqueue, &event, 1, nullptr, 0, nullptr);
    }
    
private:
    int m_timeout;
    int m_sockfd;
    int m_kqueue;
    tsqueue<std::shared_ptr<char[]>>& m_message;
};
}
