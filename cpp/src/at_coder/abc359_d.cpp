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
static const ll MOD = 998244353LL;
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

#define MAX_VALUE 9223372036854787LL

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

bool is_symmetric(ll bit, ll K)
{
	for (ll i = 0; i < K / 2LL; ++i)
	{
		auto lbit = (bit >> i) & 1LL;
		auto ubit = (bit >> (K - 1LL - i)) & 1LL;
		if (lbit != ubit)
		{
			return false;
		}
	}
	return true;
}

int solve()
{
	ll N, K;
	string S;
	cin >> N >> K;
	cin >> S;

	vector<vector<rll>> results(N + 1LL, vector<rll>(1LL << (K - 1LL)));
	for (ll i = 0; i < (1LL << (K - 1LL)); ++i)
	{
		ll idx = 0LL;
		for (ll j = 0; j < K - 1LL; ++j)
		{
			auto ch_s = S[j];
			if (ch_s == '?')
			{
				if ((i >> j) % 2LL == 0LL)
				{
					ch_s = 'A';
				}
				else
				{
					ch_s = 'B';
				}
			}
			idx <<= 1LL;
			idx += ll(ch_s) - ll('A');
		}
		results[K - 1LL][idx] = 1;
	}
	for (ll i = K; i <= S.size(); ++i)
	{
		auto ch_s = S[i - 1LL];

		for (ll idx = 0; idx < (1LL << (K - 1LL)); ++idx)
		{
			if (ch_s == 'A' || ch_s == '?')
			{
				auto new_idx = (idx << 1LL);
				if (!is_symmetric(new_idx, K))
				{

					new_idx %= (1LL << (K - 1LL));
					results[i][new_idx] += results[i - 1LL][idx];
				}
			}
			if (ch_s == 'B' || ch_s == '?')
			{
				auto new_idx = (idx << 1LL) + 1LL;
				if (!is_symmetric(new_idx, K))
				{
					new_idx %= (1LL << (K - 1LL));
					results[i][new_idx] += results[i - 1LL][idx];
				}
			}
		}
	}

	rll res = 0;
	for (ll i = 0; i < (1LL << (K - 1LL)); ++i)
	{
		res += results[N][i];
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
