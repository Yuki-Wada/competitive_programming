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
static constexpr ll MOD = 998244353LL;
static constexpr double PI = 3.14159265358979323846;

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
ll pow10 = 10000000LL;

inline ll digit(ull a)
{
	ll res = 0;
	while (a > 0ULL)
	{
		res += a % 10ULL;
		a /= 10ULL;
	}
	return res;
}

vector<vector<vector<ll>>> compute_mat(ll l1, ll l2)
{
	auto mat = make_multiple_vector(0LL, 64, 127, 127);
	for (ll i = l1; i <= l2; ++i)
	{
		auto idx1 = digit(i);
		for (ll j = 1; j < 127; ++j)
		{
			auto idx2 = i % j;
			++mat[idx1][j][idx2];
		}
	}

	return mat;
}

tuple<vector<vector<vector<ll>>>, vector<vector<vector<ll>>>, vector<vector<vector<ll>>>> compute_mats(ll l1, ll l2, ll l3)
{
	tuple<vector<vector<vector<ll>>>, vector<vector<vector<ll>>>, vector<vector<vector<ll>>>> outputs;
	auto mat = make_multiple_vector(0LL, 64, 127, 127);

	for (ll i = 0LL; i <= max({l1, l2, l3}); ++i)
	{
		auto idx1 = digit(i);
		for (ll j = 1; j < 127; ++j)
		{
			auto idx2 = i % j;
			++mat[idx1][j][idx2];
		}
		if (i == l1)
			get<0>(outputs) = mat;
		if (i == l2)
			get<1>(outputs) = mat;
		if (i == l3)
			get<2>(outputs) = mat;
	}

	return outputs;
}

ll calc(const vector<vector<vector<ll>>> &mat1, const vector<vector<vector<ll>>> &mat2)
{
	ll res = 0;
	for (ll i1 = 0; i1 < 64; ++i1)
		for (ll i2 = 0; i2 < 64; ++i2)
		{
			auto digit = i1 + i2;
			if (digit == 0LL)
				continue;
			for (ll r1 = 0; r1 < digit; ++r1)
				for (ll r2 = 0; r2 < digit; ++r2)
				{
					if (((r1 * pow10 + r2) % digit) != 0LL)
						continue;
					res += mat1[i1][digit][r1] * mat2[i2][digit][r2];
				}
		}

	return res;
}

int solve()
{
	cin >> N;

	auto mat1 = compute_mat(N / pow10, N / pow10);
	auto [mat2, mat3, mat4] = compute_mats((N % pow10), (N - (N % pow10) - 1LL) / pow10, (pow10 - 1LL));

	ll res = 0;
	res += calc(mat1, mat2);

	if ((N - (N % pow10) - 1LL) >= 0LL)
		res += calc(mat3, mat4);

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
	// REPD(i, 0, t)
	// {
	// 	solve();
	// }

	return 0;
}
