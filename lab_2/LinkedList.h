#pragma once
// Аннотация:
// 
#include <iostream>
#include "Node.h"

// Структура класса 
template<typename T>
class LinkedList {
// Хоть где 
public:
// Обёртки методов 
// Объявление что такие методы есть без конкретной реализации
    LinkedList();

    LinkedList(int count);

    LinkedList(T *items, int count);

    LinkedList(const LinkedList<T> &LinkedList);

    ~LinkedList();

    int GetLength() { return Size; }

    T &GetLast();

    T &GetFirst();

    T &Get(int index);

    void Swap(int i, int j);

    LinkedList<T> *GetSubLinkedList(int startIndex, int endIndex);

    LinkedList<T> *Concat(LinkedList<T> *LinkedList);

    void Append(T data);
    void Prepend(T data);

    void pop_front();

    void pop_back();

    void print_from_end();

    void print_from_begin();

    void InsertAt(T data, int index);

    void RemoveAt(int index);

    void clear();

    T &operator[](const int index);

// Могут вызывать только методы класса 
private:
    int Size;
    Node<T> *head;
    Node<T> *tail;

};

template<typename T>
void LinkedList<T>::Swap(int i, int j) {//в данном случае всегда i >= j
    Node<T> *first = this->Get_Elem(i);
    Node<T> *second = first;
    for (int k = 0; k < i - j; ++k) {
        second = second->pPrev;
    }
    //Node<T>* second = this->Get_Elem(j);
    T tmp = **first;
    **first = **second;
    **second = tmp;
}

// Деструктор
// Последовательно удаляем все элементы начиная с головы 
template<typename T>
LinkedList<T>::~LinkedList() {
    while (Size) {
        pop_front(); // Удаление первого элемента
    }
}

// Объявление метода линкендлистового
// Заполнение нулями
template<typename T>
LinkedList<T>::LinkedList(int count) {
    Size = 0;
    head = nullptr;
    for (int i = 0; i < count; ++i) {
        Append(0);
    }
}

// Объявление метода линкендлистового
// Создание линкед листа размера 0 с пустым указателем на голову
template<typename T>
LinkedList<T>::LinkedList() {
    Size = 0;
    head = nullptr;
}

// Объявление метода линкендлистового
//считывание значений из переданного массива
template<typename T>
LinkedList<T>::LinkedList(T *items, int count) {
    if (items == nullptr) {
        Size = 0;
        head = nullptr;
    } else {
        // Инициализируем пустой список и заполняем
        Size = 0;
        this->head = nullptr;
        this->tail = nullptr;
        for (int i = 0; i < count; ++i) {
            Append(items[i]);
        }
    }
}

// Объявление метода линкендлистового
// Создаёт копию переданного списка
template<typename T>
LinkedList<T>::LinkedList(const LinkedList <T> &list) {
    Size = 0;
    this->head = nullptr;
    Node<T> *current = list.head;
    for (int i = 0; i < list.Size; ++i) {
        this->Append(current->data);
        current = current->pNext;
    }

}

// Объявление метода линкендлистового
// Создаёт новый линкедлист, который добавляет все элементы list в this
template<typename T>
LinkedList<T> *LinkedList<T>::Concat(LinkedList<T> *list) {
    this->tail->pNext = list->head;
    list->head->pPrev = this->tail;
    this->tail = list->tail;
    Size += list->Size;

    return this;
}

// Объявление метода линкендлистового
// Получаем элемент по индексу
template<typename T>
T &LinkedList<T>::Get(int index) {
    if (index < 0 || index >= Size)
        throw "\nGet Message : Index Out Of Range\n";

    Node<T> *current;

    if (index < Size / 2) {
        current = head;
        for (int i = 0; i < index; ++i) {
            current = current->pNext;
        }
    } else {
        current = tail;
        for (int i = 0; i < Size - index - 1; ++i) {
            current = current->pPrev;
        }
    }
    return current->data;

}

