module utility;

// Definition of the function 'swap' inside the module partition
template <typename T>
void twixt::Utility::swap(T*& current, T*& opponent)
{
    T* temp = current;
    current = opponent;
    opponent = temp;
}