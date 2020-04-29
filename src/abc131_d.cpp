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

	ll N;
	cin >> N;

	vector<pair<ll, ll>> abs;
	abs.reserve(N);
	ll a, b;
	for (ll i = 0; i < N; ++i) {
		cin >> a >> b;
		abs.emplace_back(b, a);
	}
	sort(abs.begin(), abs.end());
	
	bool can_finish = true;
	ll accum = 0;
	for (ll i = 0; i < N; ++i) {
		accum += abs[i].second;
		if (accum > abs[i].first) {
			can_finish = false;
			break;
		}
	}

	cout << (can_finish ? "Yes" : "No") << endl;

	return 0;
}
