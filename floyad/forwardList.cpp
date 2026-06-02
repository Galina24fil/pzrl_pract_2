#include "forwardList.h"

ForwardList::ForwardList()
: head(nullptr), count(0) {}


void ForwardList::push_front(double value) 
{
    Node* newNode = new Node(value, head);
    head = newNode;
    count++;
}

void ForwardList::push_back(double value)
{
    Node* newNode = new Node(value);
    if (empty())
    {
	    head = newNode;
    }
    else
    {
	    Node* curr = head;
	    while (curr->next != nullptr)
	    {
	        curr = curr->next;
	    }
	    curr->next = newNode;
    }
    count++;
}

void ForwardList::pop_front()
{
    if (empty())
    {
	    return;
    }
    Node* temp = head;
    head = head->next;
    delete temp;
    count--;
}

void ForwardList::pop_back()
{
    if (empty())
    {
        return;
    }
    if (head->next == nullptr)
    {
        delete head;
	    head = nullptr;
    }
    else
    {
	    Node* curr = head;
	    while (curr->next->next != nullptr)
	    {
	        curr = curr->next;
	    }
	    delete curr->next;
	    curr->next = nullptr;
    }
    count--;
}

double& ForwardList::front()
{
    if (empty())
    {
        throw std::runtime_error("Empty");
    }
    return head->data;
}

const double& ForwardList::front() const
{
    if (empty())
    {
	    throw std::runtime_error("empty");
    }
    return head->data;
}

double& ForwardList::back()
{
    if (empty())
    {
	    throw std::runtime_error("Empty");
    }
    Node* curr = head;
    while (curr->next != nullptr)
    {
	    curr = curr->next;
    }
    return curr->data;
}

const double& ForwardList::back() const
{
    if (empty())
    {
	    throw std::runtime_error("empty");
    }
    Node* curr = head;
    while (curr->next != nullptr)
    {
	    curr = curr->next;
    }
    return curr->data;
}

double& ForwardList::operator[](size_t ind)
{
    if (ind >= count)
    {
	    throw std::runtime_error("out of range");
    }
    Node* curr = head;
    for (size_t i = 0; i < ind; i++)
    {
	    curr = curr->next;
    }
    return curr->data;
}

const double& ForwardList::operator[](size_t ind) const
{
    if (ind >= count)
    {
	    throw std::runtime_error("out of range");
    }
    Node* curr = head;
    for (size_t i = 0; i < ind; i++)
    {
	    curr = curr->next;
    }
    return curr->data;
}

size_t ForwardList::size() const
{
    return count;
}

bool ForwardList::empty() const 
{
    return head == nullptr;
}

void ForwardList::erase(double value)
{
    if (empty()) 
    {
	    return;
    }
    while (head != nullptr && head->data == value)
    {
        pop_front();
    }
    if (empty()) return;
    Node* curr = head;
    while (curr->next != nullptr)
    {
        if (curr->next->data == value)
	    {
            Node* temp = curr->next;
	        curr->next = temp->next;
	        delete temp;
	        count--;
	    }
	    else 
	    {
	        curr = curr->next;
	    }
    }
}


void ForwardList::clear() 
{
    while (!empty()) 
    {
        pop_front();
    }
}


bool ForwardList::findCycle() const 
{
    if (!head || !head->next)
    {
        return false;
    }
    
    Node* turtle = head;
    Node* hare = head;
    
    while (hare && hare->next) 
    {
        turtle = turtle->next;
        hare = hare->next->next;
        
        if (turtle == hare) 
        {
            return true;
        }
    }
    return false;
}

void ForwardList::printList() const 
{
    if (head == nullptr) 
    {
        std::cout << "No elements in ForwardList!" << std::endl;
        return;
    }
    Node* curr = head;
    while (curr) 
    {
        std::cout << curr->data << " ";
        curr = curr->next;
    }
    std::cout << std::endl;
    return;
}

void ForwardList::removeCycle() 
{
    if (!findCycle()) return;
    Node* turtle = head;
    Node* hare = head;
    while (turtle != hare)
    {
        turtle = turtle->next;
        hare = hare->next->next;
    }
    turtle = head;
    while (turtle->next != hare->next) 
    {
        turtle = turtle->next;
        hare = hare->next;
    }
    hare->next = nullptr;
}

ForwardList::~ForwardList()
{
    removeCycle();
    Node* cur = head;
    while (cur) 
    {
        Node* next = cur->next;
        delete cur;
        cur = next;
    }
}