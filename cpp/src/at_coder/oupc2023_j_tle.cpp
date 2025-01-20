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
using vector1d = vector<T>;
template <class T>
using vector2d = vector<vector<T>>;
template <class T>
using vector3d = vector<vector<vector<T>>>;
using ll1d = vector<ll>;
using ll2d = vector2d<ll>;
using ll3d = vector3d<ll>;

// constant
static const ll MOD = 998244353LL;
// static const ll MOD = (1LL << 61LL) - 1LL;
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

ll getModValue(const ll &n, ll mod)
{
	return (n % mod + mod) % mod;
}

// computational complexity: o(log(max(a, b)))
inline pair<ll, ll> getBezoutsIdentitySolution(ll a, ll b)
{
	if (b == ll(0))
		return {ll(1) / a, ll(0)};
	auto sol = getBezoutsIdentitySolution(b, a % b);
	return {sol.second, sol.first - (a / b) * sol.second};
}

// computational complexity: o(log(max(n, mod)))
inline ll getModInverse(const ll &n, ll mod)
{
	auto sol = getBezoutsIdentitySolution(n, mod);
	return getModValue(sol.first, mod);
}

template <unsigned int Mod>
class ModInt;
template <unsigned int Mod>
ModInt<Mod> &operator+=(ModInt<Mod> &lhs, const ModInt<Mod> &rhs);
template <unsigned int Mod>
ModInt<Mod> &operator+=(ModInt<Mod> &lhs, const ll &rhs);
template <unsigned int Mod>
ModInt<Mod> &operator-=(ModInt<Mod> &lhs, const ModInt<Mod> &rhs);
template <unsigned int Mod>
ModInt<Mod> &operator-=(ModInt<Mod> &lhs, const ll &rhs);
template <unsigned int Mod>
ModInt<Mod> &operator*=(ModInt<Mod> &lhs, const ModInt<Mod> &rhs);
template <unsigned int Mod>
ModInt<Mod> &operator*=(ModInt<Mod> &lhs, const ll &rhs);
template <unsigned int Mod>
ModInt<Mod> &operator/=(ModInt<Mod> &lhs, const ModInt<Mod> &rhs);
template <unsigned int Mod>
ModInt<Mod> &operator/=(ModInt<Mod> &lhs, const ll &rhs);
template <unsigned int Mod>
std::istream &operator>>(std::istream &lhs, ModInt<Mod> &rhs);

template <unsigned int Mod>
class ModInt
{
private:
	ll n_;

public:
	ModInt() : n_(getModValue(0, Mod)) {}
	ModInt(ll n) : n_(getModValue(n, Mod)) {}

	ll mod() const { return Mod; }
	ll n() const { return n_; }

	friend ModInt &operator+= <>(ModInt &lhs, const ModInt &rhs);
	friend ModInt &operator+= <>(ModInt &lhs, const ll &rhs);
	friend ModInt &operator-= <>(ModInt &lhs, const ModInt &rhs);
	friend ModInt &operator-= <>(ModInt &lhs, const ll &rhs);
	friend ModInt &operator*= <>(ModInt &lhs, const ModInt &rhs);
	friend ModInt &operator*= <>(ModInt &lhs, const ll &rhs);
	friend ModInt &operator/= <>(ModInt &lhs, const ModInt &rhs);
	friend ModInt &operator/= <>(ModInt &lhs, const ll &rhs);
	friend std::istream &operator>> <>(std::istream &lhs, ModInt &rhs);
};

