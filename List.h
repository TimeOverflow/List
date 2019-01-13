//
// Created by zhang on 2018/12/17.
//

#ifndef LIST_LIST_H
#define LIST_LIST_H

#include "ListNode.h"
#include <iostream>
#include <cstdlib>

template <typename T>
class List
{
private:
    int _size;
    ListNode<T>* header;
    ListNode<T>* trailer;

protected:
    void init();
    int clear();
    void copyNodes(ListNode<T>* p, int n);     //复制列表中自位置p起始的n项
    void merge(ListNode<T>* &, int, List<T>&, ListNode<T>*, int);
    void mergeSort(ListNode<T>* &, int);
    void selectionSort(ListNode<T>* p, int n);
    void insertionSort(ListNode<T>* p, int n);

public:
    List()
    {
        init();
    }
    List ( List<T> const& L )                 //整体复制列表
    {
        copyNodes(L.first(), L._size);
    }
    List ( List<T> const& L, int r, int n )  //复制列表中自第r项开始的n项
    {
        ListNode<T>* p = first();
        for (int i = 0; i < r; ++i)
        {
            p = p->succ;
        }
        copyNodes(p, n);
    }
    List ( ListNode<T>* p, int n )           //复制列表中自p起的n项
    {
        copyNodes(p, n);
    }

    //deconstructor
    ~List()
    {
        clear();
        delete header;
        delete trailer;
    }


    //read-only
    int size() const
    {
        return _size;
    }
    bool empty() const
    {
        return _size <= 0;
    }

    T& operator[] (int r) const;

    ListNode<T>* first() const
    {
        return header->succ;
    }
    ListNode<T>* last() const
    {
        return trailer->pred;
    }

    bool valid(ListNode<T>* p)           //判断p对外是否合法
    {
        return p && p != header && p != trailer;
    }
    //int disorded() const ;

    ListNode<T>* find(T const& e, int n, ListNode<T>* p) const;   //无序列表区间查找
    ListNode<T>* find(T const& e) const                           //无序列表整体查找
    {
        return find(e, _size, trailer);
    }

    ListNode<T>* search(T const& e, int n, ListNode<T>* p) const;
    ListNode<T>* search(T const& e) const
    {
        return search(e, _size, trailer);
    }

    ListNode<T>* selectMax(ListNode<T>* p, int n);     //在p及其n - 1个后继中选出最大者
    ListNode<T>* selectMax()
    {
        return selectMax(header->succ, _size);
    }

    //可写访问接口
    ListNode<T>* insertAsFirst ( T const& e ) //将e当作首节点插入
    {
        _size++;
        return header->insertAsSucc(e);
    }
    ListNode<T>* insertAsLast ( T const& e ) //将e当作末节点插入
    {
        _size++;
        return trailer->insertAsPred(e);
    }
    ListNode<T>* insertA ( ListNode<T>* p, T const& e ) //将e当作p的后继插入
    {
        _size++;
        return p->insertAsSucc(e);
    }
    ListNode<T>* insertB ( ListNode<T>* p, T const& e ) //将e当作p的前驱插入
    {
        _size++;
        return p->insertAsPred(e);
    }
    T remove ( ListNode<T>* p ); //删除合法位置p处的节点,返回被删除节点
    void merge ( List<T>& L ) { merge ( first(), _size, L, L.first(), L._size ); } //全列表归并
    void sort ( ListNode<T>* p, int n ) //列表区间排序
    {

        switch (rand() % 3)
        {
            case 1:
                selectionSort(p, n);
                break;
            case 2:
                insertionSort(p, n);
                break;
            default:
                mergeSort(p, n);
                break;
        }

        //mergeSort(p, n);
    }
    void sort()
    {
        sort ( first(), _size );
    } //列表整体排序
    int deduplicate(); //无序去重
    int uniquify(); //有序去重
    void swapPredSucc(ListNode<T>* & p, ListNode<T>* & s)
    {
        ListNode<T>* tmp = p;
        p = s;
        s = tmp;
    }
    void reverse(); //前后倒置（习题）

    // 遍历
    //void traverse ( void (* ) ( T& ) ); //遍历，依次实施visit操作（函数指针，只读或局部性修改）
    //template <typename VST> //操作器
    //void traverse ( VST& ); //遍历，依次实施visit操作（函数对象，可全局性修改）

    template <typename ft>
    friend std::ostream& operator<< (std::ostream& out, const List<ft>& L);

};

#endif //LIST_LIST_H
