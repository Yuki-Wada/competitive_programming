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

class State {
public:
	ll half_trans_x = 0;
	ll half_trans_y = 0;
	bool use_axis_y = false;
	bool use_axis_x = false;
	ll axis_x = 0;
	ll axis_y = 0;
	ll rotate = 0;
};

int solve() {
	ll n, m, q;
	cin >> n;
	vector<pair<ll, ll>> xys(n);
	ll x, y;
	REPD(i, 0, n) {
		cin >> x >> y;
		xys[i] = {x, y};
	}

	cin >> m;
	vector<State> states(m + 1);
	ll op, p;
	REPD(i, 0, m) {
		cin >> op;
		State state = states[i];
		if (op == 3 || op == 4) cin >> p;
		if (op == 2) {
			ll tmp = state.half_trans_x;
			state.half_trans_x = -state.half_trans_y;
			state.half_trans_y = tmp;
			
			tmp = state.axis_x;
			state.axis_x = -state.axis_y;
			state.axis_y = tmp;
			bool bool_tmp = state.use_axis_x;
			state.use_axis_x = state.use_axis_y;
			state.use_axis_y = bool_tmp;

			state.rotate += 1;
			state.rotate %= 4;
		}
		if (op == 1) {
			ll tmp = state.half_trans_y;
			state.half_trans_y = -state.half_trans_x;
			state.half_trans_x = tmp;

			tmp = state.axis_y;
			state.axis_y = -state.axis_x;
			state.axis_x = tmp;
			bool bool_tmp = state.use_axis_x;
			state.use_axis_x = state.use_axis_y;
			state.use_axis_y = bool_tmp;

			state.rotate += 3;
			state.rotate %= 4;
		}
		if (op == 3) {
			if (state.use_axis_x) {
				state.half_trans_x = p - state.axis_x;
				state.axis_x = 0;
			}
			else {
				state.axis_x = p - state.half_trans_x;
				state.half_trans_x = 0;
			}
			state.use_axis_x = !state.use_axis_x;
		}
		if (op == 4) {
			if (state.use_axis_y) {
				state.half_trans_y = p - state.axis_y;
				state.axis_y = 0;
			}
			else {
				state.axis_y = p - state.half_trans_y;
				state.half_trans_y = 0;
			}
			state.use_axis_y = !state.use_axis_y;
		}
		states[i + 1] = state;
	}

	cin >> q;
	ll a, b;
	REPD(i, 0, q) {
		cin >> a >> b;
		State state = states[a];
		tie(x, y) = xys[b - 1];

		if (state.rotate == 1) {
			ll tmp = x;
			x = -y;
			y = tmp;
		}
		else if (state.rotate == 2) {
			x = -x;
			y = -y;
		}
		else if (state.rotate == 3) {
			ll tmp = y;
			y = -x;
			x = tmp;
		}
		if (state.use_axis_x) x = 2 * state.axis_x - x;
		if (state.use_axis_y) y = 2 * state.axis_y - y;
		x += 2 * state.half_trans_x;
		y += 2 * state.half_trans_y;

		cout << x << " " << y << endl;
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
