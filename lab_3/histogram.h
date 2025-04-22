#pragma once

#include "person.h"
#include "sequence.h"
#include "dictionary.h"

using namespace std;

class Histogram
{
private:

    Dictionary<int, int>* dict;
    int (Person::*getParam)();

public:
    Histogram(ArraySequence<Person> seq, int (Person::*getParam)(), int n)
    {
        int min = (seq.get(0).*getParam)();
        int max = (seq.get(0).*getParam)();

        for (int i = 1; i < seq.getSize(); i++)
        {
            if ((seq.get(i).*getParam)() < min)
            {
                min = (seq.get(i).*getParam)();
            }
            if ((seq.get(i).*getParam)() > max)
                max = (seq.get(i).*getParam)();
        }
        int dif = (max - min) / n;
        while (dif == 0)
        {
            n--;
            dif = (max - min) / n;
        }
        dict = new Dictionary<int, int>(min, 0, asc);
        for (int i = 1; i < n; i++)
        {
            dict->add((min + dif*i), 0);
        }
        int j = 0;
        int amount = 0;
        for (int i = 0; i < seq.getSize(); i++)
        {
            j = (((seq.get(i).*getParam)() - min)  / dif);
            if (j == n) j--;
            amount = dict->get((min + j * dif));
            dict->changeElem((min + j * dif), amount + 1);
        }
        this->getParam = getParam;
    }
    ~Histogram()
    {
        delete dict;
    }
    int getInfo(int subset)
    {
        return this->dict->get(subset);
    }
    int getAmountOfSubsets()
    {
        return this->dict->getCount();
    }
    void print()
    {
        dict->print();
    }
};
