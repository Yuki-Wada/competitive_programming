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

int solve() {
	ll n, k;
	cin >> n >> k;

	vector<ll> as_positive;
	vector<ll> as_negative;
	ll a;
	for (ll i = 0; i < n; ++i) {
		cin >> a;
		if (a > 0) as_positive.emplace_back(a);
		else if (a < 0) as_negative.emplace_back(a);
	}
	sort(as_positive.begin(), as_positive.end(), greater<ll>());
	sort(as_negative.begin(), as_negative.end());

	if (as_positive.size() + as_negative.size() < k) {
		cout << 0 << endl;
		return 0;
	}
	if (n == k) {
		rll res = 1LL;
		for (ll i = 0; i < as_positive.size(); ++i) {
			res *= as_positive[i];
		}
		for (ll i = 0; i < as_negative.size(); ++i) {
			res *= as_negative[i];
		}
		cout << res.get_n() << endl;
		return 0;
	}

	if (as_positive.size() + as_negative.size() == k) {
		if (as_negative.size() % 2LL == 0LL) {
			rll res = 1LL;
			for (ll i = 0; i < as_positive.size(); ++i) {
				res *= as_positive[i];
			}
			for (ll i = 0; i < as_negative.size(); ++i) {
				res *= as_negative[i];
			}
			cout << res.get_n() << endl;
			return 0;
		}
		cout << 0 << endl;
		return 0;
	}

	if (as_positive.size() == 0) {
		if (k % 2LL != 0LL) {
			if (as_negative.size() < n) {
				cout << 0 << endl;
				return 0;
			}
			rll res = 1LL;
			for (ll i = 0; i < k; ++i) {
				res *= as_negative[n - i - 1LL];
			}
			cout << res.get_n() << endl;
			return 0;
		}
	}
	rll res = 1LL;
	ll positive_index = 0LL, negative_index = 0LL;
	while (positive_index + negative_index < k) {
		if (positive_index >= as_positive.size()) {
			res *= -as_negative[negative_index];
			++negative_index;
		}
		else if (negative_index >= as_negative.size()) {
			res *= as_positive[positive_index];
			++positive_index;
		}
		else if (as_positive[positive_index] >= (-as_negative[negative_index])) {
			res *= as_positive[positive_index];
			++positive_index;
		}
		else {
			res *= -as_negative[negative_index];
			++negative_index;
		}
	}
	if (negative_index % 2LL != 0LL) {
		if (positive_index >= as_positive.size() || negative_index <= 0) {
			res *= -as_negative[negative_index];
			++negative_index;
			--positive_index;
			res /= as_positive[positive_index];
		}
		else if (negative_index >= as_negative.size() || positive_index <= 0) {
			res *= as_positive[positive_index];
			++positive_index;
			--negative_index;
			res /= -as_negative[negative_index];
		}
		else if (as_positive[positive_index] * as_positive[positive_index - 1LL] >=
			as_negative[negative_index] * as_negative[negative_index - 1LL]) {
			res *= as_positive[positive_index];
			++positive_index;
			--negative_index;
			res /= -as_negative[negative_index];
		}
		else {
			res *= -as_negative[negative_index];
			++negative_index;
			--positive_index;
			res /= as_positive[positive_index];
		}
	}

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
