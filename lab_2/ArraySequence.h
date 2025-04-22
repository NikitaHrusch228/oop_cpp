#pragma once

#include "Sequences.h"
#include "ISorter.h"
#include "LinkedList.h"
#include "DynamicArray.h"

template<typename T>
class ArraySequence : public Sequence<T> {
public:


    ArraySequence() : data() {}

    ArraySequence<T> *Clone() override { return new ArraySequence<T>(); }

    ArraySequence<T> *CreateZeroSequence(int count) override {
        return new ArraySequence<T>(count);
    }

    ArraySequence(int count) : data(count) {}

    ArraySequence(T *item, int count) : data(item, count) {}

    ArraySequence(ArraySequence<T> &array) : data(array.data) {}

    ArraySequence(LinkedList<T> &list) {//копиконструктор для параметра LinkedList
        T *items;
        items = (T *) malloc(sizeof(T) * (list.GetLength()));
        for (int i = 0; i < list.GetLength(); ++i) {
            items[i] = list.Get(i);
        }
        data = DynamicArray<T>(items, list.GetLength());
    }

    int GetLength() {
        return data.GetSize();
    }

    T &Get(int index) {
        return data.Get(index);
    }

    T &GetFirst() {
        return data.Get(0);
    }

    T &GetLast() {
        return data.Get(data.GetSize() - 1);
    }

    void Append(T item) {
        data.Append(item);
    }

    void Prepend(T item) {
        data.Prepend(item);
    }

    void InsertAt(T item, int index) {//void Set(int index,T value)
        if (index >= data.GetSize() || index < 0)
            throw "\nInsertAt Message : Index Out Of Range";
        data.Resize(data.GetSize() + 1);
        for (int i = data.GetSize() - 2; i >= index; --i) {
            data.Set(i + 1, data.Get(i));
        }
        data.Set(index, item);
    }

    void Print() {
        data.Print();
    }

    ArraySequence<T> *GetSubsequence(int startIndex, int endIndex) {
        T *items = (T *) malloc(sizeof(T) * (endIndex - startIndex));
        for (int i = startIndex; i < endIndex; ++i) {
            items[i - startIndex] = data.Get(i);
        }
        ArraySequence<T> *result = new ArraySequence<T>(items, endIndex - startIndex);
        return result;
    }

    ArraySequence<T> *Concat(Sequence<T> *list) {
        if (list->GetLength() != 0) {
            T *items = (T *) malloc(sizeof(T) * (data.GetSize() + list->GetLength()));
            for (int i = 0; i < data.GetSize(); ++i) {
                items[i] = data.Get(i);
            }
            for (int i = 0; i < list->GetLength(); ++i) {
                items[i + data.GetSize()] = list->Get(i);
            }
            ArraySequence<T> *result = new ArraySequence<T>(items, data.GetSize() + list->GetLength());

            return result;
        } else {
            ArraySequence<T> *result = new ArraySequence<T>(*this);
            return result;
        }

    }

    void BubbleSort(bool(*cmp)(const T &, const T &)) override {
        IBubbleSort<T> obj;
        obj.Sort(cmp, this);
    }

    void QuickSort(bool(*cmp1)(const T &, const T &), bool(*cmp2)(const T &, const T &)) override {
        IQuickSort<T> obj;
        obj.Sort(cmp1, this, cmp2);
    }

    void ShellSort(bool(*cmp)(const T &, const T &)) override {
        IShellSort<T> obj;
        obj.Sort(cmp, this);
    }

private:
    DynamicArray<T> data;

};