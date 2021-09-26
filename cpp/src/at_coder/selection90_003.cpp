//include
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

//debug
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

pair<ll, ll> get_max_length(ll node, ll N, const vector<vector<ll>> &edges)
{
	vector<ll> lengths(N, -1);
	stack<ll> s;
	s.emplace(node);
	lengths[node] = 0LL;
	while (!s.empty())
	{
		node = s.top();
		s.pop();
		for (ll i = 0; i < edges[node].size(); ++i)
		{
			if (lengths[edges[node][i]] == -1LL)
			{
				s.emplace(edges[node][i]);
				lengths[edges[node][i]] = lengths[node] + 1LL;
			}
		}
	}

	auto max_iter = max_element(lengths.begin(), lengths.end());

	return make_pair(distance(lengths.begin(), max_iter), *max_iter);
}

int solve()
{
	ll N;
	cin >> N;

	vector<vector<ll>> edges(N);

	ll a, b;
	for (ll i = 0; i < N - 1LL; ++i)
	{
		cin >> a >> b;
		--a, --b;
		edges[a].emplace_back(b);
		edges[b].emplace_back(a);
	}

	ll node = 0, max_length;
	tie(node, ignore) = get_max_length(node, N, edges);
	tie(ignore, max_length) = get_max_length(node, N, edges);

	cout << max_length + 1LL << endl;

	return 0;
}

//main function
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
