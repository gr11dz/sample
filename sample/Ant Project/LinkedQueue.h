#pragma once
#include <iostream>
using namespace std;

template <typename Type>
class Node
{
    public:
        Type data;
        Node<Type>* next;

        Node(Type const DATA): data(DATA), next(nullptr){} 
};

//I wrote this linear linkedlist in a way that its always a queue,
//it always inserts at the last node and it always deletes the first node.
template <typename Type>
class LinkedList
{
    private:
        Node<Type>* root;
        Node<Type>* first;
        Node<Type>* last;

        Node<Type>* createNode(Type const DATA)
        {
            return new Node<Type>(DATA);
        }
        
        void deleteFirst()
        {
            if (!first || !root)
                return;
            
            if (first == last)
                first = last = nullptr;
            else
                first = first->next;

            delete root;
            root = first;
        }

        void deletebyPointer(Node<Type>* lastNode)
        {
            if (lastNode->next == last)
            {
                last = lastNode;
                last->next = nullptr;
            }else
            {
                lastNode->next = lastNode->next->next;
            }
        }

    public:
        LinkedList(): root(nullptr), first(nullptr), last(nullptr){}

        void push_back(Type const DATA)
        {
            if (!root)
            {
                root = createNode(DATA);
                first = root;
                last = root;
            }else
            {
                last->next = createNode(DATA);
                last = last->next;
            }
        }

        Type popFirst()
        {
            Type value = first->data;
            deleteFirst();
            return value;
        }

        void printAll()
        {
            if (!first || !root)
                return;

            Node<Type>* iter;
            for(iter = first; iter; iter = iter->next)
            {
                cout << iter->data << ' ';
            }
            cout << endl;
        }

        bool is_empty()
        {
            if (!root || (!first && !last))
                return true;
            return false;
        }

        bool checkValue(Type value)
        {
            if (!root || (!first && !first))
                return false;
            
            if (first->data == value)
            {
                popFirst();
                return false;
            }

            Node<Type>* iter;
            for(iter = first; iter->next; iter = iter->next)
            {
                if (iter->next->data == value)
                {
                    deletebyPointer(iter);
                    return false;
                }
            }
            return true;
        }

};