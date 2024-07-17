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

int solve()
{
	ll N, S;
	cin >> N >> S;
	vector<ll> diffs(N);

	ll a, b;
	vector<bool> are_tops_high;
	for (ll i = 0; i < N; ++i)
	{
		cin >> a >> b;
		auto minab = min(a, b);
		auto maxab = max(a, b);
		diffs[i] = maxab - minab;
		S -= minab;
		are_tops_high.emplace_back(maxab == a);
	}

	if (S < 0)
	{
		cout << "No" << endl;
		return 0;
	}

	vector<optional<set<ll>>> dps(S + 1, nullopt);
	dps[0] = set<ll>();
	for (ll i = 0; i < N; ++i)
	{
		auto diff = diffs[i];
		for (ll j = S; j >= 0LL; --j)
		{
			if (j + diff > S)
			{
				continue;
			}
			if (dps[j].has_value())
			{
				dps[j + diff] = dps[j].value();
				dps[j + diff].value().insert(i);
			}
		}
	}

	if (!dps[S].has_value())
	{
		cout << "No" << endl;
		return 0;
	}
	cout << "Yes" << endl;
	for (ll i = 0; i < N; ++i)
	{
		auto set = dps[S].value();
		if (are_tops_high[i] ^ (set.find(i) != set.end()))
		{
			cout << "T";
		}
		else
		{
			cout << "H";
		}
	}
	cout << endl;

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
