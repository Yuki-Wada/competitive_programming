#ifndef __POLYNOMIAL_HPP__
#define __POLYNOMIAL_HPP__ 0

// include
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

static const ll MOD = 998244353LL;

template <class Number, unsigned int mod>
class Polynomial
{
private:
	static map<Number, Number> mod_inv_cache;

public:
	vector<Number> coefs;

	Polynomial() : coefs(1U) {}
	Polynomial(unsigned int coef_num) : coefs(coef_num) {}
	Polynomial(vector<Number> coefs) : coefs(coefs) {}
	Number operator[](unsigned int n) const
	{
		return (n < coefs.size() ? coefs[n] : Number(0));
	}
	Number &operator[](unsigned int n)
	{
		if (n >= coefs.size())
			coefs.resize(n + 1U);

		return coefs[n];
	}
	unsigned int coef_num() const { return coefs.size(); }
	Number operator()(Number point) const
	{
		unsigned int N = coef_num();
		Number result = 0;
		Number point_power = 1;
		for (unsigned int i = 0; i < N; ++i)
		{
			result += coefs[i] * point_power;
			point_power *= point;

			result = mod_red(result);
			point_power = mod_red(point_power);
		}

		return result;
	}

	void resize(unsigned int n) { coefs.resize(n); }
	void mod_xn(unsigned int n) { coefs.resize(n); }
	void zero_trim()
	{
		unsigned int N = coef_num();
		unsigned int max_coef_idx = 1;
		for (unsigned int i = 0; i < N; ++i)
			if (coefs[N - i - 1U] != 0)
			{
				max_coef_idx = N - i;
				break;
			}

		coefs.resize(max_coef_idx);
	}

	static Number mod_red(Number v) { return (v % mod + mod) % mod; }
	static Number mod_inv(Number v)
	{
		if (mod_inv_cache.count(v) == 0)
		{
			struct BezoutsIdentitySolver
			{
				static pair<Number, Number> execute(Number a, Number b)
				{
					if (b == 0)
						return {1, 0};
					auto sol = execute(b, a % b);
					return {sol.second, sol.first - (a / b) * sol.second};
				}
			};
			auto sol = BezoutsIdentitySolver::execute(v, mod);
			if (v * sol.first + mod * sol.second != 1)
				return -1;

			mod_inv_cache[v] = mod_red(sol.first);
		}
		return mod_inv_cache[v];
	}
};

template <class Number, unsigned int mod>
map<Number, Number> Polynomial<Number, mod>::mod_inv_cache;

template <class Number, unsigned int mod>
Polynomial<Number, mod> operator+(const Polynomial<Number, mod> &lhs, const Polynomial<Number, mod> &rhs)
{
	unsigned int coef_num = max(lhs.coef_num(), rhs.coef_num());
	Polynomial<Number, mod> outputs(coef_num);
	for (unsigned int i = 0; i < coef_num; ++i)
	{
		outputs[i] = 0;
		if (i < lhs.coef_num())
			outputs[i] += lhs[i];
		if (i < rhs.coef_num())
			outputs[i] += rhs[i];
	}
	return outputs;
}

template <class Number, unsigned int mod>
Polynomial<Number, mod> operator+(const Polynomial<Number, mod> &lhs, Number rhs)
{
	unsigned int coef_num = lhs.coef_num();
	Polynomial<Number, mod> outputs(coef_num);
	outputs[0] = rhs;
	for (unsigned int i = 0; i < coef_num; ++i)
		outputs[i] += lhs[i];
	return {outputs};
}

template <class Number, unsigned int mod>
Polynomial<Number, mod> operator+(Number lhs, const Polynomial<Number, mod> &rhs)
{
	unsigned int coef_num = rhs.coef_num();
	Polynomial<Number, mod> outputs(coef_num);
	outputs[0] = lhs;
	for (unsigned int i = 0; i < coef_num; ++i)
		outputs[i] += rhs[i];
	return {outputs};
}

template <class Number, unsigned int mod>
Polynomial<Number, mod> operator-(const Polynomial<Number, mod> &lhs, const Polynomial<Number, mod> &rhs)
{
	unsigned int coef_num = max(lhs.coef_num(), rhs.coef_num());
	Polynomial<Number, mod> output(coef_num);
	for (unsigned int i = 0; i < coef_num; ++i)
	{
		output[i] = 0;
		if (i < lhs.coef_num())
			output[i] += lhs[i];
		if (i < rhs.coef_num())
			output[i] -= rhs[i];
	}
	return output;
}

template <class Number, unsigned int mod>
Polynomial<Number, mod> operator-(const Polynomial<Number, mod> &lhs, Number rhs)
{
	unsigned int coef_num = lhs.coef_num();
	Polynomial<Number, mod> outputs(coef_num);
	outputs[0] = -rhs;
	for (unsigned int i = 0; i < coef_num; ++i)
		outputs[i] += lhs[i];
	return {outputs};
}

