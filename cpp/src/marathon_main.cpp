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

#include <sstream>
#include <iostream>
#include <iomanip>

#include <complex>
#include <numeric>
#include <utility>

#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cctype>
#include <cstring>
#include <ctime>

#include <random>

// namespace
using namespace std;

// type alias
using ll = long long;
using ull = unsigned long long;
using comp = complex<double>;

// constant
const ll MOD = 1000000007LL;
const double PI = 3.14159265358979323846;
const double TLE = 2.0;

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

const static ll C = 26;
static ll D;
static vector<ll> cs;
static vector<vector<ll>> ss;
static double T0 = 2000;
static double T1 = 5;

class Random {
public:
	// [0, x)
	inline static unsigned get(unsigned x) {
		return ((unsigned long long)xorshift() * x) >> 32;
	}

	// [x, y]
	inline static unsigned get(unsigned x, unsigned y) {
		return get(y - x + 1) + x;
	}

	// [0, x] (x = 2^c - 1)
	inline static unsigned get_fast(unsigned x) {
		return xorshift() & x;
	}

	// [0.0, 1.0]
	inline static double probability() {
		return xorshift() * INV_MAX;
	}

	inline static bool toss() {
		return xorshift() & 1;
	}

private:
	constexpr static double INV_MAX = 1.0 / 0xFFFFFFFF;

	inline static unsigned xorshift() {
		static unsigned long long x = 88172645463325252LL;
		x = x ^ (x << 7);
		return x = x ^ (x >> 9);
	}
};

ll get_score(const vector<ll>& ts) {
	vector<ll> vs(D);
	vector<ll> lasts(C);

	for (ll i = 0; i < ts.size(); ++i) {
		if (i > 0) vs[i] = vs[i - 1LL];
		ll t = ts[i];
		vs[i] += ss[i][t];
		for (ll j = 0; j < C; ++j) {
			++lasts[j];
			if (j == t) lasts[j] = 0;
			vs[i] -= cs[j] * lasts[j];
		}
	}

	return vs[ts.size() - 1LL];
}

ll get_diff(const vector<ll>& ts, ll d, ll new_t)
{
	ll curr_t = ts[d];
	ll score = 0;

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

vector<ll> partial_greedy_search(ll k){
	vector<ll> ts(D);
	vector<ll> lasts(C);

	for (ll i = 0; i < D; ++i) {
		for (ll j = 0; j < C; ++j) {
			++lasts[j];
		}

		ll best_t;
		ll best_score = -(1LL << 60LL);
		for (ll t = 0; t < C; ++t) {
			ll score = ss[i][t];
			for (ll u = 0; u < C; ++u)
				for (ll j = 0; j <= min(k, D - 1LL- i); ++j)
					score -= cs[u] * (lasts[u] + j);
			score += cs[t] * lasts[t] * (min(k, D - i) + 1LL);

			if (best_score < score) {
				best_t = t;
				best_score = score;
			}
		}

		ts[i] = best_t;
		lasts[best_t] = 0;
	}

	return ts;
}

vector<ll> greedy_search() {
	ll best_score = -(1LL << 60LL);
	vector<ll> best_ts(D);
	for (ll i = 0; i < C; ++i) {
		auto ts = partial_greedy_search(i);
		auto score = get_score(ts);
		if (best_score < score) {
			best_ts = ts;
			best_score = score;
		}
	}

	return best_ts;
}

inline double get_prob(ull rand) {
	return double(rand % 10000LL) / 10000LL;
}

bool can_update(ll curr_score, ll new_score, double t, mt19937_64 mt) {
	if (new_score >= curr_score) return true;

	double delta = new_score - curr_score;
	double prob = get_prob(mt());
	if (prob < exp(delta / t)) return true;

	return false;
}

int solve() {
	random_device seed_gen;
	mt19937_64 engine(seed_gen());

	cin >> D;

	cs = vector<ll>(C);
	for (ll i = 0; i < C; ++i) cin >> cs[i];

	ss = vector<vector<ll>>(D, vector<ll>(C));
	for (ll i = 0; i < D; ++i) for (ll j = 0; j < C; ++j) cin >> ss[i][j];

	vector<ll> ts = greedy_search();
	ll best_score = get_score(ts);

	double T = T0;
	ll loop_count = 0;
	while (double(clock()) / CLOCKS_PER_SEC / TLE < 0.99) {
		ull rand = engine() % 10LL;
		if (rand < 4LL) {
			ll d = engine() % D;
			ll t = engine() % C;
			ll score = best_score + get_diff(ts, d, t);
			if (can_update(best_score, score, T, engine)) {
				best_score = score;
				ts[d] = t;
			}
		}
		else if (rand < 8LL) {
			ll d1 = engine() % D;
			ll d2 = engine() % D;
			if (d1 == d2) continue;
			ll t1 = ts[d1];
			ll t2 = ts[d2];
			ll score = best_score + get_diff(ts, d1, t2);
			ts[d1] = t2;
			score += get_diff(ts, d2, t1);
			ts[d1] = t1;
			if (can_update(best_score, score, T, engine)) {
				best_score = score;
				ts[d1] = t2;
				ts[d2] = t1;
			}
		}
		else {
			ll d1 = engine() % D;
			ll d2 = engine() % D;
			ll d3 = engine() % D;
			ll d4 = engine() % D;
			ll t1 = ts[d1];
			ll t2 = ts[d2];
			ll t3 = ts[d3];
			ll t4 = ts[d4];
			ll score = best_score + get_diff(ts, d1, t2);
			ts[d1] = t2;
			score += get_diff(ts, d2, t3);
			ts[d2] = t3;
			score += get_diff(ts, d3, t4);
			ts[d3] = t4;
			score += get_diff(ts, d4, t1);
			ts[d1] = t1;
			ts[d2] = t2;
			ts[d3] = t3;
			if (can_update(best_score, score, T, engine)) {
				best_score = score;
				ts[d1] = t2;
				ts[d2] = t3;
				ts[d3] = t4;
				ts[d4] = t1;
			}
		}

		++loop_count;
		if (loop_count % 100LL == 0) {
			double elapsed_time = double(clock()) / CLOCKS_PER_SEC / TLE;
			T = T0 * pow(T1 / T0, elapsed_time);
		}
	}

	cout << "Score: " << get_score(ts) << endl;
	//for (ll i = 0; i < D; ++i) {
	//	cout << ts[i] + 1LL << endl;
	//}

	return 0;
}

int main() {
	cin.tie(0);
	ios::sync_with_stdio(false);

	solve();

	return 0;
}
