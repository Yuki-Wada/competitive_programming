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

	ll mod = 1000000007LL;
	ll N;
	cin >> N;

	vector<ll> Cs(N);
	for (ll i = 0; i < N; ++i) {
		cin >> Cs[i];
	}
	map<ll, vector<ll>> pos;
	for (ll i = 0; i < N; ++i) {
		if (pos.count(Cs[i]) == 0) {
			pos[Cs[i]] = vector<ll>();
		}
		pos[Cs[i]].emplace_back(i);
	}

	vector<ll> dps(N + 1);
	dps[0] = 1;
	for (ll i = 0; i < N; ++i) {
		auto idx = distance(pos[Cs[i]].begin(), lower_bound(pos[Cs[i]].begin(), pos[Cs[i]].end(), i));
		if (idx == 0 || pos[Cs[i]][idx - 1] == i - 1) {
			dps[i + 1] = dps[i];
		}
		else {
			dps[i + 1] = (dps[i] + dps[pos[Cs[i]][idx - 1] + 1]) % mod;
		}
	}

	cout << dps[N] << endl;

	return 0;
}
