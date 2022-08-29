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
    tsize head_{0};
    tsize tail_{0};

public:
    explicit CPtrQueue(tsize capacity = 1000);
    ~CPtrQueue();

    T *dequeue();
    bool enqueue(T *item);

    bool is_empty();
    tsize size() const;
    tsize capacity() const;
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
    delete []node_;
}

template<typename T>
bool CPtrQueue<T>::enqueue(T *item)
{
    if (!item || capacity_ + 1 <= size_)
    {
        return false;
    }
    node_[head_].data = item;

    size_++;
    head_++;

    if (head_ == capacity_)
        head_ = 0;

    return true;
}

template<typename T>
T *CPtrQueue<T>::dequeue()
{
    if (size_ == 0)
    {
        return 0;
    }

    auto *data = node_[tail_].data;

    --size_;
    ++tail_;

    if (tail_ == capacity_)
        tail_ = 0;

    return data;
}

template<typename T>
bool CPtrQueue<T>::is_empty()
{
    return size_ == 0;
}

template<typename T>
tsize CPtrQueue<T>::size() const
{
    return size_;
}

template<typename T>
tsize CPtrQueue<T>::capacity() const
{
    return capacity_;
}

#endif // EVENTLOOP_UTILS_PTRQUEUE_HPP