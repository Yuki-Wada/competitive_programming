#ifndef __QUOTIENT_NUMBER_HPP__
#define __QUOTIENT_NUMBER_HPP__ 0

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

static const ll MOD = 1000000007LL;

template<class Integer> class QuotientNumber;
template<class Integer> QuotientNumber<Integer>& operator+=(QuotientNumber<Integer>& lhs, const QuotientNumber<Integer>& rhs);
template<class Integer> QuotientNumber<Integer>& operator+=(QuotientNumber<Integer>& lhs, const Integer& rhs);
template<class Integer> QuotientNumber<Integer>& operator-=(QuotientNumber<Integer>& lhs, const QuotientNumber<Integer>& rhs);
template<class Integer> QuotientNumber<Integer>& operator-=(QuotientNumber<Integer>& lhs, const Integer& rhs);
template<class Integer> QuotientNumber<Integer>& operator*=(QuotientNumber<Integer>& lhs, const QuotientNumber<Integer>& rhs);
template<class Integer> QuotientNumber<Integer>& operator*=(QuotientNumber<Integer>& lhs, const Integer& rhs);
template<class Integer> QuotientNumber<Integer>& operator/=(QuotientNumber<Integer>& lhs, const QuotientNumber<Integer>& rhs);
template<class Integer> QuotientNumber<Integer>& operator/=(QuotientNumber<Integer>& lhs, const Integer& rhs);
template<class Integer> std::istream& operator>>(std::istream& lhs, QuotientNumber<Integer>& rhs);

// computational complexity: o(log(max(a, b)))
template<class Integer>
inline Integer get_gcd(Integer a, Integer b) {
	if (b == Integer(0)) return a;
	return get_gcd(b, a % b);
}

inline pair<ll, ll> reduce(ll a, ll b) {
	ll gcd = get_gcd(abs(a), abs(b));
	a /= gcd, b /= gcd;
	return {a, b};
}

template<class Integer>
class QuotientNumber
{
private:
	Integer a_, b_;
public:
	QuotientNumber() : a_(0), b_(1) {}
	QuotientNumber(Integer n) : a_(n), b_(1) {}
	QuotientNumber(Integer a, Integer b) : a_(a), b_(b) {
		tie(a_, b_) = reduce(a, b);
	}

	Integer a() const { return a_; }
	Integer b() const { return b_; }

	friend QuotientNumber& operator+= <>(QuotientNumber& lhs, const QuotientNumber& rhs);
	friend QuotientNumber& operator+= <>(QuotientNumber& lhs, const Integer& rhs);
	friend QuotientNumber& operator-= <>(QuotientNumber& lhs, const QuotientNumber& rhs);
	friend QuotientNumber& operator-= <>(QuotientNumber& lhs, const Integer& rhs);
	friend QuotientNumber& operator*= <>(QuotientNumber& lhs, const QuotientNumber& rhs);
	friend QuotientNumber& operator*= <>(QuotientNumber& lhs, const Integer& rhs);
	friend QuotientNumber& operator/= <>(QuotientNumber& lhs, const QuotientNumber& rhs);
	friend QuotientNumber& operator/= <>(QuotientNumber& lhs, const Integer& rhs);
	friend std::istream& operator>> <>(std::istream& lhs, QuotientNumber& rhs);
};

