/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** netServer
*/

#pragma once

#include "netCommon.hpp"
#include "netConnection.hpp"
#include "netMessage.hpp"
#include "netThreadSafeQueue.hpp"

namespace olc {
namespace net {
template <typename T> class ServerInterface {
  public:
    ServerInterface(uint16_t port)
        : m_asioAcceptor(m_asioContext,
              asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port))
    {
    }
    virtual ~ServerInterface() { Stop(); }

    bool Start()
    {
        try {
            WaitForClientConnection();

            m_threadContext = std::thread([this]() { m_asioContext.run(); });
        } catch (const std::exception &e) {
            std::cerr << "[SERVER] Exception: " << e.what() << std::endl;
            return false;
        }

        std::cout << "[SERVER] Started" << std::endl;
        return true;
    }

    void Stop()
    {
        m_asioContext.stop();

        if (m_threadContext.joinable())
            m_threadContext.join();

        std::cout << "[SERVER] Stopped" << std::endl;
    }

    void WaitForClientConnection()
    {
        m_asioAcceptor.async_accept([this](std::error_code ec,
                                        asio::ip::tcp::socket socket) {
            if (!ec) {
                std::cout << "[SERVER] New connection:"
                          << socket.remote_endpoint() << std::endl;
                std::shared_ptr<connection<T>> newConnection =
                    std::make_shared<connection<T>>(
                        connection<T>::owner::server, m_asioContext,
                        std::move(socket), m_qMessagesIn);
                if (OnClientConnect(newConnection)) {
                    m_deqConnections.push_back(std::move(newConnection));
                    m_deqConnections.back()->ConnectToClient(nIDCounter++);
                    std::cout << "[" << m_deqConnections.back()->GetID()
                              << "] Connection Approved" << std::endl;
                } else {
                    std::cout << "[------] Connection Denied" << std::endl;
                }
            } else {
                std::cout << "[SERVER] New connection Error:" << ec.message()
                          << std::endl;
            }
            WaitForClientConnection();
        });
    }

    void MessageClient(
        std::shared_ptr<connection<T>> client, const message<T> &msg)
    {
        if (client && client->IsConnected()) {
            client->Send(msg);
        } else {
            OnClientDisconnect(client);
            client.reset();
            m_deqConnections.erase(std::remove(m_deqConnections.begin(),
                                       m_deqConnections.end(), client),
                m_deqConnections.end());
        }
    }

    void MessageAllClients(const message<T> &msg,
        std::shared_ptr<connection<T>> pIgnoreClient = nullptr)
    {
        bool bInvalidClientExists = false;

        for (auto &client : m_deqConnections) {
            if (client && client->IsConnected()) {
                if (client != pIgnoreClient)
                    client->Send(msg);
            } else {
                OnClientDisconnect(client);
                client.reset();
                bInvalidClientExists = true;
            }
        }

        if (bInvalidClientExists)
            m_deqConnections.erase(std::remove(m_deqConnections.begin(),
                                       m_deqConnections.end(), nullptr),
                m_deqConnections.end());
    }

    void Update(size_t nMaxMessage = -1)
    {
        size_t nMessageCount = 0;
        while (nMessageCount < nMaxMessage && !m_qMessagesIn.empty()) {
            auto msg = m_qMessagesIn.popFront();

            OnMessage(msg.remote, msg.msg);
            nMessageCount++;
        }
    }

  protected:
    virtual bool OnClientConnect(std::shared_ptr<connection<T>> client)
    {
        return false;
    }

    virtual void OnClientDisconnect(std::shared_ptr<connection<T>> client)
    {
        std::cout << "[SERVER] Client disconnected:" << std::endl;
    }

    virtual void OnMessage(
        std::shared_ptr<connection<T>> client, message<T> &msg)
    {
    }

  protected:
    ThreadSafeQueue<owned_message<T>> m_qMessagesIn;

    std::deque<std::shared_ptr<connection<T>>> m_deqConnections;

    asio::io_context m_asioContext;
    std::thread m_threadContext;

    asio::ip::tcp::acceptor m_asioAcceptor;

    uint32_t nIDCounter = 10000;
};
} // namespace net
} // namespace olc
