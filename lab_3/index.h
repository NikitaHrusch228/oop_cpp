#pragma once

#include <string>
#include "dictionary.h"
#include "sequence.h"
#include "sortFunctions.h"
#include "person.h"

using namespace std;

template <class T>
class IndexDictionary
{
private:

    Dictionary<T, Person> *dict;
    T (Person::*getParam)();

public:
    IndexDictionary(ArraySequence<Person> seq, T (Person::*getParam)())
    {
        this->getParam = getParam;
        bool (*cmp)(PairKE<T, Person>, PairKE<T, Person>) = asc;
        dict = new Dictionary<T, Person>((seq.get(0).*getParam)(), seq.get(0), cmp);
        for(int i = 1; i < seq.getSize(); i++)
        {
            dict->add((seq.get(i).*getParam)(), seq.get(i));
        }
    }
    ~IndexDictionary() = default;
    Person get(T index)
    {
        return this->dict->get(index);
    }
    int getCount()
    {
        return this->dict->getCount();
    }
    string toString()
    {
        return this->dict->toString();
    }
    void print()
    {
        this->dict->print();
    }
    bool contains(T index)
    {
        return this->dict->containsKey(index);
    }
};