template<class Integer> inline QuotientNumber<Integer> operator+(const QuotientNumber<Integer>& lhs, const QuotientNumber<Integer>& rhs){ return {lhs.a() * rhs.b() + rhs.a() * lhs.b(), lhs.b() * rhs.b()}; }
template<class Integer> inline QuotientNumber<Integer> operator+(const QuotientNumber<Integer>& lhs, const Integer& rhs){ return {lhs.a() + rhs * lhs.b(), lhs.b()}; }
template<class Integer> inline QuotientNumber<Integer> operator+(const Integer& lhs, const QuotientNumber<Integer>& rhs) { return {lhs * rhs.b() + rhs.a(), rhs.b()}; }
template<class Integer> inline QuotientNumber<Integer>& operator+=(QuotientNumber<Integer>& lhs, const QuotientNumber<Integer>& rhs) {
	lhs.a_ = lhs.a() * rhs.b() + rhs.a() * lhs.b();
	lhs.b_ = lhs.b() * rhs.b();
	tie(lhs.a_, lhs.b_) = reduce(lhs.a_, lhs.b_);
	return lhs;
}
template<class Integer> inline QuotientNumber<Integer>& operator+=(QuotientNumber<Integer>& lhs, const Integer& rhs){
	lhs.a_ = lhs.a() + rhs * lhs.b();
	tie(lhs.a_, lhs.b_) = reduce(lhs.a_, lhs.b_);
	return lhs;
}
template<class Integer> inline QuotientNumber<Integer> operator-(const QuotientNumber<Integer>& lhs, const QuotientNumber<Integer>& rhs) { return {lhs.a() * rhs.b() - rhs.a() * lhs.b(), lhs.b() * rhs.b()}; }
template<class Integer> inline QuotientNumber<Integer> operator-(const QuotientNumber<Integer>& lhs, const Integer& rhs) { return {lhs.a() - rhs * lhs.b(), lhs.b()}; }
template<class Integer> inline QuotientNumber<Integer> operator-(const Integer& lhs, const QuotientNumber<Integer>& rhs) { return {lhs * rhs.b() - rhs.a(), rhs.b()}; }
template<class Integer> inline QuotientNumber<Integer>& operator-=(QuotientNumber<Integer>& lhs, const QuotientNumber<Integer>& rhs) {
	lhs.a_ = lhs.a() * rhs.b() - rhs.a() * lhs.b();
	lhs.b_ = lhs.b() * rhs.b();
	tie(lhs.a_, lhs.b_) = reduce(lhs.a_, lhs.b_);
	return lhs;
}
template<class Integer> inline QuotientNumber<Integer>& operator-=(QuotientNumber<Integer>& lhs, const Integer& rhs) {
	lhs.a_ = lhs.a() - rhs * lhs.b();
	tie(lhs.a_, lhs.b_) = reduce(lhs.a_, lhs.b_);
	return lhs;
}
template<class Integer> inline QuotientNumber<Integer> operator*(const QuotientNumber<Integer>& lhs, const QuotientNumber<Integer>& rhs) { return {lhs.a() * rhs.a(), lhs.b() * rhs.b()}; }
template<class Integer> inline QuotientNumber<Integer> operator*(const QuotientNumber<Integer>& lhs, const Integer& rhs) { return {lhs.a() * rhs, lhs.b()}; }
template<class Integer> inline QuotientNumber<Integer> operator*(const Integer& lhs, const QuotientNumber<Integer>& rhs) { return {lhs * rhs.a(), rhs.b()}; }
template<class Integer> inline QuotientNumber<Integer>& operator*=(QuotientNumber<Integer>& lhs, const QuotientNumber<Integer>& rhs) {
	lhs.a_ = lhs.a() * rhs.a();
	lhs.b_ = lhs.b() * rhs.b();
	tie(lhs.a_, lhs.b_) = reduce(lhs.a_, lhs.b_);
	return lhs;
}
template<class Integer> inline QuotientNumber<Integer>& operator*=(QuotientNumber<Integer>& lhs, const Integer& rhs) {
	lhs.a_ = lhs.a() * rhs;
	tie(lhs.a_, lhs.b_) = reduce(lhs.a_, lhs.b_);
	return lhs;
}
template<class Integer> inline QuotientNumber<Integer> operator/(const QuotientNumber<Integer>& lhs, const QuotientNumber<Integer>& rhs) { return {lhs.a() * rhs.b(), lhs.b() * rhs.a()}; }
template<class Integer> inline QuotientNumber<Integer> operator/(const QuotientNumber<Integer>& lhs, const Integer& rhs) { return {lhs.a(), lhs.b() * rhs}; }
template<class Integer> inline QuotientNumber<Integer> operator/(const Integer& lhs, const QuotientNumber<Integer>& rhs) { return {lhs * rhs.b(), rhs.a()}; }
template<class Integer> inline QuotientNumber<Integer>& operator/=(QuotientNumber<Integer>& lhs, const QuotientNumber<Integer>& rhs) {
	lhs.a_ = lhs.a() * rhs.b();
	lhs.b_ = lhs.b() * rhs.a();
	tie(lhs.a_, lhs.b_) = reduce(lhs.a_, lhs.b_);
	return lhs;
}
template<class Integer> inline QuotientNumber<Integer>& operator/=(QuotientNumber<Integer>& lhs, const Integer& rhs) {
	lhs.b_ = lhs.b() * rhs;
	tie(lhs.a_, lhs.b_) = reduce(lhs.a_, lhs.b_);
	return lhs;
}
template<class Integer> inline bool operator==(const QuotientNumber<Integer>& lhs, const QuotientNumber<Integer>& rhs) { return lhs.a() * rhs.b() == rhs.a() * lhs.b(); }
template<class Integer> inline bool operator==(const QuotientNumber<Integer>& lhs, const Integer& rhs) { return lhs.a() == rhs * lhs.b(); }
template<class Integer> inline bool operator==(const Integer& lhs, const QuotientNumber<Integer>& rhs) { return lhs * rhs.b() == rhs.a(); }

template<class Integer>
std::ostream& operator<<(std::ostream& lhs, const QuotientNumber<Integer>& rhs)
{
	return lhs << rhs.a() << " / " << rhs.b();
}

template<class Integer>
std::istream& operator>>(std::istream& lhs, QuotientNumber<Integer>& rhs)
{
	lhs >> rhs.a_;
	rhs.b_ = 1;
	return lhs;
}

using rn = QuotientNumber<ll>;

#endif
