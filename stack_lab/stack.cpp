#include "Stack.h"
#include "StackImplementation.h"
#include <iostream>
#include <cstdlib>
#include "Vector.h"
#include "flist.h"

class VectorStack: public IStackImplementation 
{
private:
    Vector _data;
public:
    VectorStack() = default;
    VectorStack(const VectorStack& other)
    {
        for (size_t i = 0; i < other._data.size(); i++)
	{
	    _data.pushBack(other._data[i]);
	}
    }

    void push(const ValueType& value) override 
    {
	_data.pushBack(value);
    }
    void pop() override
    {
	if (!isEmpty())
	{
	    _data.popBack();
	}
    }
    const ValueType& top() const override
    {
	if (!isEmpty())
	{
	    return _data[size()-1];
	}
        throw std::runtime_error("Is Empty");
    }
    bool isEmpty() const override
    {
	if (_data.size() > 0)
	{
	    return false;
	}
	else
	{
	    return true;
	}
    }
    size_t size() const override
    {
	return _data.size();
    }

};

class ListStack: public IStackImplementation
{
private:
    ForwardList list;
public:
    ListStack() = default;
    ListStack(const ListStack& other)
    {
        for (size_t i = 0; i < other.list.size(); i++)
	{
	    list.push_back(other.list[i]);
	}	
    }
    void push(const ValueType& value) override 
    {
	list.push_back(value);
    }
    void pop() override
    {
    	if (!isEmpty())
	{
	    list.pop_back();
    	}
    }
    const ValueType& top() const override
    {
	if (!isEmpty())
	{
	    return list.back();
    	}
	throw std::runtime_error("Is Empty");
    }
    bool isEmpty() const override
    {
    	if (list.size() > 0)
	{
	    return false;
    	}
	else
	{
	    return true;
    	}
    }
    size_t size() const override
    {
        return list.size();
    }

};

Stack::Stack(StackContainer container)
: _pimpl(nullptr), _containerType(container)
{
    if (container == StackContainer::Vector)
    {
	_pimpl = new VectorStack(); 
    }
    else if (container == StackContainer::List)
    {
        _pimpl = new ListStack();
    }
}

Stack::Stack(const ValueType* valueArray, const size_t arraySize, StackContainer container): _containerType(container)
{
    if (container == StackContainer::Vector)
    {
	_pimpl = new VectorStack();
    }
    else if (container == StackContainer::List)
    {
	_pimpl = new ListStack(); 
    }
    for (size_t i = 0; i < arraySize; i++)
    {
	_pimpl->push(valueArray[i]);
    }
}


Stack::Stack(const Stack& copyStack)
: _containerType(copyStack._containerType)
{
    if (copyStack._pimpl)
    {
        if (_containerType == StackContainer::Vector)
	{
	    _pimpl = new VectorStack(*dynamic_cast<VectorStack*>(copyStack._pimpl));
	}
	else if (_containerType == StackContainer::List)
	{
	    _pimpl = new ListStack(*dynamic_cast<ListStack*>(copyStack._pimpl));
	}
	else
	{
	    return;
	}
    }
    else
    {
        return;
    }
}

Stack& Stack::operator=(const Stack& copyStack)
{
    if (this != &copyStack)
    {
        delete _pimpl;
	_pimpl = nullptr;
	*this = Stack(copyStack);
	return *this;
    }
    else
    {
	return *this;
    }
}

Stack::Stack(Stack&& moveStack) noexcept
: _pimpl(moveStack._pimpl), _containerType(moveStack._containerType)
{
    moveStack._pimpl = nullptr;
}

Stack& Stack::operator=(Stack&& moveStack) noexcept
{
    if (this != &moveStack)
    {
	delete _pimpl;
	_pimpl = moveStack._pimpl;
	_containerType = moveStack._containerType;
	moveStack._pimpl = nullptr;
	return *this;
    }
    else
    {
	return *this;
    }
}


Stack::~Stack() 
{
    delete _pimpl;
}

void Stack::push(const ValueType& value)
{
    if (_pimpl)
    {
	_pimpl->push(value);
    }
    /*else
    {
	return;
    }*/
}

void Stack::pop()
{
    if (_pimpl)
    {
	_pimpl->pop();
    }
}

const ValueType& Stack::top() const
{
    if (_pimpl)
    {
	return _pimpl->top();
    }
    throw std::runtime_error("Is Empty"); 
}

bool Stack::isEmpty() const
{
    if (!_pimpl)
    {
	return true;
    }
    else
    {
	return _pimpl->isEmpty();
    }
}

size_t Stack::size() const
{
    if (!_pimpl)
    {
	return 0;
    }
    else
    {
	return _pimpl->size();
    }
}


