#ifndef __MODINT_HPP__
#define __MODINT_HPP__ 0

//include
//------------------------------------------
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
#include <string>
#include <cstring>
#include <ctime>

#include <stdexcept>

using namespace std;

// type alias
using ll = long long;
using ull = unsigned long long;

static const ll MOD = 1000000007LL;

ll getModValue(const ll& n, ll mod)
{
	return (n % mod + mod) % mod;
}

// computational complexity: o(log(max(a, b)))
inline pair<ll, ll> getBezoutsIdentitySolution(ll a, ll b)
{
	if (b == ll(0)) return { ll(1) / a, ll(0) };
	auto sol = getBezoutsIdentitySolution(b, a % b);
	return { sol.second, sol.first - (a / b) * sol.second };
}

// computational complexity: o(log(max(n, mod)))
inline ll getModInverse(const ll& n, ll mod)
{
	auto sol = getBezoutsIdentitySolution(n, mod);
	return getModValue(sol.first, mod);
}

template<unsigned int Mod> class ModInt;
template<unsigned int Mod> ModInt<Mod>& operator+=(ModInt<Mod>& lhs, const ModInt<Mod>& rhs);
template<unsigned int Mod> ModInt<Mod>& operator+=(ModInt<Mod>& lhs, const ll& rhs);
template<unsigned int Mod> ModInt<Mod>& operator-=(ModInt<Mod>& lhs, const ModInt<Mod>& rhs);
template<unsigned int Mod> ModInt<Mod>& operator-=(ModInt<Mod>& lhs, const ll& rhs);
template<unsigned int Mod> ModInt<Mod>& operator*=(ModInt<Mod>& lhs, const ModInt<Mod>& rhs);
template<unsigned int Mod> ModInt<Mod>& operator*=(ModInt<Mod>& lhs, const ll& rhs);
template<unsigned int Mod> ModInt<Mod>& operator/=(ModInt<Mod>& lhs, const ModInt<Mod>& rhs);
template<unsigned int Mod> ModInt<Mod>& operator/=(ModInt<Mod>& lhs, const ll& rhs);
template<unsigned int Mod> std::istream& operator>>(std::istream& lhs, ModInt<Mod>& rhs);

template<unsigned int Mod>
class ModInt
{
private:
	ll n_;
public:
	ModInt() : n_(getModValue(0, Mod)) {}
	ModInt(ll n) : n_(getModValue(n, Mod)) {}

	ll mod() const { return Mod; }
	ll n() const { return n_; }

	friend ModInt& operator+= <>(ModInt& lhs, const ModInt& rhs);
	friend ModInt& operator+= <>(ModInt& lhs, const ll& rhs);
	friend ModInt& operator-= <>(ModInt& lhs, const ModInt& rhs);
	friend ModInt& operator-= <>(ModInt& lhs, const ll& rhs);
	friend ModInt& operator*= <>(ModInt& lhs, const ModInt& rhs);
	friend ModInt& operator*= <>(ModInt& lhs, const ll& rhs);
	friend ModInt& operator/= <>(ModInt& lhs, const ModInt& rhs);
	friend ModInt& operator/= <>(ModInt& lhs, const ll& rhs);
	friend std::istream& operator>> <>(std::istream& lhs, ModInt& rhs);
};

