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

	vector<ll> As(N);
	vector<ll> Bs(N);
	for (ll i = 0; i < N; ++i) {
		cin >> As[i];
	}
	for (ll i = 0; i < N; ++i) {
		cin >> Bs[i];
	}

	queue<ll> to_operate;
	ll a_plus_c;
	for (ll i = 0; i < N; ++i) {
		a_plus_c = Bs[(i - 1 + N) % N] + Bs[(i + 1 + N) % N];
		if (Bs[i] > a_plus_c && Bs[i] > As[i]) {
			to_operate.push(i);
		}
	}

	ll res = 0;
	while (!to_operate.empty()) {
		auto idx = to_operate.front();
		to_operate.pop();

		a_plus_c = Bs[(idx - 1 + N) % N] + Bs[(idx + 1 + N) % N];
		if (Bs[idx] - a_plus_c < As[idx]) {
			continue;
		}

		res += Bs[idx] / a_plus_c;
		Bs[idx] %= a_plus_c;
		if (Bs[idx] < As[idx]) {
			ll incr = (As[idx] - Bs[idx] + a_plus_c - 1) / a_plus_c;
			res -= incr;
			Bs[idx] += a_plus_c * incr;
		}

		ll i = (idx - 1 + N) % N;
		a_plus_c = Bs[(i - 1 + N) % N] + Bs[(i + 1 + N) % N];
		if (Bs[i] > a_plus_c && Bs[i] > As[i]) {
			to_operate.push(i);
		}

		i = (idx + 1 + N) % N;
		a_plus_c = Bs[(i - 1 + N) % N] + Bs[(i + 1 + N) % N];
		if (Bs[i] > a_plus_c && Bs[i] > As[i]) {
			to_operate.push(i);
		}
	}

	for (ll i = 0; i < N; ++i) {
		if (As[i] != Bs[i]) {
			res = -1;
			break;
		}
	}

	cout << res << endl;

	return 0;
}
