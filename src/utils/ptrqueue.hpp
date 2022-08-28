#ifndef EVENTLOOP_UTILS_PTRQUEUE_HPP
#define EVENTLOOP_UTILS_PTRQUEUE_HPP

#include "compat.hpp"


template<typename T>
class CPtrQueue
{
    struct QueueNode
    {
        T *data;
    };

    QueueNode *node_;
    tsize capacity_;
    tsize size_{0};

public:
    explicit CPtrQueue(tsize capacity = 1000);
    ~CPtrQueue();

    T *dequeue();
    bool enqueue(T *item);
    bool is_empty();
};

template<typename T>
CPtrQueue<T>::CPtrQueue(tsize capacity) :
    node_(new QueueNode[capacity]),
    capacity_(capacity)
{
}

template<typename T>
CPtrQueue<T>::~CPtrQueue()
{
    for (tsize i = 0; i < size_; ++i)
    {
        delete node_[i].data;
    }
    delete[]node_;
}

template<typename T>
bool CPtrQueue<T>::enqueue(T *item)
{
    if (!item || capacity_ + 1 <= size_)
    {
        return false;
    }
    node_[size_].data = item;
    size_++;
    return true;
}

template<typename T>
T *CPtrQueue<T>::dequeue()
{
    if (size_ == 0)
    {
        return 0;
    }
    return node_[--size_].data;
}

template<typename T>
bool CPtrQueue<T>::is_empty()
{
    return size_ == 0;
}

#endif // EVENTLOOP_UTILS_PTRQUEUE_HPP