#ifndef __POLYNOMIAL_HPP__
#define __POLYNOMIAL_HPP__ 0

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

template<class Coefficient> class Polynomial;
template<class Coefficient> Polynomial<Coefficient>& operator+=(Polynomial<Coefficient>& lhs, const Polynomial<Coefficient>& rhs);
template<class Coefficient> Polynomial<Coefficient>& operator-=(Polynomial<Coefficient>& lhs, const Polynomial<Coefficient>& rhs);
template<class Coefficient> Polynomial<Coefficient>& operator*=(Polynomial<Coefficient>& lhs, const Polynomial<Coefficient>& rhs);
template<class Coefficient> Polynomial<Coefficient>& operator/=(Polynomial<Coefficient>& lhs, const Polynomial<Coefficient>& rhs);
template<class Coefficient> Polynomial<Coefficient>& operator%=(Polynomial<Coefficient>& lhs, const Polynomial<Coefficient>& rhs);

template<class Coefficient>
class Polynomial
{
private:
	vector<Coefficient> coefs_;
public:
	Polynomial() : coefs_(1) {}
	Polynomial(Coefficient v) : coefs_(1, v) { coefs_[0] = v; }
	Polynomial(Coefficient v, ull degree) : coefs_(degree + 1) { coefs_[0] = v; }

	string indeterminate_representation = "√-1";

	ll get_degree() const
	{
		for (ll i = coefs_.size() - 1; i >= 0; --i) {
			if (!(coefs_[i] == Coefficient(0))) return i;
		}
		return -1;
	}

	Coefficient& operator()(ull degree)
	{
		return coefs_[degree];
	}

	const Coefficient& operator()(ull degree) const
	{
		return coefs_[degree];
	}

	friend Polynomial& operator+= <>(Polynomial& lhs, const Polynomial& rhs);
	friend Polynomial& operator-= <>(Polynomial& lhs, const Polynomial& rhs);
	friend Polynomial& operator*= <>(Polynomial& lhs, const Polynomial& rhs);
	friend Polynomial& operator/= <>(Polynomial& lhs, const Polynomial& rhs);
	friend Polynomial& operator%= <>(Polynomial& lhs, const Polynomial& rhs);
};

