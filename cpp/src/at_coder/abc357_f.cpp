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

template <class Integer, class Monoid, class OperatorII, class OperatorIM, class OperatorMM>
class SegmentTreeWithLazyPropagation
{
private:
	ull maxSize_;
	vector<Integer> data_;
	vector<Monoid> lazy_;
	OperatorII op_ii_;
	OperatorIM op_im_;
	OperatorMM op_mm_;

	void _lazy_propagate(ll k)
	{
		if (lazy_[k] == op_mm_.default_value)
			return;
		if (k < maxSize_ - 1)
		{
			lazy_[k * 2 + 1] = op_mm_.Execute(lazy_[k * 2 + 1], lazy_[k]);
			lazy_[k * 2 + 2] = op_mm_.Execute(lazy_[k * 2 + 2], lazy_[k]);
		}
		data_[k] = op_im_.Execute(data_[k], lazy_[k]);
		lazy_[k] = op_mm_.default_value;
	}

	Integer _query(ll start, ll end, ll searchStart, ll searchEnd, ll node)
	{
		_lazy_propagate(node);
		if (searchEnd <= start || end <= searchStart)
			return op_ii_.default_value;
		if (start <= searchStart && searchEnd <= end)
			return data_[node];

		return op_ii_.Execute(
			_query(start, end, searchStart, (searchStart + searchEnd) / 2, node * 2 + 1),
			_query(start, end, (searchStart + searchEnd) / 2, searchEnd, node * 2 + 2));
	}

	void _update(ll start, ll end, Monoid value, ll searchStart, ll searchEnd, ll node)
	{
		_lazy_propagate(node);
		if (start <= searchStart && searchEnd <= end)
		{
			lazy_[node] = op_mm_.Execute(lazy_[node], value);
			_lazy_propagate(node);
		}
		else if (searchStart < end && start < searchEnd)
		{
			_update(start, end, value, searchStart, (searchStart + searchEnd) / 2, node * 2 + 1);
			_update(start, end, value, (searchStart + searchEnd) / 2, searchEnd, node * 2 + 2);
			data_[node] = op_ii_.Execute(data_[node * 2 + 1], data_[node * 2 + 2]);
		}
	}

public:
	ull size() { return maxSize_; }
	SegmentTreeWithLazyPropagation(ull maxSize) : maxSize_(1)
	{
		while (maxSize_ < maxSize)
			maxSize_ *= 2;
		data_ = vector<Integer>(ll(maxSize_) * 2 - 1, op_ii_.default_value);
		lazy_ = vector<Monoid>(ll(maxSize_) * 2 - 1, op_mm_.default_value);
	}

	void update(ll start, ll end, Monoid value)
	{
		if (start < 0)
			throw invalid_argument("Start should be non-negative.");
		if (maxSize_ < end)
			throw invalid_argument("End should be less than or equal to maxSize.");
		if (start >= end)
			throw invalid_argument("End should be more than start.");

		return _update(start, end, value, 0, maxSize_, 0);
	}

	void update(ll index, Integer value)
	{
		if (index >= maxSize_)
		{
			throw invalid_argument("Index should be less than maxSize.");
		}
		index += maxSize_ - 1;
		data_[index] = value;
		while (index > 0)
		{
			index = (index - 1) / 2;
			data_[index] = op_ii_.Execute(data_[2 * index + 1], data_[index * 2 + 2]);
		}
	}

	Integer query(ll start, ll end)
	{
		if (start < 0)
			throw invalid_argument("Start should be non-negative.");
		if (maxSize_ < end)
			throw invalid_argument("End should be less than or equal to maxSize.");
		if (start >= end)
			throw invalid_argument("End should be more than start.");

		return _query(start, end, 0, maxSize_, 0);
	}
};

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

	friend ResidueInteger &operator+= <>(ResidueInteger &lhs, const ResidueInteger &rhs);
	friend ResidueInteger &operator+= <>(ResidueInteger &lhs, const Integer &rhs);
	friend ResidueInteger &operator-= <>(ResidueInteger &lhs, const ResidueInteger &rhs);
	friend ResidueInteger &operator-= <>(ResidueInteger &lhs, const Integer &rhs);
	friend ResidueInteger &operator*= <>(ResidueInteger &lhs, const ResidueInteger &rhs);
	friend ResidueInteger &operator*= <>(ResidueInteger &lhs, const Integer &rhs);
	friend ResidueInteger &operator/= <>(ResidueInteger &lhs, const ResidueInteger &rhs);
	friend ResidueInteger &operator/= <>(ResidueInteger &lhs, const Integer &rhs);

	friend std::istream &operator>> <>(std::istream &lhs, ResidueInteger &rhs);
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

using Integer = tuple<rll, rll, rll, ll>;
using Monoid = tuple<rll, rll>;
struct OperatorII
{
	const static Integer default_value;
	static Integer Execute(const Integer &a, const Integer &b)
	{
		auto [a1, a2, a3, a4] = a;
		auto [b1, b2, b3, b4] = b;

		auto c1 = a1 + b1;
		auto c2 = a2 + b2;
		auto c3 = a3 + b3;
		auto c4 = a4 + b4;

		return make_tuple(c1, c2, c3, c4);
	};
};

struct OperatorIM
{
	const static Integer default_value;
	static Integer Execute(const Integer &l, const Monoid &r)
	{
		auto [ab, a, b, cnt] = l;
		auto [plus_a, plus_b] = r;

		auto c1 = ab + a * plus_b + b * plus_a + cnt * plus_a * plus_b;
		auto c2 = a + plus_a * cnt;
		auto c3 = b + plus_b * cnt;
		auto c4 = cnt;

		return make_tuple(c1, c2, c3, c4);
	};
};
struct OperatorMM
{
	const static Monoid default_value;
	static Monoid Execute(const Monoid &a, const Monoid &b)
	{
		auto [a1, a2] = a;
		auto [b1, b2] = b;
		return make_tuple(a1 + b1, a2 + b2);
	};
};
const Integer OperatorII::default_value = make_tuple(0LL, 0LL, 0LL, 0LL);
const Integer OperatorIM::default_value = make_tuple(0LL, 0LL, 0LL, 0LL);
const Monoid OperatorMM::default_value = make_tuple(0LL, 0LL);

using RMQLP = SegmentTreeWithLazyPropagation<Integer, Monoid, OperatorII, OperatorIM, OperatorMM>;

int solve()
{
	ll N, Q;
	cin >> N >> Q;

	vector<ll> as(N);
	vector<ll> bs(N);
	for (ll i = 0; i < N; ++i)
	{
		cin >> as[i];
	}
	for (ll i = 0; i < N; ++i)
	{
		cin >> bs[i];
	}

	RMQLP rmqlp(N);
	for (ll i = 0; i < N; ++i)
	{
		rmqlp.update(i, make_tuple(rll(as[i] * bs[i]), rll(as[i]), rll(bs[i]), 1LL));
	}

	ll t, l, r, x;
	for (ll i = 0; i < Q; ++i)
	{
		cin >> t;
		if (t == 1LL)
		{
			cin >> l >> r >> x;
			rmqlp.update(l - 1LL, r, make_tuple(x, 0LL));
		}
		if (t == 2LL)
		{
			cin >> l >> r >> x;
			rmqlp.update(l - 1LL, r, make_tuple(0LL, x));
		}
		if (t == 3LL)
		{
			cin >> l >> r;
			auto res = rmqlp.query(l - 1LL, r);
			cout << get<0>(res) << endl;
		}
	}

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
