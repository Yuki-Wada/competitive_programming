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
		if (start >= end)
		{
			throw invalid_argument("End should be more than start.");
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

const ll MaxOp::default_value = 0LL;

pair<vector<ll>, vector<ll>> compress_coordinates(const vector<ll> &As)
{
	ll N = As.size();
	vector<pair<ll, ll>> items(N);
	REPD(i, 0, N)
	{
		items[i] = make_pair(As[i], i);
	}
	sort(items.begin(), items.end());

	vector<ll> compressed_coords(N);
	vector<ll> compression_table;
	ll prev_a = -1;
	ll compressed = -1;
	REPD(i, 0, N)
	{
		auto [a, idx] = items[i];
		if (prev_a != a)
		{
			compression_table.push_back(a);
			prev_a = a;
			++compressed;
		}

		compressed_coords[idx] = compressed;
	}

	return {compressed_coords, compression_table};
}

using RMQ = SegmentTree<ll, MaxOp>;
int solve()
{
	ll N;
	cin >> N;

	auto As = make_multiple_vector(0LL, N);
	REPD(i, 0, N)
	{
		cin >> As[i];
	}
	auto [coords, compression_table] = compress_coordinates(As);

	RMQ forward_rmq(N + 1LL);
	stack<pair<ll, ll>> prev_lengths;
	REPD(i, 0, N)
	{
		auto coord = coords[i];

		ll updated = (coord > 0 ? forward_rmq.query(0, coord) : 0LL) + 1LL;
		ll prev_length = forward_rmq.query(coord, coord + 1LL);

		forward_rmq.update(coord, updated);
		prev_lengths.emplace(coord, prev_length);
	}

	ll max_len = forward_rmq.query(0LL, N + 1LL);

	vector<ll> res;
	RMQ backward_rmq(N + 1LL);
	REPD(i, 0, N)
	{
		auto coord = coords[N - 1LL - i];

		ll updated = backward_rmq.query(coord + 1LL, N + 1LL) + 1LL;
		backward_rmq.update(coord, updated);

		auto val = forward_rmq.query(coord, coord + 1LL) + backward_rmq.query(coord, coord + 1LL) - 1LL;
		if (val == max_len)
		{
			res.push_back(N - i);
		}

		auto [prev_coord, prev_length] = prev_lengths.top();
		prev_lengths.pop();
		forward_rmq.update(prev_coord, prev_length);
	}

	reverse(res.begin(), res.end());

	cout << res.size() << endl;
	REPD(i, 0, res.size())
	{
		cout << res[i];
		if (i + 1LL < res.size())
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
