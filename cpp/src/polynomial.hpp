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

constexpr ll MOD_PRIMITIVE_ROOT = 3LL;
constexpr ll MOD_INVERSE_PRIMITIVE_ROOT = 332748118LL;

using rll = atcoder::modint998244353;

inline ull get_power2_more_than_input(ull input)
{
	// val is 0.
	if (input == 0ULL)
		return 1ULL;
	// val is power of 2
	if (!(input & (input - 1)))
		return input;

	ull highest_one_bit = input;
	while ((highest_one_bit & (highest_one_bit - 1LL)) != 0)
		highest_one_bit = highest_one_bit & (highest_one_bit - 1LL);
	ull power2 = highest_one_bit << 1LL;
	return power2;
}

inline ull get_value_more_than_log_2_input(ull input)
{
	auto get_power2 = [](ull input)
	{
		// val is 0.
		if (input == 0ULL)
			return 1ULL;
		// val is power of 2
		if (!(input & (input - 1)))
			return input;

		ull highest_one_bit = input;
		while ((highest_one_bit & (highest_one_bit - 1LL)) != 0)
			highest_one_bit = highest_one_bit & (highest_one_bit - 1LL);
		ull power2 = highest_one_bit << 1LL;
		return power2;
	};

	auto power2 = get_power2(input);
	ull value = 0ULL;
	while (power2 > 1ULL)
	{
		power2 >>= 1LL;
		++value;
	}
	return value;
}

// Fast Modulo Transform
vector<rll> fmt_impl(const vector<rll> &function, const rll primitive_root)
{
	ll degree = function.size();
	if (degree == 0LL)
		throw runtime_error("配列の要素数は 1 以上である必要があります。");
	if ((degree & (degree - 1LL)) != 0LL)
		throw runtime_error("配列の要素数は 2 のべき乗である必要があります。");

	auto get_power2 = [&](rll base, ull exponential)
	{
		rll result = 1;
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
	};
	rll xi = get_power2(rll(primitive_root), (MOD - 1LL) / degree);

	vector<rll> transformed(degree, 0);
	vector<rll> stored(degree, 0);

	for (ll i = 0; i < degree; ++i)
		transformed[i] = function[i];
	if (degree == 1LL)
	{
		return transformed;
	}

	ll log_2_deg = 0LL;
	for (ll i = 1; i < degree; i <<= 1LL)
		++log_2_deg;

	vector<rll> mod_xi_2s(log_2_deg);
	vector<ll> power_2s(log_2_deg);
	mod_xi_2s[0] = xi, power_2s[0] = 1LL;
	for (ll i = 1; i < log_2_deg; ++i)
		mod_xi_2s[i] = mod_xi_2s[i - 1LL] * mod_xi_2s[i - 1LL], power_2s[i] = 1LL << i;

	for (ll e = 0; e < log_2_deg; ++e)
	{
		auto mod_xi = mod_xi_2s[log_2_deg - e - 1LL];
		auto skip = power_2s[log_2_deg - e - 1LL];
		for (ll i = 0; i < degree; ++i)
			stored[i] = transformed[i];

		rll power_of_xi = 1;
		for (ll i = 0; i < (degree / skip); ++i)
		{
			for (ll start = 0; start < skip; ++start)
			{
				auto idx = start + skip * i;
				auto res_i = i % (degree / skip / 2LL);

				auto stored_idx = start + skip * res_i * 2LL;
				transformed[idx] = stored[stored_idx] + stored[stored_idx + skip] * power_of_xi;
			}
			power_of_xi = power_of_xi * mod_xi;
		}
	}
	return transformed;
}

vector<rll> fmt(const vector<rll> &function)
{
	vector<rll> transformed = fmt_impl(function, MOD_PRIMITIVE_ROOT);
	return transformed;
}

