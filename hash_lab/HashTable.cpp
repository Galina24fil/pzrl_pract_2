#include "HashTable.h"
#include <cmath>
#include <stdexcept>

HashTable::HashTable(size_t size) noexcept
    : _capacity(static_cast<int32_t>(size)), _filled(0), table(_capacity) {}

HashTable::~HashTable() = default;

size_t HashTable::hash_function(const KeyType &key) const 
{
    size_t hash = 0;
    for (size_t i = 0; i < key.length(); i++) 
    {
        char ch = key[i];
        hash = (hash * 10061 + static_cast<size_t>(ch)) % _capacity;
    }
    return hash;
}

void HashTable::insert(const KeyType &key, const ValueType &value) {
    if (getLoadFactor() > 0.75) 
    {
        int32_t old_capacity = _capacity;
        auto old_table = table;

        _capacity *= 2;
        table.clear();
        table.resize(_capacity);
        _filled = 0;

        for (const auto& bucket : old_table) 
        {
            for (const auto& pair : bucket) 
            {
                insert(pair.first, pair.second);
            }
        }
    }
    
    size_t ind = hash_function(key);
    for (auto it = table[ind].begin(); it != table[ind].end(); ++it) 
    {
        if (it->first == key) 
        {
            it->second = value;
	        return;
        }
    }
    table[ind].push_back({key, value});
    _filled++;
}

bool HashTable::find(const KeyType &key, ValueType &value) const
{
    size_t ind = hash_function(key);
    for (auto it = table[ind].begin(); it != table[ind].end(); ++it) 
    {
        if (it->first == key) 
        {
            value = it->second;
            return true;
        }
    }
    return false;
}

void HashTable::remove(const KeyType &key) 
{
    size_t ind = hash_function(key);
    for (auto it = table[ind].begin(); it != table[ind].end(); it++) 
    {
        if (it->first == key) 
        {
            table[ind].erase(it);
            _filled--;
            return;
        }
    }
}

ValueType& HashTable::operator[](const KeyType &key) 
{
    size_t ind = hash_function(key);
    for (auto it = table[ind].begin(); it != table[ind].end(); it++) 
    {
        if (it->first == key) 
        {
            return it->second;
        }
    }
    throw std::runtime_error("There is no this element");
}

double HashTable::getLoadFactor() 
{
    return static_cast<double>(_filled) / _capacity;
}