template <class Number, unsigned int mod>
Polynomial<Number, mod> operator-(Number lhs, const Polynomial<Number, mod> &rhs)
{
	unsigned int coef_num = rhs.coef_num();
	Polynomial<Number, mod> outputs(coef_num);
	outputs[0] = lhs;
	for (unsigned int i = 0; i < coef_num; ++i)
		outputs[i] -= rhs[i];
	return {outputs};
}

template <class Number, unsigned int mod>
Polynomial<Number, mod> operator-(const Polynomial<Number, mod> &original)
{
	unsigned int coef_num = original.coef_num();
	Polynomial<Number, mod> outputs(coef_num);
	for (unsigned int i = 0; i < coef_num; ++i)
	{
		outputs[i] = 0;
		outputs[i] -= original[i];
	}
	return {outputs};
}

template <class Number, unsigned int mod>
Polynomial<Number, mod> operator*(const Polynomial<Number, mod> &lhs, const Polynomial<Number, mod> &rhs)
{
	// Polynomial<Number, mod> output(atcoder::convolution<MOD>(lhs.coefs, rhs.coefs));
	Polynomial<Number, mod> output(my_convolution(lhs.coefs, rhs.coefs));
	return output;
}

template <class Number, unsigned int mod>
Polynomial<Number, mod> derivative_f(const Polynomial<Number, mod> &f)
{
	unsigned int coef_num = f.coef_num();
	Polynomial<Number, mod> diff_f(max(1U, coef_num - 1U));
	for (unsigned int i = 1; i < coef_num; i++)
		diff_f[i - 1] = Polynomial<Number, mod>::mod_red(i * f[i]);
	return diff_f;
}

template <class Number, unsigned int mod>
Polynomial<Number, mod> integral_f(const Polynomial<Number, mod> &f)
{
	unsigned int coef_num = f.coef_num();
	Polynomial<Number, mod> integral_f(coef_num);
	for (unsigned int i = 0; i < coef_num; i++)
		integral_f[i + 1] = Polynomial<Number, mod>::mod_red(f[i] * Polynomial<Number, mod>::mod_inv(i + 1U));
	return integral_f;
}

template <class Number, unsigned int mod>
Polynomial<Number, mod> inv(const Polynomial<Number, mod> &f, unsigned int exponent)
{
	Polynomial<Number, mod> gn(1U), truncated_f(1U);
	gn[0] = 1LL / Polynomial<Number, mod>::mod_inv(f[0]);
	truncated_f[0] = f[0];

	for (unsigned int e = 0; e < exponent; e++)
	{
		auto curr_pow = 1LL << e;
		auto next_pow = 1LL << (e + 1U);

		for (unsigned int i = curr_pow; i < next_pow; ++i)
			if (f[i] != 0)
				truncated_f[i] = Polynomial<Number, mod>::mod_red(f[i]);
		auto gg = gn * gn;
		gg.mod_xn(next_pow);
		auto ggf = gg * truncated_f;

		for (unsigned int i = 0; i < next_pow; ++i)
			gn[i] = Polynomial<Number, mod>::mod_red(gn[i] * 2LL - ggf[i]);
	}
	return gn;
}

template <class Number, unsigned int mod>
Polynomial<Number, mod> log(const Polynomial<Number, mod> &f, unsigned int exponent)
{
	auto pow = 1LL << exponent;
	auto inv_f = inv(f, exponent);
	auto diff_f = derivative_f(f);
	auto integrand = inv_f * diff_f;
	integrand.mod_xn(pow);
	auto int_f = integral_f(integrand);
	return int_f;
}

template <class Number, unsigned int mod>
Polynomial<Number, mod> operator/(const Polynomial<Number, mod> &lhs, const Polynomial<Number, mod> &rhs)
{
	auto reverse_polynomial = [](const Polynomial<Number, mod> &poly)
	{
		unsigned int LN = poly.coef_num();
		vector<Number> poly_rev_coefs;
		poly_rev_coefs.reserve(LN);
		for (unsigned int i = 0; i < LN; ++i)
		{
			auto poly_coef = poly[LN - i - 1U];
			poly_rev_coefs.emplace_back(poly_coef);
		}
		return Polynomial<Number, mod>(poly_rev_coefs);
	};
	auto trim_and_reverse_polynomial = [](const Polynomial<Number, mod> &poly)
	{
		unsigned int LN = poly.coef_num();
		vector<Number> poly_rev_coefs;
		for (unsigned int i = 0; i < LN; ++i)
		{
			auto poly_coef = poly[LN - i - 1U];
			if (poly_rev_coefs.size() == 0)
			{
				if (poly_coef != 0)
					poly_rev_coefs.reserve(LN - i);
				else
					continue;
			}
			poly_rev_coefs.emplace_back(poly_coef);
		}
		return Polynomial<Number, mod>(poly_rev_coefs);
	};

	auto lhs_rev = trim_and_reverse_polynomial(lhs);
	auto rhs_rev = trim_and_reverse_polynomial(rhs);

	auto lhs_rev_coef_num = lhs_rev.coef_num();
	auto rhs_rev_coef_num = rhs_rev.coef_num();
	if (lhs_rev_coef_num < rhs_rev_coef_num)
		return {0};

	auto diff_coef_num = lhs_rev_coef_num - rhs_rev_coef_num + 1U;
	ll exponent = 0;
	ull n = diff_coef_num;
	while (n != 0)
	{
		exponent++;
		n >>= 1LL;
	}

	auto rev_q = Polynomial<Number, mod>(lhs_rev) * inv(Polynomial<Number, mod>(rhs_rev), exponent);
	rev_q.mod_xn(diff_coef_num);
	auto q = reverse_polynomial(rev_q);

	return q;
}