template<unsigned int Mod> inline ModInt<Mod> operator+(const ModInt<Mod>& lhs, const ModInt<Mod>& rhs){ return lhs.n() + rhs.n(); }
template<unsigned int Mod> inline ModInt<Mod> operator+(const ModInt<Mod>& lhs, const ll& rhs){ return lhs.n() + getModValue(rhs, Mod); }
template<unsigned int Mod> inline ModInt<Mod> operator+(const ll& lhs, const ModInt<Mod>& rhs) { return getModValue(lhs, Mod) + rhs.n(); }
template<unsigned int Mod> inline ModInt<Mod>& operator+=(ModInt<Mod>& lhs, const ModInt<Mod>& rhs) { lhs.n_ = getModValue(lhs.n() + rhs.n(), Mod); return lhs; }
template<unsigned int Mod> inline ModInt<Mod>& operator+=(ModInt<Mod>& lhs, const ll& rhs){ lhs.n_ = getModValue(lhs.n() + getModValue(rhs, Mod), Mod); return lhs; }
template<unsigned int Mod> inline ModInt<Mod> operator-(const ModInt<Mod>& lhs, const ModInt<Mod>& rhs) { return lhs.n() - rhs.n(); }
template<unsigned int Mod> inline ModInt<Mod> operator-(const ModInt<Mod>& lhs, const ll& rhs) { return lhs.n() - getModValue(rhs, Mod), Mod; }
template<unsigned int Mod> inline ModInt<Mod> operator-(const ll& lhs, const ModInt<Mod>& rhs) { return getModValue(lhs, Mod) - rhs.n(); }
template<unsigned int Mod> inline ModInt<Mod>& operator-=(ModInt<Mod>& lhs, const ModInt<Mod>& rhs) { lhs.n_ = getModValue(lhs.n() - rhs.n(), Mod); return lhs; }
template<unsigned int Mod> inline ModInt<Mod>& operator-=(ModInt<Mod>& lhs, const ll& rhs) { lhs.n_ = getModValue(lhs.n() - getModValue(rhs, Mod), Mod); return lhs; }
template<unsigned int Mod> inline ModInt<Mod> operator*(const ModInt<Mod>& lhs, const ModInt<Mod>& rhs) { return lhs.n() * rhs.n(); }
template<unsigned int Mod> inline ModInt<Mod> operator*(const ModInt<Mod>& lhs, const ll& rhs) { return lhs.n() * getModValue(rhs, Mod); }
template<unsigned int Mod> inline ModInt<Mod> operator*(const ll& lhs, const ModInt<Mod>& rhs) { return getModValue(lhs, Mod) * rhs.n(); }
template<unsigned int Mod> inline ModInt<Mod>& operator*=(ModInt<Mod>& lhs, const ModInt<Mod>& rhs) { lhs.n_ = getModValue(lhs.n() * rhs.n(), Mod); return lhs; }
template<unsigned int Mod> inline ModInt<Mod>& operator*=(ModInt<Mod>& lhs, const ll& rhs) { lhs.n_ = getModValue(lhs.n() * getModValue(rhs, Mod), Mod); return lhs; }
template<unsigned int Mod> inline ModInt<Mod> operator/(const ModInt<Mod>& lhs, const ModInt<Mod>& rhs) { return lhs.n() * getModInverse(rhs.n(), Mod); }
template<unsigned int Mod> inline ModInt<Mod> operator/(const ModInt<Mod>& lhs, const ll& rhs) { return lhs.n() * getModInverse(getModValue(rhs, Mod), Mod); }
template<unsigned int Mod> inline ModInt<Mod> operator/(const ll& lhs, const ModInt<Mod>& rhs) { return getModValue(lhs, Mod) * getModInverse(rhs.n(), Mod); }
template<unsigned int Mod> inline ModInt<Mod>& operator/=(ModInt<Mod>& lhs, const ModInt<Mod>& rhs) { lhs.n_ = getModValue(lhs.n() * getModInverse(rhs.n(), Mod), Mod); return lhs; }
template<unsigned int Mod> inline ModInt<Mod>& operator/=(ModInt<Mod>& lhs, const ll& rhs) { lhs.n_ = getModValue(lhs.n() * getModInverse(getModValue(rhs, Mod), Mod), Mod); return lhs; }
template<unsigned int Mod> inline bool operator==(const ModInt<Mod>& lhs, const ModInt<Mod>& rhs) { return lhs.n() == rhs.n(); }
template<unsigned int Mod> inline bool operator==(const ModInt<Mod>& lhs, const ll& rhs) { return lhs.n() == getModValue(rhs, Mod); }
template<unsigned int Mod> inline bool operator==(const ll& lhs, const ModInt<Mod>& rhs) { return getModValue(lhs, Mod) == rhs.n(); }

template<unsigned int Mod>
std::ostream& operator<<(std::ostream& lhs, const ModInt<Mod>& rhs)
{
	return lhs << rhs.n();
}

template<unsigned int Mod>
std::istream& operator>>(std::istream& lhs, ModInt<Mod>& rhs)
{
	lhs >> rhs.n_;
	return lhs;
}

using rll = ModInt<MOD>;

vector<rll> get_exclamations(ull n) {
	vector<rll> exclamations(n + 1ULL);
	exclamations[0] = 1LL;
	for (ll i = 1; i <= n; ++i) exclamations[i] = exclamations[i - 1] * i;

	return exclamations;
}