vector<rll> inv_fmt(const vector<rll> &function)
{
	vector<rll> transformed = fmt_impl(function, MOD_INVERSE_PRIMITIVE_ROOT);
	auto inverse_n = rll(1) / rll(function.size());
	for (unsigned int i = 0; i < function.size(); ++i)
		transformed[i] = transformed[i] * inverse_n;

	return transformed;
}

vector<rll> fmt_convolution(const vector<rll> &a, const vector<rll> &b)
{
	unsigned int coef_num = a.size() + b.size() - 1U;
	unsigned int fmt_size = get_power2_more_than_input(coef_num);

	vector<rll> rll_a(fmt_size);
	vector<rll> rll_b(fmt_size);
	for (unsigned int i = 0; i < a.size(); ++i)
		rll_a[i] = a[i];
	for (unsigned int i = 0; i < b.size(); ++i)
		rll_b[i] = b[i];

	auto fmt_a = fmt(rll_a);
	auto fmt_b = fmt(rll_b);
	vector<rll> fmt_ab(fmt_size);
	for (unsigned int i = 0; i < fmt_size; ++i)
		fmt_ab[i] = fmt_a[i] * fmt_b[i];

	auto rll_ab = inv_fmt(fmt_ab);

	return rll_ab;
}

vector<rll> my_convolution(const vector<rll> &a, const vector<rll> &b)
{
	return fmt_convolution(a, b);
}

template <class Number>
class Polynomial
{
private:
public:
	vector<Number> coefs;

	Polynomial() : coefs(1U) {}
	Polynomial(Number constant) : coefs(1U, constant) {}
	Polynomial(vector<Number> coefs) : coefs(coefs) {}

	static Polynomial zero_polynomial(unsigned int coef_num)
	{
		vector<Number> coefs(coef_num);
		return Polynomial(coefs);
	}

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
			result = result + coefs[i] * point_power;
			point_power = point_power * point;

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
};

