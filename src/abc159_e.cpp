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

	ll H, W, K;
	cin >> H >> W >> K;

	vector<string> Ss(H);
	for (ll i = 0; i < H; ++i) {
		cin >> Ss[i];
	}

	vector<vector<ll>> accum_white_counts(H, vector<ll>(W + 1));
	for (ll i = 0; i < H; ++i) {
		for (ll j = 0; j < W; ++j) {
			accum_white_counts[i][j + 1] = accum_white_counts[i][j] + (Ss[i][j] == '1' ? 1: 0);
		}
	}

	ll res = 1000000000LL, bits, begin, split, white_counts;
	bool impossible;
	for (ll i = 0; i < (1LL << (H - 1)); ++i) {
		bits = i;
		begin = 0;
		split = 0;
		impossible = false;
		for (ll k = 0; k < H; ++k) {
			if (((bits >> k) & 1LL) == 1LL) ++split;
		}

		for (ll j = 1; j <= W; ++j) {
			white_counts = 0;
			for (ll k = 0; k < H; ++k) {
				white_counts += accum_white_counts[k][j] - accum_white_counts[k][begin];
				if (white_counts > K) {
					if (begin == (j - 1LL)) impossible = true;
					begin = j - 1LL;
					++split;
					break;
				}
				if (((bits >> k) & 1LL) == 1LL) white_counts = 0;
			}
			if (impossible) break;
		}
		if (!impossible) res = min(res, split);
	}

	cout << res << endl;

	return 0;
}
