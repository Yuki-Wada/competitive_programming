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

// temporary
#include <atcoder/all>
using namespace atcoder;

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

// constant
static constexpr ll MOD = 998244353LL;
static constexpr double PI = 3.14159265358979323846;

template <ull N, class T, class... Args, std::enable_if_t<N == 0, int> = 0>
auto make_multiple_vector(Args... args)
{
	return T(args...);
}

template <ull N, class T, class... Args, std::enable_if_t<N != 0, int> = 0>
auto make_multiple_vector(ull size, Args... args)
{
	using value_type = std::decay_t<decltype(make_multiple_vector<N - 1LL, T>(args...))>;
	return vector<value_type>(size, make_multiple_vector<N - 1LL, T>(args...));
}

constexpr ll MOD_PRIMITIVE_ROOT = 3LL;
constexpr ll MOD_INVERSE_PRIMITIVE_ROOT = 332748118LL;

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
// using rll = atcoder::modint998244353;

inline ull get_power2_more_than_input(ull input)
{
	// val is 0.
	if (input == 0ULL)
		return 1ULL;
	// val is power of 2
	if (!(input & (input - 1)))
		return input;

	ull highest_one_bit = input;
	while ((highest_one_bit & (highest_one_bit - 1LL)) != 0)
		highest_one_bit = highest_one_bit & (highest_one_bit - 1LL);
	ull power2 = highest_one_bit << 1LL;
	return power2;
}

inline ull get_value_more_than_log_2_input(ull input)
{
	auto get_power2 = [](ull input)
	{
		// val is 0.
		if (input == 0ULL)
			return 1ULL;
		// val is power of 2
		if (!(input & (input - 1)))
			return input;

		ull highest_one_bit = input;
		while ((highest_one_bit & (highest_one_bit - 1LL)) != 0)
			highest_one_bit = highest_one_bit & (highest_one_bit - 1LL);
		ull power2 = highest_one_bit << 1LL;
		return power2;
	};

	auto power2 = get_power2(input);
	ull value = 0ULL;
	while (power2 > 1ULL)
	{
		power2 >>= 1LL;
		++value;
	}
	return value;
}

// Fast Modulo Transform
vector<rll> fmt_impl(const vector<rll> &function, const rll primitive_root)
{
	ll degree = function.size();
	if (degree == 0LL)
		throw runtime_error("配列の要素数は 1 以上である必要があります。");
	if ((degree & (degree - 1LL)) != 0LL)
		throw runtime_error("配列の要素数は 2 のべき乗である必要があります。");

	auto get_power2 = [&](rll base, ull exponential)
	{
		rll result = 1;
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
	};
	rll xi = get_power2(rll(primitive_root), (MOD - 1LL) / degree);

	vector<rll> transformed(degree, 0);
	vector<rll> stored(degree, 0);

	for (ll i = 0; i < degree; ++i)
		transformed[i] = function[i];
	if (degree == 1LL)
	{
		return transformed;
	}

	ll log_2_deg = 0LL;
	for (ll i = 1; i < degree; i <<= 1LL)
		++log_2_deg;

	vector<rll> mod_xi_2s(log_2_deg);
	vector<ll> power_2s(log_2_deg);
	mod_xi_2s[0] = xi, power_2s[0] = 1LL;
	for (ll i = 1; i < log_2_deg; ++i)
		mod_xi_2s[i] = mod_xi_2s[i - 1LL] * mod_xi_2s[i - 1LL], power_2s[i] = 1LL << i;

	for (ll e = 0; e < log_2_deg; ++e)
	{
		auto mod_xi = mod_xi_2s[log_2_deg - e - 1LL];
		auto skip = power_2s[log_2_deg - e - 1LL];
		for (ll i = 0; i < degree; ++i)
			stored[i] = transformed[i];

		rll power_of_xi = 1;
		for (ll i = 0; i < (degree / skip); ++i)
		{
			for (ll start = 0; start < skip; ++start)
			{
				auto idx = start + skip * i;
				auto res_i = i % (degree / skip / 2LL);

				auto stored_idx = start + skip * res_i * 2LL;
				transformed[idx] = stored[stored_idx] + stored[stored_idx + skip] * power_of_xi;
			}
			power_of_xi = power_of_xi * mod_xi;
		}
	}
	return transformed;
}

