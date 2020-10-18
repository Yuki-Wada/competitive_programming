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
template <> ll rll::default_mod = MOD;

int solve() {
	ll H, W;
	cin >> H >> W;

	vector<string> S(H);
	REPD(i, 0, H) cin >> S[i];

	ll light_count = 0;
	REPD(i, 0, H) REPD(j, 0, W) if (S[i][j] == '.') ++light_count;
	vector<vector<ll>> row_lights(H, vector<ll>(W));
	vector<vector<ll>> col_lights(H, vector<ll>(W));

	ll prev, count;
	REPD(i, 0, H) {
		prev = 0, count = 0;
		REPD(j, 0, W) {
			if (S[i][j] == '.') {
				++count;
			}
			else {
				REPD(k, prev, j) {
					row_lights[i][k] = count;
				}
				prev = j + 1;
				count = 0;
			}
		}
		REPD(k, prev, W) {
			row_lights[i][k] = count;
		}
	}

	REPD(j, 0, W) {
		prev = 0, count = 0;
		REPD(i, 0, H) {
			if (S[i][j] == '.') {
				++count;
			}
			else {
				REPD(k, prev, i) {
					col_lights[k][j] = count;
				}
				prev = i + 1;
				count = 0;
			}
		}
		REPD(k, prev, H) {
			col_lights[k][j] = count;
		}
	}

	vector<rll> mod2pow(light_count + 1);
	mod2pow[0] = 1;
	REPD(i, 0, light_count) {
		mod2pow[i + 1] = mod2pow[i] * 2LL;
	}

	rll res = 0;
	REPD(i, 0, H) {
		REPD(j, 0, W) {
			if (S[i][j] == '.') {
				ll shadow_count = light_count - row_lights[i][j] - col_lights[i][j] + 1;
				res += mod2pow[light_count] - mod2pow[shadow_count];
			}
		}
	}

	cout << res << endl;

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
