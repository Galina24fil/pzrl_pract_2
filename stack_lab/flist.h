#pragma once
#include <iostream>



class ForwardList
{
private:
    struct Node {
        double data;
        Node* next;
	Node(double val, Node* nxt = nullptr)
        : data(val), next(nxt) {}
    };
    Node* head;
    size_t count;
public:
    ForwardList();
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
    ~ForwardList();
};

