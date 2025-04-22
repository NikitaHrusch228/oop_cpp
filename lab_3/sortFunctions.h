#pragma once

#include "sequence.h"
#include <ctime>

using namespace std;

template <class T>
bool asc(T a, T b)
{
    return a <= b;
}

template <class T>
bool desc(T a, T b)
{
    return a >= b;
}

template <class T>
bool isSorted(Sequence<T> *seq, bool (*compare)(T, T))
{
    int size = seq->getSize();
    if (size == 0 || size == 1) return true;
    for (int i = 0; i < size - 1; i++)
    {
        if (not compare(seq->get(i), seq->get(i + 1))) return false;
    }
    return true;
}

template <class T>
double getTimeSort(Sequence<T> *seq, void (*algSort)(Sequence<T>* seq, bool (*compare)(T, T)), bool (*compare)(T, T))
{
    clock_t start = clock();
    algSort(seq, compare);
    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    return seconds;
}
template <class T>
void bubbleSort(Sequence<T> *seq, bool (*compare)(T, T))
{
    if (seq->getSize() <= 1) return;
    int size = seq->getSize();
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            if(compare(seq->get(i), seq->get(j)))
            {
                T tmp = seq->get(i);
                seq->set(seq->get(j), i);
                seq->set(tmp, j);
            }
        }
    }
}

template <class T>
void _mergeSort_(Sequence<T> *seq, int l, int r, bool (*compare)(T,T))
{
    if (l < r)
    {
        int mid = (r + l) / 2;
        _mergeSort_(seq, l, mid, compare);
        _mergeSort_(seq, mid + 1, r, compare);
        _merge_(seq, l, r, compare);
    }
}

template <class T>
void _merge_(Sequence<T> *seq, int l, int r, bool (*compare)(T,T))
{
    int mid = (l + r) / 2;
    ArraySequence<T> *temp = new ArraySequence<T>(r - l + 1);
    int pos1 = l;
    int pos2 = mid + 1;
    int pos3 = 0;
    while (pos1 <= mid && pos2 <= r)
    {
        if(compare(seq->get(pos1), seq->get(pos2)))
        {
            temp->set(seq->get(pos1++),pos3++);
        }
        else
        {
            temp->set(seq->get(pos2++),pos3++);
        }
    }
    while (pos2 <= r)
    {
        temp->set(seq->get(pos2++), pos3++);
    }
    while (pos1 <= mid)
    {
        temp->set(seq->get(pos1++), pos3++);
    }
    for (pos3 = 0; pos3 < r - l + 1; pos3++)
    {
        seq->set(temp->get(pos3), l + pos3);
    }
    delete temp;
}

template <class T>
void mergeSort(Sequence<T> *seq, bool (*compare)(T, T))
{
    if (seq->getSize() <= 1) return;
    _mergeSort_(seq, 0, seq->getSize() - 1, compare);
}

template <class T>
void _quickSort_(Sequence<T> *seq, int l, int r, bool (*compare)(T,T))
{
    int pivot = seq->get(l);
    int lb = l;
    int rb = r;
    while (l < r)
    {
        while ((l < r) && (compare(pivot, seq->get(r))))
        {
            r--;
        }
        if (l != r)
        {
            seq->set(seq->get(r), l);
            l++;
        }
        while ((compare(seq->get(l), pivot)) && (l < r))
        {
            l++;
        }
        if (l != r)
        {
            seq->set(seq->get(l), r);
            r--;
        }
    }
    seq->set(pivot, l);
    pivot = l;
    l = lb;
    r = rb;
    if (l < pivot)
        _quickSort_(seq, l, pivot - 1, compare);
    if (r > pivot)
        _quickSort_(seq, pivot + 1, r, compare);
}

template <class T>
void quickSort(Sequence<T> *seq, bool (*compare)(T, T))
{
    if (seq->getSize() <= 1) return;
    _quickSort_(seq, 0, seq->getSize() - 1, compare);
}

template <class T>
void _shuffle_(Sequence<T> *seq)
{
    int size = seq->getSize();
    for (int i = 0; i < size; i++)
    {
        int index = rand() % size;
        T swap = seq->get(index);
        seq->set(seq->get(i), index);
        seq->set(swap, i);
    }
}

template <class T>
void bogoSort(Sequence<T> *seq, bool (*compare)(T, T))
{
    srand(time(0));
    while(not isSorted(seq, compare))
    {
        _shuffle_(seq);
    }
}