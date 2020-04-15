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

	ll K;
	cin >> K;

	if (K < 10) {
		cout << K << endl;
		return 0;
	}

	ll k;
	vector<vector<ll>> dps(32, vector<ll>(12, 0));
	ll num, digit;
	num = 0;
	for (digit = 0; digit < 10; ++digit) {
		ll idx = digit + 1;
		auto val = 1;
		dps[num][idx] = val;
	}
	++num;
	k = 9;

	for (; num < 32; ++num) {
		for (digit = 0; digit < 10; ++digit) {
			ll idx = digit + 1;
			auto val = dps[num - 1][idx - 1] + dps[num - 1][idx] + dps[num - 1][idx + 1];
			dps[num][idx] = val;
			if (digit != 0) {
				if (k + val < K) {
					k += val;
				}
				else {
					goto loop_end;
				}
			}
		}
	}
loop_end:
	ll res, pow = 1;
	for (ll i = 0; i < num; ++i) {
		pow *= 10LL;
	}
	res = digit * pow;
	pow /= 10LL;

	ll lunlun_count = K - k;
	for (; num > 0; --num) {
		for (ll i = 0; i < 3; ++i) {
			ll curr_digit = digit + i - 1;
			ll curr_idx = curr_digit + 1;
			if (lunlun_count <= dps[num - 1][curr_idx]) {
				digit = curr_digit;
				res += digit * pow;
				pow /= 10;
				break;
			}
			lunlun_count -= dps[num - 1][curr_idx];
		}
	}

	cout << res << endl;

	return 0;
}
