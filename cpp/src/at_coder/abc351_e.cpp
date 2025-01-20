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

pair<vector<ll>, vector<ll>> compress_coordinates(const vector<ll> &As)
{
	ll N = As.size();
	vector<pair<ll, ll>> items(N);
	for (ll i = 0; i < N; ++i)
	{
		items[i] = make_pair(As[i], i);
	}
	sort(items.begin(), items.end());

	vector<ll> compressed_coords(N);
	vector<ll> compression_table;

	ll prev_a = -1;
	ll compressed = -1;
	for (ll i = 0; i < N; ++i)
	{
		auto [a, idx] = items[i];
		if (i == 0LL || prev_a != a)
		{
			compression_table.push_back(a);
			++compressed;
			prev_a = a;
		}

		compressed_coords[idx] = compressed;
	}

	return {compressed_coords, compression_table};
}

ll compute_dist_sum(const ll1d &vs)
{
	auto [compressed_coords, compression_table] = compress_coordinates(vs);

	if (compression_table.size() <= 1LL)
	{
		return 0;
	}

	ll1d coord_counts(compression_table.size());
	for (ll i = 0; i < compressed_coords.size(); ++i)
	{
		auto coord = compressed_coords[i];
		coord_counts[coord]++;
	}

	ll res = 0;
	for (ll i = 1; i < compression_table.size(); ++i)
	{
		auto prev_coord = compression_table[0];
		auto curr_coord = compression_table[i];
		auto curr_count = coord_counts[i];

		res += (curr_coord - prev_coord) * curr_count;
	}

	ll res_sum = res * coord_counts[0];
	ll remaining_count = vs.size() - coord_counts[0];
	for (ll i = 1; i < compression_table.size(); ++i)
	{
		auto prev_coord = compression_table[i - 1LL];
		auto curr_coord = compression_table[i];
		// auto prev_count = coord_counts[i - 1];
		auto curr_count = coord_counts[i];

		res -= remaining_count * (curr_coord - prev_coord);
		remaining_count -= curr_count;
		res_sum += res * curr_count;
	}

	res_sum /= 2LL;
	return res_sum;
}

int solve()
{

	ll N;
	ll2d vals;

	cin >> N;
	vals.resize(4);

	ll x, y, xpy, xmy;
	REPD(i, 0, N)
	{
		cin >> x >> y;
		xpy = x + y;
		xmy = x - y;
		if (xpy % 2LL == 0LL)
		{
			vals[0].emplace_back(xpy);
			vals[1].emplace_back(xmy);
		}
		else
		{
			vals[2].emplace_back(xpy);
			vals[3].emplace_back(xmy);
		}
	}

	ll res = 0;
	REPD(i, 0, 4)
	{
		res += compute_dist_sum(vals[i]);
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
