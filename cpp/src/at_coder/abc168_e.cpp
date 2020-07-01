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
using comp = complex<double>;

const ll MOD = 1000000007LL;
const double PI = 3.14159265358979323846;

//conversion
//------------------------------------------
inline int toint(string s) { int v; istringstream sin(s); sin >> v; return v; }
template<class t> inline string tostring(t x) { ostringstream sout; sout << x; return sout.str(); }

// for loop
#define REP(i, n) for ((i) = 0;(i) < (ll)(n);(i)++)

//debug
#define DUMP(x)  cerr << #x << " = " << (x) << endl
#define DEBUG(x) cerr << #x << " = " << (x) << " (l" << __line__ << ")" << " " << __file__ << endl

template <class Integer>
class ResidueInteger
{
private:
	Integer mod_;
	Integer n_;
	static Integer global_mod_;

	// computational complexity: o(log(max(a, b))) 
	static inline pair<Integer, Integer> getBezoutsIdentitySolution(Integer a, Integer b)
	{
		if (b == 0)
		{
			return { 1, 0 };
		}
		auto sol = getBezoutsIdentitySolution(b, a % b);
		return { sol.second, sol.first - (a / b) * sol.second };
	}

public:
	static Integer default_mod_;

	Integer getModValue(const Integer& n) const
	{
		return (n % mod_ + mod_) % mod_;
	}

	// computational complexity: o(log(max(n, mod))) 
	inline Integer getModInverse(const Integer& n) const
	{
		auto sol = getBezoutsIdentitySolution(n, mod_);
		if (n * sol.first + mod_ * sol.second != 1)
		{
			return -1;
		}
		return getModValue(sol.first);
	}

	ResidueInteger() : mod_(default_mod_), n_(getModValue(0)) {}
	ResidueInteger(Integer n) : mod_(default_mod_), n_(getModValue(n)) {}
	ResidueInteger(Integer n, Integer mod) : mod_(mod), n_(getModValue(n)) {}

	inline ResidueInteger operator+(const ResidueInteger& rhs) const
	{
		if (this->mod_ != rhs.mod_)
		{
			throw invalid_argument("The mods of both operands should be equal.");
		}
		return { this->n_ + rhs.n_, this->mod_ };
	}
	inline ResidueInteger operator+(const Integer& rhs) const
	{
		return { this->n_ + getModValue(rhs), this->mod_ };
	}
	friend inline ResidueInteger operator+(const Integer& lhs, const ResidueInteger& rhs)
	{
		return { rhs.getModValue(lhs) + rhs.n_, rhs.mod_ };
	}
	inline ResidueInteger& operator+=(const ResidueInteger& rhs)
	{
		if (this->mod_ != rhs.mod_)
		{
			throw invalid_argument("The mods of both operands should be equal.");
		}
		this->n_ = getModValue(this->n_ + rhs.n_);
		return *this;
	}
	inline ResidueInteger& operator+=(const Integer& rhs)
	{
		this->n_ = getModValue(this->n_ + getModValue(rhs));
		return *this;
	}

	inline ResidueInteger operator-(const ResidueInteger& rhs) const
	{
		if (this->mod_ != rhs.mod_)
		{
			throw invalid_argument("The mods of both operands should be equal.");
		}
		return { this->n_ - rhs.n_, this->mod_ };
	}
	inline ResidueInteger operator-(const Integer& rhs) const
	{
		return { this->n_ - getModValue(rhs), this->mod_ };
	}
	friend inline ResidueInteger operator-(const Integer& lhs, const ResidueInteger& rhs)
	{
		return { rhs.getModValue(lhs) - rhs.n_, rhs.mod_ };
	}
	inline ResidueInteger& operator-=(const ResidueInteger& rhs)
	{
		if (this->mod_ != rhs.mod_)
		{
			throw invalid_argument("The mods of both operands should be equal.");
		}
		this->n_ = getModValue(this->n_ - rhs.n_);
		return *this;
	}
	inline ResidueInteger& operator-=(const Integer& rhs)
	{
		this->n_ = getModValue(this->n_ - getModValue(rhs));
		return *this;
	}

	inline ResidueInteger operator*(const ResidueInteger& rhs) const
	{
		if (this->mod_ != rhs.mod_)
		{
			throw invalid_argument("The mods of both operands should be equal.");
		}
		return { this->n_ * rhs.n_, this->mod_ };
	}
	inline ResidueInteger operator*(const Integer& rhs) const
	{
		return { this->n_ * getModValue(rhs), this->mod_ };
	}
	friend inline ResidueInteger operator*(const Integer& lhs, const ResidueInteger& rhs)
	{
		return { rhs.getModValue(lhs) * rhs.n_, rhs.mod_ };
	}
	inline ResidueInteger& operator*=(const ResidueInteger& rhs)
	{
		if (this->mod_ != rhs.mod_)
		{
			throw invalid_argument("The mods of both operands should be equal.");
		}
		this->n_ = getModValue(this->n_ * rhs.n_);
		return *this;
	}
	inline ResidueInteger& operator*=(const Integer& rhs)
	{
		this->n_ = getModValue(this->n_ * getModValue(rhs));
		return *this;
	}

