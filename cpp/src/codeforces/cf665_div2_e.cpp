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

#define MAX_VALUE 9223372036854775807

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
using bit = BinaryIndexedTree<ll>;

int solve() {
	ll n, m;
	cin >> n >> m;

	ll res = 1;

	vector<tuple<ll, ll, ll>> hors(n + 2LL);
	ll y, lx, rx;
	REPD(i, 0, n) {
		cin >> y >> lx >> rx;
		hors[i] = {y, lx, rx};
		if (lx == 0 && rx == 1000000) ++res;
	}
	hors[n] = {0, 0, 1000000};
	hors[n + 1LL] = {1000000, 0, 1000000};
	sort(hors.begin(), hors.end());

	bit top_bit_(1000001);
	bit bottom_bit_(1000001);
	ll x, ly, ry;
	priority_queue<pair<ll, ll>> top_queue;
	priority_queue<pair<ll, ll>> bottom_queue;
	REPD(i, 0, m) {
		cin >> x >> ly >> ry;
		if (ly == 0) {
			bottom_bit_.update(x, 1);
			bottom_queue.emplace(-ry, x);
		}
		else {
			top_bit_.update(x, 1);
			top_queue.emplace(ly, x);
		}
	}

	REPD(i, 0, n + 1) {
		tie(y, lx, rx) = hors[i + 1];

		while(!bottom_queue.empty()) {
			auto bottom = bottom_queue.top();
			if (y > -bottom.first) {
				bottom_bit_.update(bottom.second, -1LL);
				bottom_queue.pop();
			}
			else {
				break;
			}
		}
		res += bottom_bit_.query(rx);
		if (lx > 0) res -= bottom_bit_.query(lx - 1LL);
		DEBUG(res);
	}

	REPD(i, 0, n + 1) {
		tie(y, lx, rx) = hors[n - i];

		while(!top_queue.empty()) {
			auto top = top_queue.top();
			if (y < top.first) {
				top_bit_.update(top.second, -1LL);
				top_queue.pop();
			}
			else {
				break;
			}

		}
		res += top_bit_.query(rx);
		if (lx > 0) res -= top_bit_.query(lx - 1LL);

		DEBUG(res);
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
