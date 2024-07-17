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
static const ll MOD = 1000000007LL;
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
private:
	ll N;
	ll finished_count;
	vector<vector<ll>> edges;
	vector<ll> colors;
	ll NO_BIPARTITIE = -1LL;

public:
	Solver(vector<vector<ll>> edges) : N(edges.size()), finished_count(0), edges(edges), colors(N, -1)
	{
	}

	ll solve_impl(ll node)
	{

		class BFSExecutor : public queue<pair<ll, ll>>
		{
		private:
			vector<ll> visited_nodes;

		public:
			BFSExecutor() {}

			void bfspush(ll node, ll color, vector<ll> &colors)
			{
				emplace(node, color);
				visited_nodes.emplace_back(node);
				colors[node] = color;
			}

			pair<ll, ll> bfspop()
			{
				auto [curr, color] = front();
				color = 1 - color;
				pop();
				return make_pair(curr, color);
			}

			ll get_result(vector<vector<ll>> &edges, vector<ll> &colors)
			{
				ll res = 0;
				ll color1_count = 0, edge_count = 0;
				for (ll i = 0; i < visited_nodes.size(); ++i)
				{
					auto node = visited_nodes[i];
					edge_count += edges[node].size();
					color1_count += colors[node];
				}
				res += color1_count * (visited_nodes.size() - color1_count) - edge_count / 2LL;

				return res;
			}
			ll visited_node_count()
			{
				return visited_nodes.size();
			}
		};

		BFSExecutor bfs;
		bfs.bfspush(node, 0, colors);
		while (!bfs.empty())
		{
			auto [curr, color] = bfs.bfspop();
			for (ll i = 0; i < edges[curr].size(); ++i)
			{
				ll next = edges[curr][i];
				if (colors[next] != -1LL)
				{
					if (colors[next] != color)
					{
						return NO_BIPARTITIE;
					}
				}
				else
				{
					bfs.bfspush(next, color, colors);
				}
			}
		}

		ll res = bfs.get_result(edges, colors);
		finished_count += bfs.visited_node_count();
		res += bfs.visited_node_count() * (N - finished_count);

		return res;
	}

	ll solve()
	{
		ll result = 0, loop_result;
		for (ll i = 0; i < N; ++i)
		{
			if (colors[i] != -1LL)
			{
				continue;
			}
			loop_result = solve_impl(i);
			if (loop_result == NO_BIPARTITIE)
			{
				return 0LL;
			}
			result += loop_result;
		}

		return result;
	}
};

int solve()
{
	ll N, M, u, v;
	cin >> N >> M;
	vector<vector<ll>> edges(N);
	for (ll i = 0; i < M; ++i)
	{
		cin >> u >> v;
		--u, --v;
		edges[u].emplace_back(v);
		edges[v].emplace_back(u);
	}

	auto solver = Solver(edges);
	cout << solver.solve() << endl;

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
