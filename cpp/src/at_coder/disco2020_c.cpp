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

int solve() {
	ll H, W, K;
	cin >> H >> W >> K;

	vector<string> Ss(H);
	for (ll i = 0; i < H; ++i) {
		cin >> Ss[i];
	}

	vector<vector<ll>> res(H, vector<ll>(W, -1));
	ll first_cake_row = -1;
	ll area_name = 0LL;
	for (ll i = 0; i < H; ++i) {
		bool cake_found = false;
		for (ll j = 0; j < W; ++j) {
			if (Ss[i][j] == '#') {
				cake_found = true;
				break;
			}
		}
		if (!cake_found) {
			if (first_cake_row != -1) {
				for (ll j = 0; j < W; ++j) {
					res[i][j] = res[i - 1][j];
				}
			}
		}
		else {
			if (first_cake_row == -1) {
				first_cake_row = i;
			}
			++area_name;
			bool first_cake_found = false;
			for (ll j = 0; j < W; ++j) {
				if (Ss[i][j] == '#') {
					if (!first_cake_found) {
						first_cake_found = true;
					}
					else {
						++area_name;
					}
				}
				res[i][j] = area_name;
			}
		}
	}

	for (ll i = first_cake_row - 1; i >= 0; --i) {
		for (ll j = 0; j < W; ++j) {
			res[i][j] = res[i + 1][j];
		}
	}

	for (ll i = 0; i < H; ++i) {
		for (ll j = 0; j < W; ++j) {
			cout << res[i][j];
			if (j + 1LL < W) {
				cout << " ";
			}
		}
		cout << endl;
	}

	return 0;
}

//main function
int main()
{
	cin.tie(0);
	ios::sync_with_stdio(false);

	solve();

	return 0;
}
