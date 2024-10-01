/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** netThreadSafeQueue
*/

#pragma once

#include "netCommon.hpp"

namespace olc {
namespace net {
/**
 * @brief Thread Safe Queue
 *
 * @tparam T
 */
template <typename T> class ThreadSafeQueue {
  public:
    /**
     * @brief Construct a new Thread Safe Queue object
     *
     */
    ThreadSafeQueue() = default;
    /**
     * @brief Copy Construct a new Thread Safe Queue object
     *
     */
    ThreadSafeQueue(const ThreadSafeQueue<T> &) = delete;
    /**
     * @brief Move Construct a new Thread Safe Queue object
     *
     */
    virtual ~ThreadSafeQueue() { clear(); }

  public:
    /**
     * @brief return the front of the queue
     *
     * @return const T&
     */
    const T &front()
    {
        std::scoped_lock lock(muxQueue);
        return deqQueue.front();
    }

    /**
     * @brief return the back of the queue
     *
     * @return const T&
     */
    const T &back()
    {
        std::scoped_lock lock(muxQueue);
        return deqQueue.back();
    }

    /**
     * @brief pop the front of the queue
     *
     * @return T
     */
    T pop_front()
    {
        std::scoped_lock lock(muxQueue);
        auto t = std::move(deqQueue.front());
        deqQueue.pop_front();
        return t;
    }

    /**
     * @brief pop the back of the queue
     *
     * @return T
     */
    T pop_back()
    {
        std::scoped_lock lock(muxQueue);
        auto t = std::move(deqQueue.back());
        deqQueue.pop_back();
        return t;
    }

    /**
     * @brief push item to the back of the queue
     *
     * @param item
     */
    void push_back(const T &item)
    {
        std::scoped_lock lock(muxQueue);
        deqQueue.emplace_back(std::move(item));

        std::unique_lock<std::mutex> ul(muxBlocking);
        cvBlocking.notify_one();
    }

    /**
     * @brief push item to the front of the queue
     *
     * @param item
     */
    void push_front(const T &item)
    {
        std::scoped_lock lock(muxQueue);
        deqQueue.emplace_front(std::move(item));

        std::unique_lock<std::mutex> ul(muxBlocking);
        cvBlocking.notify_one();
    }

    /**
     * @brief return true if the queue is empty
     *
     * @return true
     * @return false
     */
    bool empty()
    {
        std::scoped_lock lock(muxQueue);
        return deqQueue.empty();
    }

    /**
     * @brief return the size of the queue
     *
     * @return size_t
     */
    size_t count()
    {
        std::scoped_lock lock(muxQueue);
        return deqQueue.size();
    }

    /**
     * @brief clear the queue
     *
     */
    void clear()
    {
        std::scoped_lock lock(muxQueue);
        deqQueue.clear();
    }

    /**
     * @brief wait for the queue to be filled
     *
     */
    void wait()
    {
        while (empty()) {
            std::unique_lock<std::mutex> ul(muxBlocking);
            cvBlocking.wait(ul);
        }
    }

  protected:
    std::mutex muxQueue;
    std::deque<T> deqQueue;

    std::condition_variable cvBlocking;
    std::mutex muxBlocking;
};
} // namespace net
} // namespace olc