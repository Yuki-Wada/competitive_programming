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

//main function
int main()
{
	cin.tie(0);
	ios::sync_with_stdio(false);

	ll N, K, C;
	string S;
	cin >> N >> K >> C >> S;

	vector<ll> wds(N);
	vector<vector<ll>> k_to_idx(K + 2);
	for (ll i = 0; i < N; ++i) {
		if (S[i] == 'o') {
			wds[i] = 1LL;
			if (i - C - 1LL >= 0) {
				wds[i] += wds[i - C - 1LL];
			}
			if (wds[i] < K + 1LL) {
				k_to_idx[wds[i]].emplace_back(i);
			}
			else {
				k_to_idx[K + 1LL].emplace_back(i);
			}
		}
		else if (S[i] == 'x') {
			if (i - 1LL >= 0) {
				wds[i] += wds[i - 1LL];
			}
		}
	}

	if (k_to_idx[K + 1].size() > 0LL) {
		cout << endl;
		return 0;
	}

	stack<ll> res;
	ll val = N;
	for (ll i = K; i > 0; --i) {
		auto iter = upper_bound(k_to_idx[i].begin(), k_to_idx[i].end(), val);
		auto dist = distance(k_to_idx[i].begin(), --iter);
		val = (*iter) - C - 1LL;
		if (dist == 0LL) {
			res.push(*iter + 1);
		}
	}
	while (!res.empty()) {
		cout << res.top() << endl;
		res.pop();
	}

	return 0;
}
