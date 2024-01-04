#include "utility.h"

template <typename T>
void twixt::Utility::swap(T*& current, T*& opponent)
{
    T* temp = current;
    current = opponent;
    opponent = temp;
}