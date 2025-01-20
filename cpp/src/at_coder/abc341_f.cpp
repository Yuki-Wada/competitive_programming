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

ll N, M;

int solve()
{
	cin >> N >> M;

	ll2d edges(N);
	ll u, v;
	REPD(i, 0, M)
	{
		cin >> u >> v;
		--u, --v;
		edges[u].emplace_back(v);
		edges[v].emplace_back(u);
	}

	priority_queue<pair<ll, ll>> que;
	ll1d Ws(N), As(N);
	REPD(i, 0, N)
	{
		cin >> Ws[i];
		que.emplace(-Ws[i], i);
	}
	REPD(i, 0, N)
	{
		cin >> As[i];
	}

	ll1d counts(N, 1LL);
	while (!que.empty())
	{
		auto [_, i] = que.top();
		que.pop();
		auto target_w = Ws[i];

		vector<llpair> option_pairs;
		REPD(j, 0, edges[i].size())
		{
			auto node = edges[i][j];
			option_pairs.emplace_back(Ws[node], counts[node]);
		}

		ll1d prevs(target_w, 1LL), currs(target_w);
		REPD(j, 0, option_pairs.size())
		{
			auto [w, c] = option_pairs[j];
			REPD(k, 0, target_w)
			{
				currs[k] = prevs[k];
				if (k >= w)
				{
					currs[k] = max(prevs[k - w] + c, prevs[k]);
				}
			}
			REPD(k, 0, target_w)
			{
				prevs[k] = currs[k];
			}
		}
		counts[i] = *max_element(prevs.begin(), prevs.end());
	}

	ll res = 0;
	REPD(i, 0, N)
	{
		res += counts[i] * As[i];
	}
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
