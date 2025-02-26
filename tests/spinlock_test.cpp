// src
#include <spinlock.hpp>

// Gtest
#include <gtest/gtest.h>

TEST(SpinLock, SingleThreaded)
{
    SpinLock lock;
    lock.lock();
    lock.unlock();
}

TEST(SpinLock, MultiThreads)
{
    SpinLock lock;
    const size_t numberOfThreads = 10;
    std::vector<std::thread> threads;
    std::atomic<int> shared_counter{};

    for (size_t i{}; i < numberOfThreads; i++)
    {
        threads.emplace_back([&]()
                             {
            for (size_t j{}; j < 1000; j++) {
                lock.lock();
                shared_counter.fetch_add(1, std::memory_order_relaxed);
                lock.unlock();
            } });
    }

    for (auto &thread : threads)
    {
        thread.join();
    }

    EXPECT_EQ(shared_counter.load(std::memory_order_relaxed), numberOfThreads * 1000);
}