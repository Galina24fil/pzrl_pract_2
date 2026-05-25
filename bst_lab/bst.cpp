#include "BST.h"
#include <iostream>
#include <stack>
#include <algorithm>

BinarySearchTree::Node::Node(Key key, Value value, Node *parent, Node *left, Node *right)
    : keyValuePair(key, value), parent(parent), left(left), right(right) {}

BinarySearchTree::Node::Node(const Node &other)
    : keyValuePair(other.keyValuePair), parent(nullptr), left(nullptr), right(nullptr) {
    if (other.left) left = new Node(*other.left);
    if (other.right) right = new Node(*other.right);
    if (left) left->parent = this;
    if (right) right->parent = this;
}

bool BinarySearchTree::Node::operator==(const Node &other) const {
    return keyValuePair == other.keyValuePair;
}

void BinarySearchTree::Node::output_node_tree() const {
    if (left) 
    {
        left->output_node_tree();
    }
    std::cout << "Поддерево с ключом: " << keyValuePair.first << ", значением: " << keyValuePair.second << std::endl;
    if (right) 
    {
        right->output_node_tree();
    }
}

void BinarySearchTree::Node::insert(const Key &key, const Value &value) {
    if (key < keyValuePair.first) 
    {
        if (left) 
        {
            left->insert(key, value);
        } 
        else 
        {
            left = new Node(key, value, this);
        }
    } 
    else if (key >= keyValuePair.first)
    {
        if (right) 
        {
            right->insert(key, value);
        } 
        else 
        {
            right = new Node(key, value, this);
        }
    }
}

void BinarySearchTree::Node::erase(const Key &key) {
    if (key != keyValuePair.first) 
    {
        if (left && key < keyValuePair.first) 
        {
            left->erase(key);
        }
    
        if (right && key > keyValuePair.first) 
        {
            right->erase(key);
        }
    } 
    else
    {
        if (left && right) 
        {
            Node* newNode = right;
            while (newNode->left)
            {
                newNode = newNode->left;
            }
            this->keyValuePair = newNode->keyValuePair;
            newNode->erase(newNode->keyValuePair.first);
        }
        else
        {
            if (right)
            {
                Node* newrNode = right;
                if (parent)
                {
                    if (parent->left == this)
                    {
                        parent->left = newrNode;
                    }
                }
                if (newrNode)
                {
                    newrNode->parent = parent;
                    delete this;
                }
            }
            if (left)
            {
                Node* newlNode = left;
                if (parent)
                {
                    if (parent->left == this)
                    {
                        parent->left = newlNode;
                    }
                }
                if (newlNode)
                {
                    newlNode->parent = parent;
                    delete this;
                }
            }
        }
    }
}

BinarySearchTree::BinarySearchTree(const BinarySearchTree &other) 
: _size(other._size) 
{
    if (other._root) _root = new Node(*other._root);
}

BinarySearchTree &BinarySearchTree::operator=(const BinarySearchTree &other)
{
    if (this == &other)
    {
        return *this;
    }
    else
    {
        BinarySearchTree temp(other);
        std::swap(_root, temp._root);
        std::swap(_size, temp._size);
    }
    return *this;
}

BinarySearchTree::BinarySearchTree(BinarySearchTree &&other) noexcept
: _size(other._size), _root(other._root) {
    other._size = 0;
    other._root = nullptr;
}

void BinarySearchTree::cleanTree(Node* node)
{
    if (!node)
    {
        return;
    }
    cleanTree(node->left);
    cleanTree(node->right);
    delete node;
}

BinarySearchTree &BinarySearchTree::operator=(BinarySearchTree &&other) noexcept {
    if (this != &other) 
    {
        this->cleanTree(_root);
        _size = other._size;
        _root = other._root;
        other._size = 0;
        other._root = nullptr;
    }
    return *this;
}

BinarySearchTree::~BinarySearchTree() 
{
    cleanTree(_root);
}

BinarySearchTree::Iterator::Iterator(Node *node) : _node(node) {};

std::pair<Key, Value>& BinarySearchTree::Iterator::operator*() 
{
	return _node->keyValuePair;
}

