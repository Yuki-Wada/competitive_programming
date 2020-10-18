#ifndef __DATA_STRUCTURE_HPP__
#define __DATA_STRUCTURE_HPP__ 0

//include
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

#define MAX_VALUE 9223372036854775807LL

class UnionFindTree
{
private:
	const unsigned elemCount_;
	vector<unsigned> parentNodeNumbers_;
	vector<unsigned> treeDepths_;
	vector<unsigned> setSizes_;

	// Average Computational Complexity: O(log(elemCount_))) 
	unsigned getRootNode(unsigned x)
	{
		if (parentNodeNumbers_[x] == x)
		{
			return x;
		}
		else
		{
			return getRootNode(parentNodeNumbers_[x]);
		}
	}

public:
	UnionFindTree(unsigned elemCount) :
		elemCount_(elemCount),
		parentNodeNumbers_(elemCount),
		treeDepths_(elemCount, 0),
		setSizes_(elemCount, 1)
	{
		for (unsigned i = 0; i < parentNodeNumbers_.size(); ++i)
		{
			parentNodeNumbers_[i] = i;
		}
	}

	// Average Computational Complexity: O(log(elemCount_))) 
	void uniteSet(unsigned x, unsigned y)
	{
		x = getRootNode(x);
		y = getRootNode(y);
		if (x == y)
		{
			return;
		}

		if (treeDepths_[x] < treeDepths_[y])
		{
			parentNodeNumbers_[x] = y;
			setSizes_[y] = setSizes_[x] + setSizes_[y];
		}
		else
		{
			parentNodeNumbers_[y] = x;
			setSizes_[x] = setSizes_[x] + setSizes_[y];
			if (treeDepths_[x] == treeDepths_[y])
			{
				++treeDepths_[x];
			}
		}
	}

	unsigned getSetSize(unsigned x)
	{
		return setSizes_[getRootNode(x)];
	}

	// Average Computational Complexity: O(log(elemCount_))) 
	bool includedInSameSet(unsigned x, unsigned y)
	{
		return getRootNode(x) == getRootNode(y);
	}
};

template<class Integer>
class BinaryIndexedTree
{
private:
	ull maxSize_;
	vector<Integer> values_;
public:
	BinaryIndexedTree(ull maxSize) : maxSize_(maxSize), values_(maxSize_, 0) {}

	void update(ll index, Integer increment)
	{
		if (maxSize_ <= index)
		{
			throw invalid_argument("Index should be less than maxSize.");
		}
		++index;

		while (index <= maxSize_)
		{
			values_[index - 1] += increment;
			index += index & -index;
		}
	}

	Integer query(ll index)
	{
		if (index < 0LL) return 0; 
		if (maxSize_ <= index)
		{
			throw invalid_argument("Index should be less than maxSize.");
		}
		++index;

		Integer res = 0;
		while (index > 0)
		{
			res += values_[index - 1];
			index -= index & -index;
		}
		return res;
	}
};
using BIT = BinaryIndexedTree<ll>;

template <class Integer, class Operator> class SegmentTree;
template <class Integer, class Operator>
std::ostream& operator<<(std::ostream& lhs, const SegmentTree<Integer, Operator>& rhs);

template<class Integer, class Operator>
class SegmentTree
{
private:
	ull maxSize_;
	vector<Integer> values_;
	Operator op;

	Integer _query(ll start, ll end, ll searchStart, ll searchEnd, ll node) const
	{
		if (searchEnd <= start || end <= searchStart)
		{
			return op.default_value;
		}
		if (start <= searchStart && searchEnd <= end)
		{
			return values_[node];
		}

		return op.Execute(
			_query(start, end, searchStart, (searchStart + searchEnd) / 2, node * 2 + 1),
			_query(start, end, (searchStart + searchEnd) / 2, searchEnd, node * 2 + 2)
		);
	}

public:
	SegmentTree(ull maxSize) : maxSize_(1)
	{
		while (maxSize_ < maxSize)
		{
			maxSize_ *= 2;
		}
		values_ = vector<Integer>(ll(maxSize_) * 2 - 1, op.default_value);
	}

	void update(ll index, Integer value)
	{
		if (index >= maxSize_)
		{
			throw invalid_argument("Index should be less than maxSize.");
		}
		index += maxSize_ - 1;
		values_[index] = value;
		while (index > 0)
		{
			index = (index - 1) / 2;
			values_[index] = op.Execute(values_[2 * index + 1], values_[index * 2 + 2]);
		}
	}

