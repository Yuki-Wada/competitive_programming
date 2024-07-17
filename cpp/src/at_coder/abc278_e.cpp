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
static const ll MOD = 1000000007LL;
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

#define MAX_VALUE 9223372036854775807LL

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

class Solver
{
private:
	ll H;
	ll W;
	ll N;
	ll h;
	ll w;
	vector<vector<ll>> As;
	vector<ll> current_counts;
	vector<ll> all_counts;

public:
	Solver(ll H, ll W, ll N, ll h, ll w, vector<vector<ll>> As) : H(H), W(W), N(N), h(h), w(w), As(As), current_counts(N), all_counts(N)
	{
		for (ll i = 0; i < H; ++i)
		{
			for (ll j = 0; j < W; ++j)
			{
				++all_counts[As[i][j]];
			}
		}
	}

	void init_line(ll lu_h)
	{
		for (ll i = 0; i < N; ++i)
		{
			current_counts[i] = all_counts[i];
		}
		for (ll i = 0; i < h; ++i)
		{
			for (ll j = 0; j < w; ++j)
			{
				--current_counts[As[lu_h + i][j]];
			}
		}
	}

	void update_column(ll lu_h, ll lu_w)
	{
		for (ll i = 0; i < h; ++i)
		{
			++current_counts[As[lu_h + i][lu_w]];
			--current_counts[As[lu_h + i][lu_w + w]];
		}
	}

	ll solve()
	{
		ll res = 0;
		for (ll i = 0; i < N; ++i)
		{
			if (current_counts[i] != 0)
				++res;
		}
		return res;
	}
};

int solve()
{
	ll H, W, N, h, w;
	cin >> H >> W >> N >> h >> w;

	vector<vector<ll>> As(H, vector<ll>(W));
	for (ll i = 0; i < H; ++i)
	{
		for (ll j = 0; j < W; ++j)
		{
			cin >> As[i][j];
			--As[i][j];
		}
	}

	auto solver = Solver(H, W, N, h, w, As);

	for (ll i = 0; i <= H - h; ++i)
	{
		solver.init_line(i);
		for (ll j = 0; j <= W - w; ++j)
		{
			cout << solver.solve();
			if (j < W - w)
			{
				solver.update_column(i, j);
				cout << " ";
			}
		}
		cout << endl;
	}

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
	// REPD(i, 0, t) solve();

	return 0;
}