template <class Number>
Polynomial<Number> operator+(const Polynomial<Number> &lhs, const Polynomial<Number> &rhs)
{
	unsigned int coef_num = max(lhs.coef_num(), rhs.coef_num());
	auto outputs = Polynomial<Number>::zero_polynomial(coef_num);
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

template <class Number>
Polynomial<Number> operator+(const Polynomial<Number> &lhs, Number rhs)
{
	unsigned int coef_num = lhs.coef_num();
	auto outputs = Polynomial<Number>::zero_polynomial(coef_num);
	outputs[0] = rhs;
	for (unsigned int i = 0; i < coef_num; ++i)
		outputs[i] = outputs[i] + lhs[i];
	return {outputs};
}

template <class Number>
Polynomial<Number> operator+(Number lhs, const Polynomial<Number> &rhs)
{
	unsigned int coef_num = rhs.coef_num();
	auto outputs = Polynomial<Number>::zero_polynomial(coef_num);
	outputs[0] = lhs;
	for (unsigned int i = 0; i < coef_num; ++i)
		outputs[i] = outputs[i] + rhs[i];
	return {outputs};
}

template <class Number>
Polynomial<Number> operator-(const Polynomial<Number> &lhs, const Polynomial<Number> &rhs)
{
	unsigned int coef_num = max(lhs.coef_num(), rhs.coef_num());
	auto output = Polynomial<Number>::zero_polynomial(coef_num);
	for (unsigned int i = 0; i < coef_num; ++i)
	{
		output[i] = 0;
		if (i < lhs.coef_num())
			output[i] = output[i] + lhs[i];
		if (i < rhs.coef_num())
			output[i] = output[i] - rhs[i];
	}
	return output;
}

template <class Number>
Polynomial<Number> operator-(const Polynomial<Number> &lhs, Number rhs)
{
	unsigned int coef_num = lhs.coef_num();
	auto outputs = Polynomial<Number>::zero_polynomial(coef_num);
	outputs[0] = -rhs;
	for (unsigned int i = 0; i < coef_num; ++i)
		outputs[i] += lhs[i];
	return {outputs};
}

template <class Number>
Polynomial<Number> operator-(Number lhs, const Polynomial<Number> &rhs)
{
	unsigned int coef_num = rhs.coef_num();
	auto outputs = Polynomial<Number>::zero_polynomial(coef_num);
	outputs[0] = lhs;
	for (unsigned int i = 0; i < coef_num; ++i)
		outputs[i] -= rhs[i];
	return {outputs};
}

template <class Number>
Polynomial<Number> operator-(const Polynomial<Number> &original)
{
	unsigned int coef_num = original.coef_num();
	auto outputs = Polynomial<Number>::zero_polynomial(coef_num);
	for (unsigned int i = 0; i < coef_num; ++i)
	{
		outputs[i] = 0;
		outputs[i] -= original[i];
	}
	return {outputs};
}

template <class Number>
Polynomial<Number> operator*(const Polynomial<Number> &lhs, const Polynomial<Number> &rhs)
{
	// Polynomial<Number> output(atcoder::convolution<MOD>(lhs.coefs, rhs.coefs));
	Polynomial<Number> output(my_convolution(lhs.coefs, rhs.coefs));
	return output;
}

template <class Number>
Polynomial<Number> derivative_f(const Polynomial<Number> &f)
{
	unsigned int coef_num = f.coef_num();
	auto diff_f = Polynomial<Number>::zero_polynomial(max(1U, coef_num - 1U));
	for (unsigned int i = 1; i < coef_num; i++)
		diff_f[i - 1] = f[i] * Number(i);
	return diff_f;
}

template <class Number>
Polynomial<Number> integral_f(const Polynomial<Number> &f)
{
	unsigned int coef_num = f.coef_num();
	auto integral_f = Polynomial<Number>::zero_polynomial(coef_num);
	for (unsigned int i = 0; i < coef_num; i++)
		integral_f[i + 1] = f[i] * Number(i + 1U);
	return integral_f;
}

template <class Number>
Polynomial<Number> inv(const Polynomial<Number> &f, unsigned int exponent)
{
	Polynomial<Number> gn(Number(1) / f[0]), truncated_f(f[0]);

	for (unsigned int e = 0; e < exponent; e++)
	{
		auto curr_pow = 1LL << e;
		auto next_pow = 1LL << (e + 1U);

		for (unsigned int i = curr_pow; i < next_pow; ++i)
			if (f[i] != 0)
				truncated_f[i] = f[i];
		auto gg = gn * gn;
		gg.mod_xn(next_pow);
		auto ggf = gg * truncated_f;

		for (unsigned int i = 0; i < next_pow; ++i)
			gn[i] = gn[i] * 2LL - ggf[i];
	}
	return gn;
}

template <class Number>
Polynomial<Number> log(const Polynomial<Number> &f, unsigned int exponent)
{
	auto pow = 1LL << exponent;
	auto inv_f = inv(f, exponent);
	auto diff_f = derivative_f(f);
	auto integrand = inv_f * diff_f;
	integrand.mod_xn(pow);
	auto int_f = integral_f(integrand);
	return int_f;
}

template <class Number>
Polynomial<Number> operator/(const Polynomial<Number> &lhs, const Polynomial<Number> &rhs)
{
	auto reverse_polynomial = [](const Polynomial<Number> &poly)
	{
		unsigned int LN = poly.coef_num();
		vector<Number> poly_rev_coefs;
		poly_rev_coefs.reserve(LN);
		for (unsigned int i = 0; i < LN; ++i)
		{
			auto poly_coef = poly[LN - i - 1U];
			poly_rev_coefs.emplace_back(poly_coef);
		}
		return Polynomial<Number>(poly_rev_coefs);
	};
	auto trim_and_reverse_polynomial = [](const Polynomial<Number> &poly)
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
		return Polynomial<Number>(poly_rev_coefs);
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

	auto rev_q = Polynomial<Number>(lhs_rev) * inv(Polynomial<Number>(rhs_rev), exponent);
	rev_q.mod_xn(diff_coef_num);
	auto q = reverse_polynomial(rev_q);

	return q;
}

template <class Number>
Polynomial<Number> operator%(const Polynomial<Number> &lhs, const Polynomial<Number> &rhs)
{
	auto q = lhs / rhs;
	auto r = lhs - rhs * q;
	auto r_coef_num = r.coef_num();
	if (rhs.coef_num() >= 2U)
		r_coef_num = min(r_coef_num, rhs.coef_num() - 1U);
	r.mod_xn(r_coef_num);
	return r;
}

template <class Number>
Polynomial<Number> exp(const Polynomial<Number> &f, unsigned int exponent)
{
	Polynomial<Number> gn(1), truncated_f(f[0]);
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
			gn[i] = Polynomial<Number>::mod_red(gf[i] + gn[i] - g_log_g[i]);
	}
	return gn;
}

