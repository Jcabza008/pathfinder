#include <gtest/gtest.h>
#include <functional>

#include "priority_queue.h"

using namespace pathfinder;

TEST(PriorityQueue, fTest_minBehavior)
{
    PriorityQueue<int> q;
    ASSERT_TRUE(q.empty());

    q.push(3);
    q.push(5);
    q.push(1);

    ASSERT_EQ(q.top(), 1);
    q.pop();
    ASSERT_EQ(q.top(), 3);
    q.pop();
    ASSERT_EQ(q.top(), 5);
    q.pop();
    ASSERT_TRUE(q.empty());
}

TEST(PriorityQueue, fTest_minComplexBehavior)
{
    PriorityQueue<int> q;
    ASSERT_TRUE(q.empty());

    q.push(3);
    ASSERT_EQ(q.top(), 3);

    q.push(5);
    ASSERT_EQ(q.top(), 3);

    q.push(1);
    ASSERT_EQ(q.top(), 1);

    q.pop();
    q.pop();
    ASSERT_EQ(q.top(), 5);

    q.push(2);
    ASSERT_EQ(q.top(), 2);

    q.pop();
    q.pop();

    ASSERT_TRUE(q.empty());
}

TEST(PriorityQueue, fTest_maxBehavior)
{
    PriorityQueue<int> q([](int lhs, int rhs){ return lhs > rhs; });
    ASSERT_TRUE(q.empty());

    q.push(3);
    q.push(5);
    q.push(1);

    ASSERT_EQ(q.top(), 5);
    q.pop();
    ASSERT_EQ(q.top(), 3);
    q.pop();
    ASSERT_EQ(q.top(), 1);
    q.pop();
    ASSERT_TRUE(q.empty());
}

TEST(PriorityQueue, fTest_maxComplexBehavior)
{
    PriorityQueue<int> q([](int lhs, int rhs){ return lhs > rhs; });
    ASSERT_TRUE(q.empty());

    q.push(3);
    ASSERT_EQ(q.top(), 3);

    q.push(5);
    ASSERT_EQ(q.top(), 5);

    q.push(1);
    ASSERT_EQ(q.top(), 5);

    q.pop();
    q.pop();
    ASSERT_EQ(q.top(), 1);

    q.push(2);
    ASSERT_EQ(q.top(), 2);

    q.pop();
    q.pop();

    ASSERT_TRUE(q.empty());
}

TEST(PriorityQueue, fTest_minManyNumbers)
{
    PriorityQueue<int> q;
    std::vector<int> v = {42, 24, 99, 95, 93, 20, 63, 21, 37, 71, 16,  1, 77, 59, 27, 19, 23, 52, 38, 50,
                        57,  8, 61, 11, 81,  7, 35,  4, 30, 29, 91, 18, 14, 56, 64, 68, 47, 62, 97, 44,
                        85, 92, 79, 89, 33, 65, 87, 67, 45, 10, 88, 98, 54, 82, 94, 73, 53, 66, 60, 17,
                        15, 25, 22, 34, 76, 12, 26,  6, 48,  9, 100, 96, 31, 5, 90, 58, 41, 75, 46, 32,
                        78, 49, 70, 80, 55,  3, 39,  2, 36, 13, 40, 84, 72, 28, 51, 43, 83, 69, 86, 74};

    for(auto it = v.cbegin(); it != v.cend(); it++)
        q.push(*it);

    ASSERT_EQ(q.size(), 100);

    for(size_t i = 1; i <= 100; i++)
    {
        ASSERT_EQ(q.top(), i);
        q.pop();
    }

    ASSERT_TRUE(q.empty());
}

TEST(PriorityQueue, fTest_updateKeyTest0)
{
    PriorityQueue<int*> q([](int* lhs, int* rhs){ return *lhs > *rhs; });
    ASSERT_TRUE(q.empty());
    int a, b, c;
    a = 1;
    b = 2;
    c = 3;

    q.push(&a);
    ASSERT_EQ(q.top(), &a);

    q.push(&c);
    ASSERT_EQ(q.top(), &c);

    q.push(&b);
    ASSERT_EQ(q.top(), &c);

    a = 4;
    b = 5;
    ASSERT_EQ(q.top(), &c);
    q.updateDecreased(&a);
    q.updateDecreased(&b);

    ASSERT_EQ(q.top(), &b);
    q.pop();

    ASSERT_EQ(q.top(), &a);
    q.pop();

    ASSERT_EQ(q.top(), &c);
    q.pop();

    ASSERT_TRUE(q.empty());
}