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

pair<bool, bool> game_should_end(const vector<ll> &As, vector<ll> &colors, ll player_color, ll color_count)
{
	if (color_count == 9LL)
	{
		ll player_0 = 0, player_1 = 0;
		REPD(i, 0, 9)
		{
			auto color = colors[i];
			if (color == 0)
			{
				player_0 += As[i];
			}
			if (color == 1)
			{
				player_1 += As[i];
			}
		}

		return {true, (player_0 > player_1) ^ (player_color == 1)};
	}

	vector<vector<ll>> vecs = {
		{0, 1, 2},
		{3, 4, 5},
		{6, 7, 8},
		{0, 3, 6},
		{1, 4, 7},
		{2, 5, 8},
		{0, 4, 8},
		{2, 4, 6},
	};
	vector<ll> players = {0LL, 1LL};
	REPI(vec, vecs)
	{
		REPI(p, players)
		{
			bool is_consistent = true;
			REPI(i, vec)
			{
				is_consistent &= (colors[i] == p);
			}
			if (is_consistent)
			{
				return {true, (player_color == p)};
			}
		}
	}

	return {false, true};
}

bool paint_color(const vector<ll> &As, vector<ll> &colors, ll player_color, ll color_count)
{
	bool player_win = false;
	REPD(i, 0, 9)
	{
		if (colors[i] == -1LL)
		{
			colors[i] = player_color;

			auto [is_ended, will_win] = game_should_end(As, colors, player_color, color_count + 1LL);
			if (is_ended)
			{
				player_win |= will_win;
			}
			else
			{
				player_win |= !paint_color(As, colors, 1LL - player_color, color_count + 1LL);
			}

			colors[i] = -1LL;
		}
	}

	return player_win;
}

int solve()
{
	// ll N, M;
	// cin >> N >> M;

	auto As = make_multiple_vector(0LL, 9LL);
	REPD(i, 0, 9)
	{
		cin >> As[i];
	}

	auto colors = make_multiple_vector(-1LL, 9LL);
	auto result = paint_color(As, colors, 0LL, 0LL);
	cout << (result ? "Takahashi" : "Aoki") << endl;

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
	// REPD(i, 0, t)
	// {
	// 	solve();
	// }

	return 0;
}
