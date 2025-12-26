// include
//------------------------------------------
#include <string>
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
#include <cstring>
#include <ctime>

// namespace
using namespace std;

// temporary
#include <atcoder/all>
using namespace atcoder;

// print
#define RET(x) return cout << x << endl, 0;

// for loop
#define REP(i, a, b) for ((i) = (ll)(a); (i) < (ll)(b); (i)++)
#define REPD(i, a, b) for (ll i = (ll)(a); (i) < (ll)(b); (i)++)
#define REPI(v, vs) for (auto &v : vs)

// debug
#ifdef LOCAL_ENV
#define DUMP(x) cerr << #x << " = " << (x) << endl
#define DEBUG(x) cerr << #x << " = " << (x) << " (l" << __LINE__ << ")" \
					  << " " << __FILE__ << endl
#else
#define DUMP(x)
#define DEBUG(x)
#endif

#define MAX_VALUE 9223372036854775807LL

// type alias
using ll = long long;
using ull = unsigned long long;
using comp = complex<double>;
using llpair = pair<ll, ll>;
template <class T>
using vector2d = vector<vector<T>>;
template <class T>
using vector3d = vector<vector<vector<T>>>;
using ll1d = vector<ll>;
using ll2d = vector2d<ll>;
using ll3d = vector3d<ll>;

// constant
static constexpr ll MOD = 998244353LL;
static constexpr double PI = 3.14159265358979323846;

template <ull N, class T, class... Args, std::enable_if_t<N == 0, int> = 0>
auto make_multiple_vector(Args... args)
{
	return T(args...);
}

template <ull N, class T, class... Args, std::enable_if_t<N != 0, int> = 0>
auto make_multiple_vector(ull size, Args... args)
{
	using value_type = std::decay_t<decltype(make_multiple_vector<N - 1LL, T>(args...))>;
	return vector<value_type>(size, make_multiple_vector<N - 1LL, T>(args...));
}

template <class Integer, class Operator>
class SegmentTree;
template <class Integer, class Operator>
std::ostream &operator<<(std::ostream &lhs, const SegmentTree<Integer, Operator> &rhs);

template <class Integer, class Operator>
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
			_query(start, end, (searchStart + searchEnd) / 2, searchEnd, node * 2 + 2));
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
		if (start > end)
		{
			throw invalid_argument("End should be more than or equal to start.");
		}

		return _query(start, end, 0, maxSize_, 0);
	}
	friend std::ostream &operator<< <>(std::ostream &lhs, const SegmentTree &rhs);
};

template <class Integer, class Operator>
std::ostream &operator<<(std::ostream &lhs, const SegmentTree<Integer, Operator> &rhs)
{
	for (ull i = 0; i < rhs.maxSize_; ++i)
	{
		lhs << rhs.query(i, i + 1ULL);
		if (i + 1 < rhs.maxSize_)
			lhs << " ";
		else
			lhs << endl;
	}
	return lhs;
}

struct MinOp
{
	const static ll default_value;
	static ll Execute(const ll &a, const ll &b) { return min(a, b); };
};

const ll MinOp::default_value = MAX_VALUE;

using RMQ = SegmentTree<ll, MinOp>;

ll solve()
{
	ll n;
	cin >> n;

	ll1d p(1LL << n);
	RMQ rmq(1LL << n);
	REPD(i, 0, 1LL << n)
	{
		cin >> p[i];
		rmq.update(i, p[i]);
	}
	ll1d diff(1LL << n);
	REPD(i, 0, n)
	{
		ll block = 1LL << i;
		for (ll j = 0; j < (1LL << n); j += block * 2LL)
		{
			auto left = j;
			auto mid = left + block;
			auto right = mid + block;
			auto left_min = rmq.query(left, mid);
			auto right_min = rmq.query(mid, right);
			if (left_min > right_min)
			{
				diff[left] += block;
				diff[mid] -= block * 2LL;
				diff[right] += block;
			}
		}
	}

	ll1d pos(1LL << n, 0LL);
	ll sum = 0LL;
	REPD(i, 0, 1LL << n)
	{
		sum += diff[i];
		pos[i] = sum + i;
	}

	ll1d res(1LL << n);
	REPD(i, 0, 1LL << n)
	{
			res[pos[i]] = p[i];
	}

	REPD(i, 0, 1LL << n)
	{
		cout << res[i];
		if (i + 1LL < (1LL << n))
		{
			cout << " ";
		}
		else
		{
			cout << endl;
		}
	}

	return 0;
}

// main function
int main()
{
	cin.tie(0);
	ios::sync_with_stdio(false);

	// solve();

	ll t;
	cin >> t;

	REPD(i, 0, t)
	{
		solve();
	}

	return 0;
}
