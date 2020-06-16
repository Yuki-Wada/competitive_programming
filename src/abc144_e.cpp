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

// for loop
#define REP(i, n) for ((i) = 0;(i) < (ll)(n);(i)++)

//debug
#define DUMP(x)  cerr << #x << " = " << (x) << endl
#define DEBUG(x) cerr << #x << " = " << (x) << " (l" << __line__ << ")" << " " << __file__ << endl

//main function
int main()
{
	cin.tie(0);
	ios::sync_with_stdio(false);

	ll N, K;
	cin >> N >> K;

	vector<ll> As(N);
	vector<ll> Fs(N);

	for (ll i = 0; i < N; ++i) {
		cin >> As[i];
	}
	for (ll i = 0; i < N; ++i) {
		cin >> Fs[i];
	}
	sort(As.begin(), As.end());
	sort(Fs.begin(), Fs.end(), greater<ll>());

	ll min_val = 0;
	ll max_val = 1000000000000LL;
	ll mid_val = (min_val + max_val) / 2;

	ll train_count;
	while (max_val - min_val >= 2) {
		train_count = 0;
		for (ll i = 0; i < N; ++i) {
			train_count += max(0LL, As[i] - mid_val / Fs[i]);
		}
		if (train_count > K) {
			min_val = mid_val;
		}
		else {
			max_val = mid_val;
		}
		mid_val = (min_val + max_val) / 2;
	}

	ll res;
	train_count = 0;
	for (ll i = 0; i < N; ++i) {
		train_count += max(0LL, As[i] - min_val / Fs[i]);
	}
	if (train_count > K) {
		res = max_val;
	}
	else {
		res = min_val;
	}

	cout << res << endl;

	return 0;
}
