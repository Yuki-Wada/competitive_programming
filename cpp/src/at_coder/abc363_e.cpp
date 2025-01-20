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

ll H, W, Y;
ll2d areas;
vector2d<bool> queued;
priority_queue<tuple<ll, ll, ll>> pq;

void push_queue(ll i, ll j)
{
	if (!queued[i][j])
	{
		queued[i][j] = true;
		pq.emplace(-areas[i][j], i, j);
	}
}

void update_queue(ll ai, ll aj)
{
	if ((ai + 1LL < H))
	{
		push_queue(ai + 1LL, aj);
	}
	if ((ai - 1LL >= 0LL))
	{
		push_queue(ai - 1LL, aj);
	}
	if ((aj + 1LL < W))
	{
		push_queue(ai, aj + 1LL);
	}
	if ((aj - 1LL >= 0LL))
	{
		push_queue(ai, aj - 1LL);
	}
}

int solve()
{
	cin >> H >> W >> Y;
	areas = make_multiple_vector(0LL, H, W);
	queued = make_multiple_vector(false, H, W);
	REPD(i, 0, H)
	REPD(j, 0, W)
	cin >> areas[i][j];

	REPD(i, 0, H)
	{
		push_queue(i, 0LL);
		push_queue(i, W - 1LL);
	}
	REPD(j, 0, W)
	{
		push_queue(0LL, j);
		push_queue(H - 1LL, j);
	}

	ll res = H * W;
	REPD(y, 1, Y + 1LL)
	{
		while (!pq.empty())
		{
			auto [av, ai, aj] = pq.top();
			av = -av;
			if (av >= y + 1LL)
			{
				break;
			}
			--res;
			pq.pop();
			update_queue(ai, aj);
		}
		cout << res << endl;
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
