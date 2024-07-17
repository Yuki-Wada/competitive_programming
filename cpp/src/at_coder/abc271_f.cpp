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

vector<vector<long long>> comb(long long n, long long r)
{
	std::vector<bool> b(n);
	std::fill(b.end() - r, b.end(), true);

	vector<vector<long long>> combs = {};
	do
	{
		vector<long long> c = {};
		for (long long i = 0; i < n; i++)
			if (b[i])
				c.push_back(i + 1);
		combs.push_back(c);
	} while (std::next_permutation(b.begin(), b.end()));
	return combs;
}

int solve()
{
	ll N;
	cin >> N;

	auto as = make_multiple_vector(0LL, N, N);
	for (ll i = 0; i < N; ++i)
		for (ll j = 0; j < N; ++j)
		{
			cin >> as[i][j];
		}

	auto count_bits = [N](auto &v)
	{
		ll cnt = 0;
		for (ll i = 0; i < N; ++i)
		{
			if (((v >> i) & 1LL) == 1LL)
			{
				++cnt;
			}
		}
		return cnt;
	};

	map<pair<ll, ll>, ll> upper_left_dict;
	map<pair<ll, ll>, ll> lower_right_dict;

	for (ll bits = 0; bits < (1LL << (N - 1)); ++bits)
	{
		ll ul_i = 0;
		ll ul_j = 0;
		ll lr_i = N - 1;
		ll lr_j = N - 1;
		ll ul = as[ul_i][ul_j];
		ll lr = as[lr_i][lr_j];
		for (ll d = 0; d + 1 < N; ++d)
		{
			if (((bits >> d) & 1LL) == 1LL)
			{
				ul_i = ul_i + 1;
				lr_j = lr_j - 1;
			}
			else
			{
				ul_j = ul_j + 1;
				lr_i = lr_i - 1;
			}
			ul = ul ^ as[ul_i][ul_j];
			lr = lr ^ as[lr_i][lr_j];
		}

		lr = lr ^ as[lr_i][lr_j];

		ll r = count_bits(bits);
		upper_left_dict[make_pair(ul, r)] += 1;
		lower_right_dict[make_pair(lr, r)] += 1;
	}

	ll res = 0;
	REPI(kv, upper_left_dict)
	{
		auto k = kv.first;
		if (lower_right_dict.count(k) > 0)
		{
			res += upper_left_dict[k] * lower_right_dict[k];
		}
	}

	cout << res << endl;

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
