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

using pair1d = vector1d<llpair>;
ll H, W;
vector2d<bool> visited;
vector2d<bool> place_existe;

int solve()
{
	cin >> W >> H;

	visited = make_multiple_vector(false, H + 2, W + 2);
	place_existe = make_multiple_vector(false, H + 2, W + 2);
	ll p;
	REPD(i, 0, H)
	REPD(j, 0, W)
	cin >> p, place_existe[i + 1][j + 1] = p == 1;

	queue<llpair> que;
	que.emplace(0, 0);
	visited[0][0] = true;
	while (!que.empty())
	{
		auto [curr_i, curr_j] = que.front();
		que.pop();

		pair1d next_idxs;
		next_idxs.emplace_back(curr_i, curr_j - 1);
		next_idxs.emplace_back(curr_i, curr_j + 1);
		next_idxs.emplace_back(curr_i - 1, curr_j);
		next_idxs.emplace_back(curr_i + 1, curr_j);
		next_idxs.emplace_back(curr_i - 1, curr_j + (curr_i % 2 == 1 ? 1 : -1));
		next_idxs.emplace_back(curr_i + 1, curr_j + (curr_i % 2 == 1 ? 1 : -1));
		REPD(i, 0, next_idxs.size())
		{
			auto [next_i, next_j] = next_idxs[i];
			if (0 <= next_i && next_i < H + 2 && 0 <= next_j && next_j < W + 2 && !place_existe[next_i][next_j] && !visited[next_i][next_j])
			{
				que.emplace(next_i, next_j);
				visited[next_i][next_j] = true;
			}
		}
	}

	ll res = 0;
	REPD(i, 0, H + 2)
	REPD(j, 0, W + 2)
	{
		if (!visited[i][j])
		{
			pair1d next_idxs;
			next_idxs.emplace_back(i, j - 1);
			next_idxs.emplace_back(i, j + 1);
			next_idxs.emplace_back(i - 1, j);
			next_idxs.emplace_back(i + 1, j);
			next_idxs.emplace_back(i - 1, j + (i % 2 == 1 ? 1 : -1));
			next_idxs.emplace_back(i + 1, j + (i % 2 == 1 ? 1 : -1));
			REPD(i, 0, next_idxs.size())
			{
				auto [next_i, next_j] = next_idxs[i];
				if (0 <= next_i && next_i < H + 2 && 0 <= next_j && next_j < W + 2 && visited[next_i][next_j])
				{
					++res;
				}
			}
		}
	}
	RET(res);

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
