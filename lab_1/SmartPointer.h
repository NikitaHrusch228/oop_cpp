#ifndef SMARTPOINTER_H
#define SMARTPOINTER_H

#include <iostream>
#include <cstddef>
#include <type_traits>

// Основной шаблон класса
template<typename T>
class SmrtPtr {
public:
    T* ptr;
    size_t* refCount;

private:
    void release() {
        if (refCount && --(*refCount) == 0) {
            delete ptr;
            delete refCount;
        }
    }

public:
    SmrtPtr() : ptr(nullptr), refCount(nullptr) {};

    T& operator*() const { return *ptr; }
    T* operator->() const { return ptr; }
    T* get() const { return ptr; }

    explicit SmrtPtr(T* p) : ptr(p), refCount(p ? new size_t(1) : nullptr) {};

    ~SmrtPtr() { release(); }

    // Конструктор копирования с поддержкой подтипов
    // U - наследник T
    // Позволяет создавать SmrtPtr<T> из SmrtPtr<U>, если U является наследником T.
    template<typename U, typename = typename std::enable_if<std::is_base_of<T, U>::value>::type>
    SmrtPtr(const SmrtPtr<U>& other) : ptr(other.ptr), refCount(other.refCount) {
        if (refCount) {
            ++(*refCount);
        }
    }

    // Позволяет присваивать SmrtPtr<T> значению SmrtPtr<U>, если U наследуется от T.
    template<typename U, typename = typename std::enable_if<std::is_base_of<T, U>::value>::type>
    SmrtPtr& operator=(const SmrtPtr<U>& other) {
        if (static_cast<const void*>(this) != static_cast<const void*>(&other)) {
            release();
            ptr = other.ptr;
            refCount = other.refCount;
            if (refCount) {
                ++(*refCount);
            }
        }
        return *this;
    }

    // Базовый конструктор копирования
    SmrtPtr(const SmrtPtr& other) : ptr(other.ptr), refCount(other.refCount) {
        if (refCount) {
            ++(*refCount);
        }
    }

    // Базовый оператор присваивания
    SmrtPtr& operator=(const SmrtPtr& other) {
        if (this != &other) {
            release();
            ptr = other.ptr;
            refCount = other.refCount;
            if (refCount) {
                ++(*refCount);
            }
        }
        return *this;
    }
};

// Специализация для массивов
template<typename T>
class SmrtPtr<T[]> {
public:
    T* ptr;
    size_t* refCount;

private:
    void release() {
        if (refCount && --(*refCount) == 0) {
            delete[] ptr;
            delete refCount;
        }
    }

public:
    SmrtPtr() : ptr(nullptr), refCount(nullptr) {};

    T& operator[](size_t index) const { return ptr[index]; }
    T* get() const { return ptr; }

    explicit SmrtPtr(T* p) : ptr(p), refCount(p ? new size_t(1) : nullptr) {};

    ~SmrtPtr() { release(); }

    SmrtPtr(const SmrtPtr& other) : ptr(other.ptr), refCount(other.refCount) {
        if (refCount) {
            ++(*refCount);
        }
    }

    SmrtPtr& operator=(const SmrtPtr& other) {
        if (this != &other) {
            release();
            ptr = other.ptr;
            refCount = other.refCount;
            if (refCount) {
                ++(*refCount);
            }
        }
        return *this;
    }
};

#endif // SMARTPOINTER_H