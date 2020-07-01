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
	string S;

	cin >> N;
	cin >> S;

	vector<ll> As(N);
	for (ll i = 0; i < N; ++i) {
		As[i] = ll(S[i] - '1');
	}

	vector<ll> power_of_2(N);
	for (ll i = 0; i < N; ++i) {
		ll n = 2;
		while (i / n > 0) {
			power_of_2[i] += i / n;
			n *= 2;
		}
	}

	ll accum = 0;
	for (ll i = 0; i < N; ++i) {
		if (power_of_2[N - 1] - power_of_2[N - 1 - i] - power_of_2[i] == 0) {
			accum += As[i];
		}
	}

	if (accum % 2 == 1) {
		cout << 1 << endl;
		return 0;
	}
	for (ll i = 0; i < N; ++i) {
		if (As[i] % 2 == 1) {
			cout << 0 << endl;
			return 0;
		}
		As[i] /= 2;
	}
	
	accum = 0;
	for (ll i = 0; i < N; ++i) {
		if (power_of_2[N - 1] - power_of_2[N - 1 - i] - power_of_2[i] == 0) {
			accum += As[i];
		}
	}
	if (accum % 2 == 0) {
		cout << 0 << endl;
	}
	else {
		cout << 2 << endl;
	}

	return 0;
}
