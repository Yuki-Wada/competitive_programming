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
	if (b == 0)
	{
		return { 1, 0 };
	}
	auto sol = getBezoutsIdentitySolution(b, a % b);
	return { sol.second, sol.first - (a / b) * sol.second };
}

// computational complexity: o(log(max(n, mod))) 
inline ll getModInverse(const ll& n, ll mod)
{
	auto sol = getBezoutsIdentitySolution(n, mod);
	if (n * sol.first + mod * sol.second != 1)
	{
		return -1;
	}
	return getModValue(sol.first, mod);
}

class ResidueInteger
{
private:
	ll mod_;
	ll n_;
public:
	ResidueInteger() : mod_(MOD), n_(getModValue(0, mod_)) {}
	ResidueInteger(ll n) : mod_(MOD), n_(getModValue(n, mod_)) {}
	ResidueInteger(ll n, ll mod) : mod_(mod), n_(getModValue(n, mod_)) {}

	friend ResidueInteger operator+(const ResidueInteger& lhs, const ResidueInteger& rhs);
	friend ResidueInteger operator+(const ResidueInteger& lhs, const ll& rhs);
	friend ResidueInteger operator+(const ll& lhs, const ResidueInteger& rhs);
	friend ResidueInteger& operator+=(ResidueInteger& lhs, const ResidueInteger& rhs);
	friend ResidueInteger& operator+=(ResidueInteger& lhs, const ll& rhs);

	friend ResidueInteger operator-(const ResidueInteger& lhs, const ResidueInteger& rhs);
	friend ResidueInteger operator-(const ResidueInteger& lhs, const ll& rhs);
	friend ResidueInteger operator-(const ll& lhs, const ResidueInteger& rhs);
	friend ResidueInteger& operator-=(ResidueInteger& lhs, const ResidueInteger& rhs);
	friend ResidueInteger& operator-=(ResidueInteger& lhs, const ll& rhs);

	friend ResidueInteger operator*(const ResidueInteger& lhs, const ResidueInteger& rhs);
	friend ResidueInteger operator*(const ResidueInteger& lhs, const ll& rhs);
	friend ResidueInteger operator*(const ll& lhs, const ResidueInteger& rhs);
	friend ResidueInteger& operator*=(ResidueInteger& lhs, const ResidueInteger& rhs);
	friend ResidueInteger& operator*=(ResidueInteger& lhs, const ll& rhs);

	friend ResidueInteger operator/(const ResidueInteger& lhs, const ResidueInteger& rhs);
	friend ResidueInteger operator/(const ResidueInteger& lhs, const ll& rhs);
	friend ResidueInteger operator/(const ll& lhs, const ResidueInteger& rhs);
	friend ResidueInteger& operator/=(ResidueInteger& lhs, const ResidueInteger& rhs);
	friend ResidueInteger& operator/=(ResidueInteger& lhs, const ll& rhs);

	friend bool operator==(const ResidueInteger& lhs, const ResidueInteger& rhs);
	friend bool operator==(const ResidueInteger& lhs, const ll& rhs);
	friend bool operator==(const ll& lhs, const ResidueInteger& rhs);

	ll n() const { return n_; }

	friend std::ostream& operator<<(std::ostream& lhs, const ResidueInteger& rhs);
	friend std::istream& operator>>(std::istream& lhs, ResidueInteger& rhs);
};

inline ResidueInteger operator+(const ResidueInteger& lhs, const ResidueInteger& rhs)
{
	if (lhs.mod_ != rhs.mod_)
	{
		throw invalid_argument("The mods of both operands should be equal.");
	}
	return { lhs.n_ + rhs.n_, lhs.mod_ };
}

inline ResidueInteger operator+(const ResidueInteger& lhs, const ll& rhs)
{
	return { lhs.n_ + getModValue(rhs, lhs.mod_), lhs.mod_ };
}

inline ResidueInteger operator+(const ll& lhs, const ResidueInteger& rhs)
{
	return { getModValue(lhs, rhs.mod_) + rhs.n_, rhs.mod_ };
}

inline ResidueInteger& operator+=(ResidueInteger& lhs, const ResidueInteger& rhs)
{
	if (lhs.mod_ != rhs.mod_)
	{
		throw invalid_argument("The mods of both operands should be equal.");
	}
	lhs.n_ = getModValue(lhs.n_ + rhs.n_, lhs.mod_);
	return lhs;
}

inline ResidueInteger& operator+=(ResidueInteger& lhs, const ll& rhs)
{
	lhs.n_ = getModValue(lhs.n_ + getModValue(rhs, lhs.mod_), lhs.mod_);
	return lhs;
}

inline ResidueInteger operator-(const ResidueInteger& lhs, const ResidueInteger& rhs)
{
	if (lhs.mod_ != rhs.mod_)
	{
		throw invalid_argument("The mods of both operands should be equal.");
	}
	return { lhs.n_ - rhs.n_, lhs.mod_ };
}

