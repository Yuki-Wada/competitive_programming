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

struct MaxOp
{
	const static ll default_value;
	static ll Execute(const ll &a, const ll &b) { return max(a, b); };
};

const ll MaxOp::default_value = 0;

using RMQ = SegmentTree<ll, MaxOp>;

pair<vector<ll>, vector<ll>> compress_coordinates(const vector<ll> &As)
{
	ll N = As.size();
	vector<pair<ll, ll>> items(N);
	for (ll i = 0; i < N; ++i)
	{
		items[i] = make_pair(As[i], i);
	}
	sort(items.begin(), items.end());

	vector<ll> compressed_coords(N);
	vector<ll> compression_table;

	ll prev_a;
	ll compressed = -1;
	for (ll i = 0; i < N; ++i)
	{
		auto [a, idx] = items[i];
		if (i == 0LL || prev_a != a)
		{
			if (i > 0LL && a - prev_a >= 2LL)
			{
				compression_table.push_back(prev_a + 1LL);
				++compressed;
			}
			compression_table.push_back(a);
			++compressed;
			prev_a = a;
		}

		compressed_coords[idx] = compressed;
	}

	compression_table.push_back(MAX_VALUE - 1LL);
	compression_table.push_back(MAX_VALUE);
	return {compressed_coords, compression_table};
}

ll N;
ll1d As;

int solve()
{
	cin >> N;
	As.resize(N);
	REPD(i, 0, N)
	{
		cin >> As[i];
	}

	auto [compressed_coords, compression_table] = compress_coordinates(As);
	RMQ up_rmq(compression_table.size());
	stack<llpair> st;
	REPD(i, 0, N)
	{
		auto coord = compressed_coords[i];
		auto prev_value = up_rmq.query(coord, coord + 1LL);
		st.emplace(coord, prev_value);
		auto curr_value = up_rmq.query(0LL, coord) + 1LL;
		up_rmq.update(coord, curr_value);
	}

	ll res = up_rmq.query(0, compression_table.size());
	RMQ down_rmq(compression_table.size());

	ll right_coord = compression_table.size() - 1LL;
	REPD(i, 0, N)
	{
		auto center_coord = compressed_coords[N - i - 1LL];

		{
			auto [_, prev_value] = st.top();
			st.pop();
			up_rmq.update(center_coord, prev_value);
		}

		{
			auto next_res = up_rmq.query(0LL, max(0LL, right_coord - 1LL)) + down_rmq.query(right_coord, compression_table.size()) + 1LL;
			res = max(res, next_res);
		}

		{
			auto value = down_rmq.query(center_coord + 1LL, compression_table.size()) + 1LL;
			down_rmq.update(center_coord, value);
			right_coord = center_coord;
		}
	}

	cout << res << endl;

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
