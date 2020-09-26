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

template<unsigned int Mod> class ResidueInteger;
template<unsigned int Mod> ResidueInteger<Mod>& operator+=(ResidueInteger<Mod>& lhs, const ResidueInteger<Mod>& rhs);
template<unsigned int Mod> ResidueInteger<Mod>& operator+=(ResidueInteger<Mod>& lhs, const ll& rhs);
template<unsigned int Mod> ResidueInteger<Mod>& operator-=(ResidueInteger<Mod>& lhs, const ResidueInteger<Mod>& rhs);
template<unsigned int Mod> ResidueInteger<Mod>& operator-=(ResidueInteger<Mod>& lhs, const ll& rhs);
template<unsigned int Mod> ResidueInteger<Mod>& operator*=(ResidueInteger<Mod>& lhs, const ResidueInteger<Mod>& rhs);
template<unsigned int Mod> ResidueInteger<Mod>& operator*=(ResidueInteger<Mod>& lhs, const ll& rhs);
template<unsigned int Mod> ResidueInteger<Mod>& operator/=(ResidueInteger<Mod>& lhs, const ResidueInteger<Mod>& rhs);
template<unsigned int Mod> ResidueInteger<Mod>& operator/=(ResidueInteger<Mod>& lhs, const ll& rhs);
template<unsigned int Mod> std::istream& operator>>(std::istream& lhs, ResidueInteger<Mod>& rhs);

template<unsigned int Mod>
class ResidueInteger
{
private:
	ll n_;
public:
	ResidueInteger() : n_(getModValue(0, Mod)) {}
	ResidueInteger(ll n) : n_(getModValue(n, Mod)) {}

	ll mod() const { return Mod; }
	ll n() const { return n_; }

	friend ResidueInteger& operator+= <>(ResidueInteger& lhs, const ResidueInteger& rhs);
	friend ResidueInteger& operator+= <>(ResidueInteger& lhs, const ll& rhs);
	friend ResidueInteger& operator-= <>(ResidueInteger& lhs, const ResidueInteger& rhs);
	friend ResidueInteger& operator-= <>(ResidueInteger& lhs, const ll& rhs);
	friend ResidueInteger& operator*= <>(ResidueInteger& lhs, const ResidueInteger& rhs);
	friend ResidueInteger& operator*= <>(ResidueInteger& lhs, const ll& rhs);
	friend ResidueInteger& operator/= <>(ResidueInteger& lhs, const ResidueInteger& rhs);
	friend ResidueInteger& operator/= <>(ResidueInteger& lhs, const ll& rhs);
	friend std::istream& operator>> <>(std::istream& lhs, ResidueInteger& rhs);
};

