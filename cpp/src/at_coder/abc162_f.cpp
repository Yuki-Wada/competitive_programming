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

	ll N;
	cin >> N;

	vector<ll> as(N);
	for (ll i = 0; i < N; ++i) {
		cin >> as[i];
	}

	vector<ll> ceil_values(N + 1);
	ceil_values[0] = 0;
	ceil_values[1] = as[0];
	ceil_values[2] = max(as[0], as[1]);
	for (ll i = 3; i <= N; ++i) {
		if (i % 2 == 0) {
			ceil_values[i] = max(
				as[i - 1] + ceil_values[i - 2],
				as[i - 2] + ceil_values[i - 3]
			);
		}
		else {
			ceil_values[i] = as[i - 1] + ceil_values[i - 2];
		}

	}

	vector<ll> floor_values(N + 1);
	floor_values[2] = ceil_values[2];
	floor_values[3] = max(max(as[0], as[1]), as[2]);
	for (ll i = 4; i <= N; ++i) {
		if (i % 2 == 0) {
			floor_values[i] = ceil_values[i];
		}
		else {
			floor_values[i] = max(
				max(
					as[i - 1] + floor_values[i - 2],
					as[i - 2] + floor_values[i - 3]
				),
				as[i - 3] + ceil_values[i - 4]
			);
		}
	}

	cout << floor_values[N] << endl;

	return 0;
}
