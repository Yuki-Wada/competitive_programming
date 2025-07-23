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

ll N, Q;

int solve()
{
	cin >> N >> Q;
	ll1d Hs(N);
	REPD(i, 0, N)
	{
		ll h;
		cin >> h;
		Hs[i] = h;
	}

	vector<tuple<ll, ll, ll>> queries;
	REPD(i, 0, Q)
	{
		ll l, r;
		cin >> l >> r;
		--l, --r;
		queries.emplace_back(l, r, i);
	}
	sort(queries.begin(), queries.end(), greater<tuple<ll, ll, ll>>());

	ll1d results(Q);
	ll q_idx = 0;
	pair1d visible_idxs;
	REPD(i, 0, N)
	{
		while (q_idx < Q)
		{
			auto [l, r, idx] = queries[q_idx];
			if (l == N - i - 1LL)
			{
				ll l_idx = 0, r_idx = visible_idxs.size() - 1LL, mid_idx = (l_idx + r_idx) / 2LL;
				ll res = 0;
				if (visible_idxs[r_idx].first >= r + 1LL)
					res = visible_idxs.size();
				else if (visible_idxs[l_idx].first < r + 1LL)
					res = 0;
				else
				{
					while (r_idx - l_idx >= 2LL)
					{
						if (visible_idxs[mid_idx].first >= r + 1LL)
							l_idx = mid_idx;
						else
							r_idx = mid_idx;
						mid_idx = (l_idx + r_idx) / 2LL;
					}
					res = l_idx + 1LL;
				}

				results[idx] = res;
				++q_idx;
			}
			else
			{
				break;
			}
		}

		auto hi = Hs[N - i - 1LL];
		while (!visible_idxs.empty())
		{
			if (visible_idxs.back().second < hi)
				visible_idxs.pop_back();
			else
				break;
		}
		visible_idxs.emplace_back(N - i - 1LL, hi);
	}

	REPD(i, 0, Q)
	cout << results[i] << endl;

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