template<unsigned int Mod> inline ResidueInteger<Mod> operator+(const ResidueInteger<Mod>& lhs, const ResidueInteger<Mod>& rhs){ return lhs.n() + rhs.n(); }
template<unsigned int Mod> inline ResidueInteger<Mod> operator+(const ResidueInteger<Mod>& lhs, const ll& rhs){ return lhs.n() + getModValue(rhs, Mod); }
template<unsigned int Mod> inline ResidueInteger<Mod> operator+(const ll& lhs, const ResidueInteger<Mod>& rhs) { return getModValue(lhs, Mod) + rhs.n(); }
template<unsigned int Mod> inline ResidueInteger<Mod>& operator+=(ResidueInteger<Mod>& lhs, const ResidueInteger<Mod>& rhs) { lhs.n_ = getModValue(lhs.n() + rhs.n(), Mod); return lhs; }
template<unsigned int Mod> inline ResidueInteger<Mod>& operator+=(ResidueInteger<Mod>& lhs, const ll& rhs){ lhs.n_ = getModValue(lhs.n() + getModValue(rhs, Mod), Mod); return lhs; }
template<unsigned int Mod> inline ResidueInteger<Mod> operator-(const ResidueInteger<Mod>& lhs, const ResidueInteger<Mod>& rhs) { return lhs.n() - rhs.n(); }
template<unsigned int Mod> inline ResidueInteger<Mod> operator-(const ResidueInteger<Mod>& lhs, const ll& rhs) { return lhs.n() - getModValue(rhs, Mod), Mod; }
template<unsigned int Mod> inline ResidueInteger<Mod> operator-(const ll& lhs, const ResidueInteger<Mod>& rhs) { return getModValue(lhs, Mod) - rhs.n(); }
template<unsigned int Mod> inline ResidueInteger<Mod>& operator-=(ResidueInteger<Mod>& lhs, const ResidueInteger<Mod>& rhs) { lhs.n_ = getModValue(lhs.n() - rhs.n(), Mod); return lhs; }
template<unsigned int Mod> inline ResidueInteger<Mod>& operator-=(ResidueInteger<Mod>& lhs, const ll& rhs) { lhs.n_ = getModValue(lhs.n() - getModValue(rhs, Mod), Mod); return lhs; }
template<unsigned int Mod> inline ResidueInteger<Mod> operator*(const ResidueInteger<Mod>& lhs, const ResidueInteger<Mod>& rhs) { return lhs.n() * rhs.n(); }
template<unsigned int Mod> inline ResidueInteger<Mod> operator*(const ResidueInteger<Mod>& lhs, const ll& rhs) { return lhs.n() * getModValue(rhs, Mod); }
template<unsigned int Mod> inline ResidueInteger<Mod> operator*(const ll& lhs, const ResidueInteger<Mod>& rhs) { return getModValue(lhs, Mod) * rhs.n(); }
template<unsigned int Mod> inline ResidueInteger<Mod>& operator*=(ResidueInteger<Mod>& lhs, const ResidueInteger<Mod>& rhs) { lhs.n_ = getModValue(lhs.n() * rhs.n(), Mod); return lhs; }
template<unsigned int Mod> inline ResidueInteger<Mod>& operator*=(ResidueInteger<Mod>& lhs, const ll& rhs) { lhs.n_ = getModValue(lhs.n() * getModValue(rhs, Mod), Mod); return lhs; }
template<unsigned int Mod> inline ResidueInteger<Mod> operator/(const ResidueInteger<Mod>& lhs, const ResidueInteger<Mod>& rhs) { return lhs.n() * getModInverse(rhs.n(), Mod); }
template<unsigned int Mod> inline ResidueInteger<Mod> operator/(const ResidueInteger<Mod>& lhs, const ll& rhs) { return lhs.n() * getModInverse(getModValue(rhs, Mod), Mod); }
template<unsigned int Mod> inline ResidueInteger<Mod> operator/(const ll& lhs, const ResidueInteger<Mod>& rhs) { return getModValue(lhs, Mod) * getModInverse(rhs.n(), Mod); }
template<unsigned int Mod> inline ResidueInteger<Mod>& operator/=(ResidueInteger<Mod>& lhs, const ResidueInteger<Mod>& rhs) { lhs.n_ = getModValue(lhs.n() * getModInverse(rhs.n(), Mod), Mod); return lhs; }
template<unsigned int Mod> inline ResidueInteger<Mod>& operator/=(ResidueInteger<Mod>& lhs, const ll& rhs) { lhs.n_ = getModValue(lhs.n() * getModInverse(getModValue(rhs, Mod), Mod), Mod); return lhs; }
template<unsigned int Mod> inline bool operator==(const ResidueInteger<Mod>& lhs, const ResidueInteger<Mod>& rhs) { return lhs.n() == rhs.n(); }
template<unsigned int Mod> inline bool operator==(const ResidueInteger<Mod>& lhs, const ll& rhs) { return lhs.n() == getModValue(rhs, Mod); }
template<unsigned int Mod> inline bool operator==(const ll& lhs, const ResidueInteger<Mod>& rhs) { return getModValue(lhs, Mod) == rhs.n(); }

template<unsigned int Mod>
std::ostream& operator<<(std::ostream& lhs, const ResidueInteger<Mod>& rhs)
{
	return lhs << rhs.n();
}

template<unsigned int Mod>
std::istream& operator>>(std::istream& lhs, ResidueInteger<Mod>& rhs)
{
	lhs >> rhs.n_;
	return lhs;
}

using rll = ResidueInteger<MOD>;

std::ostream& operator<<(std::ostream& lhs, const pair<rll, ull>& rhs)
{
	lhs << rhs.first;
	return lhs;
}

template <class Integer, class Operator> class SegmentTree;
template <class Integer, class Operator>
std::ostream& operator<<(std::ostream& lhs, const SegmentTree<Integer, Operator>& rhs);