	inline ResidueInteger operator/(const ResidueInteger& rhs) const
	{
		if (this->mod_ != rhs.mod_)
		{
			throw invalid_argument("The mods of both operands should be equal.");
		}
		return { this->n_ * getModInverse(rhs.n_), this->mod_ };
	}
	inline ResidueInteger operator/(const Integer& rhs) const
	{
		return { this->n_ * getModInverse(getModValue(rhs)), this->mod_ };
	}
	friend inline ResidueInteger operator/(const Integer& lhs, const ResidueInteger& rhs)
	{
		return { rhs.getModValue(lhs) * rhs.getModInverse(rhs.n_), rhs.mod_ };
	}
	inline ResidueInteger& operator/=(const ResidueInteger& rhs)
	{
		if (this->mod_ != rhs.mod_)
		{
			throw invalid_argument("The mods of both operands should be equal.");
		}
		this->n_ = getModValue(this->n_ * getModInverse(rhs.n_));
		return *this;
	}
	inline ResidueInteger& operator/=(const Integer& rhs)
	{
		this->n_ = getModValue(this->n_ * getModInverse(getModValue(rhs)));
		return *this;
	}

	inline bool operator==(const ResidueInteger& rhs) const
	{
		return (this->n_ == rhs.n_) && (this->mod_ == rhs.mod_);
	}
	inline bool operator==(const Integer& rhs) const
	{
		return this->n_ == getModValue(rhs);
	}
	friend bool operator==(const Integer& lhs, const ResidueInteger& rhs)
	{
		return rhs.getModValue(lhs) == rhs.n_;
	}

	Integer get_n() const { return n_; }

	friend std::ostream& operator<<(std::ostream& lhs, const ResidueInteger& rhs)
	{
		return lhs << rhs.n_;
	}

	friend std::istream& operator>>(std::istream& lhs, ResidueInteger& rhs)
	{
		lhs >> rhs.n_;
		return lhs;
	}
};
using rll = ResidueInteger<ll>;
template<> ll rll::default_mod_ = 1000000007LL;

// computational complexity: o(log(max(a, b))) 
inline ull get_gcd(ull a, ull b)
{
	if (b == 0)
	{
		return a;
	}
	return get_gcd(b, a % b);
}

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

int solve() {
	ll N;
	cin >> N;

	vector<pair<ll, ll>> pairs;
	pairs.reserve(N);
	ll A, B;
	for (ll i = 0; i < N; ++i) {
		cin >> A >> B;
		if (A == 0LL && B == 0LL) {
			pairs.emplace_back(0LL, 0LL);
		}
		else if (A == 0LL && B != 0LL) {
			pairs.emplace_back(0LL, 1LL);
		}
		else if (A != 0LL && B == 0LL) {
			pairs.emplace_back(1LL, 0LL);
		}
		else {
			if (A < 0LL) {
				A = -A;
				B = -B;
			}
			ll gcd = get_gcd(A, B >= 0 ? B: -B);
			pairs.emplace_back(A / gcd, B / gcd);
		}
	}

	ll a0bn0 = 0LL, an0b0 = 0LL, a0b0 = 0LL;
	map<pair<ll, ll>, pair<ll, ll>> ab_count;
	for (ll i = 0; i < N; ++i) {
		ll a = pairs[i].first;
		ll b = pairs[i].second;

		if (a == 0LL && b == 0LL) {
			++a0b0;
			continue;
		}
		if (a == 0LL && b != 0LL) {
			++a0bn0;
			continue;
		}
		if (a != 0LL && b == 0LL) {
			++an0b0;
			continue;
		}
		if (ab_count.count(make_pair(a, b)) != 0) {
			++ab_count[make_pair(a, b)].first;
			continue;
		}
		if (ab_count.count(make_pair(b >= 0 ? b : -b, b >= 0 ? -a : a)) != 0) {
			++ab_count[make_pair(b >= 0 ? b : -b, b >= 0 ? -a : a)].second;
			continue;
		}
		ab_count[make_pair(a, b)] = make_pair(1, 0);
	}

	rll res = 1;
	res *= get_power(rll(2), a0bn0) + get_power(rll(2), an0b0) - 1LL;
	for (auto iter = ab_count.begin(); iter != ab_count.end(); ++iter) {
		ll count1, count2;
		tie(count1, count2) = iter->second;
		res *= get_power(rll(2), count1) + get_power(rll(2), count2) - 1LL;
	}
	res -= 1LL;
	res += a0b0;

	cout << res.get_n() << endl;

	return 0;
}

//main function
int main()
{
	cin.tie(0);
	ios::sync_with_stdio(false);

	solve();

	return 0;
}