template<class Coefficient> inline Polynomial<Coefficient> operator+(const Polynomial<Coefficient>& lhs, const Polynomial<Coefficient>& rhs){
	ll lhs_degree = lhs.get_degree(), rhs_degree = rhs.get_degree();
	ll degree = max(lhs_degree, rhs_degree);
	if (degree < 0) return Polynomial<Coefficient>();
	Polynomial<Coefficient> poly(0, degree);
	for (ll i = 0; i <= lhs_degree; ++i) poly(i) += lhs(i);
	for (ll i = 0; i <= rhs_degree; ++i) poly(i) += rhs(i);
	return poly;
}
template<class Coefficient> inline Polynomial<Coefficient>& operator+=(Polynomial<Coefficient>& lhs, const Polynomial<Coefficient>& rhs) {
	ll lhs_degree = lhs.get_degree(), rhs_degree = rhs.get_degree();
	ll degree = max(lhs_degree, rhs_degree);
	if (degree < 0) return lhs;
	lhs.coefs_.reserve(degree);
	for (ll i = 0; i <= rhs_degree; ++i) {
		if (i <= lhs_degree) lhs(i) += rhs(i);
		else lhs.coefs_.emplace_back(rhs(i));
	}
	return lhs;
}
template<class Coefficient> inline Polynomial<Coefficient> operator-(const Polynomial<Coefficient>& lhs, const Polynomial<Coefficient>& rhs) {
	ll lhs_degree = lhs.get_degree(), rhs_degree = rhs.get_degree();
	ll degree = max(lhs_degree, rhs_degree);
	if (degree < 0) return Polynomial<Coefficient>();
	Polynomial<Coefficient> poly(0, degree);
	for (ll i = 0; i <= lhs_degree; ++i) poly(i) += lhs(i);
	for (ll i = 0; i <= rhs_degree; ++i) poly(i) -= rhs(i);
	return poly;
}
template<class Coefficient> inline Polynomial<Coefficient>& operator-=(Polynomial<Coefficient>& lhs, const Polynomial<Coefficient>& rhs) {
	ll lhs_degree = lhs.get_degree(), rhs_degree = rhs.get_degree();
	ll degree = max(lhs_degree, rhs_degree);
	if (degree < 0) return lhs;
	lhs.coefs_.reserve(degree);
	for (ll i = 0; i <= rhs_degree; ++i) {
		if (i <= lhs_degree) lhs(i) -= rhs(i);
		else {
			lhs.coefs_.emplace_back();
			lhs.coefs_.back() -= rhs(i);
		}
	}
	return lhs;
}
template<class Coefficient> inline Polynomial<Coefficient> operator*(const Polynomial<Coefficient>& lhs, const Polynomial<Coefficient>& rhs) {
	ll lhs_degree = lhs.get_degree(), rhs_degree = rhs.get_degree();
	if (lhs_degree < 0 || rhs_degree < 0) return Polynomial<Coefficient>();
	Polynomial<Coefficient> poly(0, lhs_degree + rhs_degree);
	for (ll i = 0; i <= lhs_degree; ++i) for (ll j = 0; j <= rhs_degree; ++j) {
		poly(i + j) += lhs(i) * rhs(j);
	}
	return poly;
}
template<class Coefficient> inline Polynomial<Coefficient>& operator*=(Polynomial<Coefficient>& lhs, const Polynomial<Coefficient>& rhs) {
	ll lhs_degree = lhs.get_degree(), rhs_degree = rhs.get_degree();
	auto out = lhs * rhs;

	ll degree = out.get_degree();
	lhs.coefs_.resize(degree + 1);
	for (ll i = 0; i <= degree; ++i) lhs(i) += out(i);
	return lhs;
}
template<class Coefficient> inline Polynomial<Coefficient> operator/(const Polynomial<Coefficient>& lhs, const Polynomial<Coefficient>& rhs) {
	ll lhs_degree = lhs.get_degree(), rhs_degree = rhs.get_degree();
	if (rhs_degree < 0) throw runtime_error("The degree of rhs should be greater than 0!");
	if (lhs_degree < rhs_degree) return Coefficient(0);

	Polynomial<Coefficient> lhs_copy(lhs);	
	Polynomial<Coefficient> poly(0, lhs_degree - rhs_degree);
	for (ll i = lhs_degree - rhs_degree; i >= 0; --i) {
		auto q = lhs_copy(i + rhs_degree) / rhs(rhs_degree);
		poly(i) = q;
		for (ll j = 0; j <= rhs_degree; ++j) {
			lhs_copy(i + j) -= q * rhs(j);
		}
	}
	return poly;
}
template<class Coefficient> inline Polynomial<Coefficient> operator/(const Coefficient& lhs, const Polynomial<Coefficient>& rhs) {
	ll lhs_degree = (lhs == 0 ? -1: 0), rhs_degree = rhs.get_degree();
	if (rhs_degree < 0) throw runtime_error("The degree of rhs should be greater than 0!");
	if (lhs_degree < rhs_degree) return 0;

	Polynomial<Coefficient> lhs_copy(lhs);	
	Polynomial<Coefficient> poly(lhs_degree - rhs_degree);
	for (ll i = lhs_degree - rhs_degree; i >= 0; --i) {
		auto q = lhs_copy(i + rhs_degree) / rhs(rhs_degree);
		poly(i) = q;
		for (ll j = 0; j <= rhs_degree; ++j) {
			lhs_copy(i + j) -= q * rhs(j);
		}
	}
	return poly;
}
template<class Coefficient> inline Polynomial<Coefficient>& operator/=(Polynomial<Coefficient>& lhs, const Polynomial<Coefficient>& rhs) {
	ll lhs_degree = lhs.get_degree(), rhs_degree = rhs.get_degree();
	auto out = lhs / rhs;

	ll degree = out.get_degree();
	lhs.coefs_.resize(degree + 1);
	for (ll i = 0; i <= degree; ++i) lhs(i) = out(i);
	return lhs;
}
template<class Coefficient> inline Polynomial<Coefficient> operator%(const Polynomial<Coefficient>& lhs, const Polynomial<Coefficient>& rhs) {
	ll lhs_degree = lhs.get_degree(), rhs_degree = rhs.get_degree();
	if (rhs_degree < 0) throw runtime_error("The degree of rhs should be greater than 0!");
	if (lhs_degree < rhs_degree) return lhs;

	Polynomial<Coefficient> lhs_copy(lhs);
	for (ll i = lhs_degree - rhs_degree; i >= 0; --i) {
		auto q = lhs_copy(i + rhs_degree) / rhs(rhs_degree);
		for (ll j = 0; j <= rhs_degree; ++j) {
			lhs_copy(i + j) -= q * rhs(j);
		}
	}
	return lhs_copy;
}
template<class Coefficient> inline Polynomial<Coefficient>& operator%=(Polynomial<Coefficient>& lhs, const Polynomial<Coefficient>& rhs) {
	ll lhs_degree = lhs.get_degree(), rhs_degree = rhs.get_degree();
	if (rhs_degree < 0) throw runtime_error("The degree of rhs should be greater than 0!");
	if (lhs_degree < rhs_degree) return lhs;

	for (ll i = lhs_degree - rhs_degree; i >= 0; --i) {
		auto q = lhs(i + rhs_degree) / rhs(rhs_degree);
		for (ll j = 0; j <= rhs_degree; ++j) {
			lhs(i + j) -= q * rhs(j);
		}
	}
	return lhs;
}
template<class Coefficient> inline bool operator==(const Polynomial<Coefficient>& lhs, const Polynomial<Coefficient>& rhs) {
	ll lhs_degree = lhs.get_degree(), rhs_degree = rhs.get_degree();
	if (lhs_degree != rhs_degree) return false;
	for (ll i = 0; i <= lhs_degree; ++i) if (!(lhs(i) == rhs(i))) return false;
	return true;
}
template<class Coefficient> inline bool operator==(const Polynomial<Coefficient>& lhs, const Coefficient& rhs) {
	ll lhs_degree = lhs.get_degree();
	if (lhs_degree > 0) return false;
	return lhs(0) == rhs;
}
template<class Coefficient> inline bool operator==(const Coefficient& lhs, const Polynomial<Coefficient>& rhs) {
	ll rhs_degree = rhs.get_degree();
	if (rhs_degree > 0) return false;
	return lhs == rhs(0);
}

template<class Coefficient>
std::ostream& operator<<(std::ostream& lhs, const Polynomial<Coefficient>& rhs)
{
	ll degree = rhs.get_degree();
	if (degree < 0) return lhs << Coefficient(0);
	for (ull i = 0; i <= degree; ++i) {
		if (rhs(i) == Coefficient(0)) continue;
		lhs << "(" << rhs(i);
		if (i > 0) lhs << " " << rhs.indeterminate_representation << "^" << i;
		lhs << ")";
		if (i < degree) lhs << " + ";
	}
	return lhs;
}

#endif