template <class Number>
vector<Number> evaluate_multiple_points(const Polynomial<Number> &f, const vector<Number> &points)
{
	if (points.size() == 0ULL)
		return {};

	struct NodeInfo
	{
		ll left_idx;
		ll right_idx;
		ll size;
		Polynomial<Number> polynomial;
		NodeInfo(
			ll left_idx,
			ll right_idx,
			ll size,
			Polynomial<Number> polynomial) : left_idx(left_idx), right_idx(right_idx), size(size), polynomial(polynomial) {}
	};

	vector<NodeInfo> node_infos;
	queue<ll> node_queue;
	ll node_idx = 0;
	for (unsigned int i = 0; i < points.size(); ++i)
	{
		node_infos.emplace_back(-1LL, -1LL, 1LL, Polynomial<Number>({points[i] * Number(-1), 1}));
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

	vector<Polynomial<Number>> residues(node_idx);
	--node_idx;
	auto compute_residual = [&](const Polynomial<Number> &parent_poly, ll idx)
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

	vector<Number> results(points.size());
	for (unsigned int i = 0; i < points.size(); ++i)
		results[i] = residues[i][0];

	return results;
}

template <class Number>
vector<Number> chirp_z_transform(const Polynomial<Number> &f, Number w, ll r)
{
	auto ys_size = f.coef_num();
	auto vs_size = ys_size + r;

	vector<Number> wis(vs_size);
	Number wi = 1;
	for (unsigned int i = 0; i < vs_size; ++i)
	{
		wis[i] = wi;
		wi = wi * w;
	}

	vector<Number> wtis(vs_size);
	Number wti = 1;
	for (unsigned int i = 0; i < vs_size; ++i)
	{
		wtis[i] = wti;
		wti = wti * wis[i];
	}

	vector<Number> ys(ys_size), vs(vs_size);
	for (unsigned int i = 0; i < ys_size; ++i)
		ys[i] = f[i] / wtis[i];
	reverse(ys.begin(), ys.end());

	for (unsigned int i = 0; i < vs_size; ++i)
		vs[i] = wtis[i];

	auto convs = my_convolution(ys, vs);
	vector<rll> outputs(r);
	for (unsigned int i = 0; i < r; ++i)
		outputs[i] = convs[ys_size - 1LL + i] / wtis[i];

	return outputs;
}

template <class Number>
Polynomial<Number> prod(const vector<Polynomial<Number>> &polys)
{
	struct NodeInfo
	{
		ll left_idx;
		ll right_idx;
		ll size;
		Polynomial<Number> polynomial;
		NodeInfo(
			ll left_idx,
			ll right_idx,
			ll size,
			Polynomial<Number> polynomial) : left_idx(left_idx), right_idx(right_idx), size(size), polynomial(polynomial) {}
	};

	vector<NodeInfo> node_infos;
	queue<ll> node_queue;
	ll node_idx = 0;
	for (unsigned int i = 0; i < polys.size(); ++i)
	{
		node_infos.emplace_back(-1LL, -1LL, 1LL, polys[i]);
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

	vector<Polynomial<Number>> residues(node_idx);
	--node_idx;

	return node_infos[node_idx].polynomial;
}

#endif
