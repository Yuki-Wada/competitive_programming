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

template <class Integer>
Integer getModValue(const Integer &n, Integer mod)
{
	return (n % mod + mod) % mod;
}

// computational complexity: o(log(max(a, b)))
template <class Integer>
inline pair<Integer, Integer> getBezoutsIdentitySolution(Integer a, Integer b)
{
	if (b == Integer(0))
		return {Integer(1) / a, Integer(0)};
	auto sol = getBezoutsIdentitySolution(b, a % b);
	return {sol.second, sol.first - (a / b) * sol.second};
}

// computational complexity: o(log(max(n, mod)))
template <class Integer>
inline Integer getModInverse(const Integer &n, Integer mod)
{
	auto sol = getBezoutsIdentitySolution(n, mod);
	return getModValue(sol.first, mod);
}

template <class Integer>
class ResidueInteger;
template <class Integer>
ResidueInteger<Integer> &operator+=(ResidueInteger<Integer> &lhs, const ResidueInteger<Integer> &rhs);
template <class Integer>
ResidueInteger<Integer> &operator+=(ResidueInteger<Integer> &lhs, const Integer &rhs);
template <class Integer>
ResidueInteger<Integer> &operator-=(ResidueInteger<Integer> &lhs, const ResidueInteger<Integer> &rhs);
template <class Integer>
ResidueInteger<Integer> &operator-=(ResidueInteger<Integer> &lhs, const Integer &rhs);
template <class Integer>
ResidueInteger<Integer> &operator*=(ResidueInteger<Integer> &lhs, const ResidueInteger<Integer> &rhs);
template <class Integer>
ResidueInteger<Integer> &operator*=(ResidueInteger<Integer> &lhs, const Integer &rhs);
template <class Integer>
ResidueInteger<Integer> &operator/=(ResidueInteger<Integer> &lhs, const ResidueInteger<Integer> &rhs);
template <class Integer>
ResidueInteger<Integer> &operator/=(ResidueInteger<Integer> &lhs, const Integer &rhs);
template <class Integer>
std::istream &operator>>(std::istream &lhs, ResidueInteger<Integer> &rhs);

template <class Integer>
class ResidueInteger
{
private:
	Integer mod_;
	Integer n_;

public:
	static Integer default_mod;
	Integer n() const { return n_; }
	Integer mod() const { return mod_; }

	ResidueInteger() : mod_(default_mod), n_(getModValue(Integer(0), mod_)) {}
	ResidueInteger(Integer n) : mod_(default_mod), n_(getModValue(n, mod_)) {}
	ResidueInteger(Integer n, Integer mod) : mod_(mod), n_(getModValue(n, mod_)) {}

	friend ResidueInteger &operator+=<>(ResidueInteger &lhs, const ResidueInteger &rhs);
	friend ResidueInteger &operator+=<>(ResidueInteger &lhs, const Integer &rhs);
	friend ResidueInteger &operator-=<>(ResidueInteger &lhs, const ResidueInteger &rhs);
	friend ResidueInteger &operator-=<>(ResidueInteger &lhs, const Integer &rhs);
	friend ResidueInteger &operator*=<>(ResidueInteger &lhs, const ResidueInteger &rhs);
	friend ResidueInteger &operator*=<>(ResidueInteger &lhs, const Integer &rhs);
	friend ResidueInteger &operator/=<>(ResidueInteger &lhs, const ResidueInteger &rhs);
	friend ResidueInteger &operator/=<>(ResidueInteger &lhs, const Integer &rhs);

	friend std::istream &operator>><>(std::istream &lhs, ResidueInteger &rhs);
};

template <class Integer>
inline ResidueInteger<Integer> operator+(const ResidueInteger<Integer> &lhs, const ResidueInteger<Integer> &rhs)
{
	if (!(lhs.mod() == rhs.mod()))
	{
		throw invalid_argument("The mods of both operands should be equal.");
	}
	return {lhs.n() + rhs.n(), lhs.mod()};
}

template <class Integer>
inline ResidueInteger<Integer> operator+(const ResidueInteger<Integer> &lhs, const Integer &rhs)
{
	return {lhs.n() + getModValue(rhs, lhs.mod()), lhs.mod()};
}

template <class Integer>
inline ResidueInteger<Integer> operator+(const Integer &lhs, const ResidueInteger<Integer> &rhs)
{
	return {getModValue(lhs, rhs.mod()) + rhs.n(), rhs.mod()};
}

