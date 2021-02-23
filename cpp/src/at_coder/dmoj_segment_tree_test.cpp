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
// static const ll MOD = (1LL << 61LL) - 1LL;
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

// computational complexity: o(log(max(a, b))) 
inline ull get_gcd(ull a, ull b)
{
	if (b == 0)
	{
		return a;
	}
	return get_gcd(b, a % b);
}

struct GCDOp {
	const static pair<ll, ll> default_value;
	static pair<ll, ll> Execute(const pair<ll, ll>& a, const pair<ll, ll>& b) {
		ll a1, a2, b1, b2;
		tie(a1, a2) = a;
		tie(b1, b2) = b;
		ll c1 = get_gcd(a1, b1), c2 = 0;
		if (c1 == a1) c2 += a2;
		if (c1 == b1) c2 += b2;
		return {c1, c2};
	};
};
const pair<ll, ll> GCDOp::default_value = {0, 1};

using RMQ = SegmentTree<ll, MinOp>;

int solve() {
	ll N, M;
	cin >> N >> M;

	RMQ min_tree(N + 1);
	SegmentTree<pair<ll, ll>, GCDOp> gcd_tree(N + 1);

	ll a;
	REPD(i, 0, N) {
		cin >> a;
		min_tree.update(i + 1, a);
		gcd_tree.update(i + 1, {a, 1});
	}

	char type;
	ll l, r;
	REPD(i, 0, M) {
		cin >> type >> l >> r;
		if (type == 'C') {
			min_tree.update(l, r);
			gcd_tree.update(l, {r, 1});
		}
		if (type == 'M') {
			cout << min_tree.query(l, r + 1) << endl;
		}
		if (type == 'G') {
			cout << gcd_tree.query(l, r + 1).first << endl;			
		}
		if (type == 'Q') {
			cout << gcd_tree.query(l, r + 1).second << endl;			
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