template <unsigned int Mod>
inline ModInt<Mod> operator+(const ModInt<Mod> &lhs, const ModInt<Mod> &rhs) { return lhs.n() + rhs.n(); }
template <unsigned int Mod>
inline ModInt<Mod> operator+(const ModInt<Mod> &lhs, const ll &rhs) { return lhs.n() + getModValue(rhs, Mod); }
template <unsigned int Mod>
inline ModInt<Mod> operator+(const ll &lhs, const ModInt<Mod> &rhs) { return getModValue(lhs, Mod) + rhs.n(); }
template <unsigned int Mod>
inline ModInt<Mod> &operator+=(ModInt<Mod> &lhs, const ModInt<Mod> &rhs)
{
	lhs.n_ = getModValue(lhs.n() + rhs.n(), Mod);
	return lhs;
}
template <unsigned int Mod>
inline ModInt<Mod> &operator+=(ModInt<Mod> &lhs, const ll &rhs)
{
	lhs.n_ = getModValue(lhs.n() + getModValue(rhs, Mod), Mod);
	return lhs;
}
template <unsigned int Mod>
inline ModInt<Mod> operator-(const ModInt<Mod> &lhs, const ModInt<Mod> &rhs) { return lhs.n() - rhs.n(); }
template <unsigned int Mod>
inline ModInt<Mod> operator-(const ModInt<Mod> &lhs, const ll &rhs) { return lhs.n() - getModValue(rhs, Mod), Mod; }
template <unsigned int Mod>
inline ModInt<Mod> operator-(const ll &lhs, const ModInt<Mod> &rhs) { return getModValue(lhs, Mod) - rhs.n(); }
template <unsigned int Mod>
inline ModInt<Mod> &operator-=(ModInt<Mod> &lhs, const ModInt<Mod> &rhs)
{
	lhs.n_ = getModValue(lhs.n() - rhs.n(), Mod);
	return lhs;
}
template <unsigned int Mod>
inline ModInt<Mod> &operator-=(ModInt<Mod> &lhs, const ll &rhs)
{
	lhs.n_ = getModValue(lhs.n() - getModValue(rhs, Mod), Mod);
	return lhs;
}
template <unsigned int Mod>
inline ModInt<Mod> operator*(const ModInt<Mod> &lhs, const ModInt<Mod> &rhs) { return lhs.n() * rhs.n(); }
template <unsigned int Mod>
inline ModInt<Mod> operator*(const ModInt<Mod> &lhs, const ll &rhs) { return lhs.n() * getModValue(rhs, Mod); }
template <unsigned int Mod>
inline ModInt<Mod> operator*(const ll &lhs, const ModInt<Mod> &rhs) { return getModValue(lhs, Mod) * rhs.n(); }
template <unsigned int Mod>
inline ModInt<Mod> &operator*=(ModInt<Mod> &lhs, const ModInt<Mod> &rhs)
{
	lhs.n_ = getModValue(lhs.n() * rhs.n(), Mod);
	return lhs;
}
template <unsigned int Mod>
inline ModInt<Mod> &operator*=(ModInt<Mod> &lhs, const ll &rhs)
{
	lhs.n_ = getModValue(lhs.n() * getModValue(rhs, Mod), Mod);
	return lhs;
}
template <unsigned int Mod>
inline ModInt<Mod> operator/(const ModInt<Mod> &lhs, const ModInt<Mod> &rhs) { return lhs.n() * getModInverse(rhs.n(), Mod); }
template <unsigned int Mod>
inline ModInt<Mod> operator/(const ModInt<Mod> &lhs, const ll &rhs) { return lhs.n() * getModInverse(getModValue(rhs, Mod), Mod); }
template <unsigned int Mod>
inline ModInt<Mod> operator/(const ll &lhs, const ModInt<Mod> &rhs) { return getModValue(lhs, Mod) * getModInverse(rhs.n(), Mod); }
template <unsigned int Mod>
inline ModInt<Mod> &operator/=(ModInt<Mod> &lhs, const ModInt<Mod> &rhs)
{
	lhs.n_ = getModValue(lhs.n() * getModInverse(rhs.n(), Mod), Mod);
	return lhs;
}
template <unsigned int Mod>
inline ModInt<Mod> &operator/=(ModInt<Mod> &lhs, const ll &rhs)
{
	lhs.n_ = getModValue(lhs.n() * getModInverse(getModValue(rhs, Mod), Mod), Mod);
	return lhs;
}
template <unsigned int Mod>
inline bool operator==(const ModInt<Mod> &lhs, const ModInt<Mod> &rhs) { return lhs.n() == rhs.n(); }
template <unsigned int Mod>
inline bool operator==(const ModInt<Mod> &lhs, const ll &rhs) { return lhs.n() == getModValue(rhs, Mod); }
template <unsigned int Mod>
inline bool operator==(const ll &lhs, const ModInt<Mod> &rhs) { return getModValue(lhs, Mod) == rhs.n(); }

template <unsigned int Mod>
std::ostream &operator<<(std::ostream &lhs, const ModInt<Mod> &rhs)
{
	return lhs << rhs.n();
}

template <unsigned int Mod>
std::istream &operator>>(std::istream &lhs, ModInt<Mod> &rhs)
{
	lhs >> rhs.n_;
	return lhs;
}

using rll = ModInt<MOD>;

