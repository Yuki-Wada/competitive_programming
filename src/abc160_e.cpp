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

	ll X, Y, A, B, C;
	cin >> X >> Y >> A >> B >> C;

	vector<pair<ll, ll>> apples;
	apples.reserve(A + B + C);
	ll apple;
	for (ll i = 0; i < A; ++i) {
		cin >> apple;
		apples.emplace_back(apple, 0);
	}
	for (ll i = 0; i < B; ++i) {
		cin >> apple;
		apples.emplace_back(apple, 1);
	}
	for (ll i = 0; i < C; ++i) {
		cin >> apple;
		apples.emplace_back(apple, 2);
	}

	sort(apples.begin(), apples.end(), greater<pair<ll, ll>>());

	ll i = 0;
	ll res = 0;
	ll ps_count = 0, qs_count = 0;
	for (; i < X + Y; ++i) {
		if (apples[i].second == 0) {
			++ps_count;
			if (ps_count > X) continue;
		}
		else if (apples[i].second == 1) {
			++qs_count;
			if (qs_count > Y) continue;
		}
		res += apples[i].first;
	}
	for (; ps_count > X; ++i) {
		if (apples[i].second == 0) continue;
		res += apples[i].first;
		--ps_count;
	}
	for (; qs_count > Y; ++i) {
		if (apples[i].second == 1) continue;
		res += apples[i].first;
		--qs_count;
	}

	cout << res << endl;

	return 0;
}
