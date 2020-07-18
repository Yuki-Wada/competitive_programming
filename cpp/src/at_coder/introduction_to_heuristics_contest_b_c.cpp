//include
//------------------------------------------
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
#include <string>
#include <cstring>
#include <ctime>

#include <stdexcept>

using namespace std;

// type alias
using ll = long long;
using ull = unsigned long long;
using comp = complex<double>;

const ll MOD = 1000000007LL;
const double PI = 3.14159265358979323846;

//conversion
//------------------------------------------
inline int toint(string s) { int v; istringstream sin(s); sin >> v; return v; }
template<class t> inline string tostring(t x) { ostringstream sout; sout << x; return sout.str(); }

//debug
#define DUMP(x)  cerr << #x << " = " << (x) << endl
#define DEBUG(x) cerr << #x << " = " << (x) << " (l" << __line__ << ")" << " " << __file__ << endl

ll score(const vector<ll>& cs, const vector<vector<ll>>& ss, const vector<ll>& ts) {
	vector<ll> vs(ts.size());
	vector<ll> lasts(26);

	for (ll i = 0; i < ts.size(); ++i) {
		if (i > 0) vs[i] = vs[i - 1LL];
		ll t = ts[i];
		vs[i] += ss[i][t];
		for (ll j = 0; j < 26; ++j) {
			++lasts[j];
			if (j == t) lasts[j] = 0;
			vs[i] -= cs[j] * lasts[j];
		}
		cout << vs[i] << endl;
	}

	return vs[ts.size() - 1LL];
}

ll change(
	const vector<ll>& cs,
	const vector<vector<ll>>& ss,
	const vector<ll>& ts,
	ll curr_score,
	ll d, ll new_t)
{
	ll curr_t = ts[d];
	ll score = curr_score;

	{
		ll curr_left_idx = -1;
		for (ll i = 0; i < d; ++i) if (ts[i] == curr_t) curr_left_idx = max(curr_left_idx, i);
		ll curr_right_idx = ts.size();
		for (ll i = ts.size() - 1LL; i > d; --i) if (ts[i] == curr_t) curr_right_idx = min(curr_right_idx, i);
		score -= ss[d][curr_t];
		score += cs[curr_t] * (d - curr_left_idx) * (d - curr_left_idx - 1LL) / 2LL;
		score += cs[curr_t] * (curr_right_idx - d) * (curr_right_idx - d - 1LL) / 2LL;
		score -= cs[curr_t] * (curr_right_idx - curr_left_idx) * (curr_right_idx - curr_left_idx - 1LL) / 2LL;

	}

	{
		ll new_left_idx = -1;
		for (ll i = 0; i < d; ++i) if (ts[i] == new_t) new_left_idx = max(new_left_idx, i);
		ll new_right_idx = ts.size();
		for (ll i = ts.size() - 1LL; i > d; --i) if (ts[i] == new_t) new_right_idx = min(new_right_idx, i);
		score += ss[d][new_t];
		score -= cs[new_t] * (d - new_left_idx) * (d - new_left_idx - 1LL) / 2LL;
		score -= cs[new_t] * (new_right_idx - d) * (new_right_idx - d - 1LL) / 2LL;
		score += cs[new_t] * (new_right_idx - new_left_idx) * (new_right_idx - new_left_idx - 1LL) / 2LL;
	}

	return score;
}

int solve() {
	ll D;
	cin >> D;

	vector<ll> cs(26);
	for (ll i = 0; i < 26; ++i) cin >> cs[i];

	vector<vector<ll>> ss(D, vector<ll>(26));
	for (ll i = 0; i < D; ++i) for (ll j = 0; j < 26; ++j) cin >> ss[i][j];

	vector<ll> ts(D);
	for (ll i = 0; i < D; ++i) {cin >> ts[i]; --ts[i]; }

	ll curr_score = score(cs, ss, ts);

	ll M;
	cin >> M;
	vector<pair<ll, ll>> dqs(M);
	ll d, q;
	for (ll i = 0; i < D; ++i) {
		cin >> d >> q; --d, --q;
		curr_score = change(cs, ss, ts, curr_score, d, q);
		cout << curr_score << endl;;
		ts[d] = q;
	}
	
	return 0;
}

int main() {
	cin.tie(0);
	ios::sync_with_stdio(false);

	solve();

	return 0;
}
