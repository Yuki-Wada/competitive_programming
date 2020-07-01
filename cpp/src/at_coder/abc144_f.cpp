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

// for loop
#define REP(i, n) for ((i) = 0;(i) < (ll)(n);(i)++)

//debug
#define DUMP(x)  cerr << #x << " = " << (x) << endl
#define DEBUG(x) cerr << #x << " = " << (x) << " (l" << __line__ << ")" << " " << __file__ << endl

//main function
int main()
{
	cin.tie(0);
	ios::sync_with_stdio(false);

	ll N, M;
	cin >> N >> M;

	vector<double> node_probs(N, 0.0);
	vector<vector<double>> edge_expects(N, vector<double>(N, 0.0));

	vector<vector<ll>> edges(N);
	vector<vector<ll>> rev_edges(N);
	ll s, t;
	for (ll i = 0; i < M; ++i) {
		cin >> s >> t;
		--s, --t;
		edges[s].emplace_back(t);
		rev_edges[t].emplace_back(s);
	}

	node_probs[0] = 1.0;
	for (ll i = 0; i < N; ++i) {
		for (ll j = 0; j < edges[i].size(); ++j) {
			node_probs[edges[i][j]] += node_probs[i] / double(edges[i].size());
		}
	}

	for (ll i = N - 1; i >= 0; --i) {
		double node_expect = 0.0;
		for (ll j = 0; j < edges[i].size(); ++j) {
			edge_expects[i][edges[i][j]] /= double(edges[i].size());
			node_expect += edge_expects[i][edges[i][j]];
		}
		for (ll j = 0; j < rev_edges[i].size(); ++j) {
			edge_expects[rev_edges[i][j]][i] = 1.0 + node_expect;
		}
	}

	double max_val = 0.0;
	for (ll i = 0; i < N; ++i) {
		double node_expect = 0.0;
		for (ll j = 0; j < edges[i].size(); ++j) {
			node_expect += edge_expects[i][edges[i][j]];
		}
		for (ll j = 0; j < edges[i].size(); ++j) {
			if (edges[i].size() > 1LL) {
				double diff = node_expect;
				diff -= (node_expect - edge_expects[i][edges[i][j]]) *
					double(edges[i].size()) /
					(double(edges[i].size()) - 1.0);
				max_val = max(max_val, node_probs[i] * diff);
			}
		}
	}

	double res = 0.0;
	for (ll i = 0; i < edges[0].size(); ++i) {
		res += edge_expects[0][edges[0][i]];
	}
	res -= max_val;

	cout << fixed << setprecision(10) << res << endl;

	return 0;
}
