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

	ll N, X, Y;
	cin >> N >> X >> Y;
	--X, --Y;

	vector<ll> res(N);
	ll val;
	for (ll j = 0; j < N; ++j) {
		for (ll i = 0; i < j; ++i) {
			if (i <= X) {
				if (j <= X) {
					val = j - i;
				}
				else if (j <= Y) {
					val = min({ j - i, X - i + 1 + Y - j});
				}
				else {
					val = X - i + 1 + j - Y;
				}
				++res[val];
			}
			else if (i <= Y) {
				if (j <= Y) {
					val = min({ j - i, i - X + 1 + Y - j });
				}
				else {
					val = min({ j - i, i - X + 1 + j - Y });
				}
				++res[val];
			}
			else {
				val = j - i;
				++res[val];
			}
		}
	}
		
	for (ll i = 1; i < N; ++i) {
		cout << res[i] << endl;
	}

	return 0;
}
