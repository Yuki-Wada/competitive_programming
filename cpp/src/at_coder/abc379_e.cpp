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
#include <random>

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

#define MAX_VALUE 9223372036854775807LL

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
using pair1d = vector<llpair>;
using pair2d = vector2d<llpair>;

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

ll N;
string S;

int solve()
{
	cin >> N >> S;
	ll1d coefs(N);
	ll1d accums(N + 1LL);
	REPD(i, 0, N)
	{
		auto ch = ll(S[i] - '0');
		coefs[i] = (i + 1LL) * ch;
	}
	REPD(i, 0, N)
	{
		accums[i + 1LL] = accums[i] + coefs[i];
	}
	reverse(accums.begin(), accums.end());

	ll1d results;
	results.reserve(N * 2LL);
	ll incr = 0;
	REPD(i, 0, N)
	{
		incr += accums[i];
		results.emplace_back(incr % 10LL);
		incr /= 10LL;
	}
	while(incr > 0LL) {
		results.emplace_back(incr % 10LL);
		incr /= 10LL;
	}

	reverse(results.begin(), results.end());
	REPD(i, 0, results.size())
	{
		cout << results[i];
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
	// REPD(i, 0, t)
	// {
	// 	solve();
	// }

	return 0;
}
