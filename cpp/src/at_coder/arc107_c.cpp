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

class UnionFindTree
{
private:
	const unsigned elemCount_;
	vector<unsigned> parentNodeNumbers_;
	vector<unsigned> treeDepths_;
	vector<unsigned> setSizes_;

	// Average Computational Complexity: O(log(elemCount_))) 
	unsigned getRootNode(unsigned x)
	{
		if (parentNodeNumbers_[x] == x)
		{
			return x;
		}
		else
		{
			return getRootNode(parentNodeNumbers_[x]);
		}
	}

public:
	UnionFindTree(unsigned elemCount) :
		elemCount_(elemCount),
		parentNodeNumbers_(elemCount),
		treeDepths_(elemCount, 0),
		setSizes_(elemCount, 1)
	{
		for (unsigned i = 0; i < parentNodeNumbers_.size(); ++i)
		{
			parentNodeNumbers_[i] = i;
		}
	}

	// Average Computational Complexity: O(log(elemCount_))) 
	void uniteSet(unsigned x, unsigned y)
	{
		x = getRootNode(x);
		y = getRootNode(y);
		if (x == y)
		{
			return;
		}

		if (treeDepths_[x] < treeDepths_[y])
		{
			parentNodeNumbers_[x] = y;
			setSizes_[y] = setSizes_[x] + setSizes_[y];
		}
		else
		{
			parentNodeNumbers_[y] = x;
			setSizes_[x] = setSizes_[x] + setSizes_[y];
			if (treeDepths_[x] == treeDepths_[y])
			{
				++treeDepths_[x];
			}
		}
	}

	unsigned getSetSize(unsigned x)
	{
		return setSizes_[getRootNode(x)];
	}

	// Average Computational Complexity: O(log(elemCount_))) 
	bool includedInSameSet(unsigned x, unsigned y)
	{
		return getRootNode(x) == getRootNode(y);
	}
};

int solve() {
	ll N, K;
	cin >> N >> K;
	
	vector<vector<ll>> matrix(N, vector<ll>(N));
	ll a;
	REPD(i, 0, N) REPD(j, 0, N) cin >> a, matrix[i][j] = a;
	
	auto excls = get_exclamations(N + 1);
	rll res = 1;
	{
		vector<vector<ll>> edges(N);
		REPD(i, 0, N) {
			REPD(j, 0, N) {
				if (i == j) continue;
				bool is_satisfied = true;
				REPD(k, 0, N) is_satisfied = is_satisfied && (matrix[i][k] + matrix[j][k] <= K);
				if (is_satisfied) edges[i].emplace_back(j), edges[j].emplace_back(i);
			}
		}

		vector<bool> is_visited(N, false);
		REPD(i, 0, N) {
			if (is_visited[i]) continue;
			ll size = 0;
			stack<ll> s;
			s.emplace(i);
			is_visited[i] = true;
			++size;
			while (!s.empty()) {
				ll curr = s.top();
				s.pop();
				REPI(next, edges[curr]) {
					if (is_visited[next]) continue;
					s.emplace(next);
					is_visited[next] = true;
					++size;
				}
			}
			res *= excls[size];
		}
	}
	{
		vector<vector<ll>> edges(N);
		REPD(i, 0, N) {
			REPD(j, 0, N) {
				if (i == j) continue;
				bool is_satisfied = true;
				REPD(k, 0, N) is_satisfied = is_satisfied && (matrix[k][i] + matrix[k][j] <= K);
				if (is_satisfied) edges[i].emplace_back(j), edges[j].emplace_back(i);
			}
		}

		vector<bool> is_visited(N, false);
		REPD(i, 0, N) {
			if (is_visited[i]) continue;
			ll size = 0;
			stack<ll> s;
			s.emplace(i);
			is_visited[i] = true;
			++size;
			while (!s.empty()) {
				ll curr = s.top();
				s.pop();
				REPI(next, edges[curr]) {
					if (is_visited[next]) continue;
					s.emplace(next);
					is_visited[next] = true;
					++size;
				}
			}
			res *= excls[size];
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
