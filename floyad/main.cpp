#include <iostream>
#include "forwardList.h"

int main()
{
    ForwardList list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);
    list.push_back(5);
    list.push_back(6);
    list.printList();
    if (list.findCycle())
    {
        std::cout << "Найден цикл!" << std::endl;
    }
    else
    {
        std::cout << "Цикл не найден!" << std::endl;
    }
    ForwardList::Node* node1 = new ForwardList::Node(1);
    ForwardList::Node* node2 = new ForwardList::Node(2);
    ForwardList::Node* node3 = new ForwardList::Node(3);
    ForwardList::Node* node4 = new ForwardList::Node(4);
    ForwardList::Node* node5 = new ForwardList::Node(5);
    ForwardList::Node* node6 = new ForwardList::Node(6);
    ForwardList::Node* node7 = new ForwardList::Node(7);
    node1->next = node2;
    node2->next = node3;
    node3->next = node4;
    node4->next = node5;
    node5->next = node6;
    node6->next = node7;
    node7->next = node4;
    ForwardList list2(node1);
    if (list2.findCycle())
    {
        std::cout << "Найден цикл!" << std::endl;
    }
    else
    {
        std::cout << "Цикл не найден!" << std::endl;
    }
    return 0;
}