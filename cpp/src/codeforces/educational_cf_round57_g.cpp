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

ll default_number_theoretic_transform_mod = 998244353LL;	// 998244353 = 119 * 2^23 + 1
ll default_number_theoretic_transform_primitive_root = 3LL; // primitive root of 998244353

// Fast Modulo Transform
void fmt_impl(
	const vector<ll> &function,
	vector<ll> &transformed,
	vector<ll> &stored,
	ll start,
	ll skip,
	ll mod = default_number_theoretic_transform_mod,
	ll primitive_root = default_number_theoretic_transform_primitive_root)
{
	ll degree = function.size() / skip;

	if (degree == 1LL)
	{
		transformed[start] = function[start];
		return;
	}

	auto get_mod = [&](const ll &n) {
		return (n % mod + mod) % mod;
	};

	auto get_mod_power = [&](ll base, ull exponential) {
		ll result = 1;
		while (exponential >= 1)
		{
			if (exponential & 1)
			{
				result *= base;
				result = get_mod(result);
			}
			base *= base;
			base = get_mod(base);
			exponential >>= 1;
		}

		return result;
	};

	fmt_impl(function, transformed, stored, start, skip * 2LL, mod, primitive_root);
	fmt_impl(function, transformed, stored, start + skip, skip * 2LL, mod, primitive_root);
	for (ll i = 0; i < degree; ++i)
	{
		stored[start + skip * i] = transformed[start + skip * i];
	}

	const ll xi = get_mod_power(primitive_root, (mod - 1LL) / degree);
	ll power_of_xi = 1;
	for (ll i = 0; i < degree; ++i)
	{
		auto res_i = i % (degree / 2LL);
		transformed[start + skip * i] = stored[start + skip * res_i * 2LL] + stored[start + skip * (res_i * 2LL + 1LL)] * power_of_xi;
		power_of_xi *= xi;
		transformed[start + skip * i] = get_mod(transformed[start + skip * i]);
		power_of_xi = get_mod(power_of_xi);
	}
}

vector<ll> fmt(
	const vector<ll> &function,
	ll mod = default_number_theoretic_transform_mod,
	ll primitive_root = default_number_theoretic_transform_primitive_root)
{
	auto degree = function.size();
	if (degree == 0LL)
		throw runtime_error("配列の要素数は 1 以上である必要があります。");
	if ((degree & (degree - 1LL)) != 0LL)
		throw runtime_error("配列の要素数は 2 のべき乗である必要があります。");
	if ((mod - 1LL) % degree != 0LL)
		throw runtime_error("mod - 1 は配列の要素数で割り切れる必要があります。");

	vector<ll> transformed(degree, 0);
	vector<ll> stored(degree, 0);
	fmt_impl(function, transformed, stored, 0LL, 1LL, mod, primitive_root);
	return transformed;
}
vector<ll> inv_fmt(
	const vector<ll> &function,
	ll mod = default_number_theoretic_transform_mod,
	ll primitive_root = default_number_theoretic_transform_primitive_root)
{
	auto get_mod = [&](const ll &n) {
		return (n % mod + mod) % mod;
	};

	auto get_mod_inverse = [&](const ll &n, ll mod) -> ll {
		struct BezoutsIdentitySolver
		{
			static pair<ll, ll> execute(ll a, ll b)
			{
				if (b == 0)
				{
					return {1, 0};
				}
				auto sol = execute(b, a % b);
				return {sol.second, sol.first - (a / b) * sol.second};
			}
		};
		auto sol = BezoutsIdentitySolver::execute(n, mod);
		if (n * sol.first + mod * sol.second != 1)
		{
			return -1;
		}
		return get_mod(sol.first);
	};

	auto inverse_primitive_root = get_mod_inverse(primitive_root, mod);
	vector<ll> transformed = fmt(
		function, mod, inverse_primitive_root);
	auto inverse_n = get_mod_inverse(function.size(), mod);
	for (ull i = 0; i < function.size(); ++i)
	{
		transformed[i] = get_mod(transformed[i] * inverse_n);
	}

	return transformed;
}

inline ll get_highest_one_bit(ll a)
{
	while ((a & (a - 1)) != 0)
	{
		a = a & (a - 1);
	}
	return a;
}

int solve()
{
	ll n, k;
	cin >> n >> k;

	ull size = get_highest_one_bit(9LL * n / 2LL) * 2LL;
	vector<ll> functions(size, 0);
	ll d;
	for (ll i = 0; i < k; ++i)
	{
		cin >> d;
		functions[d] = 1;
	}

	auto func_transformed = fmt(functions);
	vector<ll> res_transformed(size, 1);
	ll m = n / 2LL;
	while (m > 0)
	{
		for (ull i = 0; i < size; ++i)
		{
			if (m % 2LL == 1LL)
			{
				res_transformed[i] *= func_transformed[i];
				res_transformed[i] %= default_number_theoretic_transform_mod;
			}
			func_transformed[i] *= func_transformed[i];
			func_transformed[i] %= default_number_theoretic_transform_mod;
		}
		m /= 2LL;
	}

	auto results = inv_fmt(res_transformed);

	ll res = 0;
	for (ull i = 0; i < size; ++i)
	{
		res += (results[i] * results[i]);
		res %= default_number_theoretic_transform_mod;
	}

	cout << res << endl;

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
