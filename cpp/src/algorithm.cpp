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

static const double PI = 3.14;

inline ll floor(ll a, ull b)
{
	ll llb = b;
	if (a >= 0)
	{
		return a / llb;
	}
	else
	{
		return -((-a + llb - 1) / llb);
	}
}

inline ll ceil(ll a, ull b)
{
	ll llb = b;
	if (a >= 0)
	{
		return (a + llb - 1) / llb;
	}
	else
	{
		return -(-a / llb);
	}
}

inline ll get_lowest_one_bit(ll a)
{
	return a & (-a);
}

inline ll get_highest_one_bit(ll a)
{
	while ((a & (a - 1)) != 0)
	{
		a = a & (a - 1);
	}
	return a;
}

inline bool is_power2(ull a)
{
	if (a == 0)
	{
		return false;
	}
	return !(a & (a - 1));
}

inline ull get_specified_bit(ull a, ull bit)
{
	return (a >> bit) & 1LL;
}

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

vector<vector<ll>> enumerate_combination(ll n, ll k) {
	if (n == 0) return {};
	if (k == 0) return {};
	if (n < k) return {};

	vector<vector<ll>> res;
	if (k == 1) {
		for (ll i = 0; i < n; ++i) {
			res.emplace_back(vector<ll>(1, i));
		}
		return res;
	}
	if (n == k) {
		vector<ll> v(n);
		for (ll i = 0; i < n; ++i) {
			v[i] = i;
		}
		res.emplace_back(v);
		return res;
	}
	res = enumerate_combination(n - 1, k);
	vector<vector<ll>> pre = enumerate_combination(n - 1, k - 1);
	res.reserve(res.size() + pre.size());
	for (ll i = 0; i < pre.size(); ++i) {
		pre[i].emplace_back(n - 1);
	}
	copy(pre.begin(), pre.end(), std::back_inserter(res));

	return res;
}

ll get_lis_length(const vector<ll>& seq, bool strictly = true, bool ascending = true)
{

	vector<ll> min_last_seq_elem;
	using iter_type = decltype(min_last_seq_elem.begin());
	auto get_iter = [&strictly, &ascending](iter_type begin, iter_type end, ll elem)
	{
		if (strictly)
		{
			if (ascending)
				return lower_bound(begin, end, elem, less<ll>());
			else
				return lower_bound(begin, end, elem, greater<ll>());
		}
		else
		{
			if (ascending)
				return upper_bound(begin, end, elem, less<ll>());
			else
				return upper_bound(begin, end, elem, greater<ll>());
		}
	};

	for (const auto& elem : seq)
	{
		auto iter = get_iter(min_last_seq_elem.begin(), min_last_seq_elem.end(), elem);
		if (iter == min_last_seq_elem.end())
			min_last_seq_elem.emplace_back(elem);
		else
			*iter = elem;
	}

	return min_last_seq_elem.size();
}

vector<ll> get_lis(const vector<ll>& seq, bool strictly = true, bool ascending = true)
{
	vector<ll> min_last_seq_elem;
	using iter_type = decltype(min_last_seq_elem.begin());
	auto get_iter = [&strictly, &ascending](iter_type begin, iter_type end, ll elem)
	{
		if (strictly)
		{
			if (ascending)
				return lower_bound(begin, end, elem, less<ll>());
			else
				return lower_bound(begin, end, elem, greater<ll>());
		}
		else
		{
			if (ascending)
				return upper_bound(begin, end, elem, less<ll>());
			else
				return upper_bound(begin, end, elem, greater<ll>());
		}
	};

	vector<ll> update_pos;
	update_pos.reserve(seq.size());


	for (const auto& elem : seq)
	{
		auto iter = get_iter(min_last_seq_elem.begin(), min_last_seq_elem.end(), elem);

		if (iter == min_last_seq_elem.end())
		{
			min_last_seq_elem.emplace_back(elem);
			update_pos.emplace_back(-1LL);
		}
		else
		{
			*iter = elem;
			update_pos.emplace_back(distance(min_last_seq_elem.begin(), iter));
		}
	}

	vector<ll> res;
	res.reserve(min_last_seq_elem.size());
	for (ll i = 0; i < update_pos.size(); ++i)
	{
		const auto& pos = update_pos[i];
		if (pos == -1)
		{
			res.emplace_back(seq[i]);
		}
		else if (pos + 1 == res.size())
		{
			res.back() = seq[i];
		}
	}

	return move(res);
}

