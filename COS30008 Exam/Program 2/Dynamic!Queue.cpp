#pragma once

#include <optional>
#include <cassert>

template<typename T>
class DynamicQueue
{
private:
    T* fElements;    // queue elements
    size_t fFirstIndex;   // first element in queue
    size_t fLastIndex;   // next free slot
    size_t fCurrentSize;  // size of queue

    void resize(size_t aNewSize)
    {
        T* newElements = new T[aNewSize];
        size_t currentSize = size();
        for (size_t i = 0; i < currentSize; ++i)
        {
            newElements[i] = std::move(fElements[(fFirstIndex + i) % fCurrentSize]);
        }
        delete[] fElements;
        fElements = newElements;
        fFirstIndex = 0;
        fLastIndex = currentSize;
        fCurrentSize = aNewSize;
    }

    void ensure_capacity()
    {
        if (fLastIndex == fCurrentSize)
        {
            resize(fCurrentSize == 0 ? 1 : 2 * fCurrentSize);
        }
    }

    void adjust_capacity()
    {
        if (size() < fCurrentSize / 4 && fCurrentSize > 1)
        {
            resize(fCurrentSize / 2);
        }
    }

public:
    DynamicQueue() : fElements(nullptr), fFirstIndex(0), fLastIndex(0), fCurrentSize(0) {}

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
        return fElements[fFirstIndex];
    }

    void enqueue(const T& aValue)
    {
        ensure_capacity();
        fElements[fLastIndex] = aValue;
        fLastIndex = (fLastIndex + 1) % fCurrentSize;
    }

    void dequeue()
    {
        assert(fFirstIndex != fLastIndex);
        fFirstIndex = (fFirstIndex + 1) % fCurrentSize;
        adjust_capacity();
    }

    size_t size() const
    {
        return (fLastIndex >= fFirstIndex) ? fLastIndex - fFirstIndex : fCurrentSize - fFirstIndex + fLastIndex;
    }
};
