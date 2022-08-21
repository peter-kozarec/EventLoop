#ifndef EVENTLOOP_UTILS_PTRQUEUE_H
#define EVENTLOOP_UTILS_PTRQUEUE_H

#include "mutex.h"
#include "mutexlocker.h"


template< typename T >
class CPtrQueue
{
    struct QueueNode
    {
        T *data;
    };

    QueueNode *node_;
    unsigned int capacity_;
    unsigned int size_;
    CMutex mutex_;

public:
    explicit CPtrQueue( unsigned int capacity = 1000 );
    ~CPtrQueue();

    T *dequeue();
    bool enqueue( T *item );

    bool is_empty();
};

template< typename T >
CPtrQueue< T >::CPtrQueue( unsigned int capacity )
{
    node_ = new QueueNode[capacity];
    capacity_ = capacity;
    size_ = 0;
}

template< typename T >
CPtrQueue< T >::~CPtrQueue()
{
    CMutexLocker lock( mutex_ );

    for ( unsigned int i = 0; i < size_; ++i )
    {
        delete node_[ i ].data;
    }

    delete[]node_;
}

template< typename T >
bool CPtrQueue< T >::enqueue( T *item )
{
    CMutexLocker lock( mutex_ );

    if ( !item || capacity_ + 1 <= size_ )
    {
        return false;
    }

    node_[ size_ ].data = item;
    size_++;

    return true;
}

template< typename T >
T *CPtrQueue< T >::dequeue()
{
    CMutexLocker lock( mutex_ );

    if ( size_ == 0 )
    {
        return 0;
    }

    return node_[ --size_ ].data;
}

template< typename T >
bool CPtrQueue< T >::is_empty()
{
    CMutexLocker lock( mutex_ );
    return size_ == 0;
}

#endif // EVENTLOOP_UTILS_PTRQUEUE_H