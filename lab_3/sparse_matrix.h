#pragma once
#include "dictionary.h"
#include "matrix.h"
#include "sortFunctions.h"
#include <string>


template<class T1, class T2>
class Pair
{
private:
    T1 elem1;
    T2 elem2;
public:
    Pair() = default;
    Pair(T1 elem1, T2 elem2)
    {
        this->elem1 = elem1;
        this->elem2 = elem2;
    }
    ~Pair() = default;
    T1 getFirst() const
    {
        return this->elem1;
    }
    T2 getSecond() const
    {
        return this->elem2;
    }
    void setFirst(T1 elem1)
    {
        this->elem1 = elem1;
    }
    void setSecond(T2 elem2)
    {
        this->elem2 = elem2;
    }
    bool operator<(const Pair another)
    {
        if (this->elem1 != another.elem1)
            return this->elem1 < another.elem1;
        else return this->elem2 < another.elem2;
    }
    bool operator>(const Pair another)
    {
        if (this->elem1 != another.elem1)
            return this->elem1 > another.elem1;
        else return this->elem2 > another.elem2;
    }
    bool operator<=(const Pair another)
    {
        if (this->elem1 == another.elem1)
            return this->elem2 <= another.elem2;
        else return this->elem1 <= another.elem1;
    }
    bool operator>=(const Pair another)
    {
        if (this->elem1 == another.elem1)
            return this->elem2 >= another.elem2;
        return this->elem1 >= another.elem1;
    }
    bool operator!=(const Pair another)
    {
        if (this->elem1 != another.elem1)
            return this->elem2 != another.elem2;
        else return false;
    }
    bool operator==(const Pair another)
    {
        if (this->elem1 == another.elem1)
            return this->elem2 == another.elem2;
        else return false;
    }
};
template <class T1, class T2>
std::ostream& operator<< (std::ostream &out, const Pair<T1, T2> pair)
{
    return out << "(" << pair.getFirst() << "; " << pair.getSecond() << ")";
}

template <class T>
class SparseMatrix
{
private:
    Dictionary<Pair<int, int>, T> *dict;
    int rows = 0;
    int columns = 0;
public:
    SparseMatrix(Matrix<T> m)
    {
        this->rows = m.GetRows();
        this->columns = m.GetColumns();
        this->dict = new Dictionary<Pair<int, int>, T>(Pair<int,int>(0,0), m.Get(0,0), asc);
        for (int i = 0; i < m.GetRows(); i++)
        {
            for (int j = 0; j < m.GetColumns(); i++)
            {
                this->set(i, j, m.Get(i, j));
            }
        }
    }
    SparseMatrix(int rows, int columns)
    {
        this->rows = rows;
        this->columns = columns;
        this->dict = new Dictionary<Pair<int, int>, T>(Pair<int,int>(0,0), (T)0, asc);
    }
    ~SparseMatrix() = default;
    void set(int x, int y, T value)
    {
        this->set(Pair<int, int>(x,y), value);
    }
    void set(Pair<int, int> pair, T value)
    {
        if (pair.getFirst() >= this->rows or pair.getSecond() >= this->columns)
        {
            throw std::out_of_range("OUT OF RANGE");
        }
        if (value != (T)0)
            this->dict->add(pair, value);
        else this->setToZero(pair);
    }
    void setToZero(int x, int y)
    {
        this->setToZero(Pair<int, int>(x,y));
    }
    void setToZero(Pair<int, int> pair)
    {
        if (pair.getFirst() >= this->rows or pair.getSecond() >= this->columns)
        {
            throw std::out_of_range("OUT OF RANGE");
        }
        if (this->isNotZero(pair)) this->dict->remove(pair);
    }
    bool isNotZero(int x, int y)
    {
        return this->isNotZero(Pair<int,int>(x,y));
    }
    bool isNotZero(Pair<int, int> pair)
    {
        return this->dict->containsKey(pair);
    }
    T get(int x, int y)
    {
        return this->get(Pair<int,int>(x,y));
    }
    T get (Pair<int,int> pair)
    {
        if (pair.getFirst() >= this->rows or pair.getSecond() >= this->columns)
        {
            throw std::out_of_range("OUT OF RANGE");
        }
        if (this->isNotZero(pair))
        {
            return this->dict->get(pair);
        } else return (T)0;
    }
    int getAmountOfNonZero()
    {
        return dict->getCount();
    }
    int getRows()
    {
        return this->rows;
    }
    int getColumns()
    {
        return this->columns;
    }
    void setRows(int a)
    {
        this->rows = a;
    }
    void setColumns(int a)
    {
        this->columns = a;
    }
    void printAsDict()
    {
        this->dict->print();
    }
    void printAsMatrix()
    {
        for (int i = 0; i < this->rows; i++)
        {
            for (int j = 0; j < this->columns; j++)
            {
                cout << this->get(i,j) << " ";
            }
            cout << endl;
        }
    }
    Matrix<T> getMatrix()
    {
        Matrix<T> result = new Matrix<T>(this->getRows(), this->getColumns());
        for (int i = 0; i < this->getRows(); i++)
        {
            for (int j = 0; j < this->getColumns(); j++)
            {
                result.Set(this->get(i, j), i, j);
            }
        }
        return result;
    }
};
