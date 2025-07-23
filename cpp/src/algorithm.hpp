#ifndef __ALGORITHM_HPP__
#define __ALGORITHM_HPP__ 0

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
		return (a + llb - 1) / llb;
	else
		return -(-a / llb);
}

inline ull get_lowest_one_bit(ull a)
{
	return a & (-a);
}

inline ull get_highest_one_bit(ull a)
{
	while ((a & (a - 1LL)) != 0)
		a = a & (a - 1LL);
	return a;
}

inline bool is_power2(ull a)
{
	if (a == 0)
		return false;
	return !(a & (a - 1));
}

inline ull get_specified_bit(ull a, ull bit)
{
	return (a >> bit) & 1ULL;
}

inline ll toint(string s)
{
	ll v;
	istringstream sin(s);
	sin >> v;
	return v;
}
template <class t>
inline string tostring(t x)
{
	ostringstream sout;
	sout << x;
	return sout.str();
}

ll floor_sum(ll n, ll m, ll a, ll b)
{
	ll ans = 0;
	if (a >= m)
	{
		ans += (n - 1LL) * n * (a / m) / 2LL;
		a %= m;
	}
	if (b >= m)
	{
		ans += n * (b / m);
		b %= m;
	}

	ll y_max = (a * n + b) / m, x_max = (y_max * m - b);
	if (y_max == 0LL)
		return ans;

	ans += (n - (x_max + a - 1Ll) / a) * y_max;
	ans += floor_sum(y_max, a, m, (a - x_max % a) % a);
	return ans;
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

// computational complexity: o(log(max(a, b)))
inline pair<ll, ll> get_bezouts_solution(ll a, ll b)
{
	if (b == ll(0))
		return {ll(1) / a, ll(0)};
	auto sol = get_bezouts_solution(b, a % b);
	return {sol.second, sol.first - (a / b) * sol.second};
}

template <class Integer>
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

vector<ull> enumerate_quotients(ull x)
{
	if (x == 1ULL)
	{
		return {1ULL};
	}

	ull low = 1LL, high = x, mid = (low + high) / 2LL;
	while (high - low >= 2LL)
	{
		if (mid * mid + mid > x)
		{
			high = mid;
		}
		else
		{
			low = mid;
		}
		mid = (low + high) / 2LL;
	}

	vector<ull> results;
	results.reserve((low + 1LL) * 2LL);
	for (ull i = 1; i <= low + 1ULL; ++i)
	{
		results.emplace_back(x / i);
	}

	for (ull i = x / (low + 1ULL) - 1ULL; i >= 1ULL; --i)
	{
		results.emplace_back(i);
	}

	return results;
}

vector<vector<ll>> enumerate_combination_slow(ll n, ll k)
{
	if (n == 0)
		return {};
	if (k == 0)
		return {};
	if (n < k)
		return {};

	vector<vector<ll>> res;
	if (k == 1)
	{
		for (ll i = 0; i < n; ++i)
		{
			res.emplace_back(vector<ll>(1, i));
		}
		return res;
	}
	if (n == k)
	{
		vector<ll> v(n);
		for (ll i = 0; i < n; ++i)
		{
			v[i] = i;
		}
		res.emplace_back(v);
		return res;
	}
	res = enumerate_combination(n - 1, k);
	vector<vector<ll>> pre = enumerate_combination(n - 1, k - 1);
	res.reserve(res.size() + pre.size());
	for (ll i = 0; i < pre.size(); ++i)
	{
		pre[i].emplace_back(n - 1);
	}
	copy(pre.begin(), pre.end(), std::back_inserter(res));

	return res;
}

vector<vector<ll>> enumerate_combination(const vector<ll> &elems, ll k)
{
	struct CombineImpl
	{
		static void execute(ll k, ll start, const vector<ll> &elems, vector<ll> &comb, vector<vector<ll>> &combs)
		{
			if (comb.size() > k)
			{
				throw runtime_error("組合せの長さは k 以下である必要があります。");
			}

			if (comb.size() == k)
			{
				combs.emplace_back(comb);
				return;
			}

			for (ll i = start; i < elems.size(); ++i)
			{
				if (k + i > ll(comb.size()) + ll(elems.size()))
				{
					break;
				}
				comb.push_back(elems[i]);
				CombineImpl::execute(k, i + 1, elems, comb, combs);
				comb.pop_back();
			}
			return;
		};
	};

	vector<vector<ll>> combs;
	vector<ll> comb;

	CombineImpl::execute(k, 0LL, elems, comb, combs);
	return combs;
}

vector<vector<ll>> enumerate_combination(ll n, ll k)
{
	vector<ll> elems(n);
	for (ll i = 0; i < n; ++i)
		elems[i] = i;

	auto combs = enumerate_combination(elems, k);
	return combs;
}

vector<vector<ll>> compute_permutations(ll n)
{
	vector<ll> nums(n);
	ll permutation_count = 1LL;
	for (ll i = 0; i < n; ++i)
	{
		nums[i] = i;
		permutation_count *= n + 1LL;
	}

	vector<vector<ll>> permutations;
	permutations.reserve(permutation_count);
	do
	{
		permutations.push_back(nums);
	} while (next_permutation(nums.begin(), nums.end()));

	return permutations;
}

ll get_lis_length(const vector<ll> &seq, bool strictly = true, bool ascending = true)
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

	for (const auto &elem : seq)
	{
		auto iter = get_iter(min_last_seq_elem.begin(), min_last_seq_elem.end(), elem);
		if (iter == min_last_seq_elem.end())
			min_last_seq_elem.emplace_back(elem);
		else
			*iter = elem;
	}

	return min_last_seq_elem.size();
}

