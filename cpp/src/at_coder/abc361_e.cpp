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

#define MAX_VALUE 9223372036854787LL

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

pair<ll, ll> dfs(const vector<vector<pair<ll, ll>>> &edges, bitset<200000> &visited, ll idx)
{
	visited.set(idx);

	vector<ll> passes;
	vector<ll> non_passes;
	REPI(info, edges[idx])
	{
		auto [next_idx, c] = info;
		if (!visited.test(next_idx))
		{
			auto [pass, non_pass] = dfs(edges, visited, next_idx);
			passes.emplace_back(pass + c);
			non_passes.emplace_back(non_pass);
		}
	}

	if (passes.size() == 0LL)
	{
		return {0LL, 0LL};
	}

	sort(passes.begin(), passes.end());
	sort(non_passes.begin(), non_passes.end());

	ll max_pass = passes.back();
	ll max_non_pass = non_passes.back();
	if (passes.size() >= 2LL)
	{
		max_non_pass = max(max_non_pass, passes[passes.size() - 1LL] + passes[passes.size() - 2LL]);
	}

	return {max_pass, max_non_pass};
}

ll compute_max_length(const vector<vector<pair<ll, ll>>> &edges)
{
	bitset<200000> visited;
	auto [pass, non_pass] = dfs(edges, visited, 0);
	return max(pass, non_pass);
}

int solve()
{
	ll N;
	cin >> N;

	auto edges = make_multiple_vector(make_pair(0LL, 0LL), N, 0LL);
	ll res = 0;
	ll a, b, c;
	REPD(i, 0, N - 1LL)
	{
		cin >> a >> b >> c;
		--a, --b;
		edges[a].emplace_back(b, c);
		edges[b].emplace_back(a, c);
		res += c * 2LL;
	}

	res -= compute_max_length(edges);

	cout << res << endl;
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
