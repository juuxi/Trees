#include <cstddef>

template<typename V>
class Vector
{
    V* arr;
    size_t size; 
    size_t full_size;
public:
    Vector() {arr = nullptr; size = 0;}
    Vector(size_t _size){arr = new V[_size]; full_size = _size; size = 0;}
    void add(size_t, V);
    void remove(size_t);
    size_t get_size() {return size;}
    V get_value(size_t);
private:
    void ensure_capacity();
};

template<typename V>
void Vector<V>::add(size_t _pos, V _value)
{ 
    ensure_capacity();
    for (int i = size - 1; i > _pos-2; i--)
        arr[i+1] = arr[i];
    arr[_pos - 1] = _value;
    size++;
}

template<typename V>
void Vector<V>::remove(size_t _pos)
{
    for (int i = _pos - 1; i < full_size; i++)
        arr[i] = arr[i+1];
    size--;
}

template<typename V>
void Vector<V>::ensure_capacity()
{
    if (size >= full_size - 1)
    {
        V* new_arr = new V[full_size * 2];
        for (int i = 0; i < size; i++)
            new_arr[i] = arr[i];
        delete[] arr;
        arr = new_arr;
    }
}

template<typename V>
V Vector<V>::get_value(size_t pos)
{
    return arr[pos - 1];
}
