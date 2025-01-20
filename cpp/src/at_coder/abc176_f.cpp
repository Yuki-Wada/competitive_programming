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

ll N;
ll1d As;
vector<llpair> replace_idxs;
ll3d dps;
ll triple_same_count = 0;

bool chmax(ll &v1, ll v2)
{
	bool value_changed = v1 < v2;
	v1 = max(v1, v2);
	return value_changed;
}
void update_case_1_pick(ll p, ll q, ll r)
{
	auto val = max({dps[0][N][N], dps[0][p][p] + 1LL});
	if (chmax(dps[1][q][r], val))
	{
		replace_idxs.emplace_back(q, r);
	}
	chmax(dps[1][q][N], val);
	chmax(dps[1][N][r], val);

	if (chmax(dps[1][r][q], val))
	{
		replace_idxs.emplace_back(r, q);
	}
	chmax(dps[1][r][N], val);
	chmax(dps[1][N][q], val);
	chmax(dps[1][N][N], val);
}

void update_case_2_pick(ll p, ll q, ll r)
{
	REPD(i, 0, N)
	{
		auto val = max({dps[0][N][i], dps[0][p][i] + (p == q ? 1LL : 0LL)});
		if (chmax(dps[1][r][i], val))
		{
			replace_idxs.emplace_back(r, i);
		}
		chmax(dps[1][r][N], val);
		chmax(dps[1][N][i], val);

		val = max({dps[0][i][N], dps[0][i][p] + (p == q ? 1LL : 0LL)});
		if (chmax(dps[1][i][r], val))
		{
			replace_idxs.emplace_back(i, r);
		}
		chmax(dps[1][i][N], val);
		chmax(dps[1][N][r], val);
		chmax(dps[1][N][N], val);
	}
}

void trans()
{
	REPI(idxs, replace_idxs)
	{
		auto [p, q] = idxs;
		dps[0][p][q] = dps[1][p][q];
	}
	REPD(i, 0, N)
	{
		dps[0][i][N] = dps[1][i][N];
		dps[0][N][i] = dps[1][N][i];
	}
	dps[0][N][N] = dps[1][N][N];
}

int solve()
{
	cin >> N;

	As = make_multiple_vector(0LL, N * 3LL);
	dps = make_multiple_vector(-N * 3LL, 2LL, N + 1LL, N + 1LL);

	REPD(i, 0, N * 3LL)
	{
		cin >> As[i];
		--As[i];
	}

	ll a, b, p, q, r;
	a = As[0] < As[1] ? As[0] : As[1];
	b = As[0] < As[1] ? As[1] : As[0];
	dps[0][a][b] = dps[0][a][N] = dps[0][N][b] = 0;
	dps[0][b][a] = dps[0][b][N] = dps[0][N][a] = 0;
	dps[0][N][N] = 0;
	dps[1][a][b] = dps[1][a][N] = dps[1][N][b] = 0;
	dps[1][b][a] = dps[1][b][N] = dps[1][N][a] = 0;
	dps[1][N][N] = 0;
	REPD(i, 0, N - 1LL)
	{
		replace_idxs.resize(0LL);
		p = As[i * 3LL + 2LL];
		q = As[i * 3LL + 3LL];
		r = As[i * 3LL + 4LL];

		if (p == q && q == r)
		{
			triple_same_count++;
			continue;
		}
		update_case_1_pick(p, q, r);
		update_case_1_pick(q, r, p);
		update_case_1_pick(r, p, q);
		update_case_2_pick(p, q, r);
		update_case_2_pick(q, r, p);
		update_case_2_pick(r, p, q);
		trans();
	}
	r = As.back();
	dps[0][r][r]++;

	ll res = 0;
	REPD(i, 0, N)
	{
		REPD(j, 0, N)
		{
			res = max(res, dps[0][i][j]);
		}
	}

	cout << res + triple_same_count << endl;
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
