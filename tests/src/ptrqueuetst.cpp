#include <gtest/gtest.h>
#include "utils/ptrqueue.hpp"


TEST(CPtrQueueTests, enqueue)
{
    CPtrQueue<int> int_queue;

    int_queue.enqueue(new int(10));
    int_queue.enqueue(new int(20));

    EXPECT_EQ(int_queue.size(), 2);
}

TEST(CPtrQueueTests, dequeue)
{
    CPtrQueue<int> int_queue;

    auto *first = new int(10);
    auto *second = new int(20);

    int_queue.enqueue(first);
    int_queue.enqueue(second);

    auto *first_dequeue = int_queue.dequeue();
    auto *second_dequeue = int_queue.dequeue();

    EXPECT_EQ(*first_dequeue, *first);
    EXPECT_EQ(*second_dequeue, *second);

    delete first_dequeue;
    delete second_dequeue;
}

TEST(CPtrQueueTests, overflow)
{
    CPtrQueue<int> int_queue(10);

    auto result = true;

    for (auto i = 0; i <= 100; ++i)
    {
        auto *item = new int(10);
        result &= int_queue.enqueue(item);
        result &= *int_queue.dequeue() == *item;
        delete item;
    }

    EXPECT_TRUE(result);
}