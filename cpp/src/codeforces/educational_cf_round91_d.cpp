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
const ll MOD = 1000000007LL;
const double PI = 3.14159265358979323846;

// conversion
inline ll toint(string s) { ll v; istringstream sin(s); sin >> v; return v; }
template<class t> inline string tostring(t x) { ostringstream sout; sout << x; return sout.str(); }

// print
#define RET(x) return cout << x << endl, 0;

// for loop
#define REP(i, a, b) for ((i) = (ll)(a);(i) < (ll)(b);(i)++)
#define REPD(i, a, b) for (ll i = (ll)(a);(i) < (ll)(b);(i)++)
#define REPI(v, vs) for (auto v : vs)

//debug
#define DUMP(x)  cerr << #x << " = " << (x) << endl
#define DEBUG(x) cerr << #x << " = " << (x) << " (l" << __LINE__ << ")" << " " << __FILE__ << endl

ll x, k, y;

ll get_min_mana(ll left_idx, ll right_idx, const vector<ll> & as) {
	ll left = (left_idx >= 0 ? as[left_idx] : -1);
	ll right = (right_idx < as.size() ? as[right_idx] : -1);

	ll count_to_delete = right_idx - left_idx - 1;
	if (count_to_delete == 0) return 0;

	bool exist_upper = false;
	REPD(i, left_idx + 1, right_idx) if (as[i] > max(left, right)) {
		exist_upper = true;
		break;
	}

	if (exist_upper && count_to_delete < k) return -1;

	if (x <= k * y) return (count_to_delete / k) * x + (count_to_delete % k) * y;
	if (exist_upper) return x + (count_to_delete - k) * y;
	return count_to_delete * y;
}

int solve() {
	ll n, m;
	cin >> n >> m >> x >> k >> y;

	vector<ll> as(n), bs(m);
	REPD(i, 0, n) cin >> as[i];
	REPD(i, 0, m) cin >> bs[i];

	ll res = 0, mana;
	ll prev_a_idx = -1, a_idx = 0;
	ll b_idx = 0;
	REP(b_idx, 0, m) {
		while (a_idx < n && as[a_idx] != bs[b_idx]) ++a_idx;
		if (a_idx >= n) RET(-1);
		mana = get_min_mana(prev_a_idx, a_idx, as);
		if (mana == -1) RET(-1);
		res += mana;
		prev_a_idx = a_idx;
	}
	mana = get_min_mana(prev_a_idx, n, as);
	if (mana == -1) RET(-1);
	res += mana;

	RET(res);
}

//main function
int main()
{
	cin.tie(0);
	ios::sync_with_stdio(false);

	solve();

	return 0;
}
