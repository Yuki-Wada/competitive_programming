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

// constant
static const ll MOD = 998244353LL;
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

void compute_euler_tour(ll node, const ll2d &rev_edges, ll1d &result)
{
	result.emplace_back(node);
	REPD(i, 0, rev_edges[node].size())
	{
		auto prev_node = rev_edges[node][i];
		compute_euler_tour(prev_node, rev_edges, result);
	}
	result.emplace_back(-1LL);
}

ll N, K;

int solve()
{
	cin >> N >> K;

	ll1d next_indexes(N);
	ll2d rev_edges(N);
	ll1d dst_indexes(N);
	ll1d As(N);

	ll X, A;
	REPD(i, 0, N)
	{
		cin >> X;
		--X;
		next_indexes[i] = X;
		rev_edges[X].emplace_back(i);
		dst_indexes[i] = -1LL;
	}
	REPD(i, 0, N)
	{
		cin >> A;
		As[i] = A;
	}

	vector<ll> visit_counts(N, -1LL);
	REPD(i, 0, N)
	{
		if (visit_counts[i] >= 0LL)
		{
			continue;
		}

		ll visit_count = 1;
		visit_counts[i] = ++visit_count;
		auto idx = next_indexes[i];
		while (visit_counts[idx] == -1LL)
		{
			visit_counts[idx] = ++visit_count;
			idx = next_indexes[idx];
		}

		auto closed_path_length = ++visit_count - visit_counts[idx];
		ll1d closed_path_indexes(closed_path_length);
		REPD(j, 0, closed_path_length)
		{
			closed_path_indexes[j] = idx;
			idx = next_indexes[idx];
		}

		REPD(j, 0, closed_path_length)
		{
			auto node = closed_path_indexes[j];
			auto next_node = closed_path_indexes[(K + j) % closed_path_length];
			dst_indexes[node] = next_node;
			visit_counts[node] = 0LL;
		}

		REPD(j, 0, closed_path_length)
		{
			auto node = closed_path_indexes[j];
			REPD(k, 0, rev_edges[node].size())
			{
				auto prev_node = rev_edges[node][k];
				if (visit_counts[prev_node] == 0LL)
				{
					continue;
				}
				ll1d euler_tour;
				compute_euler_tour(prev_node, rev_edges, euler_tour);

				ll1d path;
				REPD(l, 0, euler_tour.size())
				{
					auto n = euler_tour[l];
					if (n == -1LL)
					{
						path.pop_back();
						continue;
					}
					path.emplace_back(n);
					if (K >= path.size())
					{
						auto next_node = closed_path_indexes[(K - path.size() + j) % closed_path_length];
						dst_indexes[n] = next_node;
					}
					else
					{
						auto next_node = path[path.size() - K - 1LL];
						dst_indexes[n] = next_node;
					}
					visit_counts[n] = 0LL;
				}
			}
		}
	}

	REPD(i, 0, N)
	{
		cout << As[dst_indexes[i]];
		if (i + 1LL < N)
		{
			cout << " ";
		}
		else
		{
			cout << endl;
		}
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
