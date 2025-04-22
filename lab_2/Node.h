#pragma once
// Аннотация
// Тут реализуем класс ячейки
// Хотим реализовать функционал для обращения к элементу
// Создаём 3 поля - указатель на предыдущий объект, указатель на следующий элемент, дата в ячейке
// Добавляем перегрузку операторов на разыменовывание, сравнение узлов с нулевым состоянием, сравнение узлов по дате, вывод в поток
 
#include <tuple>
#include <iostream>
template<typename T>
class Node {
public:

    Node *pNext;
    Node *pPrev;

    T data;

    Node(T data = T(), Node *pPrev = nullptr, Node *pNext = nullptr) {
        this->data = data;
        this->pPrev = pPrev;
        this->pNext = pNext;
    }
// Разыменовывание
    T &operator*() {
        return data;
    }
};

// Сравниваем два узла: разные если pNext или pPrev не равны nullptr и дата не равна 0
template<typename T>
bool operator!=(Node<T> &lhs, Node<T> &rhs) {
    return std::make_tuple(lhs.pNext, lhs.pPrev, lhs.data) != std::make_tuple(nullptr, nullptr, 0);
}

// Позволяет выводить узел в поток, выводим только data
template<typename T>
std::ostream &operator<<(std::ostream &output, const Node<T> &node) {
    return output << node.data;
}
// Сравнивает узлы по их данным (data), возвращаем true если левый больше правого
template<typename T>
bool operator<=(Node<T> &lhs, Node<T> &rhs) {
    return lhs.data <= rhs.data;
}