template<class Integer>
inline Integer get_power(Integer base, ull exponential)
{
	Integer result = 1;
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

template<class Integer, class Monoid, class OperatorII, class OperatorIM, class OperatorMM>
class SegmentTreeWithLazyPropagation {
private:
	ull maxSize_;
	vector<Integer> data_;
	vector<Monoid> lazy_;
	OperatorII op_ii_;
	OperatorIM op_im_;
	OperatorMM op_mm_;

	void _lazy_propagate(ll k) {
		if (lazy_[k] == op_mm_.default_value) return;
		if (k < maxSize_ - 1) {
			lazy_[k * 2 + 1] = op_mm_.Execute(lazy_[k * 2 + 1], lazy_[k]);
            lazy_[k * 2 + 2] = op_mm_.Execute(lazy_[k * 2 + 2], lazy_[k]);
        }
        data_[k] = op_im_.Execute(data_[k], lazy_[k]);
        lazy_[k] = op_mm_.default_value;
	}

	Integer _query(ll start, ll end, ll searchStart, ll searchEnd, ll node)
	{
		_lazy_propagate(node);
		if (searchEnd <= start || end <= searchStart) return op_ii_.default_value;
		if (start <= searchStart && searchEnd <= end) return data_[node];

		return op_ii_.Execute(
			_query(start, end, searchStart, (searchStart + searchEnd) / 2, node * 2 + 1),
			_query(start, end, (searchStart + searchEnd) / 2, searchEnd, node * 2 + 2)
		);
	}

	void _update(ll start, ll end, Monoid value, ll searchStart, ll searchEnd, ll node)
	{
		_lazy_propagate(node);
		if (start <= searchStart && searchEnd <= end) {
			lazy_[node] = op_mm_.Execute(lazy_[node], value);
			_lazy_propagate(node);
		}
		else if (searchStart < end && start < searchEnd) {
			_update(start, end, value, searchStart, (searchStart + searchEnd) / 2, node * 2 + 1);
			_update(start, end, value, (searchStart + searchEnd) / 2, searchEnd, node * 2 + 2);
			data_[node] = op_ii_.Execute(data_[node * 2 + 1], data_[node * 2 + 2]);
		}
	}

public:
	ull size() {return maxSize_;}
	SegmentTreeWithLazyPropagation(ull maxSize) : maxSize_(1) {
		while (maxSize_ < maxSize) maxSize_ *= 2;
		data_ = vector<Integer>(ll(maxSize_) * 2 - 1, op_ii_.default_value);
		lazy_ = vector<Monoid>(ll(maxSize_) * 2 - 1, op_mm_.default_value);
	}

	void update(ll start, ll end, Monoid value)
	{
		if (start < 0) throw invalid_argument("Start should be non-negative.");
		if (maxSize_ < end) throw invalid_argument("End should be less than or equal to maxSize.");
		if (start >= end) throw invalid_argument("End should be more than start.");

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
		if (start < 0) throw invalid_argument("Start should be non-negative.");
		if (maxSize_ < end) throw invalid_argument("End should be less than or equal to maxSize.");
		if (start >= end) throw invalid_argument("End should be more than start.");

		return _query(start, end, 0, maxSize_, 0);
	}
};

struct MinOp {
	const static ll default_value = MAX_VALUE;
	static ll Execute(const ll& a, const ll& b) { return min(a, b); };
};

using RMQLP = SegmentTreeWithLazyPropagation<ll, ll, MinOp, MinOp, MinOp>;

vector<rll> power10;
vector<rll> power10_sum;
struct OpII {
	const pair<rll, ull> default_value = {0LL, 1LL};
	static pair<rll, ull> Execute(const pair<rll, ull>& a, const pair<rll, ull>& b) {
		rll a_num, b_num;
		ull a_cnt, b_cnt;
		forward_as_tuple(a_num, a_cnt) = a;
		forward_as_tuple(b_num, b_cnt) = b;
		return {a_num * power10[b_cnt] + b_num, a_cnt + b_cnt};
	};
};

struct OpIM {
	const pair<rll, ull> default_value = {0LL, 1LL};
	static pair<rll, ull> Execute(const pair<rll, ull>& a, const ll& b) {
		rll a_num;
		ll a_cnt;
		forward_as_tuple(a_num, a_cnt) = a;
		return {power10_sum[a_cnt] * b, a_cnt};
	};
};

struct OpMM {
	const ll default_value = -1;
	static ll Execute(const ll& a, const ll& b) {
		return b;
	};
};

int solve() {
	ll N, Q;
	cin >> N >> Q;

	SegmentTreeWithLazyPropagation<pair<rll, ull>, ll, OpII, OpIM, OpMM> sum(N);
	power10 = vector<rll>(sum.size() + 1);
	power10_sum = vector<rll>(sum.size() + 1);
	power10[0] = 1;
	power10_sum[0] = 0;
	REPD(i, 0, sum.size()) {
		power10[i + 1] = power10[i] * 10;
		power10_sum[i + 1] = power10[i] + power10_sum[i];
	}

	REPD(i, 0, sum.size()) {
		sum.update(i, {1, 1});
	}
	
	rll coef = 1 / power10[sum.size() - N];
	ll l, r, d;
	REPD(i, 0, Q) {
		cin >> l >> r >> d;
		sum.update(l - 1, r, d);
		cout << (sum.query(0, sum.size()).first - (N < sum.size() ? sum.query(N, sum.size()).first: 0)) * coef << endl;
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
