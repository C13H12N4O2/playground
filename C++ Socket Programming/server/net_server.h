#pragma once

#include "net_common.h"
#include "net_tsqueue.h"
#include "net_message.h"
#include "net_connection.h"

namespace net {
template<typename T>
class Server {
public:
    Server(uint16_t port) : m_port(port), m_sockfd(-1), m_kqueue(-1) {
        
    }
    
    virtual ~Server() {
        close(m_kqueue);
        close(m_sockfd);
    }
    
    void Start() {
        m_sockfd = ::socket(AF_INET, SOCK_STREAM, 0);
        if (m_sockfd < 0) {
            std::cerr << "Socket creation failed\n";
            exit(EXIT_FAILURE);
        }
        
        struct sockaddr_in address;
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(m_port);
        
        int opt = 1;
        if (setsockopt(m_sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
            std::cerr << "Setsockopt failed: " << strerror(errno) << "\n";
            exit(EXIT_FAILURE);
        }
        
        if (bind(m_sockfd, (struct sockaddr *) &address, sizeof(address)) < 0) {
            std::cerr << "Bind failed:" << strerror(errno) << "\n";
            exit(EXIT_FAILURE);
        }
        
        m_kqueue = kqueue();
        if (m_kqueue < 0) {
            throw std::runtime_error("kqueue creation failed");
        }
        
        RegisterSocketEvent();
        RegisterMessageEvent();
        
        WaitForClientConnection();
    }
    
    void WaitForClientConnection() {
        if (listen(m_sockfd, 5) < 0) {
            throw std::runtime_error("Listen failed");
        }
        
        std::cout << "Server listening on port " << m_port << "\n";
        
        struct kevent events[10];
        
        while (true) {
            int count = kevent(m_kqueue, nullptr, 0, events, 10, nullptr);
            if (count < 0) {
                std::cerr << "kevent failed\n";
                sleep(1);
                continue;
            }
            
            for (int i = 0; i < count; ++i) {
                if (events[i].ident == static_cast<uintptr_t>(m_sockfd)) {
                    AcceptClientConnection();
                } else if (events[i].ident == SERVER_MSG_EVENT_IDENT) {
                    auto conn = FindConnection(events[i].ident);
                    if (conn == nullptr)
                        continue;
                    
                    auto buffer = std::move(m_messages.pop_front());
                    std::cout << buffer << "\n";
                    auto packet = reinterpret_cast<Test1*>(buffer.get());
                    
                    std::memcpy(packet->code, "0800210", sizeof(packet->code));
                    
                    conn->Send(buffer);
                } else {
                    auto conn = FindConnection(events[i].ident);
                    if (conn == nullptr)
                        continue;
                    
                    try {
                        conn->HandleEvent(events[i]);
                    } catch (const std::exception &e) {
                        std::cerr << "Connection error on socket " << conn->GetSocketFd() << ": " << e.what() << "\n";
                        
                        RemoveConnection(conn->GetSocketFd());
                    }
                }
            }
        }
    }
    
    void MessageAllClients() {
        
    }
    
private:
    void AcceptClientConnection() {
        auto sockfd = accept(m_sockfd, nullptr, nullptr);
        if (sockfd < 0) {
            std::cerr << "Failed to accept client connection\n";
            return;
        }

        std::cout << "Client connected: " << sockfd << "\n";
        
        fcntl(sockfd, F_SETFL, O_NONBLOCK);
        m_connections.emplace_back(std::make_unique<Connection<T>>(sockfd, m_kqueue, m_messages));
    }
    
    Connection<T>* FindConnection(uintptr_t sockfd) {
        for (auto& conn : m_connections) {
            if (conn->GetSocketFd() == sockfd) {
                return conn.get();
            }
        }
        return nullptr;
    }
    
    void RemoveConnection(int sockfd) {
        m_connections.erase(
            std::remove_if(m_connections.begin(), m_connections.end(),
                           [sockfd](const std::unique_ptr<Connection<T>>& conn) {
                               return conn->GetSocketFd() == sockfd;
                           }),
            m_connections.end());
    }
    
    void RegisterSocketEvent() {
        struct kevent event;
        EV_SET(&event, m_sockfd, EVFILT_READ, EV_ADD, 0, 0, nullptr);
        if (kevent(m_kqueue, &event, 1, nullptr, 0, nullptr) < 0) {
            throw std::runtime_error("kevent registration failed");
        }
    }
    
    void RegisterMessageEvent() {
        struct kevent event;
        EV_SET(&event, SERVER_MSG_EVENT_IDENT, EVFILT_USER, EV_ADD | EV_CLEAR, 0, 0, nullptr);
        if (kevent(m_kqueue, &event, 1, nullptr, 0, nullptr) < 0) {
            throw std::runtime_error("Failed to register server message event");
        }
    }
    
private:
    uint16_t m_port;
    int      m_sockfd;
    int      m_kqueue;
    tsqueue<std::shared_ptr<char[]>> m_messages;
    std::vector<std::unique_ptr<Connection<T>>> m_connections;
};
}
