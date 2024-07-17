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
	ll N, M, K;
	cin >> N >> M >> K;

	vector<ll> As(N);
	REPD(i, 0, N)
	{
		cin >> As[i];
	}

	vector<ll> bufs(M);
	REPD(i, 0, M)
	{
		bufs[i] = As[i];
	}

	sort(bufs.begin(), bufs.end());

	multiset<ll> lower_set, upper_set;
	ll res = 0;
	REPD(i, 0, K)
	{
		lower_set.insert(bufs[i]);
		res += bufs[i];
	}
	REPD(i, K, M)
	{
		upper_set.insert(bufs[i]);
	}

	cout << res;

	ll v;
	REPD(i, 1, N - M + 1)
	{
		auto r = As[i + M - 1], l = As[i - 1];

		v = *lower_set.rbegin();
		if (l > v)
		{
			upper_set.erase(upper_set.find(l));
		}
		else
		{
			lower_set.erase(lower_set.find(l));
			res -= l;
		}

		if (r > v)
		{
			upper_set.insert(r);
		}
		else
		{
			lower_set.insert(r);
			res += r;
		}

		if (lower_set.size() == K + 1LL)
		{
			v = *lower_set.rbegin();
			res -= v;
			lower_set.erase(lower_set.find(v));
			upper_set.insert(v);
		}
		else if (lower_set.size() == K - 1LL)
		{
			v = *upper_set.begin();
			res += v;
			upper_set.erase(upper_set.find(v));
			lower_set.insert(v);
		}

		cout << " " << res;
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
