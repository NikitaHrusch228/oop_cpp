#pragma once

#include "binary_tree.h"

template <class T>
class Set
{
private:

	BinaryTree<T>* set;

public:
	Set(const T elem, bool (*cmp)(T, T))
	{
		this->set = new BinaryTree<T>(elem, cmp);
	}
	Set(const Set<T> &set)
    {
	    this->set = new BinaryTree<T>(set);
    }
	~Set() = default;
	void add(const T elem)
	{
		if(this->exist(elem) == true)
		{
			return;
		}
		this->set->add(elem);
	}
	bool exist(const T elem) const
	{
		return this->set->exist(elem);
	}
	void erase(const T elem)
	{
		if(this->exist(elem) == true)
		{
			this->set->erase(elem);
		}
	}
	void show() const
	{
		this->set->printAll();
	}
	int getSize()
	{
		return this->set->getSize();
	}
};