// Объявление метода линкендлистового
// Получаем первый элемент по индексу
template<typename T>
T &LinkedList<T>::GetFirst() {
    if (Size == 0)
        throw "\nGetFirst Message : Index Out Of Range\n";
    return Get(0);
}

// Объявление метода линкендлистового
// Получаем последний элемент по индексу
template<typename T>
T &LinkedList<T>::GetLast() {
    if (Size == 0)
        throw "\nGetLast Message : Index Out Of Range\n";
    return Get(Size - 1);
}

// Объявление метода линкендлистового
// Получаем подлист из листа 
template<typename T>
LinkedList<T> *LinkedList<T>::GetSubLinkedList(int startIndex, int endIndex) {
    if (startIndex < 0 || endIndex < 0 || startIndex >= Size || endIndex >= Size)
        throw "\nGetSubLinkedList Message : Index Out Of Range\n";
    std::cout << "\nGetSubLinkedList\n";
    Node<T> *current = this->head;
    for (int i = 0; i < startIndex; ++i) {
        current = current->pNext;
    }
    T *items;
    // Выделяем память под элементы подлиста
    items = (T *) malloc(sizeof(T *) * (endIndex - startIndex));
    for (int i = 0; i < endIndex - startIndex; ++i) {
        items[i] = current->data;
        current = current->pNext;
    }

    LinkedList<T> *result = new LinkedList<T>(items, endIndex - startIndex);
    delete[] items;
    return result;

}

// Объявление метода линкендлистового
// Выводим балду с конца разделяя пробелами
template<typename T>
void LinkedList<T>::print_from_end() {
    std::cout << std::endl;
    Node<T> *tmp = this->tail;
    if (Size == 1)
        std::cout << tail->data << " ";
    else {
        while (tmp != nullptr) {
            std::cout << tmp->data << " ";
            tmp = tmp->pPrev;
        }
    }
}

// Объявление метода линкендлистового
// Выводим балду с начала разделяя пробелами
template<typename T>
void LinkedList<T>::print_from_begin() {
    if (head != nullptr) {
        Node<T> *tmp = this->head;
        if (Size == 1)
            std::cout << head->data << std::endl;
        else {
            while (tmp != nullptr) {
                std::cout << tmp->data << ' ';
                tmp = tmp->pNext;
            }
        }
    }
    std::cout << std::endl;
}

// Объявление метода линкендлистового
// Добавление элемента в конец, пробегаемся до конца и тыкаем туда
template<typename T>
void LinkedList<T>::Append(T data) {
    if (head == nullptr) {//если только один элемент,то заполняем head
        head = new Node<T>(data);
        this->tail = head;
    } else {//если больше,то добавляем и присваиваем tail этот элемент
        Node<T> *current = this->head;//временная переменная
        Node<T> *tmp;//для двусторонней связи между узлами
        while (current->pNext != nullptr) {
            tmp = current;
            current = current->pNext;
            current->pPrev = tmp;
        }

        this->tail = new Node<T>(data, current, current->pNext);//вставка между current и nullptr
        current->pNext = tail;//перенаправление бывшего tail
    }

    ++Size;
}

// Объявление метода линкендлистового
// Добавление элемента в начало
template<typename T>
void LinkedList<T>::Prepend(T data) {
    if (head == nullptr) {
        head = new Node<T>(data);
        this->tail = head;
    } else {
        Node<T> *one_more = new Node<T>(data, head->pPrev,
                                        head);//создание нового узла(следующий - head,предыдущего нет)
        head->pPrev = one_more;
        this->head = one_more;
        Node<T> *current = head;//обновление tail и установка связи между узлами
        while (current->pNext != nullptr) {
            current = current->pNext;
        }
        this->tail = current;
    }
    Size++;
}

