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

// functions and classes
using Edge = pair<ll, ll>;

//main function
int main()
{
	cin.tie(0);
	ios::sync_with_stdio(false);

	ll N, K;
	cin >> N >> K;

	vector<ll> ps(N);
	for (ll i = 0; i < N; ++i)
	{
		cin >> ps[i];
	}

	ll res = K;
	ll sum = K;
	for (ll i = 0; i < ps.size(); ++i)
	{
		sum += ps[i];
		if (i >= K) {
			sum -= ps[i - K];
		}
		res = (res < sum ? sum : res);
	}

	cout << fixed << setprecision(12);
	cout << double(res) / 2.0 << endl;

	return 0;
}
