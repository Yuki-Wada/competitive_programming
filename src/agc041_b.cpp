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

	ll N, M, V, P;
	cin >> N >> M >> V >> P;

	vector<ll> As(N);
	for (ll i = 0; i < N; ++i) {
		cin >> As[i];
	}
	sort(As.begin(), As.end(), greater<ll>());

	vector<ll> accums(N + 1);
	accums[0] = 0;
	for (ll i = 0; i < N; ++i) {
		accums[i + 1] = accums[i] + As[i];
	}

	ll res = P;
	for (ll i = P; i < N; ++i) {
		if (As[i] + M < As[P - 1]) {
			continue;
		}
		ll m_count = V - (N - i + P - 1);
		if (m_count < 0) {
			++res;
			continue;
		}
		if ((As[i] + M) * (i + 1 - P) - (accums[i] - accums[P - 1]) >= M * m_count) {
			++res;
		}
	}

	cout << res << endl;

	return 0;
}
