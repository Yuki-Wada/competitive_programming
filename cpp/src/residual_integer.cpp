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

template<class Integer>
Integer getModValue(const Integer& n, Integer mod)
{
	return (n % mod + mod) % mod;
}

// computational complexity: o(log(max(a, b)))
template<class Integer>
inline pair<Integer, Integer> getBezoutsIdentitySolution(Integer a, Integer b)
{
	if (b == 0)
	{
		return { 1, 0 };
	}
	auto sol = getBezoutsIdentitySolution(b, a % b);
	return { sol.second, sol.first - (a / b) * sol.second };
}

// computational complexity: o(log(max(n, mod)))
template<class Integer>
inline Integer getModInverse(const Integer& n, Integer mod)
{
	auto sol = getBezoutsIdentitySolution(n, mod);
	if (n * sol.first + mod * sol.second != 1)
	{
		return -1;
	}
	return getModValue(sol.first, mod);
}

template<class Integer> class ResidueInteger;
template<class Integer> ResidueInteger<Integer>& operator+=(ResidueInteger<Integer>& lhs, const ResidueInteger<Integer>& rhs);
template<class Integer> ResidueInteger<Integer>& operator+=(ResidueInteger<Integer>& lhs, const Integer& rhs);
template<class Integer> ResidueInteger<Integer>& operator-=(ResidueInteger<Integer>& lhs, const ResidueInteger<Integer>& rhs);
template<class Integer> ResidueInteger<Integer>& operator-=(ResidueInteger<Integer>& lhs, const Integer& rhs);
template<class Integer> ResidueInteger<Integer>& operator*=(ResidueInteger<Integer>& lhs, const ResidueInteger<Integer>& rhs);
template<class Integer> ResidueInteger<Integer>& operator*=(ResidueInteger<Integer>& lhs, const Integer& rhs);
template<class Integer> ResidueInteger<Integer>& operator/=(ResidueInteger<Integer>& lhs, const ResidueInteger<Integer>& rhs);
template<class Integer> ResidueInteger<Integer>& operator/=(ResidueInteger<Integer>& lhs, const Integer& rhs);
template<class Integer> std::istream& operator>>(std::istream& lhs, ResidueInteger<Integer>& rhs);

template<class Integer>
class ResidueInteger
{
private:
	Integer mod_;
	Integer n_;
public:
	Integer n() const { return n_; }
	Integer mod() const { return mod_; }

	ResidueInteger() : mod_(MOD), n_(getModValue(0, mod_)) {}
	ResidueInteger(Integer n) : mod_(MOD), n_(getModValue(n, mod_)) {}
	ResidueInteger(Integer n, Integer mod) : mod_(mod), n_(getModValue(n, mod_)) {}

	friend ResidueInteger& operator+= <>(ResidueInteger& lhs, const ResidueInteger& rhs);
	friend ResidueInteger& operator+= <>(ResidueInteger& lhs, const Integer& rhs);
	friend ResidueInteger& operator-= <>(ResidueInteger& lhs, const ResidueInteger& rhs);
	friend ResidueInteger& operator-= <>(ResidueInteger& lhs, const Integer& rhs);
	friend ResidueInteger& operator*= <>(ResidueInteger& lhs, const ResidueInteger& rhs);
	friend ResidueInteger& operator*= <>(ResidueInteger& lhs, const Integer& rhs);
	friend ResidueInteger& operator/= <>(ResidueInteger& lhs, const ResidueInteger& rhs);
	friend ResidueInteger& operator/= <>(ResidueInteger& lhs, const Integer& rhs);

	friend std::istream& operator>> <>(std::istream& lhs, ResidueInteger& rhs);
};

template<class Integer>
inline ResidueInteger<Integer> operator+(const ResidueInteger<Integer>& lhs, const ResidueInteger<Integer>& rhs)
{
	if (!(lhs.mod() == rhs.mod()))
	{
		throw invalid_argument("The mods of both operands should be equal.");
	}
	return { lhs.n() + rhs.n(), lhs.mod() };
}

template<class Integer>
inline ResidueInteger<Integer> operator+(const ResidueInteger<Integer>& lhs, const Integer& rhs)
{
	return { lhs.n() + getModValue(rhs, lhs.mod()), lhs.mod() };
}

template<class Integer>
inline ResidueInteger<Integer> operator+(const Integer& lhs, const ResidueInteger<Integer>& rhs)
{
	return { getModValue(lhs, rhs.mod()) + rhs.n(), rhs.mod() };
}

template<class Integer>
inline ResidueInteger<Integer>& operator+=(ResidueInteger<Integer>& lhs, const ResidueInteger<Integer>& rhs)
{
	if (!(lhs.mod() == rhs.mod()))
	{
		throw invalid_argument("The mods of both operands should be equal.");
	}
	lhs.n_ = getModValue(lhs.n() + rhs.n(), lhs.mod());
	return lhs;
}

template<class Integer>
inline ResidueInteger<Integer>& operator+=(ResidueInteger<Integer>& lhs, const Integer& rhs)
{
	lhs.n_ = getModValue(lhs.n() + getModValue(rhs, lhs.mod()), lhs.mod());
	return lhs;
}

template<class Integer>
inline ResidueInteger<Integer> operator-(const ResidueInteger<Integer>& lhs, const ResidueInteger<Integer>& rhs)
{
	if (!(lhs.mod() == rhs.mod()))
	{
		throw invalid_argument("The mods of both operands should be equal.");
	}
	return { lhs.n() - rhs.n(), lhs.mod() };
}

