#pragma once

#include <optional>
#include <cassert>
#include <algorithm>  // for std::copy

template<typename T>
class DynamicQueue
{
private:
    T* fElements;    // queue elements
    size_t fFirstIndex;   // first element in queue
    size_t fLastIndex;   // next free slot  
    size_t fCurrentSize;   // size of queue

    void resize(size_t aNewSize)
    {
        T* newElements = new T[aNewSize];
        size_t newSize = 0;

        for (size_t i = fFirstIndex; i < fLastIndex; ++i)
        {
            newElements[newSize++] = std::move(fElements[i % fCurrentSize]);
        }

        delete[] fElements;

        fElements = newElements;
        fCurrentSize = aNewSize;
        fFirstIndex = 0;
        fLastIndex = newSize;
    }

    void ensure_capacity()
    {
        if (fLastIndex - fFirstIndex >= fCurrentSize)
        {
            resize(fCurrentSize * 2 + 1);
        }
    }

    void adjust_capacity()
    {
        if (fLastIndex - fFirstIndex < fCurrentSize / 4)
        {
            resize(std::max(fCurrentSize / 2, size_t(1)));
        }
    }

public:
    DynamicQueue()
        : fElements(new T[1]), fFirstIndex(0), fLastIndex(0), fCurrentSize(1)
    {
    }

    ~DynamicQueue()
    {
        delete[] fElements;
    }

    DynamicQueue(const DynamicQueue&) = delete;
    DynamicQueue& operator=(const DynamicQueue&) = delete;

    std::optional<T> top() const noexcept
    {
        if (fFirstIndex == fLastIndex)
        {
            return std::nullopt;
        }
        return fElements[fFirstIndex % fCurrentSize];
    }

    void enqueue(const T& aValue)
    {
        ensure_capacity();
        fElements[fLastIndex % fCurrentSize] = aValue;
        ++fLastIndex;
    }

    void dequeue()
    {
        if (fFirstIndex == fLastIndex)
        {
            return; // Queue is empty
        }
        ++fFirstIndex;
        adjust_capacity();
    }
};
