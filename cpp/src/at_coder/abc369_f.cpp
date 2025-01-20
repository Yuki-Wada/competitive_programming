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
#include <random>

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
using pair1d = vector<llpair>;
using pair2d = vector2d<llpair>;

// constant
static const ll MOD = 998244353LL;
static const double PI = 3.14159265358979323846;

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

using val = tuple<ll, ll>;

struct MaxOp
{
	const static val default_value;
	static val Execute(const val &a, const val &b) { return max(a, b); };
};

const val MaxOp::default_value = {0LL, 0LL};

using RMQ = SegmentTree<val, MaxOp>;

ll H, W, N;

int solve()
{
	cin >> H >> W >> N;

	ll2d coins(H);
	REPD(i, 0, N)
	{
		ll r, c;
		cin >> r >> c;
		coins[--r].emplace_back(--c);
	}

	vector<tuple<ll, ll, ll, ll>> histories;
	RMQ rmq(W);
	REPD(i, 0, H)
	{
		sort(coins[i].begin(), coins[i].end());
		REPI(j, coins[i])
		{
			auto [coin_count, prev_j] = rmq.query(0, j + 1LL);
			rmq.update(j, make_tuple(coin_count + 1LL, j));
			histories.emplace_back(i, j, prev_j, coin_count + 1LL);
		}
	}

	ll curr_r = H - 1LL, curr_c = W - 1LL;
	auto [result_coin_count, prev_c] = rmq.query(0, W);
	cout << result_coin_count << endl;

	vector<char> res_chars;
	res_chars.reserve(H + W - 2LL);
	REPD(i, 0, curr_c - prev_c)
	{
		res_chars.emplace_back('R');
	}
	curr_c = prev_c;

	reverse(histories.begin(), histories.end());
	REPD(i, 0, histories.size())
	{
		auto [prev_r, prev_c, prev_prev_c, _] = histories[i];
		if (prev_c == curr_c)
		{
			REPD(i, 0, curr_r - prev_r)
			{
				res_chars.emplace_back('D');
			}
			REPD(i, 0, prev_c - prev_prev_c)
			{
				res_chars.emplace_back('R');
			}
			curr_r = prev_r;
			curr_c = prev_prev_c;
		}
	}
	REPD(i, 0, curr_r)
	{
		res_chars.emplace_back('D');
	}
	REPD(i, 0, curr_c)
	{
		res_chars.emplace_back('R');
	}
	reverse(res_chars.begin(), res_chars.end());

	REPI(res_char, res_chars)
	{
		cout << res_char;
	}
	cout << endl;

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
	// REPD(i, 0, t)
	// {
	// 	solve();
	// }

	return 0;
}
