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

ll BOX_COUNT = 8192;
ll UPPER_COUNT = 2048;
ll N;
ll1d As;
pair1d residual_sums(BOX_COUNT);
pair2d residual_boxes(BOX_COUNT);

ll _f(ll residual_i, ll residual_j)
{
	ll incr = (residual_i + residual_j) / BOX_COUNT;
	auto as = residual_boxes[residual_i];
	auto bs = residual_boxes[residual_j];

	ll res = 0;
	REPD(i, 0, as.size())
	{
		REPD(j, 0, bs.size())
		{
			auto curr_res = as[i].first + bs[j].first + incr;
			if (curr_res == 0LL)
			{
				continue;
			}
			while ((curr_res % 2LL) == 0LL)
			{
				curr_res >>= 1LL;
			}
			curr_res *= as[i].second * bs[j].second;
			res += curr_res;
		}
	}
	return res;
}

ll _f(ll residual_i)
{
	ll incr = (residual_i + residual_i) / BOX_COUNT;
	auto as = residual_boxes[residual_i];

	ll res = 0;
	REPD(i, 0, as.size())
	{
		REPD(j, i, as.size())
		{
			auto curr_res = as[i].first + as[j].first + incr;
			if (curr_res == 0LL)
			{
				continue;
			}
			while ((curr_res % 2LL) == 0LL)
			{
				curr_res >>= 1LL;
			}
			if (i == j)
			{
				curr_res *= as[i].second * (as[i].second + 1LL) / 2LL;
			}
			else
			{
				curr_res *= as[i].second * as[j].second;
			}
			res += curr_res;
		}
	}
	return res;
}

int solve()
{
	cin >> N;
	As.resize(N);

	REPD(i, 0, N)
	{
		ll a;
		cin >> a;
		residual_sums[a % BOX_COUNT].first += a;
		residual_sums[a % BOX_COUNT].second++;
		As[i] = a;
	}
	sort(As.begin(), As.end());
	REPD(i, 0, N)
	{
		auto a = As[i];
		if (i > 0LL && a == As[i - 1LL])
		{
			residual_boxes[a % BOX_COUNT].back().second++;
		}
		else
		{
			residual_boxes[a % BOX_COUNT].emplace_back(a / BOX_COUNT, 1LL);
		}
	}

	ll res = 0;
	REPD(i, 0, BOX_COUNT)
	{
		REPD(j, i, BOX_COUNT)
		{
			if ((i + j) % BOX_COUNT != 0)
			{
				auto residual = i + j;
				ll curr_res;
				if (i == j)
				{
					curr_res = residual_sums[i].first * (residual_sums[j].second + 1LL);
				}
				else
				{
					curr_res = residual_sums[i].first * residual_sums[j].second + residual_sums[j].first * residual_sums[i].second;
				}

				if (curr_res == 0)
				{
					continue;
				}
				while ((residual % 2LL) == 0LL)
				{
					curr_res >>= 1LL;
					residual >>= 1LL;
				}
				res += curr_res;
			}
			else
			{
				if (i == j)
				{
					res += _f(i);
				}
				else
				{
					res += _f(i, j);
				}
			}
		}
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
