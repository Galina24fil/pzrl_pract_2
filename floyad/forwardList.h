#pragma once
#include <iostream>



class ForwardList
{
public:
    struct Node 
    {
        double data;
        Node* next;
	Node(double val, Node* nxt = nullptr)
        : data(val), next(nxt) {}
    };
    
    ForwardList();
    ForwardList(Node* node) : head(node), count(0) {}
    void push_front(double value);
    void push_back(double value);
    void pop_front();
    void pop_back();
    double &front();
    const double& front() const;
    double &back();
    const double& back() const;
    double& operator[](size_t ind);
    const double& operator[](size_t ind) const;
    size_t size() const;
    bool empty() const;
    void erase(double value);
    void clear();
    void printList() const;
    bool findCycle() const;
    void removeCycle();
    ~ForwardList();
private:
    Node* head;
    size_t count;
};

