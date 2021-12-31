#pragma once

#include "Net.h"

namespace server {
	template<typename T>
	class server_interface {
	public:
		server_interface(uint16_t port)
			: m_asioAcceptor(m_asioContext, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port)) {

		}

		virtual ~server_interface() {

		}

		bool Start() {
			try {
				m_threadContext = std::thread([this]() { m_asioContext.run(); });
			}
			catch (std::exception& e) {
				std::cerr << "[SERVER] Exception: " << e.what() << "\n";
				return false;
			}

			std::cout << "[SERVER] Started\n";
			return true;
		}

		void Stop();
		void WaitForClientConnection();
		void MessageClient();
		void MessageAllClients();

		void Update(size_t nMaxMessages = -1) {
			//size_t nMessageCount = 0;
			//while (nMessageCount < nMaxMessages && !m_qMessagesIn.empty()) {
			//	auto msg = m_qMessagesIn.pop_front();
			//	OnMessage(msg.remote, msg.msg);
			//	++nMessageCount;
			//}
		}

	protected:
		bool OnClientConnect();
		void OnClientDisconnect();
		virtual void OnMessage(std::shared_ptr<net::connection<T>> client, net::message<T>& msg) {

		}

	protected:
		olc::net::tsqueue<net::owned_message<T>> m_qMessagesIn;
		std::deque<std::shared_ptr<::net::connection<T>>> m_deqConnections;
		asio::io_context m_asioContext;
		std::thread m_threadContext;
		asio::ip::tcp::acceptor m_asioAcceptor;
	};
}