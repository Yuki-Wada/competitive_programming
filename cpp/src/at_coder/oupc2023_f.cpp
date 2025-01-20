// include
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

// print
#define RET(x) return cout << x << endl, 0;

// for loop
#define REP(i, a, b) for ((i) = (ll)(a); (i) < (ll)(b); (i)++)
#define REPD(i, a, b) for (ll i = (ll)(a); (i) < (ll)(b); (i)++)
#define REPI(v, vs) for (auto &v : vs)

// debug
#ifdef LOCAL_ENV
#define DUMP(x) cerr << #x << " = " << (x) << endl
#define DEBUG(x) cerr << #x << " = " << (x) << " (l" << __LINE__ << ")" \
					  << " " << __FILE__ << endl
#else
#define DUMP(x)
#define DEBUG(x)
#endif

#define MAX_VALUE 9223372036854787LL

// type alias
using ll = long long;
using ull = unsigned long long;
using comp = complex<double>;
using llpair = pair<ll, ll>;
template <class T>
using vector1d = vector<T>;
template <class T>
using vector2d = vector<vector<T>>;
template <class T>
using vector3d = vector<vector<vector<T>>>;
using ll1d = vector<ll>;
using ll2d = vector2d<ll>;
using ll3d = vector3d<ll>;

// constant
static const ll MOD = 998244353LL;
// static const ll MOD = (1LL << 61LL) - 1LL;
static const double PI = 3.14159265358979323846;

template <class T, class... Args>
auto make_multiple_vector(T default_value)
{
	return T(default_value);
}

template <class T, class... Args>
auto make_multiple_vector(T default_value, ull size, Args... args)
{
	using value_type = std::decay_t<decltype(make_multiple_vector<T>(default_value, args...))>;
	return vector<value_type>(size, make_multiple_vector<T>(default_value, args...));
}

using triplet = tuple<ll, ll, ll>;
using triplet1d = vector1d<triplet>;
ll N, Q;
ll1d As;
triplet1d triplets;

void precompute1()
{
	ll max_a = As.back();
	vector<ll> counts(max_a + 2LL);
	REPD(i, 0, As.size())
	{
		counts[As[i]]++;
	}
	ll accum = 0;
	REPD(i, 0, counts.size())
	{
		accum += counts[i];
		counts[i] = accum;
	}

	ll sum = 0;
	REPD(m, 1, As.back() + 2LL)
	{
		ll max_a_residual = max_a % m;

		ll km = 0;
		ll count_a = 0;
		while (km <= max_a)
		{
			ll left = max(km - 1LL, 0LL);
			ll right = min(km + max_a_residual, max_a + 1LL);
			count_a += counts[right] - counts[left];
			km += m;
		}

		auto incr = count_a == N ? 1LL : 0LL;
		triplets.emplace_back(m, sum, incr);
		sum += incr;
	}
}

ll compute_answer(ll m)
{
	auto iter = lower_bound(triplets.begin(), triplets.end(), make_tuple(m, MAX_VALUE, MAX_VALUE));
	--iter;
	auto [base_m, sum, incr] = *iter;
	ll res = sum + (m - base_m + 1LL) * incr;
	return res;
}

void compute1()
{
	precompute1();

	cin >> Q;
	ll m;
	REPD(i, 0, Q)
	{
		cin >> m;
		cout << compute_answer(m) << "\n";
	}
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

void precompute2()
{
	ll max_a = As.back();

	triplet1d intermediates;
	REPD(i, 0, As.size())
	{
		REPD(j, 0, 2)
		{
			ll a = j == 0 ? As[i] : max_a - As[i];
			if (a <= 0)
			{
				continue;
			}
			auto quots = enumerate_quotients(a);

			REPD(k, 0, quots.size())
			{
				ll m = a / quots[k] + 1LL;
				intermediates.emplace_back(m, i, j);
			}
		}
	}
	sort(intermediates.begin(), intermediates.end());

	ll left_val = 0, right_val = N * floor(max_a, 1);
	REPD(i, 0, N)
	{
		left_val += floor(As[i], 1) + floor(max_a - As[i], 1);
	}

	ll prev_m = 1;
	ll prev_sum = 0;
	REPD(i, 0, intermediates.size())
	{
		auto [m, idx, j] = intermediates[i];
		if (prev_m != m)
		{
			auto incr = left_val == right_val ? 1LL : 0LL;
			triplets.emplace_back(prev_m, prev_sum, incr);

			prev_sum += (m - prev_m) * incr;
			prev_m = m;
		}

		if (j == 0)
		{
			left_val -= floor(As[idx], m - 1LL);
			left_val += floor(As[idx], m);
		}
		else
		{
			left_val -= floor(max_a - As[idx], m - 1LL);
			left_val += floor(max_a - As[idx], m);
		}

		if (idx + 1LL == N)
		{
			if (j == 0)
			{
				right_val = N * floor(max_a, m);
			}
		}
	}

	auto incr = left_val == right_val ? 1LL : 0LL;
	triplets.emplace_back(prev_m, prev_sum, incr);
}

void compute2()
{
	precompute2();

	cin >> Q;
	ll m;
	REPD(i, 0, Q)
	{
		cin >> m;
		cout << compute_answer(m) << "\n";
	}
}

int solve()
{
	cin >> N;
	As = make_multiple_vector(0LL, N);
	REPD(i, 0, N)
	cin >> As[i];
	sort(As.begin(), As.end());

	if (As.back() <= 2000000)
	{
		compute1();
	}
	else
	{
		compute2();
	}

	return 0;
}

// main function
int main()
{
	cin.tie(0);
	ios::sync_with_stdio(false);

	solve();

	// ll t;
	// cin >> t;
	// REPD(i, 0, t)
	// {
	// 	solve();
	// }

	return 0;
}
