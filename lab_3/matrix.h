#pragma once

#include "Sequence.h"
#include <math.h>

#define NUMBER_OF_ROWS_IS_NOT_EQAL "number of rows is not equal"
#define NUMBER_OF_COLUMNS_IS_NOT_EQAL "number of columns is not equal"
#define NEGATIVE_SIZE_MESSAGE "size is negative"
#define IMPOSSIBLE_TO_MULTIPLY_BECAUSE_OF_SIZE "impossible to multiply because of size"

using namespace std;

template <class T> class Matrix
{
private:

	Sequence<Sequence<T>*>* elements;
	int rows = 0;
	int columns = 0;

public:
	Matrix() = default;
	Matrix(const int rows, const int columns)
	{
		if (rows < 0)
		{
			throw out_of_range(NEGATIVE_SIZE_MESSAGE);
		}
		if (columns < 0)
		{
			throw out_of_range(NEGATIVE_SIZE_MESSAGE);
		}
		if (rows == 0 || columns == 0)
		{
			rows = columns = 0;
		}
		this.rows = rows;
		this.columns = columns;
		this->elements = (Sequence<Sequence<T>*>*) new ListSequence<ListSequence<T>*>;
		for (int i = 0; i < rows; i++)
		{
			this->elements->append(new ListSequence<T>(this->columns));
		}
	}
	~Matrix() = default;
	Matrix operator+(const Matrix<T>& two)
	{
		if (this->rows != two.rows)
		{
			throw std::invalid_argument(NUMBER_OF_ROWS_IS_NOT_EQAL);
		}
		if (this->columns != two.columns)
		{
			throw std::invalid_argument(NUMBER_OF_COLUMNS_IS_NOT_EQAL);
		}
		Matrix result(this->rows, this->columns);
		for (int i = 0; i < this->rows; i++)
		{
			for (int j = 0; j < this->columns; j++)
			{
				result->Set(this->get(i, j) + two->get(i, j), i, j);
			}
		}
		return result;
	}
	Matrix operator=(const Matrix<T>& matr)
	{
		this->rows = matr.rows;
		this->columns = matr.columns;
		for (int i = 0; i < this->rows; i++)
		{
			for (int j = 0; j < this->columns; j++)
			{
				this->elements->set(matr.elements->get(i, j), i, j);
			}
		}
	}
	Matrix multiply(const T scalar)
	{
		for (int i = 0; i < this->rows; i++)
		{
			for (int j = 0; j < this->columns; j++)
			{
				this->Set(scalar*this->Get(i, j), i, j);
			}
		}
		return *this;
	}
	int GetNorm()
	{
		int norm = 0;
		for (int i = 0; i < this->rows; i++)
		{
			int sum = 0;
			for (int j = 0; j < this->columns; j++)
			{
				sum = sum + (int)abs(this->elements->get(i)->get(j))*(int)abs(this->elements->get(i)->get(j));
			}
			norm = norm + sum;
		}
		return norm;
	}
	int GetRows()
	{
		return this->rows;
	}
	int GetColumns()
	{
		return this->columns;
	}
	T Get(const int i, const int j)
	{
		if (i < 0 || i >= this->rows || j < 0 || j >= this->columns) throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);

		return elements->get(i).get(j);
	}
	void Set(T element, int i, int j)
	{
		if (i < 0 || i >= this->rows || j < 0 || j >= this->columns) throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);

		this->elements->get(i)->set(element, j);
	}
	void Show()
	{
		for (int i = 0; i < this->rows; i++)
		{
			for (int j = 0; j < this->columns; j++)
			{
				T el = this->elements->get(i)->get(j);
				cout << el << " ";
			}
			cout << endl;
		}
	}
	Matrix operator*(const Matrix<T>& two)
	{
		if (this->columns != two.rows)
		{
			throw std::invalid_argument(IMPOSSIBLE_TO_MULTIPLY_BECAUSE_OF_SIZE);
		}
		Matrix result(this->columns, two.columns);
		for (int i = 0; i < this->rows; i++)
		{
			for (int j = 0; j < two.columns; j++)
			{
				T sum = 0;
				for (int k = 0; k < this->columns; k++)
				{
					sum = sum + (T)(this.Get(i, k)) + (T)(two.get(k, j));
				}
				result.Set(sum, i, j);
			}
		}
		return result;
	}
};