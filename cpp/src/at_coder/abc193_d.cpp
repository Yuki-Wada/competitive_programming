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

//debug
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

template <class Integer>
inline Integer get_power(Integer base, ull exponential)
{
	Integer result = 1;
	while (exponential >= 1)
	{
		if (exponential & 1)
		{
			result = result * base;
		}
		base = base * base;
		exponential >>= 1;
	}

	return result;
}

ll eval(string str, ll i)
{
	vector<ll> cards(10);

	++cards[i];
	REPD(i, 0, 4)
	{
		++cards[str[i] - '0'];
	}

	ll res = 0;
	ll pow10 = 1;
	REPD(i, 1, 10)
	{
		res += i * get_power(10LL, cards[i]);
	}

	return res;
}

int solve()
{
	ll K;
	cin >> K;

	string takahashi, aoki;
	cin >> takahashi >> aoki;

	vector<ll> remains(10, K);
	REPD(i, 1, 10)
	REPD(j, 0, 4)
	{
		if ((takahashi[j] - '0') == i)
			--remains[i];
		if ((aoki[j] - '0') == i)
			--remains[i];
	}

	ll all_comb = (K * 9LL - 8LL) * (K * 9LL - 9LL);
	ll win_comb = 0LL;

	REPD(i, 1, 10)
	REPD(j, 1, 10)
	{
		if (i == j)
		{
			if (remains[i] >= 2)
			{
				if (eval(takahashi, i) > eval(aoki, i))
				{
					win_comb += remains[i] * (remains[i] - 1LL);
				}
			}
		}
		else
		{
			if (remains[i] >= 1 && remains[j] >= 1)
			{
				if (eval(takahashi, i) > eval(aoki, j))
				{
					win_comb += remains[i] * remains[j];
				}
			}
		}
	}

	cout << std::fixed << std::setprecision(8) << double(win_comb) / double(all_comb) << endl;

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
