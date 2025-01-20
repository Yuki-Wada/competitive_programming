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

// type alias
using ll = long long;
using ull = unsigned long long;
using comp = complex<double>;
using llpair = pair<ll, ll>;
template <class T>
using vector2d = vector<vector<T>>;
template <class T>
using vector3d = vector<vector<vector<T>>>;
using ll1d = vector<ll>;
using ll2d = vector2d<ll>;
using ll3d = vector3d<ll>;

// constant
static const ll MOD = 998244353LL;
static const double PI = 3.14159265358979323846;

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

ll M, N, K;
ll2d areas;
ll2d J_counts;
ll2d O_counts;
ll2d I_counts;

int solve()
{
	cin >> M >> N >> K;
	areas = make_multiple_vector(0LL, M, N);
	J_counts = make_multiple_vector(0LL, M + 1LL, N + 1LL);
	O_counts = make_multiple_vector(0LL, M + 1LL, N + 1LL);
	I_counts = make_multiple_vector(0LL, M + 1LL, N + 1LL);

	string line;
	REPD(i, 0, M)
	{
		cin >> line;
		REPD(j, 0, N)
		{
			if (line[j] == 'J')
			{
				areas[i][j] = 0;
			}
			else if (line[j] == 'O')
			{

				areas[i][j] = 1;
			}
			else if (line[j] == 'I')
			{
				areas[i][j] = 2;
			}
		}
	}

	REPD(i, 0, M)
	{
		ll line_J_count = 0;
		ll line_O_count = 0;
		ll line_I_count = 0;
		REPD(j, 0, N)
		{
			if (areas[i][j] == 0)
			{
				++line_J_count;
			}
			else if (areas[i][j] == 1)
			{
				++line_O_count;
			}
			else if (areas[i][j] == 2)
			{
				++line_I_count;
			}

			J_counts[i + 1LL][j + 1LL] = J_counts[i][j + 1LL] + line_J_count;
			O_counts[i + 1LL][j + 1LL] = O_counts[i][j + 1LL] + line_O_count;
			I_counts[i + 1LL][j + 1LL] = I_counts[i][j + 1LL] + line_I_count;
		}
	}

	ll a, b, c, d;
	REPD(k, 0, K)
	{
		cin >> a >> b >> c >> d;
		ll J_res = J_counts[c][d] - J_counts[a - 1LL][d] - J_counts[c][b - 1LL] + J_counts[a - 1LL][b - 1LL];
		ll O_res = O_counts[c][d] - O_counts[a - 1LL][d] - O_counts[c][b - 1LL] + O_counts[a - 1LL][b - 1LL];
		ll I_res = I_counts[c][d] - I_counts[a - 1LL][d] - I_counts[c][b - 1LL] + I_counts[a - 1LL][b - 1LL];
		cout << J_res << " " << O_res << " " << I_res << endl;
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
	// REPD(i, 0, t)
	// {
	// 	solve();
	// }

	return 0;
}
