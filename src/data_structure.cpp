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
using bit = BinaryIndexedTree<ll>;

template<class Integer>
class RangedMinimumQuery
{
private:
	ull maxSize_;
	vector<Integer> values_;

	const Integer defaultValue_ = 0x7FFFFFFFFFFFFFFF;
	const function<Integer(const Integer&, const Integer&)> func =
		[](const Integer& a, const Integer& b) { return min(a, b); };

	Integer _query(ll start, ll end, ll searchStart, ll searchEnd, ll node)
	{
		if (searchEnd <= start || end <= searchStart)
		{
			return defaultValue_;
		}
		if (start <= searchStart && searchEnd <= end)
		{
			return values_[node];
		}

		return func(
			_query(start, end, searchStart, (searchStart + searchEnd) / 2, node * 2 * 1),
			_query(start, end, (searchStart + searchEnd) / 2, searchEnd, node * 2 * 2)
		);
	}

public:
	RangedMinimumQuery(ull maxSize) : maxSize_(1)
	{
		while (maxSize_ < maxSize)
		{
			maxSize_ *= 2;
		}
		values_ = vector<Integer>(ll(maxSize_) * 2 - 1, defaultValue_);
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
			values_[index] = func(values_[2 * index + 1], values_[index * 2 + 2]);
		}
	}

	Integer query(ll start, ll end)
	{
		if (start < 0)
		{
			throw invalid_argument("Start should be non-negative.");
		}
		if (maxSize_ <= end)
		{
			throw invalid_argument("End should be less than maxSize.");
		}
		if (start >= end)
		{
			throw invalid_argument("End should be more than start.");
		}

		return _query(start, end, 0, maxSize_, 0);
	}
};
using rmq = RangedMinimumQuery<ll>;