vector<rll> get_exclamations(ull n)
{
	vector<rll> exclamations(n + 1ULL);
	exclamations[0] = 1LL;
	for (ll i = 1; i <= n; ++i)
		exclamations[i] = exclamations[i - 1] * i;

	return exclamations;
}

rll pow(rll base, ll t)
{
	rll res = 1;
	while (t > 0LL)
	{
		if (t % 2LL == 1LL)
		{
			res *= base;
		}
		base *= base;
		t >>= 1LL;
	}
	return res;
}

ll N, M;

ll DEFAULT_NUMBER_THEORETIC_TRANSFORM_MOD = 998244353LL;	// 998244353 = 119 * 2^23 + 1
ll DEFAULT_NUMBER_THEORETIC_TRANSFORM_PRIMITIVE_ROOT = 3LL; // primitive root of 998244353

// Fast Modulo Transform
void fmt_impl(
	const vector<ll> &function,
	vector<ll> &transformed,
	vector<ll> &stored,
	ll start,
	ll skip,
	ll mod,
	ll xi)
{
	ll degree = function.size() / skip;

	if (degree == 1LL)
	{
		transformed[start] = function[start];
		return;
	}

	auto get_mod = [&](const ll n)
	{
		if (n < 0LL)
		{
			ll minus_mod_n = (-n) % mod;
			if (minus_mod_n == 0LL)
			{
				return 0LL;
			}
			return mod - minus_mod_n;
		}
		return n % mod;
	};

	fmt_impl(function, transformed, stored, start, skip * 2LL, mod, get_mod(xi * xi));
	fmt_impl(function, transformed, stored, start + skip, skip * 2LL, mod, get_mod(xi * xi));
	for (ll i = 0; i < degree; ++i)
	{
		stored[start + skip * i] = transformed[start + skip * i];
	}

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
	ll mod = DEFAULT_NUMBER_THEORETIC_TRANSFORM_MOD,
	ll primitive_root = DEFAULT_NUMBER_THEORETIC_TRANSFORM_PRIMITIVE_ROOT)
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

	auto get_mod = [&](const ll &n)
	{
		if (n < 0LL)
		{
			ll minus_mod_n = (-n) % mod;
			if (minus_mod_n == 0LL)
			{
				return 0LL;
			}
			return mod - minus_mod_n;
		}
		return n % mod;
	};

	auto get_mod_power = [&](ll base, ull exponential)
	{
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
	ll xi = get_mod_power(primitive_root, (mod - 1LL) / degree);
	fmt_impl(function, transformed, stored, 0LL, 1LL, mod, xi);
	return transformed;
}

