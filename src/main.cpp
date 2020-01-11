//include
//------------------------------------------
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
#include <string>
#include <cstring>
#include <ctime>

#include <stdexcept>

using namespace std;

// type alias
using ll = long long;
using ull = unsigned long long;
using comp = complex<double>;

const ll MOD = 1000000007LL;
const double PI = 3.14159265358979323846;

//conversion
//------------------------------------------
inline int toint(string s) { int v; istringstream sin(s); sin >> v; return v; }
template<class t> inline string tostring(t x) { ostringstream sout; sout << x; return sout.str(); }

//debug
#define DUMP(x)  cerr << #x << " = " << (x) << endl
#define DEBUG(x) cerr << #x << " = " << (x) << " (l" << __line__ << ")" << " " << __file__ << endl

// functions and classes
using Edge = pair<ll, ll>;

//main function
int main()
{
	cin.tie(0);
	ios::sync_with_stdio(false);

	ll N, M;
	cin >> N >> M;

	vector<vector<ll>> edges(N);
	set<Edge> edge_set;
	ll s, t;
	for (ll i = 0; i < M; ++i)
	{
		cin >> s >> t;
		--s, --t;
		edges[s].emplace_back(t);
		edge_set.insert({ s, t });
	}

	vector<double> ps(N);
	ps[0] = 1.0;
	for (ll i = 1; i < N; ++i)
	{
		for (ll j = 0; j < i; ++j)
		{
			if (edge_set.count({ j, i }) == 0LL )
				continue;
			ps[i] += ps[j] / edges[j].size();
		}
	}

	vector<double> pns(N, 1LL << 60);
	for (ll i = 0; i < N; ++i)
	{
		if (edges[i].size() == 0LL) continue;
		pns[i] = ps[i] / edges[i].size();
	}

	vector<double> pnss(N, 1LL << 60);
	for (ll i = 0; i < N; ++i)
	{
		if (edges[i].size() == 0LL) continue;
		pnss[i] = pns[i] * (*min_element(edges[i].begin(), edges[i].end()) - i);
	}

	s = distance(pnss.begin(), min_element(pnss.begin(), pnss.end()));
	t = distance(edges[s].begin(), min_element(edges[s].begin(), edges[s].end()));
	edges[s].erase(min_element(edges[s].begin(), edges[s].end()));

	vector<double> es(N);
	es[N - 1LL] = 0.0;
	for (ll i = N - 2LL; i >= 0; --i)
	{
		for (ll j = i + 1; j < N; ++j)
		{

		}
	}

	return 0;
}
