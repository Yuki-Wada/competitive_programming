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

#define MAX_VALUE 9223372036854775807

template <ull N, class T, class... Args, std::enable_if_t<N == 0, int> = 0>
auto make_multiple_vector(Args... args) {
    return T(args...);
}

template <ull N, class T, class... Args, std::enable_if_t<N != 0, int> = 0>
auto make_multiple_vector(ull size, Args... args) {
    using value_type = std::decay_t<decltype(make_multiple_vector<N - 1, T>(args...))>;
    return vector<value_type>(size, make_multiple_vector<N - 1, T>(args...));
}

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

int solve() {
	string S;
	ll K;
	cin >> S >> K;

	vector<ll> one_counts;
	ll one_count = 0;
	REPD (i, 0, S.size()) {
		if (S[i] == '0'){
			one_counts.emplace_back(one_count);
			one_count = 0;
		}
		else {
			++one_count;
		}
	}
	one_counts.emplace_back(one_count);
	K = min(K, accumulate(one_counts.begin(), one_counts.end(), 0LL));

	// dps[i][j][k] は、以下の i, j, k における場合の数を表している
	// i: 左から i + 1 番目の 0 を指し示している 
	// j: (左から) i + 1 番目の 0 より右にある、移動させる予定の 1 の個数
	// k: (左から) i + 1 番目の 0 より右にあり、i 番目の 0 より左に移動させる予定の 1 の個数 (1 をどこに入れるかは決めておらず、プールされている)
	auto dps = make_multiple_vector<3, rll>(one_counts.size(), K + 1, K + 1);
	dps[one_counts.size() - 1][0][0] = 1;
	for (ll i = one_counts.size() - 1; i >= 1; --i) {
		for (ll j = 0; j <= K; j++) {
			for (ll k = 0; k <= j; k++) {
				for (ll l = 1; l <= one_counts[i]; ++l) {
					if (k + l > K || j + l > K) continue;
					// 「1 を移動させる」場合の数を求めている
					dps[i - 1][j + l][k + l] += dps[i][j][k];
				}
				for (ll l = 0; l <= k; ++l) {
					// 「左から来た移動させる予定の 1 のうち、ここに 1 を残す」場合の数を求めている
					dps[i - 1][j][l] += dps[i][j][k];
				}
			}
 		}
	}

	rll ans = 0;
	// i = 0 の場合の j, k の総和を求めることで、答えが求められる
	// i = 0 の場合、k は一番左の 0 より右に移動させる 1 の個数を表している
	for (ll i = 0; i <= K; i++) {
		for (ll j = 0; j <= K; j++) {
			ans += dps[0][i][j];
		}
	}
	RET(ans);

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