template<class Integer>
inline ResidueInteger<Integer> operator-(const ResidueInteger<Integer>& lhs, const Integer& rhs)
{
	return { lhs.n() - getModValue(rhs, lhs.mod()), lhs.mod() };
}

template<class Integer>
inline ResidueInteger<Integer> operator-(const Integer& lhs, const ResidueInteger<Integer>& rhs)
{
	return { getModValue(lhs, rhs.mod()) - rhs.n(), rhs.mod() };
}

template<class Integer>
inline ResidueInteger<Integer>& operator-=(ResidueInteger<Integer>& lhs, const ResidueInteger<Integer>& rhs)
{
	if (!(lhs.mod() == rhs.mod()))
	{
		throw invalid_argument("The mods of both operands should be equal.");
	}
	lhs.n_ = getModValue(lhs.n() - rhs.n(), lhs.mod());
	return lhs;
}

template<class Integer>
inline ResidueInteger<Integer>& operator-=(ResidueInteger<Integer>& lhs, const Integer& rhs)
{
	lhs.n_ = getModValue(lhs.n() - getModValue(rhs, lhs.mod()), lhs.mod());
	return lhs;
}

template<class Integer>
inline ResidueInteger<Integer> operator*(const ResidueInteger<Integer>& lhs, const ResidueInteger<Integer>& rhs)
{
	if (!(lhs.mod() == rhs.mod()))
	{
		throw invalid_argument("The mods of both operands should be equal.");
	}
	return { lhs.n() * rhs.n(), lhs.mod() };
}

template<class Integer>
inline ResidueInteger<Integer> operator*(const ResidueInteger<Integer>& lhs, const Integer& rhs)
{
	return { lhs.n() * getModValue(rhs, lhs.mod()), lhs.mod() };
}

template<class Integer>
inline ResidueInteger<Integer> operator*(const Integer& lhs, const ResidueInteger<Integer>& rhs)
{
	return { getModValue(lhs, rhs.mod()) * rhs.n(), rhs.mod() };
}

template<class Integer>
inline ResidueInteger<Integer>& operator*=(ResidueInteger<Integer>& lhs, const ResidueInteger<Integer>& rhs)
{
	if (!(lhs.mod() == rhs.mod()))
	{
		throw invalid_argument("The mods of both operands should be equal.");
	}
	lhs.n_ = getModValue(lhs.n() * rhs.n(), lhs.mod());
	return lhs;
}

template<class Integer>
inline ResidueInteger<Integer>& operator*=(ResidueInteger<Integer>& lhs, const Integer& rhs)
{
	lhs.n_ = getModValue(lhs.n() * getModValue(rhs, lhs.mod()), lhs.mod());
	return lhs;
}

template<class Integer>
inline ResidueInteger<Integer> operator/(const ResidueInteger<Integer>& lhs, const ResidueInteger<Integer>& rhs)
{
	if (!(lhs.mod() == rhs.mod()))
	{
		throw invalid_argument("The mods of both operands should be equal.");
	}
	return { lhs.n() * getModInverse(rhs.n(), lhs.mod()), lhs.mod() };
}

template<class Integer>
inline ResidueInteger<Integer> operator/(const ResidueInteger<Integer>& lhs, const Integer& rhs)
{
	return { lhs.n() * getModInverse(getModValue(rhs, lhs.mod()), lhs.mod()), lhs.mod() };
}

template<class Integer>
inline ResidueInteger<Integer> operator/(const Integer& lhs, const ResidueInteger<Integer>& rhs)
{
	return { getModValue(lhs, rhs.mod()) * getModInverse(rhs.n(), rhs.mod()), rhs.mod() };
}

template<class Integer>
inline ResidueInteger<Integer>& operator/=(ResidueInteger<Integer>& lhs, const ResidueInteger<Integer>& rhs)
{
	if (!(lhs.mod() == rhs.mod()))
	{
		throw invalid_argument("The mods of both operands should be equal.");
	}
	lhs.n_ = getModValue(lhs.n() * getModInverse(rhs.n(), lhs.mod()), lhs.mod());
	return lhs;
}

template<class Integer>
inline ResidueInteger<Integer>& operator/=(ResidueInteger<Integer>& lhs, const Integer& rhs)
{
	lhs.n_ = getModValue(lhs.n() * getModInverse(getModValue(rhs, lhs.mod()), lhs.mod()), lhs.mod());
	return lhs;
}

template<class Integer>
inline bool operator==(const ResidueInteger<Integer>& lhs, const ResidueInteger<Integer>& rhs)
{
	return (lhs.n() == rhs.n()) && (lhs.mod() == rhs.mod());
}

template<class Integer>
inline bool operator==(const ResidueInteger<Integer>& lhs, const Integer& rhs)
{
	return lhs.n() == getModValue(rhs, lhs.mod());
}

template<class Integer>
bool operator==(const Integer& lhs, const ResidueInteger<Integer>& rhs)
{
	return getModValue(lhs, rhs.mod()) == rhs.n();
}

template<class Integer>
std::ostream& operator<<(std::ostream& lhs, const ResidueInteger<Integer>& rhs)
{
	return lhs << rhs.n();
}

template<class Integer>
std::istream& operator>>(std::istream& lhs, ResidueInteger<Integer>& rhs)
{
	lhs >> rhs.n_;
	return lhs;
}
