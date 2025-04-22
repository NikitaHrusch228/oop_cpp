#pragma once

#include "binary_tree.h"

#define NO_ELEMENT "NO ELEMENT WITH GIVEN KEY"

template<class TKey, class TElement>
class PairKE
{
private:
    TKey key;
    TElement element;
public:
    PairKE() = default;
    PairKE(TKey key, TElement element)
    {
        this->key = key;
        this->element = element;
    }
    ~PairKE() = default;
    TElement getElem() const
    {
        return this->element;
    }
    TKey getKey() const
    {
        return this->key;
    }
    void setKey(TKey key)
    {
        this->key = key;
    }
    void setElem(TElement elem)
    {
        this->element = elem;
    }
    bool operator<(const PairKE another)
    {
        return this->key < another.key;
    }
    bool operator>(const PairKE another)
    {
        return this->key > another.key;
    }
    bool operator<=(const PairKE another)
    {
        return this->key <= another.key;
    }
    bool operator>=(const PairKE another)
    {
        return this->key >= another.key;
    }
    bool operator!=(const PairKE another)
    {
        return this->key != another.key;
    }
    bool operator==(const PairKE another)
    {
        return this->key == another.key;
    }
};
template <class TKey, class TElement>
std::ostream& operator<< (std::ostream &out, const PairKE<TKey, TElement> pair)
{
    return out << "<" << pair.getKey() << ", " << pair.getElem() << ">";
}

template <class TKey, class TElement>
class Dictionary
{
protected:

    BinaryTree<PairKE<TKey,  TElement>>* dict;

public:
    Dictionary(const TKey key, const TElement elem, bool (*cmp)(PairKE<TKey, TElement>, PairKE<TKey, TElement>))
    {
        PairKE<TKey, TElement> spair = PairKE<TKey, TElement>(key, elem);
        this->dict = new BinaryTree<PairKE<TKey, TElement>>(spair, cmp);
    }
    ~Dictionary() = default;
    int getCount()
    {
        return this->dict->getSize();
    }
    TElement get(TKey key)
    {
        PairKE<TKey, TElement> spair = PairKE<TKey, TElement>();
        spair.setKey(key);
        if(this->dict->exist(spair))
        {
            return this->dict->getElem(dict->search(spair)).getElem();
        }
        throw std::out_of_range(NO_ELEMENT);
    }
    bool containsKey(TKey key)
    {
        PairKE<TKey, TElement> spair = PairKE<TKey, TElement>();
        spair.setKey(key);
        return this->dict->exist(spair);
    }
    void add(TKey key, TElement element)
    {
        PairKE<TKey, TElement> spair = PairKE<TKey, TElement>(key, element);
        if(this->dict->exist(spair))
        {
            return;
        }
        this->dict->add(spair);
    }
    void remove(TKey key)
    {
        PairKE<TKey, TElement> spair = PairKE<TKey, TElement>();
        spair.setKey(key);
        if(this->dict->exist(spair))
        {
            this->dict->erase(spair);
            return;
        }
        throw std::out_of_range(NO_ELEMENT);
    }
    void print()
    {
        this->dict->printAll();
    }
    void showDFS()
    {
        this->dict->showDFS();
    }
    string toString()
    {
        return this->dict->toString();
    }
    void changeElem(TKey key, TElement elem)
    {
        PairKE<TKey, TElement> pair = PairKE<TKey, TElement>(key, elem);
        this->dict->setElem(this->dict->search(pair), pair);
    }
};