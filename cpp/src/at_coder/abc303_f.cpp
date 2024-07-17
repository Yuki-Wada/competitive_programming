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
	vector<pair<ll, ll>> tds;
	vector<ll> times;
	vector<ll> dameges;
	vector<ll> max_totals;
	vector<ll> max_singles;

public:
	Solver(ll H) {}
	void register_value(ll t, ll d)
	{
		tds.emplace_back(t, d);
	}
	void setup()
	{
		sort(tds.begin(), tds.end());
		auto [prev_t, prev_d] = tds[0];
		for (ll i = 1; i < tds.size(); ++i)
		{
			auto [a, b] = tds[i];
			if (prev_t != a)
			{
				times.emplace_back(prev_t);
				dameges.emplace_back(prev_d);
			}
			prev_t = a, prev_d = b;
		}
		times.emplace_back(prev_t);
		dameges.emplace_back(prev_d);

		ll max_total = 0;
		for (ll i = 0; i < times.size(); ++i)
		{
			max_total = max(max_total, times[i] * dameges[i]);
			max_totals.emplace_back(max_total);
		}
		ll max_single = 0;
		for (ll i = times.size() - 1LL; i >= 0LL; --i)
		{
			max_single = max(max_single, dameges[i]);
			max_singles.emplace_back(max_single);
		}
		reverse(max_singles.begin(), max_singles.end());
	}
	ll ceil(ll m, ll n)
	{
		return (m + n - 1LL) / n;
	}
	bool compare_and_subtract(ll &a, ll b, ll c)
	{
		if (b == 0LL)
			return false;
		if (ceil(a, b) <= c)
			return true;
		a -= b * c;
		return false;
	}
	bool is_executable(ll turn, ll H)
	{
		ll remain = H;
		for (ll i = 0; i < times.size(); ++i)
		{
			auto curr_time = i >= 1LL ? times[i - 1LL] : 1LL;
			auto next_time = times[i];
			auto end_time = min(turn, next_time - 1LL);
			if (curr_time == next_time)
				continue;

			auto maxtotal = i >= 1LL ? max_totals[i - 1LL] : 0LL;
			auto maxsingle = max_singles[i];
			auto inflection_time = maxtotal / maxsingle + 1LL;

			inflection_time = max(curr_time, inflection_time);
			inflection_time = min(inflection_time, end_time + 1LL);
			if (compare_and_subtract(remain, maxsingle, (inflection_time + end_time) * (end_time - inflection_time + 1LL) / 2LL))
				return true;
			if (compare_and_subtract(remain, maxtotal, (inflection_time - curr_time)))
				return true;

			if (turn <= next_time - 1LL)
				return remain <= 0LL;
		}

		auto curr_time = times.back();
		auto maxtotal = max_totals.back();
		return compare_and_subtract(remain, maxtotal, (turn - curr_time + 1LL));
	}
};

int solve()
{
	ll N, H;
	cin >> N >> H;

	Solver solver(H);
	ll t, d;
	REPD(i, 0, N)
	{
		cin >> t >> d;
		solver.register_value(t, d);
	}
	solver.setup();

	ll low = 0, high = H, middle = (low + high) / 2LL;
	while (high - low >= 2LL)
	{
		if (solver.is_executable(middle, H))
			high = middle;
		else
			low = middle;
		middle = (low + high) / 2LL;
	}

	cout << high << endl;

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
