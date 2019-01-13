//
// Created by zhang on 2018/12/17.
//

#ifndef LIST_LISTNODE_H
#define LIST_LISTNODE_H

#include <iostream>
//#define NULL 0
template <typename T>
class ListNode
{
public:
    T data;
    ListNode<T>* pred;
    ListNode<T>* succ;

public:
    ListNode()
    {
        pred = NULL;
        succ = NULL;
    }
    explicit ListNode(T e, ListNode<T>* p = NULL, ListNode<T>* s = NULL)
    {
        data = e;
        pred = p;
        succ = s;
    }
    ListNode<T>* insertAsPred(T const& e)
    {
        auto* x = new ListNode(e, pred, this);
        pred->succ = x;
        pred = x;
        return x;
    }
    ListNode<T>* insertAsSucc(T const& e)
    {
        auto* x = new ListNode(e, this, succ);
        succ->pred = x;
        succ = x;
        return x;
    }
};


#endif //LIST_LISTNODE_H
