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

ll calc_one_bit_count(ull a) {
	ll res = 0;
	while (a > 0LL) {
		res += (a & 1LL);
		a >>= 1LL;
	}
	return res;
}

//main function
int main()
{
	cin.tie(0);
	ios::sync_with_stdio(false);

	ll N, M;
	cin >> N;

	ll a, b;
	vector<vector<ll>> edges(N);
	for (ll i = 0; i + 1 < N; ++i) {
		cin >> a >> b;
		edges[a - 1].emplace_back(b - 1);
		edges[b - 1].emplace_back(a - 1);
	}

	vector<ll> rev_tree(N, -1LL);
	rev_tree[N - 1] = N - 1;
	queue<ll> queue;
	queue.push(N - 1);
	while (!queue.empty()) {
		ll node = queue.front();
		queue.pop();
		for (auto next : edges[node]) {
			if (rev_tree[next] != -1) continue;
			rev_tree[next] = node;
			queue.push(next);
		}
	}
	vector<ll> edge_bits(N);
	for (ll i = 0; i + 1 < N; ++i) {
		ll node = i;
		ll edge_bit = 0;
		while (node != N - 1) {
			edge_bit += (1LL << node);
			node = rev_tree[node];
		}
		edge_bits[i] = edge_bit;
	}

	cin >> M;
	vector<pair<ll, ll>> restrictions;
	restrictions.reserve(M);
	for (ll i = 0; i < M; ++i) {
		cin >> a >> b;
		restrictions.emplace_back(a - 1, b - 1);
	}

	ll res = 0;
	for (ll i = 0; i < (1LL << M); ++i) {
		ll set = i;
		ll sign = 1;
		ll edge_union = 0;
		for (ll j = 0; j < M; ++j) {
			if (set & 1LL) {
				sign *= -1LL;
				edge_union |= edge_bits[restrictions[j].first] ^ edge_bits[restrictions[j].second];
			}
			set >>= 1LL;
		}
		res += sign * (1LL << (N - 1LL - calc_one_bit_count(edge_union)));
	}

	cout << res << endl;

	return 0;
}