vector<ll> z_algorithm(string S) {
	vector<ll> As(S.size());

	if (S.size() == 0)
	{
		return As;
	}

	ll base_pos = 0;
	for (ll curr_pos = 1; curr_pos < S.size(); curr_pos++)
	{
		if (curr_pos + As[curr_pos - base_pos] < base_pos + As[base_pos])
		{
			As[curr_pos] = As[curr_pos - base_pos];
		}
		else
		{
			ll check_pos = max(0LL, base_pos + As[base_pos] - curr_pos);
			while (curr_pos + check_pos < S.size() && S[check_pos] == S[curr_pos + check_pos])
				++check_pos;
			As[curr_pos] = check_pos;
			base_pos = curr_pos;
		}
	}
	As[0] = S.size();

	return As;
}

ll boyer_moore_algorithm(const vector<ll>& pattern, const vector<ll>& str) {
	map<ll, ll> shift;
	ll pattern_idx;
	for (ll i = 0; i < pattern.size(); ++i) {
		pattern_idx = pattern.size() - 1 - i;
		if (shift.count(shift[pattern[pattern_idx]]) == 0) {
			shift[pattern[pattern_idx]] = i;
		}
	}

	ll base_idx = pattern.size() - 1;
	ll curr_idx = base_idx;
	bool found = false;
	while (base_idx < str.size()) {
		for (ll i = 0; i < pattern.size(); ++i) {
			curr_idx = base_idx - i;
			pattern_idx = pattern.size() - 1 - i;

			if (pattern[pattern_idx] != str[curr_idx]) {
				if (shift.count(str[curr_idx]) == 0) {
					curr_idx += pattern.size();
				}
				else {
					curr_idx += shift[str[curr_idx]];
				}
				if (base_idx >= curr_idx) {
					++base_idx;
				}
				else {
					base_idx = curr_idx;
				}
				break;
			}
			if (i + 1 == pattern.size()) {
				found = true;
			}
		}
		if (found) {
			return curr_idx;
		}
	}

	return -1;
}

bool visit(ll node, const vector<vector<ll>>& edges, vector<ll>& status, vector<ll>& result) {
	if (status[node] == 1) return true;
	if (status[node] == 0) {
		status[node] = 1;
		for (ll i = 0; i < edges[node].size(); ++i) {
			if (visit(edges[node][i], edges, status, result)) return false;
		}
		status[node] = 2;
		result.emplace_back(node);
	}

	return true;
}

bool topological_sort(const vector<vector<ll>>& edges, vector<ll>& result) {
	vector<ll> status(edges.size());
	for (ll i = 0; i < edges.size(); ++i) {
		if (status[i] == 0 && !visit(i, edges, status, result)) return false;
	}
	reverse(result.begin(), result.end());
	return true;
}

vector<comp> fft(const vector<comp>& function)
{
	ll degree = function.size();
	if (degree == 0LL)
		throw runtime_error("配列の要素数は 1 以上である必要があります。");
	if ((degree & (degree - 1LL)) != 0LL)
		throw runtime_error("配列の要素数は 2 のべき乗である必要があります。");

	if (degree == 1LL)
		return { function[0] };

	vector<comp> function0(degree / 2LL);
	vector<comp> function1(degree / 2LL);
	for (ll i = 0; i < degree / 2LL; ++i)
	{
		function0[i] = function[i * 2LL];
		function1[i] = function[i * 2LL + 1LL];
	}
	function0 = fft(function0);
	function1 = fft(function1);

	const comp xi = exp(comp(0.0, -2.0 * PI / static_cast<double>(degree)));
	comp power_of_xi(1.0, 0.0);
	vector<comp> transformed_function(degree);
	for (ll i = 0; i < degree; ++i)
	{
		auto res_i = i % (degree / 2LL);
		transformed_function[i] = function0[res_i] + function1[res_i] * power_of_xi;
		power_of_xi *= xi;
	}

	return move(transformed_function);
}

