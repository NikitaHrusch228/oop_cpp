#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include "SmartPointer.h"
#include <iostream>
#include <stdexcept>

template <typename T>
class DynamicArray {
private:
    SmrtPtr<T[]> data;
    size_t size; // Количество элементов массива
    size_t capacity; // Текущий размер выделенной памяти

public:
// По умолчанию
    DynamicArray() : size(0), capacity(1) {
        data = SmrtPtr<T[]>(new T[capacity]);
    }
    // Добавляет элемент в конец массива, стандартная реализация умножением на 2 количества памяти, аналогичное вектору
    void push_back(const T& value) {
        if (size >= capacity) {
            resize(capacity * 2);
        }
        data[size++] = value;
    }
    // Если индекс для обращения больше чем количество элементов массива, то выкидываем предупреждение или выдаём элемент
    T& operator[](size_t index) { // Разрешаем изменять значение
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    const T& operator[](size_t index) const { // Запрещаем изменять значнеие
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    size_t getSize() const { return size; }
    size_t getCapacity() const { return capacity; }

private:
    void resize(size_t newCapacity) {
        SmrtPtr<T[]> newData(new T[newCapacity]);
        for (size_t i = 0; i < size; ++i) {
            newData[i] = data[i];
        }
        data = newData;
        capacity = newCapacity;
    }
};

#endif // DYNAMICARRAY_H