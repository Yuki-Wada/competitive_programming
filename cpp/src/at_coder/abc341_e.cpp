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

// type alias
using ll = long long;
using ull = unsigned long long;
using comp = complex<double>;

// constant
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

// debug
#ifdef LOCAL_ENV
#define DUMP(x) cerr << #x << " = " << (x) << endl
#define DEBUG(x) cerr << #x << " = " << (x) << " (l" << __LINE__ << ")" \
					  << " " << __FILE__ << endl
#else
#define DUMP(x)
#define DEBUG(x)
#endif

#define MAX_VALUE 9223372036854787LL

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

using container = pair<ll, ll>;

struct MergeOp
{
	const static container default_value;
	static container Execute(const container &a, const container &b)
	{
		return make_pair(a.first + b.first, a.second + b.second);
	};
};
const container MergeOp::default_value = make_pair(0LL, 0LL);

struct ActionOp
{
	const static container default_value;
	static container Execute(const container &a, const bool &b)
	{
		return make_pair(a.second, a.first);
	};
};
const container ActionOp::default_value = make_pair(0LL, 0LL);

struct MonoidOp
{
	const static bool default_value;
	static bool Execute(const bool &a, const bool &b)
	{
		return a ^ b;
	};
};
const bool MonoidOp::default_value = false;

using RMQ = SegmentTreeWithLazyPropagation<container, bool, MergeOp, ActionOp, MonoidOp>;

int solve()
{
	ll N, Q;
	cin >> N >> Q;

	string S;
	cin >> S;
	RMQ rmq(N);
	REPD(i, 0, N)
	{
		auto bit = ll(S[i] - '0') == 1LL;
		if (i % 2LL == 0LL)
		{
			bit = !bit;
		}
		rmq.update(i, make_pair(bit ? 1LL : 0LL, bit ? 0LL : 1LL));
	}
	ll n, l, r;
	REPD(i, 0, Q)
	{
		cin >> n >> l >> r;
		--l, --r;
		if (n == 1)
		{
			rmq.update(l, r + 1LL, true);
		}
		if (n == 2)
		{
			auto [first, second] = rmq.query(l, r + 1LL);
			cout << ((first == 0 || second == 0) ? "Yes" : "No") << endl;
		}
	}

	return 0;
}

// main function
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
