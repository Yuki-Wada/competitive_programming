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

// type alias
using ll = long long;
using ull = unsigned long long;
using comp = complex<double>;

// constant
static const ll MOD = 1000000007LL;
// static const ll MOD = (1LL << 61LL) - 1LL;
static const double PI = 3.14159265358979323846;

// conversion
inline ll toint(string s)
{
	ll v;
	istringstream sin(s);
	sin >> v;
	return v;
}
template <class t>
inline string tostring(t x)
{
	ostringstream sout;
	sout << x;
	return sout.str();
}

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

pair<ll, vector<vector<ll>>> minimux_xor(const vector<ll> &bufs, const vector<ll> &group, ll bit_length)
{
	vector<ll> max_results(1LL << bit_length);
	REPD(bit, 0, 1LL << bit_length)
	{
		ll buf;
		ll max_res = 0;
		REPD(i, 0, group.size())
		{
			buf = bufs[group[i]];
			max_res = max(max_res, buf ^ bit);
		}
		max_results[bit] = max_res;
	}
	ll min_max_res = *min_element(max_results.begin(), max_results.end());

	vector<vector<ll>> subgroups;
	REPD(bit, 0, 1LL << bit_length)
	{
		if (max_results[bit] == min_max_res)
		{
			vector<ll> subgroup;
			REPD(i, 0, group.size())
			{
				ll buf;
				buf = bufs[group[i]];
				if ((buf ^ bit) == min_max_res)
				{
					subgroup.emplace_back(group[i]);
				}
			}
			subgroups.emplace_back(subgroup);
		}
	}

	return {min_max_res, subgroups};
}

int solve()
{
	ll N;
	cin >> N;
	vector<ll> As(N);
	REPD(i, 0, N)
	{
		cin >> As[i];
	}

	vector<vector<ll>> prev_groups;
	vector<vector<ll>> curr_groups(1, vector<ll>(N));
	REPD(i, 0, N)
	{
		curr_groups[0][i] = i;
	}

	ll res = 0;
	vector<ll> bufs(N);
	REPD(b, 0, 4)
	{
		REPD(i, 0, N)
		{
			bufs[i] = (As[i] >> ((3LL - b) * 8LL));
			bufs[i] = (bufs[i] & ((1LL << 8LL) - 1LL));
		}

		vector<pair<ll, vector<vector<ll>>>> gp_results;
		ll gp_min_res = MAX_VALUE;
		REPD(i, 0, curr_groups.size())
		{
			auto gp_res = minimux_xor(bufs, curr_groups[i], 8LL);
			gp_results.emplace_back(gp_res);
			gp_min_res = min(gp_min_res, gp_res.first);
		}

		res += (gp_min_res << ((3LL - b) * 8LL));

		prev_groups = vector<vector<ll>>(0);
		REPD(i, 0, gp_results.size())
		{
			auto gp_res = gp_results[i];
			if (gp_min_res == gp_res.first)
			{
				prev_groups.insert(prev_groups.end(), gp_res.second.begin(), gp_res.second.end());
			}
		}

		curr_groups = prev_groups;
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
	// REPD(i, 0, t) solve();

	return 0;
}