// Объявление метода линкендлистового
// Удаление элемента в начале
template<typename T>
void LinkedList<T>::pop_front() {
    if (Size == 1) {
        delete[] tail;
        Size--;
    } else {
        Node<T> *tmp = head;//запоминаем ссылку,по которой находится текущий head
        head = head->pNext;//сдвиг head к концу на один элемент
        head->pPrev = nullptr;//"обнуление" указателя на предыдущий элемент
        delete[] tmp;//удаление старого head
        Size--;
    }

}

// Объявление метода линкендлистового
// Удаление элемента в конце
template<typename T>
void LinkedList<T>::pop_back() {
    if (Size != 1) {
        Node<T> *tmp = tail;
        tail = tail->pPrev;
        tail->pNext = nullptr;
        delete[] tmp;
    } else {
        delete[] tail;
        head = nullptr;
        tail = nullptr;
    }
    Size--;

}

// Объявление метода линкендлистового
// Вставка элемента дата в указанный индекс
template<typename T>
//усовершенствован для двусвязного списка
void LinkedList<T>::InsertAt(T data, int index) {
    if (index < 0 || index >= Size)
        throw "\nInsertAt Message : Index Out Of Range\n";
    Node<T> *previous;
    Node<T> *new_elem;
    Node<T> *tmp;
    //std::cout << "\nInsertAt data = " << data << " index = " << index << "\n";
    if (index <= Size / 2) {//идём сначала
        if (index == 0)
            Prepend(data);
        previous = head;
        for (int i = 0; i < index - 1; ++i) {
            previous = previous->pNext;
        }
    } else {//идём с конца

        previous = tail;
        for (int i = 0; i < Size - index; ++i) {
            previous = previous->pPrev;
        }
    }
    tmp = previous->pNext;//запоминаем адрес следующего узла
    new_elem = new Node<T>(data, previous, previous->pNext);//создаем новый узел
    previous->pNext = new_elem;//обновляем указатель на следующий узел у предыдущего
    tmp->pPrev = new_elem;//обновляем указатель на предыдущий узел у следующего

    Size++;
}

template<typename T>
// Объявление метода линкендлистового
// Удаление элемента дата из указанного индекса
void LinkedList<T>::RemoveAt(int index) {
    if (index < 0 || index >= Size)
        throw "removeAt Message : Index Out Of Range\n";
    std::cout << "\nremoveAt index = " << index << "\n";
    if (index == 0)
        pop_front();
    else {
        if (index == Size - 1)
            pop_back();
        else {
            Node<T> *previous;
            Node<T> *toDelete;
            if (index <= Size / 2) {
                previous = head;
                for (int i = 0; i < index - 1; ++i) {
                    previous = previous->pNext;
                }
            } else {
                previous = tail;
                for (int i = 0; i < Size - index; ++i) {
                    previous = previous->pPrev;
                }
            }

            toDelete = previous->pNext;//запоминаем ссылку на удаляемый узел
            previous->pNext = toDelete->pNext;//изменяем поле следующего узла у идущего перед удаляемым
            toDelete->pNext->pPrev = previous;//изменяем поле предыдущего узла у идущего после удаляемого

            delete[] toDelete;//очистка памяти по ссылке удаляемого узла
        }
        Size--;
    }
}

// Объявление метода линкендлистового
// Ищем элемент по индексу
template<typename T>
//усовершенствован для двусвязного списка
T &LinkedList<T>::operator[](const int index) {//перегрузка оператора []
    //для нахождения элемента с номером index
    int counter;
    Node<T> *current;
    if (index <= Size / 2) {//идём с начала
        counter = 0;
        current = this->head;
        while (current != nullptr) {
            if (counter == index) {
                return current->data;
            }
            current = current->pNext;
            counter++;
        }
    } else {//идём с конца
        counter = Size - 1;
        current = this->tail;
        while (current != nullptr) {
            if (counter == index) {
                return current->data;
            }
            current = current->pPrev;
            counter--;
        }
    }
}