template <class Number, unsigned int mod>
Polynomial<Number, mod> operator%(const Polynomial<Number, mod> &lhs, const Polynomial<Number, mod> &rhs)
{
	auto q = lhs / rhs;
	auto r = lhs - rhs * q;
	auto r_coef_num = r.coef_num();
	if (rhs.coef_num() >= 2U)
		r_coef_num = min(r_coef_num, rhs.coef_num() - 1U);
	r.mod_xn(r_coef_num);
	return r;
}

template <class Number, unsigned int mod>
Polynomial<Number, mod> exp(const Polynomial<Number, mod> &f, unsigned int exponent)
{
	Polynomial<Number, mod> gn(1U), truncated_f(1U);
	gn[0] = 1LL;
	truncated_f[0] = f[0];

	for (unsigned int e = 0; e < exponent; e++)
	{
		auto curr_pow = 1LL << e;
		auto next_pow = 1LL << (e + 1U);
		for (unsigned int i = curr_pow; i < next_pow; ++i)
			if (f[i] != 0)
				truncated_f[i] = f[i];

		auto gf = gn * truncated_f;
		auto log_g = log(gn, e + 1U);
		log_g.mod_xn(next_pow);
		auto g_log_g = gn * log_g;

		for (unsigned int i = 0; i < next_pow; ++i)
			gn[i] = Polynomial<Number, mod>::mod_red(gf[i] + gn[i] - g_log_g[i]);
	}
	return gn;
}

template <class Number, unsigned int mod>
vector<ll> evaluate_multiple_points(const Polynomial<Number, mod> &f, const vector<ll> &points)
{
	if (points.size() == 0ULL)
		return {};

	struct NodeInfo
	{
		ll left_idx;
		ll right_idx;
		ll size;
		Polynomial<Number, mod> polynomial;
		NodeInfo(
			ll left_idx,
			ll right_idx,
			ll size,
			Polynomial<Number, mod> polynomial) : left_idx(left_idx), right_idx(right_idx), size(size), polynomial(polynomial) {}
	};

	Polynomial<Number, mod> prod(1);
	prod[0] = 1;

	vector<NodeInfo> node_infos;
	queue<ll> node_queue;
	ll node_idx = 0;
	for (unsigned int i = 0; i < points.size(); ++i)
	{
		node_infos.emplace_back(-1LL, -1LL, 1LL, Polynomial<Number, mod>({-points[i], 1}));
		node_queue.emplace(node_idx);
		++node_idx;
	}
	while (true)
	{
		if (node_queue.empty())
			break;
		auto i1 = node_queue.front();
		node_queue.pop();
		if (node_queue.empty())
			break;
		auto i2 = node_queue.front();
		node_queue.pop();

		auto size1 = node_infos[i1].size;
		auto size2 = node_infos[i2].size;
		auto poly1 = node_infos[i1].polynomial;
		auto poly2 = node_infos[i2].polynomial;

		node_infos.emplace_back(i1, i2, size1 + size2, poly1 * poly2);
		node_queue.emplace(node_idx);
		++node_idx;
	}

	vector<Polynomial<Number, mod>> residues(node_idx);
	--node_idx;
	auto compute_residual = [&](const Polynomial<Number, mod> &parent_poly, ll idx)
	{
		auto child_poly = node_infos[idx].polynomial;
		residues[idx] = parent_poly % child_poly;
		node_queue.emplace(idx);
	};

	compute_residual(f, node_idx);
	while (!node_queue.empty())
	{
		auto parent_idx = node_queue.front();
		node_queue.pop();
		auto parent_node_info = node_infos[parent_idx];
		auto parent_poly = residues[parent_idx];

		auto left_idx = parent_node_info.left_idx;
		if (left_idx != -1LL)
			compute_residual(parent_poly, left_idx);

		auto right_idx = parent_node_info.right_idx;
		if (right_idx != -1LL)
			compute_residual(parent_poly, right_idx);
	}

	vector<ll> results(points.size());
	for (unsigned int i = 0; i < points.size(); ++i)
		results[i] = Polynomial<Number, mod>::mod_red(residues[i][0]);

	return results;
}

#endif
