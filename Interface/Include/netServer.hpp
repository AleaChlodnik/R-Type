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
        } catch (std::exception &e) {
            std::cerr << "[SERVER] Exception: " << e.what() << "\n";
            return false;
        }

        std::cout << "[SERVER] Started!\n";
        return true;
    }

    void Stop()
    {
        m_asioContext.stop();

        if (m_threadContext.joinable())
            m_threadContext.join();

        std::cout << "[SERVER] Stopped!\n";
    }

    void WaitForClientConnection()
    {
        m_asioAcceptor.async_accept([this](std::error_code ec,
                                        asio::ip::tcp::socket socket) {
            if (!ec) {
                std::cout << "[SERVER] New Connection: "
                          << socket.remote_endpoint() << "\n";

                std::shared_ptr<Connection<T>> newconn =
                    std::make_shared<Connection<T>>(
                        Connection<T>::owner::server, m_asioContext,
                        std::move(socket), m_qMessagesIn);

                if (OnClientConnect(newconn)) {
                    m_deqConnections.push_back(std::move(newconn));

                    m_deqConnections.back()->ConnectToClient(this, nIDCounter++);

                    std::cout << "[" << m_deqConnections.back()->GetID()
                              << "] Connection Approved\n";
                } else {
                    std::cout << "[-----] Connection Denied\n";
                }
            } else {
                std::cout << "[SERVER] New Connection Error: " << ec.message()
                          << "\n";
            }

            WaitForClientConnection();
        });
    }

    void MessageClient(
        std::shared_ptr<Connection<T>> client, const message<T> &msg)
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
        std::shared_ptr<Connection<T>> pIgnoreClient = nullptr)
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

    void Update(size_t nMaxMessages = -1, bool bWait = false)
    {
        if (bWait)
            m_qMessagesIn.wait();

        size_t nMessageCount = 0;
        while (nMessageCount < nMaxMessages && !m_qMessagesIn.empty()) {
            auto msg = m_qMessagesIn.pop_front();

            OnMessage(msg.remote, msg.msg);

            nMessageCount++;
        }
    }

    virtual void OnClientValidated(std::shared_ptr<Connection<T>> client)
    {
    }

  protected:
    virtual bool OnClientConnect(std::shared_ptr<Connection<T>> client)
    {
        return false;
    }

    virtual void OnClientDisconnect(std::shared_ptr<Connection<T>> client) {}

    virtual void OnMessage(
        std::shared_ptr<Connection<T>> client, message<T> &msg)
    {
    }

  protected:
    ThreadSafeQueue<owned_message<T>> m_qMessagesIn;

    std::deque<std::shared_ptr<Connection<T>>> m_deqConnections;

    asio::io_context m_asioContext;
    std::thread m_threadContext;

    asio::ip::tcp::acceptor m_asioAcceptor;

    uint32_t nIDCounter = 10000;
};
} // namespace net
} // namespace olc