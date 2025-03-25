#include "circular-queue.h"
#include <iostream>

const CircularQueue::QueueItem CircularQueue::EMPTY_QUEUE = -999;

CircularQueue::CircularQueue()
{
    capacity_ = 16;
    items_ = new QueueItem[capacity_];
    size_ = 0;
    head_ = 0;
    tail_ = 0;
}

CircularQueue::CircularQueue(unsigned int capacity)
{
    capacity_ = capacity;
    items_ = new QueueItem[capacity];
    size_ = 0;
    head_ = 0;
    tail_ = 0;
}

CircularQueue::~CircularQueue()
{
    delete[] items_;
    items_ = nullptr;
}

unsigned int CircularQueue::size() const
{
    return size_;
}

bool CircularQueue::empty() const
{
    if (size_ == 0)
    {
        return true;
    }
    return false;
}

bool CircularQueue::full() const
{
    if (size_ == capacity_)
    {
        return true;
    }
    return false;
}

CircularQueue::QueueItem CircularQueue::peek() const
{
    if (empty())
    {
        return EMPTY_QUEUE;
    }
    return items_[head_];
}

bool CircularQueue::enqueue(QueueItem value)
{
    if (full())
    {
        std::cout << "Queue is full" << std::endl;
        return false;
    }
    items_[tail_] = value;
    tail_ = (tail_ + 1) % capacity_;
    size_++;
    return true;
}

CircularQueue::QueueItem CircularQueue::dequeue()
{
    if (empty())
    {
        return EMPTY_QUEUE;
    }
    QueueItem temp = items_[head_];
    head_ = (head_ + 1) % capacity_;
    size_--;
    return temp;
}

void CircularQueue::print() const
{
    if (empty()) {
        std::cout<<"Queue is empty"<<std::endl;
        return;
    }
    std::cout<<items_[tail_]<<std::endl;
    for (int i = 0; i < size_; i++)
    {
        int index = (head_ + i) % capacity_;
        std::cout << items_[index] << std::endl;
    }
}