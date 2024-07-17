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

class TrieTree
{
	vector<vector<ll>> edges;
	vector<ll> counts;
	ll effective_count;

public:
	TrieTree(ll N) : edges(N, vector<ll>(26LL, -1LL)), counts(N), effective_count(1LL){};
	void add(string s)
	{
		ll prev_idx = 0;
		ll curr_idx;

		counts[prev_idx]++;
		REPI(ch, s)
		{
			ll alphabet_number = ll(ch - 'a');
			if (edges[prev_idx][alphabet_number] == -1LL)
			{
				edges[prev_idx][alphabet_number] = effective_count++;
			}
			curr_idx = edges[prev_idx][alphabet_number];
			counts[curr_idx]++;
			prev_idx = curr_idx;
		}
	};

	ll dfs(ll idx, ll length)
	{
		ll res = 0LL;
		ll collected_count = counts[idx] * (counts[idx] - 1LL) / 2LL;
		REPD(i, 0, edges[idx].size())
		{
			ll next_idx = edges[idx][i];
			if (next_idx == -1LL)
			{
				continue;
			}
			if ((i + 1 >= edges[idx].size()) || (next_idx != edges[idx][i + 1LL]))
			{
				res += dfs(next_idx, length + 1LL);
				collected_count -= counts[next_idx] * (counts[next_idx] - 1LL) / 2LL;
			}
		}

		res += collected_count * length;
		return res;
	}
};

int solve()
{
	ll N;
	cin >> N;

	TrieTree trie_tree(300001LL);

	string S;
	REPD(i, 0, N)
	{
		cin >> S;
		trie_tree.add(S);
	}

	ll res = trie_tree.dfs(0LL, 0LL);

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

ll dfs(vector<vector<ll>> &edges, ll idx, ll node_size, ll length)
{
	ll res = 0LL;
	ll collected_count = node_size * (node_size - 1LL) / 2LL;
	ll next_node_size = 0;
	REPD(i, 0, edges[idx].size())
	{
		ll next_idx = edges[idx][i];
		next_node_size++;
		if ((i + 1 >= edges[idx].size()) || (next_idx != edges[idx][i + 1LL]))
		{
			res += dfs(edges, next_idx, next_node_size, length + 1LL);
			collected_count -= next_node_size * (next_node_size - 1LL) / 2LL;
			next_node_size = 0;
		}
	}

	res += collected_count * length;
	return res;
}

int solve()
{
	ll N;
	cin >> N;

	auto edges = make_multiple_vector(0LL, 300001, 0);
	map<string, ll> str2idx;
	str2idx[""] = 0LL;

	string S;
	REPD(i, 0, N)
	{
		cin >> S;
		string prev_str = "";
		string curr_str = "";

		REPI(ch, S)
		{
			curr_str += ch;
			if (str2idx.count(curr_str) == 0LL)
			{
				str2idx[curr_str] = str2idx.size();
			}
			auto prev_idx = str2idx[prev_str];
			auto curr_idx = str2idx[curr_str];

			edges[prev_idx].push_back(curr_idx);
			prev_str = curr_str;
		}
	}
	REPD(i, 0, edges.size())
	{
		sort(edges[i].begin(), edges[i].end());
	}

	ll res = dfs(edges, 0LL, N, 0LL);

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
