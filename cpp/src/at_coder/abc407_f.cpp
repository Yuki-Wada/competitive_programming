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

struct MaxOp
{
	const static pair<ll, ll> default_value;
	static pair<ll, ll> Execute(const pair<ll, ll> &a, const pair<ll, ll> &b) { return max(a, b); };
};

const pair<ll, ll> MaxOp::default_value = {-1LL, -1LL};

using RMQ = SegmentTree<pair<ll, ll>, MaxOp>;

ll solve()
{
	ll n;
	cin >> n;
	RMQ rmq(n);
	ll1d a(n);
	REPD(i, 0, n)
	{
		cin >> a[i];
		rmq.update(i, make_pair(a[i], i));
	}

	vector<pair<ll, ll>> lrs;
	REPD(i, 0, n)
	{
		auto v = make_pair(a[i], i);
		ll left = 0LL;
		ll right = n - 1LL;
		{
			ll low = 0, high = i;
			if (rmq.query(low, i + 1LL) == v)
			{
				left = low;
			}
			else
			{
				while (high - low > 1)
				{
					ll mid = (low + high) / 2;
					if (rmq.query(mid, i + 1LL) == v)
					{
						high = mid;
					}
					else
					{
						low = mid;
					}
				}
				left = high;
			}
		}
		{
			ll low = i, high = n - 1LL;
			if (rmq.query(i, high + 1LL) == v)
			{
				right = high;
			}
			else
			{
				while (high - low > 1)
				{
					ll mid = (low + high) / 2;
					if (rmq.query(i, mid + 1LL) == v)
					{
						low = mid;
					}
					else
					{
						high = mid;
					}
				}
				right = low;
			}
		}
		lrs.push_back({i - left, right - i});
	}

	auto biases_diff = make_multiple_vector<1, ll>(n + 2, 0);
	auto slopes_diff = make_multiple_vector<1, ll>(n + 2, 0);
	REPD(i, 0, n)
	{
		auto [l, r] = lrs[i];
		auto min_lr = min(l, r);
		auto max_lr = max(l, r);
		auto a_ = a[i];

		slopes_diff[0] += a_;

		slopes_diff[min_lr + 1] -= a_;
		biases_diff[min_lr + 1] += (min_lr + 1) * a_;

		biases_diff[max_lr + 1] -= (min_lr + 1) * a_;
		biases_diff[max_lr + 1] += (2 + min_lr + max_lr) * a_;
		slopes_diff[max_lr + 1] += -a_;

		biases_diff[max_lr + min_lr + 2] -= (2 + min_lr + max_lr) * a_;
		slopes_diff[max_lr + min_lr + 2] -= -a_;
	}

	auto biases = make_multiple_vector<1, ll>(n + 1, 0);
	auto slopes = make_multiple_vector<1, ll>(n + 1, 0);
	ll bias_sum = 0, slope_sum = 0;
	REPD(i, 0, n + 1LL)
	{
		bias_sum += biases_diff[i];
		slope_sum += slopes_diff[i];
		biases[i] = bias_sum;
		slopes[i] = slope_sum;
	}

	REPD(k, 1, n + 1LL)
	{
		ll res = 0;
		ll b = biases[k];
		ll s = slopes[k];
		res = s * k + b;
		cout << res << endl;
	}

	return 0;
}

// main function
int main()
{
	cin.tie(0);
	ios::sync_with_stdio(false);

	auto r = solve();

	// ll t;
	// cin >> t;

	// REPD(i, 0, t)
	// {
	// 	auto r = solve();
	// }

	return 0;
}
