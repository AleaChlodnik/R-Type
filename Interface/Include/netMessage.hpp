/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** netMessage
*/

#pragma once
#include "netCommon.hpp"
#include "netConnection.hpp"

namespace r_type {
namespace net {
/**
 * @brief Message Header
 * to be sent over the network
 * to send Body size and ID
 *
 * @tparam T
 */
template <typename T> struct MessageHeader {
    T id{};
    uint32_t size = 0;
};

/**
 * @brief Message
 *
 * @tparam T
 */
template <typename T> struct Message {
    MessageHeader<T> header{};
    std::vector<uint8_t> body;

    size_t size() const { return body.size(); }

    friend std::ostream &operator<<(std::ostream &os, const Message<T> &msg)
    {
        os << "ID:" << int(msg.header.id) << " Size:" << msg.header.size;
        return os;
    }

    /**
     * @brief pile data in message
     *
     * @tparam DataType
     * @param msg
     * @param data
     * @return Message<T>&
     */
    template <typename DataType>
    friend Message<T> &operator<<(Message<T> &msg, const DataType &data)
    {
        static_assert(std::is_standard_layout<DataType>::value,
            "Data is too complex to be pushed into vector");

        size_t i = msg.body.size();

        msg.body.resize(msg.body.size() + sizeof(DataType));

        std::memcpy(msg.body.data() + i, &data, sizeof(DataType));

        msg.header.size = msg.size();

        return msg;
    }

    /**
     * @brief unpile data from message
     *
     * @tparam DataType
     * @param msg
     * @param data
     * @return Message<T>&
     */
    template <typename DataType> friend Message<T> &operator>>(Message<T> &msg, DataType &data)
    {
        static_assert(std::is_standard_layout<DataType>::value,
            "Data is too complex to be pulled from vector");

        size_t i = msg.body.size() - sizeof(DataType);

        std::memcpy(&data, msg.body.data() + i, sizeof(DataType));

        msg.body.resize(i);

        msg.header.size = msg.size();

        return msg;
    }
};

template <typename T> class Connection;

/**
 * @brief
 *
 * @tparam T
 */
template <typename T> struct OwnedMessage {
    std::shared_ptr<Connection<T>> remote = nullptr;
    Message<T> msg;

    friend std::ostream &operator<<(std::ostream &os, const OwnedMessage<T> &msg)
    {
        os << msg.msg;
        return os;
    }
};

} // namespace net
} // namespace r_type
