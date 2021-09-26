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

void print(const vector<bool> &v)
{
	ll n = v.size();
	vector<ll> bs;
	bs.reserve(n);

	REPD(k, 0, n)
	if (v[k])
		bs.emplace_back(k + 1LL);

	cout << bs.size() << " ";
	REPD(k, 0, bs.size())
	{
		cout << bs[k];
		if (k + 1LL < bs.size())
			cout << " ";
		else
			cout << endl;
	}
};

int solve()
{
	ll n;
	cin >> n;

	vector<ll> as(n);
	REPD(i, 0, n)
	cin >> as[i];

	vector<vector<bool>> mass(200, vector<bool>(n, false));

	vector<bool> found(200, false), next_search(200, false);
	REPD(i, 0, as.size())
	{
		auto a = as[i];
		REPD(f, 0, 200)
		{
			if (f != 0 && !found[f])
				continue;

			REPD(j, 0, i)
			{
				if (f == 0 && found[0])
				{
					cout << "Yes" << endl;
					if (a % 200LL != 0LL)
					{
						mass[0][i] = true;
						print(mass[0]);
						mass[a % 200LL][i] = true;
						print(mass[a % 200LL]);
					}
					else
					{
						print(mass[0]);
						mass[0][i] = true;
						print(mass[0]);
					}
					return 0;
				}
				if (found[(f + a) % 200LL])
				{
					cout << "Yes" << endl;
					print(mass[(f + a) % 200LL]);
					mass[f][i] = true;
					print(mass[f]);

					return 0;
				}
			}

			REPD(j, 0, i)
			{
				mass[(f + a) % 200LL][j] = mass[f][j];
			}
			mass[(f + a) % 200LL][i] = true;
			next_search[(f + a) % 200LL] = true;
		}

		REPD(f, 0, 200)
		found[f] = next_search[f];
	}

	cout << "No" << endl;

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
