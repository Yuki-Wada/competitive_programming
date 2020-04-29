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

// computational complexity: o(log(max(a, b))) 
inline ull get_gcd(ull a, ull b)
{
	if (b == 0)
	{
		return a;
	}
	return get_gcd(b, a % b);
}

//main function
int main()
{
	cin.tie(0);
	ios::sync_with_stdio(false);

	ll N, X, D;
	cin >> N >> X >> D;

	if (D == 0) {
		if (X == 0) {
			cout << 1 << endl;
		}
		else {
			cout << N + 1 << endl;
		}
		return 0;
	}

	ll d = get_gcd(abs(X), abs(D));
	X /= d;
	D /= d;
	if (D < 0) {
		X *= -1;
		D *= -1;
	}

	ll res = 0;
	ll count, prev_val;
	vector<pair<ll, ll>> boundaries;
	for (ll i = 0; i <= N; ++i) {
		if (i >= D) break;
		boundaries = vector<pair<ll, ll>>();
		for (ll j = 0; i + D * j <= N; ++j) {
			boundaries.emplace_back(
				X * j + (i + D * j - 1) * (i + D * j) / 2, 1
			);
			boundaries.emplace_back(
				X * j + ((N - 1) + (N - 1 - (i + D * j - 1))) * (i + D * j) / 2 + 1, -1
			);
		}
		sort(boundaries.begin(), boundaries.end());

		count = 0;
		for (ll idx = 0; idx < boundaries.size(); ++idx) {
			if (count == 0) {
				prev_val = boundaries[idx].first;
			}
			count += boundaries[idx].second;
			if (count == 0) {
				res += boundaries[idx].first - prev_val;
			}
		}
	}

	cout << res << endl;

	return 0;
}
