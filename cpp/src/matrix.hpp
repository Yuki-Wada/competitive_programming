#ifndef __MATRIX_HPP__
#define __MATRIX_HPP__

// include
//------------------------------------------
#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <complex>

#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cctype>
#include <string>
#include <cstring>
#include <ctime>

#include <stdexcept>

using namespace std;

// type alias
using ll = long long;
using ull = unsigned long long;
using comp = complex<double>;

template <class Integer, unsigned int row, unsigned int col>
class Matrix
{
protected:
	vector<Integer> values_;

public:
	Matrix() : values_(row * col) {}

	ull get_row_size() const
	{
		return row;
	}

	ull get_col_size() const
	{
		return col;
	}

	Integer &operator()(ull rowIndex, ull colIndex)
	{
		return values_[rowIndex * col + colIndex];
	}

	const Integer &operator()(ull rowIndex, ull colIndex) const
	{
		return values_[rowIndex * col + colIndex];
	}
};

template <class Integer, unsigned int row, unsigned int col>
inline Matrix<Integer, row, col> operator+(
	const Matrix<Integer, row, col> &lhs,
	const Matrix<Integer, row, col> &rhs)
{
	Matrix<Integer, row, col> res;
	for (ll i = 0; i < row; ++i)
		for (ll j = 0; j < col; ++j)
			res(i, j) = lhs(i, j) + rhs(i, j);

	return res;
}

template <class Integer, unsigned int row, unsigned int col>
inline Matrix<Integer, row, col> operator-(
	const Matrix<Integer, row, col> &lhs,
	const Matrix<Integer, row, col> &rhs)
{
	Matrix<Integer, row, col> res;
	for (ll i = 0; i < row; ++i)
		for (ll j = 0; j < col; ++j)
			res(i, j) = lhs(i, j) - rhs(i, j);

	return res;
}

template <class Integer, unsigned int row, unsigned int mid, unsigned int col>
inline Matrix<Integer, row, col> operator*(
	const Matrix<Integer, row, mid> &lhs,
	const Matrix<Integer, mid, col> &rhs)
{
	Matrix<Integer, row, col> res;
	for (ll i = 0; i < row; ++i)
		for (ll j = 0; j < col; ++j)
			for (ll k = 0; k < mid; ++k)
				res(i, j) += lhs(i, k) * rhs(k, j);

	return res;
}

template <class Integer, unsigned int row, unsigned int col>
inline Matrix<Integer, row, col> operator*(const Matrix<Integer, row, col> &lhs, Integer a)
{
	Matrix<Integer, row, col> res;
	for (ll i = 0; i < row; ++i)
		for (ll j = 0; j < col; ++j)
			res(i, j) += lhs(i, j) * a;

	return res;
}

template <class Integer, unsigned int row, unsigned int col>
inline Matrix<Integer, row, col> operator*(Integer a, const Matrix<Integer, row, col> &rhs)
{
	Matrix<Integer, row, col> res;
	for (ll i = 0; i < row; ++i)
		for (ll j = 0; j < col; ++j)
			res(i, j) += a * rhs(i, j);

	return res;
}

template <class Integer, unsigned int row, unsigned int col>
std::ostream &operator<<(std::ostream &lhs, const Matrix<Integer, row, col> &rhs)
{
	for (ll i = 0; i < rhs.get_row_size(); ++i)
	{
		if (i == 0)
			lhs << "[";
		else
			lhs << " ";

		lhs << "[";
		for (ll j = 0; j < rhs.get_col_size(); ++j)
		{
			lhs << rhs(i, j);
			if (j + 1 < rhs.get_col_size())
				lhs << ", ";
		}

		if (i + 1 < rhs.get_row_size())
			lhs << "]," << endl;
		else
			lhs << "]]";
	}
	return lhs;
}

template <class Integer, unsigned int order>
class SquareMatrix : public Matrix<Integer, order, order>
{
public:
	SquareMatrix() : Matrix<Integer, order, order>() {}
	SquareMatrix(Matrix<Integer, order, order> &&m) : Matrix<Integer, order, order>(m) {}
	SquareMatrix(Integer a) : Matrix<Integer, order, order>()
	{
		for (unsigned int i = 0; i < order; ++i)
			(*this)(i, i) = a;
	}

	ull get_order() const
	{
		return order;
	}

	Integer trace() const
	{
		Integer result = 0;
		for (unsigned int i = 0; i < order; ++i)
			result = result + (*this)(i, i);

		return result;
	}
};

#endif
