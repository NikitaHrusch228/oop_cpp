#pragma once
// Аннотация:
// Тут реализуем интерфейс(абстрактный класс) для последовательностей.
// Взяли методы такие как:
//      Создание подпоследовательности из нулей заданной длины, получение подпоследовательности из последовательности по индексам
//      Получение элемента первого, последнего, по индексу, длины, Добавление элемента, вставка элемента по индексу, вывод элемента
//      Сортировка, применяемая к объекту - пузырёк, быстрая,шел
template<typename T>
class Sequence {
public:
    virtual Sequence<T> *CreateZeroSequence(int count) = 0;
    virtual Sequence<T> *GetSubsequence(int startIndex, int endIndex) = 0;
    virtual Sequence<T> *Concat(Sequence<T> *list) = 0;
    virtual Sequence<T> *Clone() = 0;
    virtual T &GetFirst() = 0;
    virtual T &GetLast() = 0;
    virtual T &Get(int index) = 0;
    virtual void BubbleSort(bool(*cmp)(const T &, const T &)) = 0;
    virtual void QuickSort(bool(*cmp1)(const T &, const T &), bool(*cmp2)(const T &, const T &)) = 0;
    virtual void ShellSort(bool(*cmp)(const T &, const T &)) = 0;
    virtual int GetLength() = 0;
    virtual void Append(T item) = 0;
    virtual void Prepend(T item) = 0;
    virtual void InsertAt(T item, int index) = 0;
    virtual void Print() = 0;
};