inline ResidueInteger operator-(const ResidueInteger& lhs, const ll& rhs)
{
	return { lhs.n_ - getModValue(rhs, lhs.mod_), lhs.mod_ };
}

inline ResidueInteger operator-(const ll& lhs, const ResidueInteger& rhs)
{
	return { getModValue(lhs, rhs.mod_) - rhs.n_, rhs.mod_ };
}

inline ResidueInteger& operator-=(ResidueInteger& lhs, const ResidueInteger& rhs)
{
	if (lhs.mod_ != rhs.mod_)
	{
		throw invalid_argument("The mods of both operands should be equal.");
	}
	lhs.n_ = getModValue(lhs.n_ - rhs.n_, lhs.mod_);
	return lhs;
}

inline ResidueInteger& operator-=(ResidueInteger& lhs, const ll& rhs)
{
	lhs.n_ = getModValue(lhs.n_ - getModValue(rhs, lhs.mod_), lhs.mod_);
	return lhs;
}

inline ResidueInteger operator*(const ResidueInteger& lhs, const ResidueInteger& rhs)
{
	if (lhs.mod_ != rhs.mod_)
	{
		throw invalid_argument("The mods of both operands should be equal.");
	}
	return { lhs.n_ * rhs.n_, lhs.mod_ };
}

inline ResidueInteger operator*(const ResidueInteger& lhs, const ll& rhs)
{
	return { lhs.n_ * getModValue(rhs, lhs.mod_), lhs.mod_ };
}

inline ResidueInteger operator*(const ll& lhs, const ResidueInteger& rhs)
{
	return { getModValue(lhs, rhs.mod_) * rhs.n_, rhs.mod_ };
}

inline ResidueInteger& operator*=(ResidueInteger& lhs, const ResidueInteger& rhs)
{
	if (lhs.mod_ != rhs.mod_)
	{
		throw invalid_argument("The mods of both operands should be equal.");
	}
	lhs.n_ = getModValue(lhs.n_ * rhs.n_, lhs.mod_);
	return lhs;
}

inline ResidueInteger& operator*=(ResidueInteger& lhs, const ll& rhs)
{
	lhs.n_ = getModValue(lhs.n_ * getModValue(rhs, lhs.mod_), lhs.mod_);
	return lhs;
}

inline ResidueInteger operator/(const ResidueInteger& lhs, const ResidueInteger& rhs)
{
	if (lhs.mod_ != rhs.mod_)
	{
		throw invalid_argument("The mods of both operands should be equal.");
	}
	return { lhs.n_ * getModInverse(rhs.n_, lhs.mod_), lhs.mod_ };
}

inline ResidueInteger operator/(const ResidueInteger& lhs, const ll& rhs)
{
	return { lhs.n_ * getModInverse(getModValue(rhs, lhs.mod_), lhs.mod_), lhs.mod_ };
}

inline ResidueInteger operator/(const ll& lhs, const ResidueInteger& rhs)
{
	return { getModValue(lhs, rhs.mod_) * getModInverse(rhs.n_, rhs.mod_), rhs.mod_ };
}

inline ResidueInteger& operator/=(ResidueInteger& lhs, const ResidueInteger& rhs)
{
	if (lhs.mod_ != rhs.mod_)
	{
		throw invalid_argument("The mods of both operands should be equal.");
	}
	lhs.n_ = getModValue(lhs.n_ * getModInverse(rhs.n_, lhs.mod_), lhs.mod_);
	return lhs;
}

inline ResidueInteger& operator/=(ResidueInteger& lhs, const ll& rhs)
{
	lhs.n_ = getModValue(lhs.n_ * getModInverse(getModValue(rhs, lhs.mod_), lhs.mod_), lhs.mod_);
	return lhs;
}

inline bool operator==(const ResidueInteger& lhs, const ResidueInteger& rhs)
{
	return (lhs.n_ == rhs.n_) && (lhs.mod_ == rhs.mod_);
}

inline bool operator==(const ResidueInteger& lhs, const ll& rhs)
{
	return lhs.n_ == getModValue(rhs, lhs.mod_);
}

bool operator==(const ll& lhs, const ResidueInteger& rhs)
{
	return getModValue(lhs, rhs.mod_) == rhs.n_;
}

std::ostream& operator<<(std::ostream& lhs, const ResidueInteger& rhs)
{
	return lhs << rhs.n_;
}

std::istream& operator>>(std::istream& lhs, ResidueInteger& rhs)
{
	lhs >> rhs.n_;
	return lhs;
}

using rll = ResidueInteger;

vector<rll> get_exclamations(ull n) {
	vector<rll> exclamations(n + 1ULL);
	exclamations[0] = 1LL;
	for (ll i = 1; i <= n; ++i) exclamations[i] = exclamations[i - 1] * i;

	return exclamations;
}
