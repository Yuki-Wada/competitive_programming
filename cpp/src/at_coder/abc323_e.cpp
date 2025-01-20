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

ll N, X;
vector<ll> Ts;
vector<rll> dps;

void compute_ev(ll x)
{
	REPD(i, 0, N)
	{
		if (x + Ts[i] < X + 1LL)
		{
			dps[x] += dps[x + Ts[i]] / rll(N);
		}
		else
		{
			if (i == 0)
			{
				dps[x] += rll(1) / rll(N);
			}
		}
	}
}

int solve()
{
	cin >> N >> X;

	Ts = make_multiple_vector(0LL, N);
	REPD(i, 0, N)
	{
		cin >> Ts[i];
	}

	dps = make_multiple_vector(rll(0), X + 1LL);

	REPD(i, 0, X + 1LL)
	{
		compute_ev(X - i);
	}
	cout << dps[0].n() << endl;
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
