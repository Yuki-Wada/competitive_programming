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
static const ll MOD = 998244353LL;
static const double PI = 3.14159265358979323846;

// conversion
inline ll toint(string s) { ll v; istringstream sin(s); sin >> v; return v; }
template<class t> inline string tostring(t x) { ostringstream sout; sout << x; return sout.str(); }

// print
#define RET(x) return cout << x << endl, 0;

// for loop
#define REP(i, a, b) for ((i) = (ll)(a);(i) < (ll)(b);(i)++)
#define REPD(i, a, b) for (ll i = (ll)(a);(i) < (ll)(b);(i)++)
#define REPI(v, vs) for (auto& v : vs)

//debug
#ifdef LOCAL_ENV
#define DUMP(x)  cerr << #x << " = " << (x) << endl
#define DEBUG(x) cerr << #x << " = " << (x) << " (l" << __LINE__ << ")" << " " << __FILE__ << endl
#else
#define DUMP(x)
#define DEBUG(x)
#endif

#define MAX_VALUE 9223372036854775807LL

template <ull N, class T, class... Args, std::enable_if_t<N == 0, int> = 0>
auto make_multiple_vector(Args... args) {
    return T(args...);
}

template <ull N, class T, class... Args, std::enable_if_t<N != 0, int> = 0>
auto make_multiple_vector(ull size, Args... args) {
    using value_type = std::decay_t<decltype(make_multiple_vector<N - 1, T>(args...))>;
    return vector<value_type>(size, make_multiple_vector<N - 1, T>(args...));
}


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
			_query(start, end, searchStart, (searchStart + searchEnd) / 2, node * 2 + 1),
			_query(start, end, (searchStart + searchEnd) / 2, searchEnd, node * 2 + 2)
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
};
using RMQ = RangedMinimumQuery<ll>;


int solve() {
	ll N, Q;
	cin >> N >> Q;

	RMQ row_rmq(N);
	RMQ col_rmq(N);
	REPD(i, 0, N) {
		row_rmq.update(i, N - 2);
		col_rmq.update(i, N - 2);
	}

	ll res = (N - 2LL) * (N - 2LL);;
	ll type, place;
	ll min_row = N - 1, min_col = N - 1;
	REPD(i, 0, Q) {
		cin >> type >> place;
		if (type == 1) {
			res -= col_rmq.query(place - 1, N);
			if (row_rmq.query(min_row, min_row + 1LL) > place - 2) {
				row_rmq.update(min_row, place - 2);
			}
			min_col = min(min_col, place - 1LL);
		}
		else {
			res -= row_rmq.query(place - 1, N);
			if (col_rmq.query(min_col, min_col + 1LL) > place - 2) {
				col_rmq.update(min_col, place - 2);
			}
			min_row = min(min_row, place - 1LL);
		}
	}
	RET(res);

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
