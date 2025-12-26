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

// temporary
#include <atcoder/all>
using namespace atcoder;

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
static constexpr ll MOD = 998244353LL;
static constexpr double PI = 3.14159265358979323846;

template <ull N, class T, class... Args, std::enable_if_t<N == 0, int> = 0>
auto make_multiple_vector(Args... args)
{
	return T(args...);
}

template <ull N, class T, class... Args, std::enable_if_t<N != 0, int> = 0>
auto make_multiple_vector(ull size, Args... args)
{
	using value_type = std::decay_t<decltype(make_multiple_vector<N - 1LL, T>(args...))>;
	return vector<value_type>(size, make_multiple_vector<N - 1LL, T>(args...));
}

bool can_solve(const ll1d &a, ll idx)
{
	if (idx * 2LL > a.size())
	{
		return false;
	}

	ll left = 0;
	ll right = a.size() - idx;
	REPD(i, 0, idx)
	{
		if (a[right + i] < a[left + i] * 2LL)
		{
			return false;
		}
	}

	return true;
}

ll solve()
{
	ll n;
	cin >> n;

	auto a = make_multiple_vector<2, ll>(n, n, -1LL);
	REPD(i, 0, n)
	{
		REPD(j, 0, n)
		{
			char c;
			cin >> c;
			if (c == '-')
			{
				a[i][j] = -1LL;
			}
			else
			{
				a[i][j] = (ll)(c - 'a');
			}
		}
	}

	auto res = make_multiple_vector<2, ll>(n, n, -1LL);
	queue<pair<ll, ll>> q;
	REPD(i, 0, n)
	{
		q.emplace(i, i);
		res[i][i] = 0;
	}

	REPD(i, 0, n)
	{
		REPD(j, 0, n)
		{
			if (i != j)
			{
				if (a[i][j] != -1LL)
				{
					res[i][j] = 1;
					q.emplace(i, j);
				}
			}
		}
	}
	while (!q.empty())
	{
		auto [x, y] = q.front();
		q.pop();
		ll len = res[x][y];
		REPD(i, 0, n)
		{
			REPD(j, 0, n)
			{
				if (res[i][j] != -1LL)
				{
					continue;
				}
				if (a[i][x] != -1LL && a[y][j] != -1LL && a[i][x] == a[y][j])
				{
					if (res[i][j] != -1LL)
					{
						continue;
					}
					res[i][j] = len + 2LL;
					q.emplace(i, j);
				}
			}
		}
	}

	REPD(i, 0, n)
	{
		REPD(j, 0, n)
		{
			cout << res[i][j];
			if (j + 1 < n)
			{
				cout << " ";
			}
			else
			{
				cout << endl;
			}
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
