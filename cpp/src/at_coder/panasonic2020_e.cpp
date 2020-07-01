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

	string a, b, c;
	cin >> a >> b >> c;

	ll base = 50000;
	vector<bool> ab_matched(base * 2, true);
	vector<bool> ac_matched(base * 2, true);
	vector<bool> bc_matched(base * 2, true);

	ll i, j;
	REP (i, a.size()) {
		REP(j, b.size()) {
			if (a[i] != '?' && b[j] != '?' && a[i] != b[j]) {
				ab_matched[i - j + base] = false;
			}
		}
	}
	REP(i, a.size()) {
		REP(j, c.size()) {
			if (a[i] != '?' && c[j] != '?' && a[i] != c[j]) {
				ac_matched[i - j + base] = false;
			}
		}
	}
	REP(i, b.size()) {
		REP(j, c.size()) {
			if (b[i] != '?' && c[j] != '?' && b[i] != c[j]) {
				bc_matched[i - j + base] = false;
			}
		}
	}

	ll len_a = a.size();
	ll len_b = b.size();
	ll len_c = c.size();

	ll res = 1LL << 60LL;
	ll length;
	for (i = -4000; i <= 4000; ++i) {
		for (j = -4000; j <= 4000; ++j) {
			if (ab_matched[i + base] && ac_matched[j + base] && bc_matched[j - i + base]) {
				length = max(len_a, max(i + len_b, j + len_c)) - min(0LL, min(i, j));
				res = min(res, length);
			}
		}
	}

	cout << res << endl;

	return 0;
}