template <class Integer>
inline ResidueInteger<Integer> &operator+=(ResidueInteger<Integer> &lhs, const ResidueInteger<Integer> &rhs)
{
	if (!(lhs.mod() == rhs.mod()))
	{
		throw invalid_argument("The mods of both operands should be equal.");
	}
	lhs.n_ = getModValue(lhs.n() + rhs.n(), lhs.mod());
	return lhs;
}

template <class Integer>
inline ResidueInteger<Integer> &operator+=(ResidueInteger<Integer> &lhs, const Integer &rhs)
{
	lhs.n_ = getModValue(lhs.n() + getModValue(rhs, lhs.mod()), lhs.mod());
	return lhs;
}

template <class Integer>
inline ResidueInteger<Integer> operator-(const ResidueInteger<Integer> &lhs, const ResidueInteger<Integer> &rhs)
{
	if (!(lhs.mod() == rhs.mod()))
	{
		throw invalid_argument("The mods of both operands should be equal.");
	}
	return {lhs.n() - rhs.n(), lhs.mod()};
}

template <class Integer>
inline ResidueInteger<Integer> operator-(const ResidueInteger<Integer> &lhs, const Integer &rhs)
{
	return {lhs.n() - getModValue(rhs, lhs.mod()), lhs.mod()};
}

template <class Integer>
inline ResidueInteger<Integer> operator-(const Integer &lhs, const ResidueInteger<Integer> &rhs)
{
	return {getModValue(lhs, rhs.mod()) - rhs.n(), rhs.mod()};
}

template <class Integer>
inline ResidueInteger<Integer> &operator-=(ResidueInteger<Integer> &lhs, const ResidueInteger<Integer> &rhs)
{
	if (!(lhs.mod() == rhs.mod()))
	{
		throw invalid_argument("The mods of both operands should be equal.");
	}
	lhs.n_ = getModValue(lhs.n() - rhs.n(), lhs.mod());
	return lhs;
}

template <class Integer>
inline ResidueInteger<Integer> &operator-=(ResidueInteger<Integer> &lhs, const Integer &rhs)
{
	lhs.n_ = getModValue(lhs.n() - getModValue(rhs, lhs.mod()), lhs.mod());
	return lhs;
}

template <class Integer>
inline ResidueInteger<Integer> operator*(const ResidueInteger<Integer> &lhs, const ResidueInteger<Integer> &rhs)
{
	if (!(lhs.mod() == rhs.mod()))
	{
		throw invalid_argument("The mods of both operands should be equal.");
	}
	return {lhs.n() * rhs.n(), lhs.mod()};
}

template <class Integer>
inline ResidueInteger<Integer> operator*(const ResidueInteger<Integer> &lhs, const Integer &rhs)
{
	return {lhs.n() * getModValue(rhs, lhs.mod()), lhs.mod()};
}

template <class Integer>
inline ResidueInteger<Integer> operator*(const Integer &lhs, const ResidueInteger<Integer> &rhs)
{
	return {getModValue(lhs, rhs.mod()) * rhs.n(), rhs.mod()};
}

template <class Integer>
inline ResidueInteger<Integer> &operator*=(ResidueInteger<Integer> &lhs, const ResidueInteger<Integer> &rhs)
{
	if (!(lhs.mod() == rhs.mod()))
	{
		throw invalid_argument("The mods of both operands should be equal.");
	}
	lhs.n_ = getModValue(lhs.n() * rhs.n(), lhs.mod());
	return lhs;
}

template <class Integer>
inline ResidueInteger<Integer> &operator*=(ResidueInteger<Integer> &lhs, const Integer &rhs)
{
	lhs.n_ = getModValue(lhs.n() * getModValue(rhs, lhs.mod()), lhs.mod());
	return lhs;
}

template <class Integer>
inline ResidueInteger<Integer> operator/(const ResidueInteger<Integer> &lhs, const ResidueInteger<Integer> &rhs)
{
	if (!(lhs.mod() == rhs.mod()))
	{
		throw invalid_argument("The mods of both operands should be equal.");
	}
	return {lhs.n() * getModInverse(rhs.n(), lhs.mod()), lhs.mod()};
}

