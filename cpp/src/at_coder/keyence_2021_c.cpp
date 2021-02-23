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

int solve() {
	ll H, W, K;
	cin >> H >> W >> K;
	
	vector<vector<char>> chs(H, vector<char>(W, 'N'));
	ll h, w; char c;
	REPD(i, 0, K) {
		cin >> h >> w >> c;
		--h, --w;
		chs[h][w] = c;
	}
 
	ll accum;
	vector<vector<ll>> accum_row_ns(H, vector<ll>(W, 0));
	vector<vector<ll>> accum_col_ns(H, vector<ll>(W, 0));
	REPD(i, 0, H) {
		accum = 0;
		REPD(j, 0, W) {
			if (chs[i][j] == 'N') ++accum;
			accum_row_ns[i][j] = accum;
		}
	}
	REPD(j, 0, W) {
		accum = 0;
		REPD(i, 0, H) {
			if (chs[i][j] == 'N') ++accum;
			accum_col_ns[i][j] = accum;
		}
	}
	vector<rll> power3(max(H, W) + 1LL, 1);
	rll pow = 1;
	REPD(i, 0, max(H, W)) {
		pow *= 3LL;
		power3[i + 1] = pow;
	}
 
 	vector<vector<rll>> dps(H + 1, vector<rll>(W + 1, 0));
	dps[H - 1][W - 1] = chs[H - 1][W - 1] == 'N' ? 3 : 1;
	rll res;
	REPD(i, 0, H) {
		REPD(j, 0, W) {
			if (i == 0 && j == 0) continue;
			if (chs[H - i - 1LL][W - j - 1LL] != 'D') {
				res = 0;
				res += dps[H - i - 1LL][W - j];
				res *= power3[accum_col_ns[H - 1LL][W - j - 1LL] - accum_col_ns[H - i - 1LL][W - j - 1LL]];
				if (chs[H - i - 1LL][W - j - 1LL] == 'N') res *= 2LL;
				dps[H - i - 1LL][W - j - 1LL] += res;
			}
			if (chs[H - i - 1LL][W - j - 1LL] != 'R'){
				res = 0;
				res += dps[H - i][W - j - 1LL];
				res *= power3[accum_row_ns[H - i - 1LL][W - 1LL] - accum_row_ns[H - i - 1LL][W - j - 1LL]];
				if (chs[H - i - 1LL][W - j - 1LL] == 'N') res *= 2LL;
				dps[H - i - 1LL][W - j - 1LL] += res;
			}
		}
	}
 
	cout << dps[0][0] << endl;
 
	return 0;

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