vector<ll> inv_fmt(
	const vector<ll> &function,
	ll mod = DEFAULT_NUMBER_THEORETIC_TRANSFORM_MOD,
	ll primitive_root = DEFAULT_NUMBER_THEORETIC_TRANSFORM_PRIMITIVE_ROOT)
{
	auto get_mod = [&](const ll &n)
	{
		if (n < 0LL)
		{
			ll minus_mod_n = (-n) % mod;
			if (minus_mod_n == 0LL)
			{
				return 0LL;
			}
			return mod - minus_mod_n;
		}
		return n % mod;
	};

	auto get_mod_inverse = [&](const ll n) -> ll
	{
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

	auto inverse_primitive_root = get_mod_inverse(primitive_root);
	vector<ll> transformed = fmt(
		function, mod, inverse_primitive_root);
	auto inverse_n = get_mod_inverse(function.size());
	for (ull i = 0; i < function.size(); ++i)
	{
		transformed[i] = get_mod(transformed[i] * inverse_n);
	}

	return transformed;
}

vector<ll> multiple_polynomials(
	const vector<ll> &function1,
	const vector<ll> &function2,
	ll mod = DEFAULT_NUMBER_THEORETIC_TRANSFORM_MOD,
	ll primitive_root = DEFAULT_NUMBER_THEORETIC_TRANSFORM_PRIMITIVE_ROOT)
{
	auto get_mod = [&](const ll n)
	{
		if (n < 0LL)
		{
			ll minus_mod_n = (-n) % mod;
			if (minus_mod_n == 0LL)
			{
				return 0LL;
			}
			return mod - minus_mod_n;
		}
		return n % mod;
	};

	ull degree_sum = function1.size() + function2.size();
	ull array_size = 1LL;
	while (degree_sum > 0)
	{
		array_size <<= 1LL;
		degree_sum >>= 1LL;
	}

	vector<ll> function1_fmt_container(array_size, 0LL);
	vector<ll> function2_fmt_container(array_size, 0LL);
	for (ull i = 0; i < function1.size(); ++i)
	{
		function1_fmt_container[i] = function1[i];
	}
	for (ull i = 0; i < function2.size(); ++i)
	{
		function2_fmt_container[i] = function2[i];
	}

	auto source_container = fmt(function1_fmt_container, mod, primitive_root);
	auto target_container = fmt(function2_fmt_container, mod, primitive_root);
	for (ull i = 0; i < array_size; ++i)
	{
		source_container[i] *= target_container[i];
		source_container[i] = get_mod(source_container[i]);
	}

	auto result = inv_fmt(source_container, mod);

	return result;
}

vector<ll> compute_inverse_power_series(
	const vector<ll> &original_power_series,
	ull required_degree,
	ll mod = DEFAULT_NUMBER_THEORETIC_TRANSFORM_MOD,
	ll primitive_root = DEFAULT_NUMBER_THEORETIC_TRANSFORM_PRIMITIVE_ROOT)
{
	auto get_mod = [&](const ll n)
	{
		if (n < 0LL)
		{
			ll minus_mod_n = (-n) % mod;
			if (minus_mod_n == 0LL)
			{
				return 0LL;
			}
			return mod - minus_mod_n;
		}
		return n % mod;
	};
	auto get_highest_bit_place = [](ll x)
	{
		ll bit_place = 0;
		while (x > 0LL)
		{
			x >>= 1LL;
			++bit_place;
		}
		return bit_place;
	};
	auto get_mod_inverse = [&](const ll n) -> ll
	{
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

	ll original_degree = original_power_series.size() - 1LL;
	ll loop_count = get_highest_bit_place(required_degree);
	ll series_degree = 1LL << get_highest_bit_place(loop_count * (1LL << loop_count));

	vector<ll> g(series_degree);
	vector<ll> f(series_degree);

	g[0] = get_mod_inverse(original_power_series[0]);
	auto fmt_g = fmt(g, mod, primitive_root);

	for (ll i = 0; i < loop_count; ++i)
	{
		auto f_degree = min(ull(original_power_series.size()), ull(1LL << (i + 1LL)));
		for (ull j = 0; j < f_degree; ++j)
		{
			f[j] = original_power_series[j];
		}

		auto fmt_f = fmt(f, mod, primitive_root);
		for (ull j = 0; j < fmt_g.size(); ++j)
		{
			auto gg = get_mod(fmt_g[j] * fmt_g[j]);
			auto ggf = get_mod(gg * fmt_f[j]);
			auto g2 = get_mod(fmt_g[j] * 2LL);
			fmt_g[j] = get_mod(g2 - ggf);
		}
	}

	auto computed = inv_fmt(fmt_g, mod);
	vector<ll> results(required_degree + 1LL);
	for (ll i = 0; i <= required_degree; ++i)
	{
		results[i] = computed[i];
	}

	return results;
}

vector<rll> compute_pow_sums()
{
	vector<ll> numerator_series(N + 1LL);
	vector<ll> denominator_series(N + 1LL);

	rll excl = 1;
	rll m_pow = M + 1LL;
	REPD(i, 1, N + 2LL)
	{
		numerator_series[i - 1] = ((m_pow - rll(1)) / excl).n();
		denominator_series[i - 1] = (rll(1) / excl).n();
		excl *= rll(i + 1LL);
		m_pow *= rll(M + 1LL);
	}
	denominator_series = compute_inverse_power_series(denominator_series, N);
	auto series = multiple_polynomials(numerator_series, denominator_series);

	vector<rll> results(N);
	excl = 1;
	REPD(i, 0, N)
	{
		results[i] = series[i + 1LL] * excl;
		excl *= rll(i + 2LL);
	}

	return results;
}

int solve()
{
	cin >> N >> M;

	rll res = 0;

	auto pow_sums = compute_pow_sums();

	ll a, b;
	REPD(i, 0, N)
	{
		cin >> a;
		res += rll(a) * pow_sums[i];
	}

	REPD(i, 0, N)
	{
		cin >> b;
		if (i > 0)
		{
			rll k = i + 1;
			res += rll(b) * (pow(k, M + 1LL) - k) / (k - rll(1));
		}
		else
		{
			res += rll(b) * rll(M);
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
	// REPD(i, 0, t)
	// {
	// 	solve();
	// }

	return 0;
}
