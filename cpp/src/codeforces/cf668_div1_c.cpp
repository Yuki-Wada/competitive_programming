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
static const ll MOD = 1000000007LL;
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
		if (index < 0) return 0;
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
using BIT = BinaryIndexedTree<ll>;

ll binary_search(BIT& bit, ll end_idx, ll a) {
	if (bit.query(end_idx) < a) return -1;
	ll left_idx = 0;
	ll right_idx = end_idx;
	ll mid_idx = (right_idx + left_idx) / 2;
	while(right_idx - left_idx > 1) {
		if (bit.query(end_idx) - (mid_idx - 1 >= 0 ? bit.query(mid_idx - 1) : 0LL) >= a) left_idx = mid_idx;
		else right_idx = mid_idx;
		mid_idx = (right_idx + left_idx) / 2;
	}
	if (bit.query(end_idx) - (right_idx - 1 >= 0 ? bit.query(right_idx - 1) : 0LL) >= a) return right_idx;
	return left_idx;
}

int solve() {
	ll n, q;
	cin >> n >> q;
	
	vector<ll> as(n);
	REPD(i, 0, n) {
		cin >> as[i];
		as[i] = i + 1 - as[i];
	}

	vector<tuple<ll, ll, ll>> yxis(q);
	ll x, y;
	REPD(i, 0, q) {
		cin >> x >> y;
		yxis[i] = {n - y - 1, x, i};
	}
	sort(yxis.begin(), yxis.end());

	BIT bit(n + 1);
	vector<ll> results(q);
	ll q_idx = 0, idx;
	REPD(i, 0, n) {
		if (as[i] >= 0) {
			ll idx = binary_search(bit, i, as[i]);
			if (idx >= 0) bit.update(idx, 1);
		}
		while(true) {
			tie(y, x, idx) = yxis[q_idx];
			if (i != y) break;
			results[idx] = bit.query(i) - bit.query(x - 1);
			++q_idx;
		}
	}

	REPD(i, 0, q) cout << results[i] << endl;

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