vector<ll> get_lis(const vector<ll> &seq, bool strictly = true, bool ascending = true)
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

	for (const auto &elem : seq)
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
		const auto &pos = update_pos[i];
		if (pos == -1)
		{
			res.emplace_back(seq[i]);
		}
		else if (pos + 1 == res.size())
		{
			res.back() = seq[i];
		}
	}

	return res;
}

pair<vector<ll>, vector<ll>> compress_coordinates(const vector<ll> &As)
{
	ll N = As.size();
	vector<pair<ll, ll>> items(N);
	for (ll i = 0; i < N; ++i)
	{
		items[i] = make_pair(As[i], i);
	}
	sort(items.begin(), items.end());

	vector<ll> compressed_coords(N);
	vector<ll> compression_table;

	ll prev_a;
	ll compressed = -1;
	for (ll i = 0; i < N; ++i)
	{
		auto [a, idx] = items[i];
		if (i == 0LL || prev_a != a)
		{
			compression_table.push_back(a);
			++compressed;
			prev_a = a;
		}

		compressed_coords[idx] = compressed;
	}

	return {compressed_coords, compression_table};
}

pair<bool, vector<ll>> topological_sort(const vector<vector<ll>> &edges)
{
	struct DFS
	{
		static bool visit(ll node, const vector<vector<ll>> &edges, vector<ll> &status, vector<ll> &result)
		{
			if (status[node] == 1)
				return false;
			if (status[node] == 0)
			{
				status[node] = 1;
				for (ull i = 0; i < edges[node].size(); ++i)
					if (!visit(edges[node][i], edges, status, result))
						return false;

				status[node] = 2;
				result.emplace_back(node);
			}

			return true;
		}
	};

	vector<ll> result;
	vector<ll> status(edges.size());
	for (ull i = 0; i < edges.size(); ++i)
		if (status[i] == 0 && !DFS::visit(i, edges, status, result))
			return make_pair(false, vector<ll>());

	reverse(result.begin(), result.end());

	return make_pair(true, result);
}

