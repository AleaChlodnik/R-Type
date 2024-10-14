/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** netMessage
*/

#pragma once
#include "common.hpp"
#include "connection.hpp"

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
     * @brief Overloaded insertion operator for adding data to a message.
     *
     * This function allows adding data of any type to a message object using the insertion
     * operator (<<). The data is copied into the message's body vector, and the message's size is
     * updated accordingly.
     *
     * @tparam DataType The type of data being added to the message.
     * @param msg The message object to which the data is being added.
     * @param data The data being added to the message.
     * @return A reference to the modified message object.
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
     * @brief Overloaded stream extraction operator for deserializing data from a Message object.
     *
     * This function allows extracting data of type DataType from a Message object using the stream
     * extraction operator (>>). The DataType must be a standard layout type, otherwise a
     * static_assert will be triggered. The function retrieves the data from the body of the
     * Message object and resizes the body accordingly. Finally, it updates the size of the header
     * in the Message object.
     *
     * @tparam DataType The type of data to be extracted.
     * @param msg The Message object from which to extract the data.
     * @param data The variable to store the extracted data.
     * @return A reference to the modified Message object.
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
 * @brief A struct representing an owned message.
 *
 * This struct holds a shared pointer to a Connection object and a Message object.
 * It is used to represent a message that is owned by a specific connection.
 *
 * @tparam T The type of the message.
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
