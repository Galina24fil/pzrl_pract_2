#include "Vector.h"
#include <algorithm>
#include <stdexcept>
Vector::Vector(const ValueType* rawArray, const size_t size, float coef)
	: _size(size), _capacity(size), _multiplicativeCoef(coef)
{
    if (rawArray && _capacity > 0)
    {
	_data = new ValueType [_size];
	for (size_t i = 0; i < _size; i++)
	{
	    _data[i] = rawArray[i];
	}

    }    
    else
    {
	_data = nullptr;
    }
}

Vector::Vector(const Vector& other)
{
    *this = other;
}

Vector& Vector::operator=(const Vector& other)
{
    if (this != &other)
    {
	_size = other._size;
	_capacity = other._size;
	_multiplicativeCoef = other._multiplicativeCoef;
	if (_data)
	{
	    delete[] _data;
	    _data = nullptr;
	}
	if (_size > 0)
	{
	    _data = new ValueType[_capacity];
	    for (size_t i = 0; i < _size; i++)
	    {
	        _data[i] = other._data[i];

	    }
	}
	else
	{
	    _data = nullptr;
	}
        return *this;
    }
    else
    {
	return *this;
    }
}	

Vector::Vector(Vector&& other) noexcept
{
    *this = std::move(other);
}

Vector& Vector::operator=(Vector&& other) noexcept
{
    if (this != &other)
    {
	delete[] _data;
	_data = other._data;
	_size = other._size;
	_capacity = other._capacity;
	_multiplicativeCoef = other._multiplicativeCoef;
	other._data = nullptr;
	other._size = 0;
	other._capacity = 0;
    }
    return *this;
}

Vector::~Vector()
{
    delete[] _data;
}

void Vector::pushBack(const ValueType& value)
{
    if (_size == _capacity)
    {
        size_t new_capacity;
	if (_capacity == 0)
	{
	    new_capacity = static_cast<size_t>(_multiplicativeCoef);
	    if (new_capacity < 1)
	    {
		new_capacity = 1;
	    }
	}
	else
	{
	    new_capacity = static_cast<size_t>(_capacity * _multiplicativeCoef);
	}
	ValueType* new_data = new ValueType[new_capacity];
	for (size_t i = 0; i < _size; i++)
	{
	    new_data[i] = _data[i];
	}
	delete[] _data;
	_data = new_data;
	_capacity = new_capacity;
    }
    _data[_size] = value;
    _size++;
}

void Vector::pushFront(const ValueType& value)
{
    insert(value, 0);
}

void Vector::insert(const ValueType& value, size_t pos)
{
    if (_size == _capacity)
    {
	size_t new_capacity;
	if (_capacity == 0)
	{
	    new_capacity = static_cast<size_t>(_multiplicativeCoef);
	    if (new_capacity < 1)
	    {
		new_capacity = 1;
	    }
	}
	else
	{
	    new_capacity = static_cast<size_t>(_capacity * _multiplicativeCoef);
	}
    reserve(new_capacity);
    }
    for (size_t i = _size; i > pos; i--)
    {
	_data[i] = _data[i - 1];
    }
    _data[pos] = value;
    _size++;
}

void Vector::insert(const ValueType* values, size_t size, size_t pos)
{
    if (size == 0)
    {
	return;
    }
    size_t new_size = _size + size;
    if (new_size > _capacity)
    {
	size_t new_capacity = _capacity;
	while (new_capacity < new_size)
	{
	    if (new_capacity != 0)
	    {
	        new_capacity = static_cast<size_t>(new_capacity * _multiplicativeCoef);
	    }
	    else
	    {
		new_capacity = static_cast<size_t>(_multiplicativeCoef);
		if (new_capacity < 1)
		{
		    new_capacity = 1;
		}
	    }
	}
	reserve(new_capacity);
    }
    if (pos < _size)
    {
	for (size_t i = _size; i > pos; i--)
        {
	    _data[i + size - 1] = _data[i - 1];
        }
    }
    for (size_t i = 0; i < size; i++)
    {
	_data[pos + i] = values[i];
    }
    _size = new_size;
}

