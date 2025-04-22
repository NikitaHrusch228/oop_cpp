#include <iostream>
#include "SmartPointer.h"
#include "DynamicArray.h"

// Простая структура для теста
struct Point {
    int x, y;
    void print() const { std::cout << "Point(" << x << ", " << y << ")\n"; }
};

class Base {
public:
    virtual ~Base() {}
    virtual void print() const { std::cout << "Base\n"; }
};

class Derived : public Base {
public:
    void print() const override { std::cout << "Derived\n"; }
};

// Проверка базовых обращений, разыменовывания и т.п.
void testBasic(){
    std :: cout << "\n=== Basic Test ===" << std :: endl;
    SmrtPtr<int> ptr1(new int(42));
    std :: cout << "*ptr1 == " << *ptr1 << std :: endl;
    std :: cout << "ptr1.get == " << ptr1.get() << std :: endl;

    SmrtPtr<Point> ptr2(new Point{10,20});
    std :: cout << "ptr2->x == " << ptr2->x << std :: endl;
    ptr2->y = 30;
    ptr2->print();
}

// Проверка функционала с "иерархией"
void testCopyConstrustor(){
    std :: cout << "\n=== CopyConstructor Test ===" << std :: endl;
    SmrtPtr<int> ptr1(new int(43));
    SmrtPtr<int> ptr2 = ptr1;

    std :: cout << "*ptr1 = " << *ptr1 << ", *ptr2 = " << *ptr2 << std :: endl;
    std :: cout << "ptr1 refCount = " << *ptr1.refCount << std :: endl;
}
// Проверка функционала с присваиванием
void testAssigment(){
    std :: cout << "\n=== Assigment Test ===" << std :: endl;
    SmrtPtr<int> ptr1(new int(43));
    SmrtPtr<int> ptr2(new int(45));

    ptr2 = ptr1;

    std :: cout << "*ptr1 = " << *ptr1 << ", *ptr2 = " << *ptr2 << std :: endl;
    std :: cout << "ptr1 refCount = " << *ptr1.refCount << std :: endl;
}
// Проверка функционала с самоприсваиванием
void testSelfAssigment(){
    std :: cout << "\n=== Self Assigment Test ===" << std :: endl;
    SmrtPtr<int> ptr1(new int(43));
    std :: cout << "*ptr1 = " << *ptr1 << std :: endl;
    std :: cout << "ptr1 refCount =" << *ptr1.refCount << std :: endl;
    ptr1 = ptr1;
    std :: cout << "*ptr1 = " << *ptr1 << std :: endl;
    std :: cout << "ptr1 refCount = " << *ptr1.refCount << std :: endl;
}

// Проверка выделения памяти в области видимости
void testMemoryRelease(){
    std :: cout << "\n=== Memory release test ===" << std :: endl;
    {
        SmrtPtr<int> ptr1(new int(70));
        {
            SmrtPtr<int> ptr2 = ptr1;
            std::cout << "Inside inner scope: refCount = " << *ptr1.refCount << std::endl;
        }
        std::cout << "After inner scope: refCount = " << *ptr1.refCount << std::endl;
    }
    std::cout << "After outer scope: memory should be freed" << std::endl;
}

void testConstructor() {
    std::cout << "\n=== Constructor Test ===" << std::endl;

    // Тест 1: Создание с реальным указателем
    int* rawInt = new int(42);
    SmrtPtr<int> ptr1(rawInt);
    std::cout << "*ptr1 = " << *ptr1 << " (expected: 42)" << std::endl;
    std::cout << "ptr1.get() = " << ptr1.get() << " (expected: " << rawInt << ")" << std::endl;
    std::cout << "refCount = " << (ptr1.get() ? *ptr1.refCount : 0) << " (expected: 1)" << std::endl;

    // Тест 2: Создание с nullptr
    SmrtPtr<int> ptr2(nullptr);
    std::cout << "ptr2.get() = " << ptr2.get() << " (expected: 0)" << std::endl;
    std::cout << "ptr2.refCount = " << ptr2.refCount << " (expected: 0)" << std::endl;
}

void testSubtyping() {
    std::cout << "\n=== Subtyping Test ===" << std::endl;

    SmrtPtr<Derived> derivedPtr(new Derived());
    SmrtPtr<Base> basePtr(derivedPtr);  // Явное преобразование

    basePtr->print();  // Выведет: Derived
}

void testDynamicArray() {
    std::cout << "\n=== DynamicArray Test ===" << std::endl;

    DynamicArray<int> arr;
    arr.push_back(10);
    arr.push_back(20);
    arr.push_back(30);

    std::cout << "Array elements: ";
    for (size_t i = 0; i < arr.getSize(); ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

int main(){
    testBasic();
    testCopyConstrustor();
    testAssigment();
    testSelfAssigment();
    testMemoryRelease();
    testConstructor();
    testSubtyping();
    testDynamicArray(); 
    return 0;
}