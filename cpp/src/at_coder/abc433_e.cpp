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
	using value_type = std::decay_t<decltype(make_multiple_vector<N - 1, T>(args...))>;
	return vector<value_type>(size, make_multiple_vector<N - 1, T>(args...));
}

#include <optional>

std::optional<ll2d> solve()
{
	ll n, m;
	cin >> n >> m;
	ll1d x(n);
	ll1d y(m);
	bool invalid = false;
	map<ll, ll> x_pos;
	map<ll, ll> y_pos;
	REPD(i, 0, n)
	{
		cin >> x[i];
		if (x_pos.count(x[i]) != 0)
		{
			invalid = true;
		}
		x_pos[x[i]] = i;
	}
	REPD(i, 0, m)
	{
		cin >> y[i];
		if (y_pos.count(y[i]) != 0)
		{
			invalid = true;
		}
		y_pos[y[i]] = i;
	}
	if (invalid)
	{
		return std::nullopt;
	}

	vector<vector<pair<ll, ll>>> lists = vector<vector<pair<ll, ll>>>(m * n + 1ULL, vector<pair<ll, ll>>(0ULL, make_pair(0LL, 0LL)));
	for (ll i = 0; i < n; i++)
	{
		for (ll j = 0; j < m; j++)
		{
			auto idx = min(x[i], y[j]);
			lists[idx].emplace_back(i, j);
		}
	}

	vector<pair<ll, ll>> residuals = vector<pair<ll, ll>>(0ULL);
	residuals.reserve(m * n);
	ll2d results = vector<vector<ll>>(n, vector<ll>(m, 0LL));
	for (ll num = m * n; num >= 1; num--)
	{
		if (x_pos.count(num) != 0 && y_pos.count(num) != 0)
		{
			bool placed = false;
			for (ll j = 0; j < lists[num].size(); j++)
			{
				auto [xi, yj] = lists[num][j];
				if (!placed && xi == x_pos[num] && yj == y_pos[num])
				{
					results[xi][yj] = num;
					placed = true;
				}
				else
				{
					residuals.emplace_back(xi, yj);
				}
			}
			if (!placed)
			{
				return std::nullopt;
			}
		}
		else if (x_pos.count(num) != 0)
		{
			bool placed = false;
			for (ll j = 0; j < lists[num].size(); j++)
			{
				auto [xi, yj] = lists[num][j];
				if (!placed && xi == x_pos[num])
				{
					results[xi][yj] = num;
					placed = true;
				}
				else
				{
					residuals.emplace_back(xi, yj);
				}
			}
			if (!placed)
			{
				return std::nullopt;
			}
		}
		else if (y_pos.count(num) != 0)
		{
			bool placed = false;
			for (ll j = 0; j < lists[num].size(); j++)
			{
				auto [xi, yj] = lists[num][j];
				if (!placed && yj == y_pos[num])
				{
					results[xi][yj] = num;
					placed = true;
				}
				else
				{
					residuals.emplace_back(xi, yj);
				}
			}
			if (!placed)
			{
				return std::nullopt;
			}
		}
		else
		{
			for (ll j = 0; j < lists[num].size(); j++)
			{
				auto [xi, yj] = lists[num][j];
				residuals.emplace_back(xi, yj);
			}
			if (residuals.size() == 0)
			{
				return std::nullopt;
			}
			auto [xi, yj] = residuals.back();
			residuals.pop_back();
			results[xi][yj] = num;
		}
	}

	return results;
}

// main function
int main()
{
	cin.tie(0);
	ios::sync_with_stdio(false);

	// cin >> N >> x >> y;
	// solve();

	ll t;
	cin >> t;

	REPD(i, 0, t)
	{
		auto r = solve();
		if (!r.has_value())
		{
			cout << "No" << endl;
			continue;
		}
		else
		{
			cout << "Yes" << endl;
			auto mat = r.value();
			REPD(j, 0, mat.size())
			{
				REPD(k, 0, mat[j].size())
				{
					cout << mat[j][k];
					if (k != mat[j].size() - 1)
					{
						cout << " ";
					}
				}
				cout << endl;
			}
		}
	}

	return 0;
}