vector<ll> z_algorithm(string S)
{
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

ll boyer_moore_algorithm(const vector<ll> &pattern, const vector<ll> &str)
{
	map<ll, ll> shift;
	ll pattern_idx;
	for (ll i = 0; i < pattern.size(); ++i)
	{
		pattern_idx = pattern.size() - 1 - i;
		if (shift.count(shift[pattern[pattern_idx]]) == 0)
		{
			shift[pattern[pattern_idx]] = i;
		}
	}

	ll base_idx = pattern.size() - 1;
	ll curr_idx = base_idx;
	bool found = false;
	while (base_idx < str.size())
	{
		for (ll i = 0; i < pattern.size(); ++i)
		{
			curr_idx = base_idx - i;
			pattern_idx = pattern.size() - 1 - i;

			if (pattern[pattern_idx] != str[curr_idx])
			{
				if (shift.count(str[curr_idx]) == 0)
				{
					curr_idx += pattern.size();
				}
				else
				{
					curr_idx += shift[str[curr_idx]];
				}
				if (base_idx >= curr_idx)
				{
					++base_idx;
				}
				else
				{
					base_idx = curr_idx;
				}
				break;
			}
			if (i + 1 == pattern.size())
			{
				found = true;
			}
		}
		if (found)
		{
			return curr_idx;
		}
	}

	return -1;
}

vector<ull> construct_suffix_array(const vector<ull> &vec)
{
	struct DoublingComparer
	{
		static bool compare(ll i, ll j, vector<ll> &ranks, ll K, ll N)
		{
			if (ranks[i] != ranks[j])
			{
				return ranks[i] < ranks[j];
			}
			ll di = i + K <= N ? ranks[i + K] : -1LL;
			ll dj = j + K <= N ? ranks[j + K] : -1LL;

			return di < dj;
		};
	};

	ll N = vec.size();
	vector<ull> suffix_array(N + 1LL);
	vector<ll> ranks(N + 1LL);

	for (ll i = 0; i <= N; ++i)
	{
		suffix_array[i] = i;
		ranks[i] = i < N ? vec[i] : -1LL;
	}

	vector<ull> tmp_ranks(N);

	for (ll k = 1; k < N; k *= 2LL)
	{
		auto compare = [&ranks, k, N](ll i, ll j)
		{
			return DoublingComparer::compare(i, j, ranks, k, N);
		};
		sort(suffix_array.begin(), suffix_array.end(), compare);

		tmp_ranks[suffix_array[0]] = 0;
		for (ll i = 1; i <= N; ++i)
		{
			tmp_ranks[suffix_array[i]] = tmp_ranks[suffix_array[i - 1LL]];
			if (DoublingComparer::compare(suffix_array[i - 1LL], suffix_array[i], ranks, k, N))
			{
				++tmp_ranks[suffix_array[i]];
			}
		}
		for (ll i = 0; i <= N; ++i)
		{
			ranks[i] = tmp_ranks[i];
		}
	}
	return suffix_array;
}

vector<ull> construct_lcp(const vector<ull> &vec)
{
	ll N = vec.size();
	vector<ull> lcp(N);

	vector<ull> suffix_array = construct_suffix_array(vec);
	vector<ull> ranks(N + 1LL);
	for (ll i = 0; i <= N; ++i)
	{
		ranks[suffix_array[i]] = i;
	}

	lcp[0] = 0;
	ll h = 0;
	for (ll i = 0; i < N; ++i)
	{
		ll j = suffix_array[ranks[i] - 1LL];
		if (h > 0LL)
		{
			--h;
		}
		for (; j + h < N && i + h < N; ++h)
		{
			if (vec[j + h] != vec[i + h])
			{
				break;
			}
		}
		lcp[ranks[i] - 1LL] = h;
	}

	return lcp;
}

void fft_impl(
	const vector<comp> &function,
	vector<comp> &transformed,
	vector<comp> &stored,
	ll start,
	ll skip)
{
	ll degree = function.size() / skip;
	if (degree == 1LL)
	{
		transformed[start] = function[start];
		return;
	}

	fft_impl(function, transformed, stored, start, skip * 2LL);
	fft_impl(function, transformed, stored, start + skip, skip * 2LL);
	for (ll i = 0; i < degree; ++i)
	{
		stored[start + skip * i] = transformed[start + skip * i];
	}

	const comp xi = exp(comp(0.0, -2.0 * PI / static_cast<double>(degree)));
	comp power_of_xi(1.0, 0.0);
	vector<comp> transformed_function(degree);
	for (ll i = 0; i < degree; ++i)
	{
		auto res_i = i % (degree / 2LL);
		transformed[start + skip * i] = stored[start + skip * res_i * 2LL] + stored[start + skip * (res_i * 2LL + 1LL)] * power_of_xi;
		power_of_xi *= xi;
	}
}

vector<comp> fft(const vector<comp> &function)
{
	ll degree = function.size();
	if (degree == 0LL)
		throw runtime_error("配列の要素数は 1 以上である必要があります。");
	if ((degree & (degree - 1LL)) != 0LL)
		throw runtime_error("配列の要素数は 2 のべき乗である必要があります。");

	vector<comp> transformed(degree, 0);
	vector<comp> stored(degree, 0);
	fft_impl(function, transformed, stored, 0LL, 1LL);

	return transformed;
}

vector<comp> inv_fft(const vector<comp> &function)
{
	vector<comp> conj_function(function.size());
	for (ull i = 0; i < function.size(); ++i)
	{
		conj_function[i] = conj(function[i]);
	}

	conj_function = fft(move(conj_function));

	for (ull i = 0; i < function.size(); ++i)
	{
		conj_function[i] = conj(conj_function[i]) / static_cast<comp>(function.size());
	}

	return conj_function;
}

ll DEFAULT_NUMBER_THEORETIC_TRANSFORM_MOD = 998244353LL;	// 998244353 = 119 * 2^23 + 1
ll DEFAULT_NUMBER_THEORETIC_TRANSFORM_PRIMITIVE_ROOT = 3LL; // primitive root of 998244353

// Fast Modulo Transform
void fmt_recursive_impl(
	const vector<ll> &function,
	vector<ll> &transformed,
	vector<ll> &stored,
	ll start,
	ll skip,
	ll mod,
	ll xi)
{
	ll degree = function.size() / skip;

	if (degree == 1LL)
	{
		transformed[start] = function[start];
		return;
	}

	auto get_mod = [&](const ll &n)
	{
		return (n % mod + mod) % mod;
	};

	fmt_recursive_impl(function, transformed, stored, start, skip * 2LL, mod, get_mod(xi * xi));
	fmt_recursive_impl(function, transformed, stored, start + skip, skip * 2LL, mod, get_mod(xi * xi));
	for (ll i = 0; i < degree; ++i)
	{
		stored[start + skip * i] = transformed[start + skip * i];
	}

	ll power_of_xi = 1;
	for (ll i = 0; i < degree; ++i)
	{
		auto res_i = i % (degree / 2LL);
		transformed[start + skip * i] = stored[start + skip * res_i * 2LL] + stored[start + skip * (res_i * 2LL + 1LL)] * power_of_xi;
		power_of_xi *= xi;
		transformed[start + skip * i] = get_mod(transformed[start + skip * i]);
		power_of_xi = get_mod(power_of_xi);
	}
}

vector<ll> fmt_recursive(
	const vector<ll> &function,
	ll mod = DEFAULT_NUMBER_THEORETIC_TRANSFORM_MOD,
	ll primitive_root = DEFAULT_NUMBER_THEORETIC_TRANSFORM_PRIMITIVE_ROOT)
{
	auto degree = function.size();
	if (degree == 0LL)
		throw runtime_error("配列の要素数は 1 以上である必要があります。");
	if ((degree & (degree - 1LL)) != 0LL)
		throw runtime_error("配列の要素数は 2 のべき乗である必要があります。");
	if ((mod - 1LL) % degree != 0LL)
		throw runtime_error("mod - 1 は配列の要素数で割り切れる必要があります。");

	vector<ll> transformed(degree, 0);
	vector<ll> stored(degree, 0);

	auto get_mod = [&](const ll &n)
	{
		return (n % mod + mod) % mod;
	};

	auto get_mod_power = [&](ll base, ull exponential)
	{
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
	ll xi = get_mod_power(primitive_root, (mod - 1LL) / degree);
	fmt_recursive_impl(function, transformed, stored, 0LL, 1LL, mod, xi);
	return transformed;
}
vector<ll> inv_fmt_recursive(
	const vector<ll> &function,
	ll mod = DEFAULT_NUMBER_THEORETIC_TRANSFORM_MOD,
	ll primitive_root = DEFAULT_NUMBER_THEORETIC_TRANSFORM_PRIMITIVE_ROOT)
{
	auto get_mod = [&](const ll &n)
	{
		return (n % mod + mod) % mod;
	};

	auto get_mod_inverse = [&](const ll &n, ll mod) -> ll
	{
		struct BezoutsIdentitySolver
		{
			static pair<ll, ll> execute(ll a, ll b)
			{
				if (b == 0)
				{
					return {1, 0};
				}
				auto sol = execute(b, a % b);
				return {sol.second, sol.first - (a / b) * sol.second};
			}
		};
		auto sol = BezoutsIdentitySolver::execute(n, mod);
		if (n * sol.first + mod * sol.second != 1)
		{
			return -1;
		}
		return get_mod(sol.first);
	};

	auto inverse_primitive_root = get_mod_inverse(primitive_root, mod);
	vector<ll> transformed = fmt_recursive(
		function, mod, inverse_primitive_root);
	auto inverse_n = get_mod_inverse(function.size(), mod);
	for (ull i = 0; i < function.size(); ++i)
	{
		transformed[i] = get_mod(transformed[i] * inverse_n);
	}

	return transformed;
}

#include <atcoder/all>
using rll = atcoder::modint998244353;
constexpr ll MOD_PRIMITIVE_ROOT = 3LL;
constexpr ll MOD_INVERSE_PRIMITIVE_ROOT = 332748118LL;

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
vector<rll> fmt_impl(const vector<rll> &function, const ll primitive_root)
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
	rll xi = get_power2(rll(primitive_root), (rll::mod() - 1LL) / degree);

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

vector<ll> fmt_convolution(const vector<ll> &a, const vector<ll> &b)
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
	vector<ll> ab(coef_num);
	for (unsigned int i = 0; i < coef_num; ++i)
		ab[i] = rll_ab[i].val();

	return ab;
}

vector<ll> my_convolution(const vector<ll> &a, const vector<ll> &b)
{
	return fmt_convolution(a, b);
}

#endif
