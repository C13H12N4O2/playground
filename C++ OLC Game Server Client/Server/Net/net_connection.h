#pragma once

#include "net.h"

namespace net {
	template<typename T>
	class connection : public std::enable_shared_from_this<connection<T>> {
	public:
		enum class owner {
			server,
			client,
		};

	public:
		connection(owner parent, asio::io_context& asioContext, asio::ip::tcp::socket socket, olc::net::tsqueue<owned_message<T>>& qIn)
			: m_asioContext(asioContext), m_socket(std::move(socket)), m_qMessagesIn(qIn) {
			m_nOwnerType = parent;
		}
		virtual ~connection() {

		}

	protected:
		asio::ip::tcp::socket m_socket;
		asio::io_context& m_asioContext;
		olc::net::tsqueue<message<T>> m_qMessagesOut;
		olc::net::tsqueue<owned_message<T>>& m_qMessagesIn;
		message<T> m_msgTemporaryIn;
		owner m_nOwnerType = owner::server;
	};
}