const std::pair<Key, Value>& BinarySearchTree::Iterator::operator*() const 
{
	return _node->keyValuePair;
}

std::pair<Key, Value>* BinarySearchTree::Iterator::operator->() 
{
	return &_node->keyValuePair;
}

const std::pair<Key, Value>* BinarySearchTree::Iterator::operator->() const 
{
	return &_node->keyValuePair;
}

BinarySearchTree::Iterator BinarySearchTree::Iterator::operator++()
{
    if (!_node)
    {
        return *this;
    }
    if (_node->right) 
    {
        _node = _node->right;
        while (_node->left) 
        {
            _node = _node->left;
        }
    } 
    else
    {
        Node* parent = _node->parent;
        while (parent && _node == parent->right) 
        {
            _node = parent;
            parent = parent->parent;
        }
        _node = parent;
    }
    return *this;
}

BinarySearchTree::Iterator BinarySearchTree::Iterator::operator++(int)
{
	Iterator temp(*this);
	++(*this);
	return temp;
}

BinarySearchTree::Iterator BinarySearchTree::Iterator::operator--()
{
    if (!_node)
    {
        return *this;
    }
    if (_node->left) 
    {
        _node = _node->left;
        while (_node->right) 
        {
            _node = _node->right;
        }
    } 
    else
    {
        Node* parent = _node->parent;
        while (parent && _node == parent->left) 
        {
            _node = parent;
            parent = parent->parent;
        }
        _node = parent;
    }
    return *this;
}

BinarySearchTree::Iterator BinarySearchTree::Iterator::operator--(int)
{
	Iterator temp(*this);
	--(*this);
	return temp;
}

bool BinarySearchTree::Iterator::operator==(const Iterator &other) const
{
	return _node == other._node;
}

bool BinarySearchTree::Iterator::operator!=(const Iterator &other) const
{
	return _node != other._node;
}

BinarySearchTree::ConstIterator::ConstIterator(const Node *node) : _node(node) {};

const std::pair<Key, Value>& BinarySearchTree::ConstIterator::operator*() const
{
	return _node->keyValuePair;
}

const std::pair<Key, Value>* BinarySearchTree::ConstIterator::operator->() const
{
	return &_node->keyValuePair;
}


BinarySearchTree::ConstIterator BinarySearchTree::ConstIterator::operator++()
{
    if (!_node)
    {
        return *this;
    }
    if (_node->right) 
    {
        _node = _node->right;
        while (_node->left) 
        {
            _node = _node->left;
        }
    } 
    else
    {
        Node* parent = _node->parent;
        while (parent && _node == parent->right) 
        {
            _node = parent;
            parent = parent->parent;
        }
        _node = parent;
    }
    return *this;
}

BinarySearchTree::ConstIterator BinarySearchTree::ConstIterator::operator++(int)
{
	ConstIterator temp(*this);
	++(*this);
	return temp;
}

BinarySearchTree::ConstIterator BinarySearchTree::ConstIterator::operator--()
{
    if (!_node)
    {
        return *this;
    }
    if (_node->left) 
    {
        _node = _node->left;
        while (_node->right) 
        {
            _node = _node->right;
        }
    } 
    else
    {
        Node* parent = _node->parent;
        while (parent && _node == parent->left) 
        {
            _node = parent;
            parent = parent->parent;
        }
        _node = parent;
    }
    return *this;
}

BinarySearchTree::ConstIterator BinarySearchTree::ConstIterator::operator--(int)
{
	ConstIterator temp(*this);
	--(*this);
	return temp;
}

bool BinarySearchTree::ConstIterator::operator==(const ConstIterator &other) const
{
	return _node == other._node;
}

bool BinarySearchTree::ConstIterator::operator!=(const ConstIterator &other) const
{
	return _node != other._node;
}

void BinarySearchTree::insert(const Key& key, const Value& value) 
{
    if (!_root) 
    {
        _root = new Node(key, value);
    } 
    else 
    {
        _root->insert(key, value);
    }
    _size++;
}

