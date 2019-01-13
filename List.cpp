//
// Created by zhang on 2018/12/17.
//

#include "List.h"

template <typename T>
void List<T>::init()
{
    header = new ListNode<T>;
    trailer = new ListNode<T>;
    header->pred = NULL;
    header->succ = trailer;
    trailer->pred = header;
    trailer->succ = NULL;
    _size = 0;
}

template <typename T>
T& List<T>::operator[] (int r) const
{
    ListNode<T>* p = first();
    while (r > 0)
    {
        p = p->succ;
        r--;
    }
    return p->data;
}

/*
 * 在无序列表内节点p(可能是trailer)的n个前驱中，找到e的最后者
 */
template <typename T>
ListNode<T>* List<T>::find(const T &e, int n, ListNode<T> *p) const
{
    while (n > 0 && p != header)
    {
        p = p->pred;
        if (p->data == e)
            return p;
    }
    return NULL;
}

template <typename T>
void List<T>::copyNodes(ListNode<T> *p, int n)
{
    init();
    while (n > 0)
    {
        insertAsLast(p->data);
        p = p->succ;
        n--;
    }
}

template <typename T>
T List<T>::remove(ListNode<T> *p)
{
    T e = p->data;
    p->pred->succ = p->succ;
    p->succ->pred = p->pred;
    delete p;
    _size--;
    return e;
}

template <typename T>
int List<T>::clear()
{
    int oldSize = _size;
    while (_size > 0)
    {
        remove(header->succ);   //反复删除首节点，直至列表变空
    }
    return oldSize;
}

template <typename T>
int List<T>::deduplicate()
{
    if (_size <= 1)
    {
        return 0;
    }
    int oldSize = _size;
    ListNode<T>* p = first();
    int r = 0;
    while (p != trailer)
    {
        ListNode<T>* q = find(p->data, r, p);
        q ? remove(q) : r++;
        p = p->succ;
    }
    return oldSize - _size;
}

template <typename T>
int List<T>::uniquify()
{
    if (_size <= 1)
    {
        return 0;
    }
    int oldSize = _size;
    ListNode<T>* p = first();
    ListNode<T>* q = p->succ;
    while (q != trailer)
    {
        if (q->data != p->data)
        {
            p = q;
        }
        else
        {
            remove(q);
        }
        q = p->succ;
    }
    return oldSize - _size;
}

template <typename T>
ListNode<T>* List<T>::search(const T &e, int n, ListNode<T> *p) const
{
    while ( n-- >= 0 )
    {
        p = p->pred;
        if (p->data <= e)
        {
            break;
        }
    }
    return p;
}

template <typename ft>
std::ostream& operator<< (std::ostream& out, const List<ft>& L)
{
    if (L.empty())
    {
        out << "Empty List." << std::endl;
    }
    else
    {
        ListNode<ft>* p = L.first();
        for (int i = 0; i < L._size; ++i)
        {
            out << p->data << '\t';
            p = p->succ;
        }
    }
    out << '\n';
    return out;
}

template <typename T>
void List<T>::insertionSort(ListNode<T> *p, int n)
{
    for (int r = 0; r < n; ++r)
    {
        insertA( search(p->data, r, p), p->data );
        p = p->succ;
        remove(p->pred);
    }
}

template <typename T>
void List<T>::selectionSort(ListNode<T> *p, int n)
{
    ListNode<T>* head = p->pred;
    ListNode<T>* tail = p;
    for (int i = 0; i < n; ++i)
    {
        tail = tail->succ;
    }
    while (n > 1)
    {
        ListNode<T>* max = selectMax(head->succ, n);
        insertB( tail, remove(max) );
        tail = tail->pred;
        n--;
    }
}

template <typename T>
ListNode<T>* List<T>::selectMax(ListNode<T> *p, int n)
{
    ListNode<T>* max = p;
    for (ListNode<T>* curr = p->succ; n > 1; n--)
    {
        if (curr->data >= max->data)
        {
            max = curr;
        }
        curr = curr->succ;
    }
    return max;
}

template <typename T>
void List<T>::merge(ListNode<T>*& p, int n, List<T>& L, ListNode<T>* q, int m)
{
    ListNode<T>* pp = p->pred;
    while (m > 0)
    {
        if (n > 0 && (p->data <= q->data))
        {
            p = p->succ;
            if (q == p)
            {
                break;
            }
            n--;
        }
        else
        {
            q = q->succ;
            insertB( p, L.remove(q->pred) );
            m--;
        }
    }
    p = pp->succ;
}

template <typename T>
void List<T>::mergeSort(ListNode<T> *& p, int n)
{
    if (n <= 1)  return;
    int m = n / 2;
    ListNode<T>* q = p;
    for (int i = 0; i < m; ++i)
    {
        q = q->succ;
    }
    mergeSort(p, m);
    mergeSort(q, n - m);
    merge(p, m, *this, q, n - m);
}

template <typename T>
void List<T>::reverse()
{
    ListNode<T>* p = header;
    while (p)
    {
        swapPredSucc(p->pred, p->succ);
        p = p->pred;
    }
    swapPredSucc(header, trailer);
}

