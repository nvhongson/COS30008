
// COS30008, Final Exam, 2024

#include "PalindromeStringIterator.h"

void PalindromeStringIterator::moveToNextIndex()
{
    while (fIndex < static_cast<int>(fString.length()) && !std::isalpha(fString[fIndex]))
    {
        ++fIndex;
    }
}

void PalindromeStringIterator::moveToPreviousIndex()
{
    while (fIndex >= 0 && !std::isalpha(fString[fIndex]))
    {
        --fIndex;
    }
}

PalindromeStringIterator::PalindromeStringIterator(const std::string& aString)
    : fString(aString), fIndex(0)
{
    moveToNextIndex();
}

char PalindromeStringIterator::operator*() const noexcept
{
    return std::toupper(fString[fIndex]);
}

PalindromeStringIterator& PalindromeStringIterator::operator++() noexcept
{
    ++fIndex;
    moveToNextIndex();
    return *this;
}

PalindromeStringIterator PalindromeStringIterator::operator++(int) noexcept
{
    PalindromeStringIterator old = *this;
    ++(*this);
    return old;
}

PalindromeStringIterator& PalindromeStringIterator::operator--() noexcept
{
    --fIndex;
    moveToPreviousIndex();
    return *this;
}

PalindromeStringIterator PalindromeStringIterator::operator--(int) noexcept
{
    PalindromeStringIterator old = *this;
    --(*this);
    return old;
}

bool PalindromeStringIterator::operator==(const PalindromeStringIterator& aOther) const noexcept
{
    return fIndex == aOther.fIndex;
}

bool PalindromeStringIterator::operator!=(const PalindromeStringIterator& aOther) const noexcept
{
    return !(*this == aOther);
}

PalindromeStringIterator PalindromeStringIterator::begin() const noexcept
{
    PalindromeStringIterator iter(fString);
    iter.fIndex = 0;
    iter.moveToNextIndex();
    return iter;
}

PalindromeStringIterator PalindromeStringIterator::end() const noexcept
{
    PalindromeStringIterator iter(fString);
    iter.fIndex = static_cast<int>(fString.length());
    return iter;
}

PalindromeStringIterator PalindromeStringIterator::rbegin() const noexcept
{
    PalindromeStringIterator iter(fString);
    iter.fIndex = static_cast<int>(fString.length()) - 1;
    iter.moveToPreviousIndex();
    return iter;
}

PalindromeStringIterator PalindromeStringIterator::rend() const noexcept
{
    PalindromeStringIterator iter(fString);
    iter.fIndex = -1;
    return iter;
}
