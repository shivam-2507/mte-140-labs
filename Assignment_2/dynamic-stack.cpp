#include "dynamic-stack.h"
#include <iostream>

const DynamicStack::StackItem DynamicStack::EMPTY_STACK = -999;

DynamicStack::DynamicStack()
{
    capacity_ = 16;
    init_capacity_ = 16;
    size_ = 0;
    items_ = new StackItem[capacity_];
}

DynamicStack::DynamicStack(unsigned int capacity)
{
    capacity_ = capacity;
    init_capacity_ = capacity;
    size_ = 0;
    items_ = new StackItem[capacity_];
}

DynamicStack::~DynamicStack()
{
    delete[] items_;
    items_ = nullptr;
}

unsigned int DynamicStack::size() const
{
    return size_;
}

bool DynamicStack::empty() const
{
    return (size_ == 0);
}

DynamicStack::StackItem DynamicStack::peek() const
{
    if (empty())
    {
        std::cout << "Stack is empty" << std::endl;
        return EMPTY_STACK;
    }
    return items_[size_ - 1];
}

void DynamicStack::push(StackItem value)
{
    if (size_ >= capacity_)
    {
        capacity_ *= 2;
        StackItem *new_items = new StackItem[capacity_];
        for (unsigned int i = 0; i < size_; i++)
        {
            new_items[i] = items_[i];
        }
        delete[] items_;
        items_ = new_items;
    }
    items_[size_] = value;
    size_++;
}

DynamicStack::StackItem DynamicStack::pop()
{
    if (empty())
    {
        return EMPTY_STACK;
    }

    StackItem popped_value = items_[size_ - 1];
    size_--;

    if (size_ <= capacity_ / 4 && capacity_ > init_capacity_)
    {
        capacity_ /= 2;
        StackItem *new_items = new StackItem[capacity_];

        for (unsigned int i = 0; i < size_; i++)
        {
            new_items[i] = items_[i];
        }

        delete[] items_;
        items_ = new_items;
    }
    return popped_value;
}

void DynamicStack::print() const
{
    if (empty())
    {
        std::cout << "Stack is empty" << std::endl;
        return;
    }

    // Print in stack order (top to bottom)
    for (int i = size_ - 1; i >= 0; i--)
    {
        std::cout << items_[i] << std::endl;
    }
}