	Integer query(ll start, ll end) const
	{
		if (start < 0)
		{
			throw invalid_argument("Start should be non-negative.");
		}
		if (maxSize_ < end)
		{
			throw invalid_argument("End should be less than or equal to maxSize.");
		}
		if (start >= end)
		{
			throw invalid_argument("End should be more than start.");
		}

		return _query(start, end, 0, maxSize_, 0);
	}
	friend std::ostream& operator<< <>(std::ostream& lhs, const SegmentTree& rhs);
};

template <class Integer, class Operator>
std::ostream& operator<<(std::ostream& lhs, const SegmentTree<Integer, Operator>& rhs)
{
	for (ull i = 0; i < rhs.maxSize_; ++i) {
		lhs << rhs.query(i, i + 1ULL);
		if (i + 1 < rhs.maxSize_) lhs << " ";
		else lhs << endl;
	}
	return lhs;
}

struct MinOp {
	const static ll default_value;
	static ll Execute(const ll& a, const ll& b) { return min(a, b); };
};

const ll MinOp::default_value = MAX_VALUE;

using RMQ = SegmentTree<ll, MinOp>;

template<class Integer, class Monoid, class OperatorII, class OperatorIM, class OperatorMM>
class SegmentTreeWithLazyPropagation {
private:
	ull maxSize_;
	vector<Integer> data_;
	vector<Monoid> lazy_;
	OperatorII op_ii_;
	OperatorIM op_im_;
	OperatorMM op_mm_;

	void _lazy_propagate(ll k) {
		if (lazy_[k] == op_mm_.default_value) return;
		if (k < maxSize_ - 1) {
			lazy_[k * 2 + 1] = op_mm_.Execute(lazy_[k * 2 + 1], lazy_[k]);
            lazy_[k * 2 + 2] = op_mm_.Execute(lazy_[k * 2 + 2], lazy_[k]);
        }
        data_[k] = op_im_.Execute(data_[k], lazy_[k]);
        lazy_[k] = op_mm_.default_value;
	}

	Integer _query(ll start, ll end, ll searchStart, ll searchEnd, ll node)
	{
		_lazy_propagate(node);
		if (searchEnd <= start || end <= searchStart) return op_ii_.default_value;
		if (start <= searchStart && searchEnd <= end) return data_[node];

		return op_ii_.Execute(
			_query(start, end, searchStart, (searchStart + searchEnd) / 2, node * 2 + 1),
			_query(start, end, (searchStart + searchEnd) / 2, searchEnd, node * 2 + 2)
		);
	}

	void _update(ll start, ll end, Monoid value, ll searchStart, ll searchEnd, ll node)
	{
		_lazy_propagate(node);
		if (start <= searchStart && searchEnd <= end) {
			lazy_[node] = op_mm_.Execute(lazy_[node], value);
			_lazy_propagate(node);
		}
		else if (searchStart < end && start < searchEnd) {
			_update(start, end, value, searchStart, (searchStart + searchEnd) / 2, node * 2 + 1);
			_update(start, end, value, (searchStart + searchEnd) / 2, searchEnd, node * 2 + 2);
			data_[node] = op_ii_.Execute(data_[node * 2 + 1], data_[node * 2 + 2]);
		}
	}

public:
	ull size() {return maxSize_;}
	SegmentTreeWithLazyPropagation(ull maxSize) : maxSize_(1) {
		while (maxSize_ < maxSize) maxSize_ *= 2;
		data_ = vector<Integer>(ll(maxSize_) * 2 - 1, op_ii_.default_value);
		lazy_ = vector<Monoid>(ll(maxSize_) * 2 - 1, op_mm_.default_value);
	}

	void update(ll start, ll end, Monoid value)
	{
		if (start < 0) throw invalid_argument("Start should be non-negative.");
		if (maxSize_ < end) throw invalid_argument("End should be less than or equal to maxSize.");
		if (start >= end) throw invalid_argument("End should be more than start.");

		return _update(start, end, value, 0, maxSize_, 0);
	}

	void update(ll index, Integer value)
	{
		if (index >= maxSize_)
		{
			throw invalid_argument("Index should be less than maxSize.");
		}
		index += maxSize_ - 1;
		data_[index] = value;
		while (index > 0)
		{
			index = (index - 1) / 2;
			data_[index] = op_ii_.Execute(data_[2 * index + 1], data_[index * 2 + 2]);
		}
	}

	Integer query(ll start, ll end)
	{
		if (start < 0) throw invalid_argument("Start should be non-negative.");
		if (maxSize_ < end) throw invalid_argument("End should be less than or equal to maxSize.");
		if (start >= end) throw invalid_argument("End should be more than start.");

		return _query(start, end, 0, maxSize_, 0);
	}
};

using RMQLP = SegmentTreeWithLazyPropagation<ll, ll, MinOp, MinOp, MinOp>;

#endif