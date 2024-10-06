/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** netServer
*/

#include <net_server_abstract.hpp>

/**
 * @brief Construct a new Server Interface object
 *
 * @param port
 */
template <typename T>
NetServerAbstract<T>::NetServerAbstract(uint16_t port) : r_type::net::NetServerInterface<T>(port)
{
}

/**
 * @brief Destroy the Server Interface object
 *
 */
template <typename T> NetServerAbstract<T>::~NetServerAbstract() { Stop(); }

/**
 * @brief Start the server
 *
 * @return true
 * @return false
 */
template <typename T> bool NetServerAbstract<T>::Start()
{
    try {
        WaitForClientMessage();

        m_threadContext = std::thread([this]() { m_asioContext.run(); });
    } catch (std::exception &e) {
        std::cerr << "[SERVER] Exception: " << e.what() << "\n";
        return false;
    }

    std::cout << "[SERVER] Started!\n";
    return true;
}

/**
 * @brief Stop the server
 *
 */
template <typename T> void NetServerAbstract<T>::Stop()
{
    m_asioContext.stop();

    if (m_threadContext.joinable())
        m_threadContext.join();

    std::cout << "[SERVER] Stopped!\n";
}

/**
 * @brief wait for client connection
 *
 */
template <typename T> void NetServerAbstract<T>::WaitForClientMessage()
{
    m_asioSocket.async_receive_from(asio::buffer(m_tempBuffer.data(), m_tempBuffer.size()),
        m_clientEndpoint, [this](std::error_code ec, std::size_t bytes_recvd) {
            if (m_clientEndpoint.protocol() != asio::ip::udp::v4())
                return WaitForClientMessage();
            if (!ec) {
                std::cout << "[SERVER] New Connection: " << m_clientEndpoint.address().to_string()
                          << ":" << m_clientEndpoint.port() << std::endl;
                // create client socket
                asio::ip::udp::socket newClientSocket(m_asioContext);
                newClientSocket.open(m_clientEndpoint.protocol());
                newClientSocket.bind(asio::ip::udp::endpoint(asio::ip::udp::v4(), 0));

                std::cout << newClientSocket.local_endpoint().address().to_string() << ":"
                          << newClientSocket.local_endpoint().port() << std::endl;

                std::shared_ptr<Connection<T>> newConn =
                    std::make_shared<Connection<T>>(Connection<T>::owner::server, m_asioContext,
                        std::move(newClientSocket), m_qMessagesIn);

                if (OnClientConnect(newConn)) {
                    m_deqConnections.push_back(std::move(newConn));
                    m_deqConnections.back()->ConnectToClient(this, nIDCounter++);
                    std::cout << "[" << m_deqConnections.back()->GetID()
                              << "] Connection Approved\n";
                } else {
                    std::cout << "[-----] Connection Denied\n";
                }
            } else {
                std::cout << "[SERVER] New Connection Error: " << ec.message() << "\n";
            }
        });
}

/**
 * @brief send message message to client
 *
 * @param client
 * @param msg
 */
template <typename T>
void NetServerAbstract<T>::MessageClient(
    std::shared_ptr<r_type::net::Connection<T>> client, const Message<T> &msg)
{
    if (client && client->IsConnected()) {
        client->Send(msg);
    } else {
        OnClientDisconnect(client);

        client.reset();

        m_deqConnections.erase(
            std::remove(m_deqConnections.begin(), m_deqConnections.end(), client),
            m_deqConnections.end());
    }
}

/**
 * @brief message all clients
 *
 * @param msg
 * @param pIgnoreClient
 */
template <typename T>
void NetServerAbstract<T>::MessageAllClients(
    const Message<T> &msg, std::shared_ptr<Connection<T>> pIgnoreClient)
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
        m_deqConnections.erase(
            std::remove(m_deqConnections.begin(), m_deqConnections.end(), nullptr),
            m_deqConnections.end());
}

/**
 * @brief update server
 *
 * @param nMaxMessages
 * @param bWait
 */
template <typename T> void NetServerAbstract<T>::Update(size_t nMaxMessages, bool bWait)
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
