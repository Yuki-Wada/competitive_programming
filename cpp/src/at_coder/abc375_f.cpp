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
#include <random>

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

#define MAX_VALUE 9223372036854775807LL

// type alias
using ll = long long;
using ull = unsigned long long;
using comp = complex<double>;
using llpair = pair<ll, ll>;
template <class T>
using vector2d = vector<vector<T>>;
template <class T>
using vector3d = vector<vector<vector<T>>>;
using ll1d = vector<ll>;
using ll2d = vector2d<ll>;
using ll3d = vector3d<ll>;
using pair1d = vector<llpair>;
using pair2d = vector2d<llpair>;

// constant
static constexpr ll MOD = 998244353LL;
static constexpr double PI = 3.14159265358979323846;

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

ll N, M, Q;

using edge = tuple<ll, ll, ll>;
using answer_query = tuple<ll, ll, ll>;
using edge1d = vector<edge>;
using query1d = vector<answer_query>;
using query2d = vector<vector<answer_query>>;

int solve()
{
	cin >> N >> M >> Q;

	edge1d edges(M);
	REPD(i, 0, M)
	{
		ll a, b, c;
		cin >> a >> b >> c;
		--a, --b;
		edges[i] = {a, b, c};
	}

	vector<bool> enabled_until_end(M, true);
	edge1d seq_edges;
	ll answer_count = 0;
	query2d answer_query_lists;
	query1d answer_query_list;
	REPD(i, 0, Q)
	{
		ll t;
		cin >> t;
		if (t == 1)
		{
			ll block;
			cin >> block;
			--block;
			enabled_until_end[block] = false;
			seq_edges.emplace_back(edges[block]);
			answer_query_lists.emplace_back(answer_query_list);
			answer_query_list.resize(0);
		}
		if (t == 2)
		{
			ll x, y;
			cin >> x >> y;
			--x, --y;
			answer_query_list.emplace_back(answer_count, x, y);
			++answer_count;
		}
	}
	answer_query_lists.emplace_back(answer_query_list);
	reverse(answer_query_lists.begin(), answer_query_lists.end());
	reverse(seq_edges.begin(), seq_edges.end());

	ll1d results(answer_count);
	auto dists = make_multiple_vector(1LL << 60LL, N, N);
	REPD(i, 0, N)
	dists[i][i] = 0LL;

	REPD(i, 0, M)
	if (enabled_until_end[i])
	{
		auto [from, to, info] = edges[i];
		dists[from][to] = min(dists[from][to], info);
		dists[to][from] = min(dists[to][from], info);
	}
	for (unsigned long long k = 0; k < N; ++k)
		for (unsigned long long i = 0; i < N; ++i)
			for (unsigned long long j = 0; j < N; ++j)
			{
				dists[i][j] = min(dists[i][j], dists[i][k] + dists[k][j]);
			}

	REPD(i, 0, answer_query_lists.size())
	{
		for (auto [idx, x, y] : answer_query_lists[i])
			results[idx] = dists[x][y];

		if (i < seq_edges.size())
		{
			auto [a, b, c] = seq_edges[i];
			for (unsigned long long i = 0; i < N; ++i)
				for (unsigned long long j = 0; j < N; ++j)
				{
					dists[i][j] = min({dists[i][j], dists[i][a] + dists[b][j] + c,  dists[i][b] + dists[a][j] + c});
				}
		}
	}

	REPD(i, 0, answer_count)
	cout << (results[i] < (1LL << 60LL) ? results[i] : -1LL) << endl;

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
