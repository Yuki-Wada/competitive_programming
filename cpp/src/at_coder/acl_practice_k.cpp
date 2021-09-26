//include
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

// type alias
using ll = long long;
using ull = unsigned long long;
using comp = complex<double>;

// constant
// static const ll MOD = 1000000007LL;
static const ll MOD = 998244353LL;
// static const ll MOD = (1LL << 61LL) - 1LL;
static const double PI = 3.14159265358979323846;

// conversion
inline ll toint(string s)
{
	ll v;
	istringstream sin(s);
	sin >> v;
	return v;
}
template <class t>
inline string tostring(t x)
{
	ostringstream sout;
	sout << x;
	return sout.str();
}

// print
#define RET(x) return cout << x << endl, 0;

// for loop
#define REP(i, a, b) for ((i) = (ll)(a); (i) < (ll)(b); (i)++)
#define REPD(i, a, b) for (ll i = (ll)(a); (i) < (ll)(b); (i)++)
#define REPI(v, vs) for (auto &v : vs)

//debug
#ifdef LOCAL_ENV
#define DUMP(x) cerr << #x << " = " << (x) << endl
#define DEBUG(x) cerr << #x << " = " << (x) << " (l" << __LINE__ << ")" \
					  << " " << __FILE__ << endl
#else
#define DUMP(x)
#define DEBUG(x)
#endif

#define MAX_VALUE 9223372036854775807LL

template <class T, class... Args>
auto make_multiple_vector(T default_value)
{
	return T(default_value);
}

template <class T, class... Args>
auto make_multiple_vector(T default_value, ull size, Args... args)
{
	using value_type = std::decay_t<decltype(make_multiple_vector<T>(default_value, args...))>;
	return vector<value_type>(size, make_multiple_vector<T>(default_value, args...));
}

template <class Integer, class Monoid, class OperatorII, class OperatorIM, class OperatorMM>
class SegmentTreeWithLazyPropagation
{
private:
	ull maxSize_;
	vector<Integer> data_;
	vector<Monoid> lazy_;
	OperatorII op_ii_;
	OperatorIM op_im_;
	OperatorMM op_mm_;

	void _lazy_propagate(ll k)
	{
		if (lazy_[k] == op_mm_.default_value)
			return;
		if (k < maxSize_ - 1)
		{
			lazy_[k * 2 + 1] = op_mm_.Execute(lazy_[k * 2 + 1], lazy_[k]);
			lazy_[k * 2 + 2] = op_mm_.Execute(lazy_[k * 2 + 2], lazy_[k]);
		}
		data_[k] = op_im_.Execute(data_[k], lazy_[k]);
		lazy_[k] = op_mm_.default_value;
	}

	Integer _query(ll start, ll end, ll searchStart, ll searchEnd, ll node)
	{
		_lazy_propagate(node);
		if (searchEnd <= start || end <= searchStart)
			return op_ii_.default_value;
		if (start <= searchStart && searchEnd <= end)
			return data_[node];

		return op_ii_.Execute(
			_query(start, end, searchStart, (searchStart + searchEnd) / 2, node * 2 + 1),
			_query(start, end, (searchStart + searchEnd) / 2, searchEnd, node * 2 + 2));
	}

	void _update(ll start, ll end, Monoid value, ll searchStart, ll searchEnd, ll node)
	{
		_lazy_propagate(node);
		if (start <= searchStart && searchEnd <= end)
		{
			lazy_[node] = op_mm_.Execute(lazy_[node], value);
			_lazy_propagate(node);
		}
		else if (searchStart < end && start < searchEnd)
		{
			_update(start, end, value, searchStart, (searchStart + searchEnd) / 2, node * 2 + 1);
			_update(start, end, value, (searchStart + searchEnd) / 2, searchEnd, node * 2 + 2);
			data_[node] = op_ii_.Execute(data_[node * 2 + 1], data_[node * 2 + 2]);
		}
	}

public:
	ull size() { return maxSize_; }
	SegmentTreeWithLazyPropagation(ull maxSize) : maxSize_(1)
	{
		while (maxSize_ < maxSize)
			maxSize_ *= 2;
		data_ = vector<Integer>(ll(maxSize_) * 2 - 1, op_ii_.default_value);
		lazy_ = vector<Monoid>(ll(maxSize_) * 2 - 1, op_mm_.default_value);
	}

	void update(ll start, ll end, Monoid value)
	{
		if (start < 0)
			throw invalid_argument("Start should be non-negative.");
		if (maxSize_ < end)
			throw invalid_argument("End should be less than or equal to maxSize.");
		if (start >= end)
			throw invalid_argument("End should be more than start.");

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
		if (start < 0)
			throw invalid_argument("Start should be non-negative.");
		if (maxSize_ < end)
			throw invalid_argument("End should be less than or equal to maxSize.");
		if (start >= end)
			throw invalid_argument("End should be more than start.");

		return _query(start, end, 0, maxSize_, 0);
	}
};

using range_sum = pair<ll, ll>;
using affine_op = pair<ll, ll>;

struct IIOp
{
	const static range_sum default_value;
	static range_sum Execute(const range_sum &a, const range_sum &b)
	{
		ll k, l, m, n;
		tie(k, l) = a;
		tie(m, n) = b;
		return {(k + m + MOD) % MOD, l + n};
	};
};

const range_sum IIOp::default_value = make_pair(0, 0);

struct IMOp
{
	static range_sum Execute(const range_sum &a, const affine_op &b)
	{
		ll k, l, m, n;
		tie(k, l) = a;
		tie(m, n) = b;
		return {((k * m + n * l + MOD) % MOD), l};
	};
};

struct MMOp
{
	const static affine_op default_value;
	static affine_op Execute(const affine_op &a, const affine_op &b)
	{
		ll k, l, m, n;
		tie(k, l) = a;
		tie(m, n) = b;
		return make_pair((m * k + MOD) % MOD, ((m * l) % MOD + n + MOD) % MOD);
	};
};

const affine_op MMOp::default_value = make_pair(1, 0);
using RMQLP = SegmentTreeWithLazyPropagation<range_sum, affine_op, IIOp, IMOp, MMOp>;

int solve()
{
	ll n, q;
	cin >> n >> q;

	RMQLP rmq(n);
	ll a;
	REPD(i, 0, n)
	{
		cin >> a;
		rmq.update(i, make_pair(a, 1));
	}

	ll t, l, r, b, c;
	ll res;
	REPD(i, 0, q)
	{
		cin >> t;
		if (t == 0)
		{
			cin >> l >> r >> b >> c;
			rmq.update(l, r, make_pair(b, c));
		}
		else
		{
			cin >> l >> r;

			tie(res, ignore) = rmq.query(l, r);
			cout << res << endl;
		}
	}

	return 0;
}

//main function
int main()
{
	cin.tie(0);
	ios::sync_with_stdio(false);

	solve();
	// ll t;
	// cin >> t;
	// REPD(i, 0, t) solve();

	return 0;
}