void BinarySearchTree::erase(const Key& key) 
{
    if (_root) 
    {
        if (!_root->left && !_root->right && _root->keyValuePair.first == key)
        {
            delete _root;
            _root = nullptr;
            _size--;
        }
        else
        {
            Iterator r(_root);
            if ((r = find(key)) != end())
            {
                r._node->erase(key);
                _size--;
            }
        }
    }
    else
    {
        _size--;
    }
}

BinarySearchTree::ConstIterator BinarySearchTree::find(const Key& key) const
{
    Node* node = _root;
    while (node)
    {
        if (key == node->keyValuePair.first)
        {
            return ConstIterator(node);
        }
        else if (key < node->keyValuePair.first)
        {
            node = node->left;
        }
        else
        {
            node = node->right;
        }
    }
    return cend();
}

BinarySearchTree::Iterator BinarySearchTree::find(const Key& key)
{
    Node* node = _root;
    while (node)
    {
        if (key == node->keyValuePair.first)
        {
            return Iterator(node);
        }
        else if (key < node->keyValuePair.first)
        {
            node = node->left;
        }
        else
        {
            node = node->right;
        }
    }
    return end();
}

std::pair<BinarySearchTree::Iterator, BinarySearchTree::Iterator> BinarySearchTree::equalRange(const Key& key)
{
    Iterator first = find(key);
    if (first == end()) 
    {
        return {end(), end()};
    }
    Iterator last = first;
    while (last++ != end() && last->first == key);
    return {first, last};
}

std::pair<BinarySearchTree::ConstIterator, BinarySearchTree::ConstIterator> BinarySearchTree::equalRange(const Key& key) const
{
    ConstIterator first = find(key);
    if (first == cend()) 
    {
        return {cend(), cend()};
    }
    ConstIterator last = first;
    while (last++ != cend() && last->first == key);
    return {first, last};
}

BinarySearchTree::ConstIterator BinarySearchTree::min() const
{
    return cbegin();
}

BinarySearchTree::ConstIterator BinarySearchTree::max() const 
{ 
    if (!_root)
    {
        return cend();
    }
    const Node* node = _root;
    while (node->right)
    {
        node = node->right;
    }
    return ConstIterator(node); 
}

BinarySearchTree::ConstIterator BinarySearchTree::min(const Key&) const
{
    return cbegin();
}

BinarySearchTree::ConstIterator BinarySearchTree::max(const Key&) const
{
    return max();
}

BinarySearchTree::Iterator BinarySearchTree::begin() 
{ 
    if (!_root) 
    {
        return end();
    }
    Node* node = _root; 
    while (node->left)
    {
        node = node->left; 
    }
        return Iterator(node); 
    }


BinarySearchTree::Iterator BinarySearchTree::end() 
{ 
    if (!_root) 
    {
        return end();
    }
    Node* node = _root; 
    while (node->right)
    {
        node = node->right; 
    }
    return Iterator(node); 
}

/*BinarySearchTree::Iterator BinarySearchTree::end() 
{
    return Iterator(nullptr); 
}*/


BinarySearchTree::ConstIterator BinarySearchTree::cbegin() const
{ 
    if (!_root) 
    {
        return cend();
    }
    Node* node = _root; 
    while (node->left)
    {
        node = node->left; 
    }
        return ConstIterator(node); 
    }


BinarySearchTree::ConstIterator BinarySearchTree::cend() const
{ 
    if (!_root) 
    {
        return cend();
    }
    Node* node = _root; 
    while (node->right)
    {
        node = node->right; 
    }
    return ConstIterator(node); 
}

size_t BinarySearchTree::size() const
{
    return _size;
}

void BinarySearchTree::output_tree()
{
    if (_root)
    {
        _root->output_node_tree();
    }
}

/*size_t BinarySearchTree::max_heigh(Node* node, size_t height = 0) const 
{
    if (!node)
    {
        return height - 1;
    }
    size_t left_height  = max_heigh(node->left,  height + 1);
    size_t right_height = max_heigh(node->right, height + 1);
      
    return std::max(left_height, right_height);
}

size_t BinarySearchTree::max_height() const { 
      if (!_root)
         return 0; // пустое дерево имеет высоту 0

      return max_heigh(_root); 
   }*/