vector<rll> fmt(const vector<rll> &function)
{
	vector<rll> transformed = fmt_impl(function, MOD_PRIMITIVE_ROOT);
	return transformed;
}

vector<rll> inv_fmt(const vector<rll> &function)
{
	vector<rll> transformed = fmt_impl(function, MOD_INVERSE_PRIMITIVE_ROOT);
	auto inverse_n = rll(1) / rll(function.size());
	for (unsigned int i = 0; i < function.size(); ++i)
		transformed[i] = transformed[i] * inverse_n;

	return transformed;
}

vector<rll> fmt_convolution(const vector<rll> &a, const vector<rll> &b)
{
	unsigned int coef_num = a.size() + b.size() - 1U;
	unsigned int fmt_size = get_power2_more_than_input(coef_num);

	vector<rll> rll_a(fmt_size);
	vector<rll> rll_b(fmt_size);
	for (unsigned int i = 0; i < a.size(); ++i)
		rll_a[i] = a[i];
	for (unsigned int i = 0; i < b.size(); ++i)
		rll_b[i] = b[i];

	auto fmt_a = fmt(rll_a);
	auto fmt_b = fmt(rll_b);
	vector<rll> fmt_ab(fmt_size);
	for (unsigned int i = 0; i < fmt_size; ++i)
		fmt_ab[i] = fmt_a[i] * fmt_b[i];

	auto rll_ab = inv_fmt(fmt_ab);

	return rll_ab;
}

vector<rll> my_convolution(const vector<rll> &a, const vector<rll> &b)
{
	return fmt_convolution(a, b);
}

template <class Number>
class Polynomial
{
private:
public:
	vector<Number> coefs;

	Polynomial() : coefs(1U) {}
	Polynomial(Number constant) : coefs(1U, constant) {}
	Polynomial(vector<Number> coefs) : coefs(coefs) {}

	static Polynomial zero_polynomial(unsigned int coef_num)
	{
		vector<Number> coefs(coef_num);
		return Polynomial(coefs);
	}

	Number operator[](unsigned int n) const
	{
		return (n < coefs.size() ? coefs[n] : Number(0));
	}
	Number &operator[](unsigned int n)
	{
		if (n >= coefs.size())
			coefs.resize(n + 1U);

		return coefs[n];
	}
	unsigned int coef_num() const { return coefs.size(); }
	Number operator()(Number point) const
	{
		unsigned int N = coef_num();
		Number result = 0;
		Number point_power = 1;
		for (unsigned int i = 0; i < N; ++i)
		{
			result = result + coefs[i] * point_power;
			point_power = point_power * point;

			result = mod_red(result);
			point_power = mod_red(point_power);
		}

		return result;
	}

	void resize(unsigned int n) { coefs.resize(n); }
	void mod_xn(unsigned int n) { coefs.resize(n); }
	void zero_trim()
	{
		unsigned int N = coef_num();
		unsigned int max_coef_idx = 1;
		for (unsigned int i = 0; i < N; ++i)
			if (coefs[N - i - 1U] != 0)
			{
				max_coef_idx = N - i;
				break;
			}

		coefs.resize(max_coef_idx);
	}
};

template <class Number>
Polynomial<Number> operator+(const Polynomial<Number> &lhs, const Polynomial<Number> &rhs)
{
	unsigned int coef_num = max(lhs.coef_num(), rhs.coef_num());
	auto outputs = Polynomial<Number>::zero_polynomial(coef_num);
	for (unsigned int i = 0; i < coef_num; ++i)
	{
		outputs[i] = 0;
		if (i < lhs.coef_num())
			outputs[i] += lhs[i];
		if (i < rhs.coef_num())
			outputs[i] += rhs[i];
	}
	return outputs;
}

