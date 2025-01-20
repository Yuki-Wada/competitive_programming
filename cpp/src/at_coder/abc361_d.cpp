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
static const ll MOD = 998244353LL;
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

#define MAX_VALUE 9223372036854787LL

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

ll calc_idx(string str)
{
	ll n = str.size() - 2LL;
	ll space_idx = 1LL << n;
	ll idx = 0;
	ll pow2 = 1;
	REPD(i, 0, str.size())
	{
		auto ch = str[i];
		if (ch == 'B' || ch == 'W')
		{
			idx += (ch == 'W' ? 1LL : 0LL) * pow2;
			pow2 *= 2LL;
		}
		else
		{
			idx += space_idx * i;
			space_idx = 0;
		}
	}
	return idx;
}

string swap_string(string str, ll i, ll j)
{
	ll tmp_ch0 = str[i];
	ll tmp_ch1 = str[i + 1LL];
	str[i] = str[j];
	str[i + 1LL] = str[j + 1LL];
	str[j] = tmp_ch0;
	str[j + 1LL] = tmp_ch1;
	return str;
}

ll calc_dist(ll N, string S, string T)
{
	ll node_count = (1LL << N) * (N + 1LL);
	auto visited = make_multiple_vector(false, node_count);
	ll start_idx = calc_idx(S);
	ll end_idx = calc_idx(T);

	if (start_idx == end_idx)
	{
		return 0LL;
	}

	queue<pair<string, ll>> que;
	que.emplace(S, 0LL);
	visited[start_idx] = true;

	while (!que.empty())
	{
		auto [currS, dist] = que.front();
		que.pop();

		ll space_idx = 0;
		REPD(i, 0, currS.size())
		{
			if (currS[i] == '.')
			{
				space_idx = i;
				break;
			}
		}

		REPD(i, 0, currS.size() - 1LL)
		{
			if (currS[i] == '.' || currS[i + 1LL] == '.')
			{
				continue;
			}

			auto nextS = swap_string(currS, i, space_idx);
			auto next_idx = calc_idx(nextS);
			if (visited[next_idx])
			{
				continue;
			}
			if (next_idx == end_idx)
			{
				return dist + 1LL;
			}
			que.emplace(nextS, dist + 1LL);
			visited[next_idx] = true;
		}
	}
	return -1LL;
}

int solve()
{
	ll N;
	cin >> N;

	string S, T;
	cin >> S >> T;

	S += "..";
	T += "..";

	auto res = calc_dist(N, S, T);
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