template <class Integer>
inline ResidueInteger<Integer> operator/(const ResidueInteger<Integer> &lhs, const Integer &rhs)
{
	return {lhs.n() * getModInverse(getModValue(rhs, lhs.mod()), lhs.mod()), lhs.mod()};
}

template <class Integer>
inline ResidueInteger<Integer> operator/(const Integer &lhs, const ResidueInteger<Integer> &rhs)
{
	return {getModValue(lhs, rhs.mod()) * getModInverse(rhs.n(), rhs.mod()), rhs.mod()};
}

template <class Integer>
inline ResidueInteger<Integer> &operator/=(ResidueInteger<Integer> &lhs, const ResidueInteger<Integer> &rhs)
{
	if (!(lhs.mod() == rhs.mod()))
	{
		throw invalid_argument("The mods of both operands should be equal.");
	}
	lhs.n_ = getModValue(lhs.n() * getModInverse(rhs.n(), lhs.mod()), lhs.mod());
	return lhs;
}

template <class Integer>
inline ResidueInteger<Integer> &operator/=(ResidueInteger<Integer> &lhs, const Integer &rhs)
{
	lhs.n_ = getModValue(lhs.n() * getModInverse(getModValue(rhs, lhs.mod()), lhs.mod()), lhs.mod());
	return lhs;
}

template <class Integer>
inline bool operator==(const ResidueInteger<Integer> &lhs, const ResidueInteger<Integer> &rhs)
{
	return (lhs.n() == rhs.n()) && (lhs.mod() == rhs.mod());
}

template <class Integer>
inline bool operator==(const ResidueInteger<Integer> &lhs, const Integer &rhs)
{
	return lhs.n() == getModValue(rhs, lhs.mod());
}

template <class Integer>
bool operator==(const Integer &lhs, const ResidueInteger<Integer> &rhs)
{
	return getModValue(lhs, rhs.mod()) == rhs.n();
}

template <class Integer>
std::ostream &operator<<(std::ostream &lhs, const ResidueInteger<Integer> &rhs)
{
	return lhs << rhs.n();
}

template <class Integer>
std::istream &operator>>(std::istream &lhs, ResidueInteger<Integer> &rhs)
{
	lhs >> rhs.n_;
	return lhs;
}

using rll = ResidueInteger<ll>;
template <>
ll rll::default_mod = MOD;

class Matrix
{
public:
	const unsigned int row_;
	const unsigned int col_;
	vector<rll> values_;

	Matrix(unsigned int row, unsigned int col) : row_(row), col_(col), values_(row * col) {}
	Matrix(unsigned int row, unsigned int col, rll l) : row_(row), col_(col), values_(row * col)
	{
		REPD(i, 0, row)
		{
			(*this)(i, i) = l;
		}
	}

	ull get_row_size() const
	{
		return row_;
	}

	ull get_col_size() const
	{
		return col_;
	}

	rll &operator()(ull rowIndex, ull colIndex)
	{
		return values_[rowIndex * col_ + colIndex];
	}

	const rll &operator()(ull rowIndex, ull colIndex) const
	{
		return values_[rowIndex * col_ + colIndex];
	}
	inline Matrix operator*(const Matrix &rhs)
	{
		auto row = row_;
		auto mid = col_;
		auto col = rhs.col_;
		Matrix res(row, col);
		for (ll i = 0; i < row; ++i)
			for (ll j = 0; j < col; ++j)
				for (ll k = 0; k < mid; ++k)
					res(i, j) += (*this)(i, k) * rhs(k, j);

		return res;
	}

	inline Matrix &operator=(const Matrix &rhs)
	{
		REPD(i, 0, values_.size())
		{
			values_[i] = rhs.values_[i];
		}
		return (*this);
	}
};

template <class Integer>
inline Integer get_power(Integer base, ull exponential)
{
	Integer result(base.row_, base.col_, rll(1LL));
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
}

// https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_4_A&lang=ja#
int solve()
{
	ll n, b, k;
	cin >> n >> b >> k;

	auto cs = make_multiple_vector(0LL, k);
	REPD(i, 0, k)
	cin >> cs[i];

	Matrix trans_mat(b, b);
	REPD(i, 0, b)
	{
		REPI(c, cs)
		{
			trans_mat((i * 10 + c) % b, i) = trans_mat((i * 10 + c) % b, i) + 1LL;
		}
	}

	auto pow_mat = get_power(trans_mat, n);

	cout << pow_mat(0, 0).n() << endl;

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
