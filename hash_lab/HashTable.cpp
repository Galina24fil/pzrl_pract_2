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

double HashTable::getLoadFactor() 
{
    return static_cast<double>(_filled) / _capacity;
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
    
    size_t index = hash_function(key);
    for (auto &pair : table[index]) 
    {
        if (pair.first == key) 
        {
            pair.second = value;
	        return;
        }
    }
    table[index].push_back({key, value});
    _filled++;
}

bool HashTable::find(const KeyType &key, ValueType &value) const
{
    size_t ind = hash_function(key);
    for (const auto &pair : table[ind]) 
    {
        if (pair.first == key) 
        {
            value = pair.second;
            return true;
        }
    }
    return false;
}

void HashTable::remove(const KeyType &key) 
{
    size_t index = hash_function(key);
    for (auto it = table[index].begin(); it != table[index].end(); it++) 
    {
        if (it->first == key) 
        {
            table[index].erase(it);
            _filled--;
            return;
        }
    }
}

ValueType& HashTable::operator[](const KeyType &key) 
{
    size_t ind = hash_function(key);
    for (auto &pair : table[ind]) 
    {
        if (pair.first == key) 
        {
            return pair.second;
        }
    }
    throw std::runtime_error("There is no this element");
}