void Vector::insert(const Vector& vector, size_t pos)
{
    insert(vector._data, vector._size, pos);
}

void Vector::popBack()
{
    if (_size > 0)
    {
	_size--;
    }
    else if (_size == 0)
    {
	throw::std::out_of_range("Size is 0");
    }
}

void Vector::popFront()
{
    if (_size > 0)
    {
	erase(0, 1);
    }
    if (_size == 0)
    {
	throw::std::out_of_range("Size is 0");
    }
}

void Vector::erase(size_t pos, size_t count)
{
    if (pos >= _size)
    {
	return;
    }
    else
    {
        size_t count_rem = std::min(pos + count, _size) - pos;
	for (size_t i = pos; i + count_rem < _size; i++)
	{
	    _data[i] = _data[i + count_rem];
	}
	_size -= count_rem;
    }
}

void Vector::eraseBetween(size_t beginPos, size_t endPos)
{
    if (beginPos >= endPos || beginPos >= _size)
    {
        return;
    }
    endPos = std::min(endPos, _size);
    size_t count_rem = endPos - beginPos;
    for (size_t i = beginPos; i + count_rem < _size; i++)
    {
	_data[i] = _data[i + count_rem];
    }
    _size -= count_rem;
}

size_t Vector::size() const
{
    return _size;
}

size_t Vector::capacity() const
{
    return _capacity;
}

double Vector::loadFactor() const
{
    if (_capacity == 0)
    {
	return 0.0;
    }
    else
    {
	return static_cast<double>(_size) / _capacity;
    }
}

ValueType& Vector::operator[](size_t ind)
{
    return _data[ind];
}

const ValueType& Vector::operator[](size_t ind) const
{
    return _data[ind];
}

long long Vector::find(const ValueType& value) const
{
    for (size_t i = 0; i < _size; i++)
    {
	if (value == _data[i])
	{
	    return i;
	}
    }
    return -1;
}

void Vector::reserve(size_t capacity)
{
    if (capacity <= _capacity)
    {
	return ;
    }
    ValueType* new_data = new ValueType[capacity];
    if (_data != nullptr)
    {
        for (size_t i = 0; i < _size; i++)
        {
	    new_data[i] = _data[i];
        }
        delete[] _data;
    }
    _data = new_data;
    //delete[] new_data;
    _capacity = capacity;
}

void Vector::shrinkToFit()
{
    if (_size >= _capacity)
    {
	return;
    }
    if (_size == 0)
    {
	delete[] _data;
	_data = nullptr;
	_capacity = 0;
	return;
    }
    ValueType* new_data = new ValueType[_size];
    for (size_t i = 0; i < _size; i++)
    {
	new_data[i] = _data[i];
    }
    delete[] _data;
    _data = new_data;
    _capacity = _size;
    //delete[] new_data;
}

Vector::Iterator::Iterator(ValueType* ptr) : _ptr(ptr) {}

ValueType& Vector::Iterator::operator*() 
{
    return *_ptr; 
}

const ValueType& Vector::Iterator::operator*() const 
{
    return *_ptr;
}

ValueType* Vector::Iterator::operator->() 
{
    return _ptr;
}

const ValueType* Vector::Iterator::operator->() const 
{
    return _ptr;
}

Vector::Iterator Vector::Iterator::operator++() 
{
    ++_ptr; 
    return *this;
}

Vector::Iterator Vector::Iterator::operator++(int)
{
    Iterator tmp = *this;
    ++_ptr;
    return tmp;
}

bool Vector::Iterator::operator==(const Iterator& other) const 
{
    return _ptr == other._ptr;
}

bool Vector::Iterator::operator!=(const Iterator& other) const 
{
    return _ptr != other._ptr;
}

Vector::Iterator Vector::begin() 
{
    return Iterator(_data);
}

Vector::Iterator Vector::end() 
{
    return Iterator(_data + _size);
}