vector<comp> inv_fft(const vector<comp>& function)
{
	vector<comp> conj_function(function.size());
	for (ll i = 0; i < function.size(); ++i)
	{
		conj_function[i] = conj(function[i]);
	}

	conj_function = fft(move(conj_function));

	for (ll i = 0; i < function.size(); ++i)
	{
		conj_function[i] = conj(conj_function[i]) / static_cast<comp>(function.size());
	}

	return move(conj_function);
}

ll default_number_theoretic_transform_mod = 998244353LL; // 998244353 = 119 * 2^23 + 1
ll default_number_theoretic_transform_primitive_root = 3LL; // primitive root of 998244353

vector<ll> fmt(
	const vector<ll>& function,
	ll mod = default_number_theoretic_transform_mod,
	ll primitive_root = default_number_theoretic_transform_primitive_root
)
{
	ll degree = function.size();
	if (degree == 0LL)
		throw runtime_error("配列の要素数は 1 以上である必要があります。");
	if ((degree & (degree - 1LL)) != 0LL)
		throw runtime_error("配列の要素数は 2 のべき乗である必要があります。");
	if ((mod - 1LL) % degree != 0LL)
		throw runtime_error("mod - 1 は配列の要素数で割り切れる必要があります。");

	if (degree == 1LL)
		return { function[0] };

	auto get_mod = [&](const ll& n){
		return (n % mod + mod) % mod;
	};

	vector<ll> function0(degree / 2LL);
	vector<ll> function1(degree / 2LL);
	for (ll i = 0; i < degree / 2LL; ++i)
	{
		function0[i] = function[i * 2LL];
		function1[i] = function[i * 2LL + 1LL];
		function0[i] = get_mod(function0[i]);
		function1[i] = get_mod(function1[i]);
	}
	function0 = fmt(function0, mod, primitive_root);
	function1 = fmt(function1, mod, primitive_root);

	auto get_mod_power = [&](ll base, ull exponential){
		ll result = 1;
		while (exponential >= 1)
		{
			if (exponential & 1)
			{
				result *= base;
				result = get_mod(result);
			}
			base *= base;
			base = get_mod(base);
			exponential >>= 1;
		}

		return result;
	};

	const ll xi = get_mod_power(primitive_root, (mod - 1LL) / degree);
	ll power_of_xi = 1;
	vector<ll> transformed_function(degree);
	for (ll i = 0; i < degree; ++i)
	{
		auto res_i = i % (degree / 2LL);
		transformed_function[i] = function0[res_i] + function1[res_i] * power_of_xi;
		power_of_xi *= xi;
		transformed_function[i] = get_mod(transformed_function[i]);
		power_of_xi = get_mod(power_of_xi);
	}

	return move(transformed_function);
}

vector<ll> inv_fmt(
	const vector<ll>& function,
	ll mod = default_number_theoretic_transform_mod,
	ll primitive_root = default_number_theoretic_transform_primitive_root
)
{
	auto get_mod = [&](const ll& n){
		return (n % mod + mod) % mod;
	};

	auto get_mod_inverse = [&](const ll& n, ll mod) -> ll{
		struct BezoutsIdentitySolver {
			static pair<ll, ll> execute(ll a, ll b) {
				if (b == 0)
				{
					return { 1, 0 };
				}
				auto sol = execute(b, a % b);
				return { sol.second, sol.first - (a / b) * sol.second };
			}
		};
		auto sol = BezoutsIdentitySolver::execute(n, mod);
		if (n * sol.first + mod * sol.second != 1)
		{
			return -1;
		}
		return get_mod(sol.first);
	};

	auto inverse_primitive_root =  get_mod_inverse(primitive_root, mod);
	vector<ll> transformed_function = fmt(
		function, mod, inverse_primitive_root);
	auto inverse_n = get_mod_inverse(function.size(), mod);
	for (ll i = 0; i < function.size(); ++i)
	{
		transformed_function[i] = get_mod(transformed_function[i] * inverse_n);
	}

	return move(transformed_function);
}