template <class Number>
Polynomial<Number> operator+(const Polynomial<Number> &lhs, Number rhs)
{
	unsigned int coef_num = lhs.coef_num();
	auto outputs = Polynomial<Number>::zero_polynomial(coef_num);
	outputs[0] = rhs;
	for (unsigned int i = 0; i < coef_num; ++i)
		outputs[i] = outputs[i] + lhs[i];
	return {outputs};
}

template <class Number>
Polynomial<Number> operator+(Number lhs, const Polynomial<Number> &rhs)
{
	unsigned int coef_num = rhs.coef_num();
	auto outputs = Polynomial<Number>::zero_polynomial(coef_num);
	outputs[0] = lhs;
	for (unsigned int i = 0; i < coef_num; ++i)
		outputs[i] = outputs[i] + rhs[i];
	return {outputs};
}

template <class Number>
Polynomial<Number> operator-(const Polynomial<Number> &lhs, const Polynomial<Number> &rhs)
{
	unsigned int coef_num = max(lhs.coef_num(), rhs.coef_num());
	auto output = Polynomial<Number>::zero_polynomial(coef_num);
	for (unsigned int i = 0; i < coef_num; ++i)
	{
		output[i] = 0;
		if (i < lhs.coef_num())
			output[i] = output[i] + lhs[i];
		if (i < rhs.coef_num())
			output[i] = output[i] - rhs[i];
	}
	return output;
}

template <class Number>
Polynomial<Number> operator-(const Polynomial<Number> &lhs, Number rhs)
{
	unsigned int coef_num = lhs.coef_num();
	auto outputs = Polynomial<Number>::zero_polynomial(coef_num);
	outputs[0] = -rhs;
	for (unsigned int i = 0; i < coef_num; ++i)
		outputs[i] += lhs[i];
	return {outputs};
}

template <class Number>
Polynomial<Number> operator-(Number lhs, const Polynomial<Number> &rhs)
{
	unsigned int coef_num = rhs.coef_num();
	auto outputs = Polynomial<Number>::zero_polynomial(coef_num);
	outputs[0] = lhs;
	for (unsigned int i = 0; i < coef_num; ++i)
		outputs[i] -= rhs[i];
	return {outputs};
}

template <class Number>
Polynomial<Number> operator-(const Polynomial<Number> &original)
{
	unsigned int coef_num = original.coef_num();
	auto outputs = Polynomial<Number>::zero_polynomial(coef_num);
	for (unsigned int i = 0; i < coef_num; ++i)
	{
		outputs[i] = 0;
		outputs[i] -= original[i];
	}
	return {outputs};
}

template <class Number>
Polynomial<Number> operator*(const Polynomial<Number> &lhs, const Polynomial<Number> &rhs)
{
	// Polynomial<Number> output(atcoder::convolution<MOD>(lhs.coefs, rhs.coefs));
	Polynomial<Number> output(my_convolution(lhs.coefs, rhs.coefs));
	return output;
}

ll solve()
{
	ll n;
	cin >> n;
	ll1d s(n);

	REPD(i, 0, n)
	{
		cin >> s[i];
	}
	sort(s.begin(), s.end());
	ll max_s = s[s.size() - 1LL];
	vector<rll> coefs(max_s + 1ULL);
	REPD(i, 0, s.size())
	{
		coefs[s[i]] = 1LL;
	}
	Polynomial<rll> f(coefs);

	auto ff = f * f;
	ll res = 0LL;
	REPD(i, 0, s.size())
	{
		auto val = ff.coefs[s[i] * 2LL].n();
		val = ((val % MOD) + MOD) % MOD;
		res += (val - 1LL) / 2LL;
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
