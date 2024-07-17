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

// type alias
using ll = long long;
using ull = unsigned long long;
using comp = complex<double>;

// constant
static const ll MOD = 998244353LL;
// static const ll MOD = (1LL << 61LL) - 1LL;
static const double PI = 3.14159265358979323846;

// conversion
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

#define MAX_VALUE 9223372036854775807LL

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

class Solver
{
	ll N;
	vector<vector<vector<ll>>> dps;
	vector<vector<ll>> edges;
	vector<ll> init_dps0;
	vector<ll> init_dps1;

public:
	Solver(ll N, vector<vector<ll>> edges) : N(N), dps(N, vector<vector<ll>>(2LL)), edges(edges)
	{
		init_dps0.emplace_back(1);
		init_dps1.emplace_back(0);
		init_dps1.emplace_back(1);
	}

	vector<ll> calc_sum_for_dps0(ll node)
	{
		calc_dps0(node);
		calc_dps1(node);

		ll vector_size = max(ll(dps[node][0].size()), ll(dps[node][1].size()));
		vector<ll> result(vector_size);

		for (ll i = 0; i < dps[node][0].size(); ++i)
		{
			result[i] += dps[node][0][i];
			result[i] %= MOD;
		}

		for (ll i = 0; i < dps[node][1].size(); ++i)
		{
			result[i] += dps[node][1][i];
			result[i] %= MOD;
		}

		return result;
	}

	vector<ll> calc_sum_for_dps1(ll node)
	{
		calc_dps0(node);
		calc_dps1(node);

		ll vector_size = max(ll(dps[node][0].size()), ll(dps[node][1].size()) - 1LL);
		vector<ll> result(vector_size);

		for (ll i = 0; i < dps[node][0].size(); ++i)
		{
			result[i] += dps[node][0][i];
			result[i] %= MOD;
		}
		for (ll i = 1; i < dps[node][1].size(); ++i)
		{
			result[i - 1] += dps[node][1][i];
			result[i - 1] %= MOD;
		}

		return result;
	}

	void calc_dps0(ll node)
	{
		if (dps[node][0].size() > 0)
		{
			return;
		}

		vector<ll> prev_results;
		vector<ll> curr_results = init_dps0;
		for (auto next : edges[node])
		{
			auto counts = calc_sum_for_dps0(next);

			prev_results = curr_results;
			curr_results = vector<ll>(prev_results.size() + counts.size() - 1LL);

			for (ll j = 0; j < prev_results.size(); ++j)
			{
				for (ll k = 0; k < counts.size(); ++k)
				{
					auto val = (prev_results[j] * counts[k]) % MOD;
					curr_results[j + k] += val;
					curr_results[j + k] %= MOD;
				}
			}
		}

		dps[node][0] = curr_results;

		return;
	}

	void calc_dps1(ll node)
	{
		if (dps[node][1].size() > 0)
		{
			return;
		}

		vector<ll> prev_results;
		vector<ll> curr_results = init_dps1;
		for (auto next : edges[node])
		{
			auto counts = calc_sum_for_dps1(next);

			prev_results = curr_results;
			curr_results = vector<ll>(prev_results.size() + counts.size() - 1LL);

			for (ll j = 0; j < prev_results.size(); ++j)
			{
				for (ll k = 0; k < counts.size(); ++k)
				{
					auto val = (prev_results[j] * counts[k]) % MOD;
					curr_results[j + k] += val;
					curr_results[j + k] %= MOD;
				}
			}
		}

		dps[node][1] = curr_results;

		return;
	}

	vector<ll> solve(ll i)
	{
		calc_dps0(0);
		calc_dps1(0);

		vector<ll> results(N);
		for (ll i = 1; i < dps[0][0].size(); ++i)
		{
			results[i - 1] += dps[0][0][i];
			results[i - 1] %= MOD;
		}
		for (ll i = 1; i < dps[0][1].size(); ++i)
		{
			results[i - 1] += dps[0][1][i];
			results[i - 1] %= MOD;
		}
		return results;
	}
};

int solve()
{
	ll N;
	cin >> N;

	vector<vector<ll>> edges(N);
	ll a, b;
	REPD(i, 0, N - 1)
	{
		cin >> a >> b;
		--a, --b;
		edges[a].emplace_back(b);
		edges[b].emplace_back(a);
	}

	vector<vector<ll>> trees(N);
	vector<bool> is_visited(N, false);

	REPD(i, 0, N)
	{
		if (is_visited[i])
			continue;

		queue<ll> que;
		que.emplace(i);
		is_visited[i] = true;
		while (!que.empty())
		{
			auto node = que.front();
			que.pop();
			for (auto next : edges[node])
			{
				if (is_visited[next])
					continue;
				trees[node].emplace_back(next);
				que.emplace(next);
				is_visited[next] = true;
			}
		}
		que.emplace(i);
		is_visited[i] = true;
	}

	Solver solver(N, trees);
	auto results = solver.solve(0);
	for (ll i = 0; i < N; ++i)
	{
		cout << results[i] << endl;
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
	// REPD(i, 0, t) solve();

	return 0;
}
