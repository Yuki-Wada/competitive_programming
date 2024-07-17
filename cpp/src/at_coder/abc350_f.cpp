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

string dfs(vector<vector<ll>> &edges, vector<ll> &parent_nodes, string &S, ll node, bool is_even)
{
	if (edges[node].size() == 0LL && S[node - 1LL] != '(')
	{
		auto ch = S[node - 1LL];
		if (!is_even)
		{
			return string(1, ch);
		}
		if (ll(ch) - ll('a') >= 0LL && ll(ch) - ll('a') <= 25LL)
		{
			ch = char(ll(ch) - ll('a') + ll('A'));
			return string(1, ch);
		}
		if (ll(ch) - ll('A') >= 0LL && ll(ch) - ll('A') <= 25LL)
		{
			ch = char(ll(ch) - ll('A') + ll('a'));
			return string(1, ch);
		}
		return "";
	}

	string res = "";
	REPD(i, 0, edges[node].size())
	{
		ll idx = is_even ? i : edges[node].size() - i - 1LL;
		ll next_node = edges[node][idx];
		res += dfs(edges, parent_nodes, S, next_node, !is_even);
	}
	return res;
}

int solve()
{
	string S;
	cin >> S;

	vector<vector<ll>> edges(S.size() + 1LL);
	vector<ll> parent_nodes(S.size() + 1LL, -1LL);
	parent_nodes[0] = 0;

	ll parent = 0;
	REPD(i, 1, S.size() + 1LL)
	{
		auto ch = S[i - 1LL];
		if (S[i - 1LL] == ')')
		{
			parent = parent_nodes[parent];
		}
		else
		{
			edges[parent].emplace_back(i);
			parent_nodes[i] = parent;
			if (ch == '(')
			{
				parent = i;
			}
		}
	}

	string res = dfs(edges, parent_nodes, S, 0, true);

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
