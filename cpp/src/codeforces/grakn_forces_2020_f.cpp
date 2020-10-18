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
static const ll MOD = 998244353LL;
// static const ll MOD = (1LL << 61LL) - 1LL;
static const double PI = 3.14159265358979323846;

// conversion
inline ll toint(string s) { ll v; istringstream sin(s); sin >> v; return v; }
template<class t> inline string tostring(t x) { ostringstream sout; sout << x; return sout.str(); }

// print
#define RET(x) return cout << x << endl, 0;

// for loop
#define REP(i, a, b) for ((i) = (ll)(a);(i) < (ll)(b);(i)++)
#define REPD(i, a, b) for (ll i = (ll)(a);(i) < (ll)(b);(i)++)
#define REPI(v, vs) for (auto& v : vs)

//debug
#ifdef LOCAL_ENV
#define DUMP(x)  cerr << #x << " = " << (x) << endl
#define DEBUG(x) cerr << #x << " = " << (x) << " (l" << __LINE__ << ")" << " " << __FILE__ << endl
#else
#define DUMP(x)
#define DEBUG(x)
#endif

#define MAX_VALUE 9223372036854775807LL

template <ull N, class T, class... Args, std::enable_if_t<N == 0, int> = 0>
auto make_multiple_vector(Args... args) {
    return T(args...);
}

template <ull N, class T, class... Args, std::enable_if_t<N != 0, int> = 0>
auto make_multiple_vector(ull size, Args... args) {
    using value_type = std::decay_t<decltype(make_multiple_vector<N - 1, T>(args...))>;
    return vector<value_type>(size, make_multiple_vector<N - 1, T>(args...));
}


template<class Integer>
Integer getModValue(const Integer& n, Integer mod)
{
	return (n % mod + mod) % mod;
}

// computational complexity: o(log(max(a, b)))
template<class Integer>
inline pair<Integer, Integer> getBezoutsIdentitySolution(Integer a, Integer b)
{
	if (b == Integer(0)) return { Integer(1) / a, Integer(0) };
	auto sol = getBezoutsIdentitySolution(b, a % b);
	return { sol.second, sol.first - (a / b) * sol.second };
}

// computational complexity: o(log(max(n, mod)))
template<class Integer>
inline Integer getModInverse(const Integer& n, Integer mod)
{
	auto sol = getBezoutsIdentitySolution(n, mod);
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
	static Integer default_mod;
	Integer n() const { return n_; }
	Integer mod() const { return mod_; }

	ResidueInteger() : mod_(default_mod), n_(getModValue(Integer(0), mod_)) {}
	ResidueInteger(Integer n) : mod_(default_mod), n_(getModValue(n, mod_)) {}
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

using rll = ResidueInteger<ll>;
template<> ll rll::default_mod = MOD;

int solve() {
	ll N;
	cin >> N;

	if (N == 1) {
		cout << 0 << endl;
		return 0;
	}
	ll i = 2;
	vector<vector<pair<ll, ll>>> pairs_list;
	vector<pair<ll, ll>> pairs;
	pairs.emplace_back(1, 2);
	pairs_list.emplace_back(pairs);
	ll x, y;
	while (i * 2 <= N) {
		pairs.clear();
		for (const auto& pair: pairs_list.back()) {
			tie(x, y) = pair;
			pairs.emplace_back(x, y);
			pairs.emplace_back(x + i, y + i);
		}
		for (ll j = 1; j <= i; ++j) {
			pairs.emplace_back(j, j + i);
		}
		i *= 2;
		pairs_list.emplace_back(pairs);
	}

	vector<pair<ll, ll>> res;
	for (const auto& pair: pairs_list.back()) {
		tie(x, y) = pair;
		res.emplace_back(x, y);
	}

	for (const auto& pair: pairs_list.back()) {
		tie(x, y) = pair;
		res.emplace_back(x + N - i, y + N - i);
	}

	cout << res.size() << endl;
	REPI(pair, res) {
		tie(x, y) = pair;
		cout << x << " " << y << endl;
	}

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
