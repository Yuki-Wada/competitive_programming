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
	
	ll a;
	vector<ll> counts(N);
	for (ll i = 0; i < N; ++i) {
		cin >> a;
		++counts[--a];
	}
	sort(counts.begin(), counts.end());

	vector<ll> dists(N);
	for (ll i = 0; i < N; ++i) {
		dists[i] = distance(lower_bound(counts.begin(), counts.end(), i + 1), counts.end());
	}

	vector<ll> fs(N);
	ll f = 0;
	for (ll i = 0; i < N; ++i) {
		f += dists[i];
		fs[i] = f / (i + 1);
	}

	vector<ll> results(N);
	for (ll k = N, i = 0; k > 0; --k) {
		while (i < N) {
			if (fs[i] < k) {
				results[k - 1] = i;
				break;
			}
			else {
				++i;
			}
		}
	}
	results[0] = N;

	for (ll i = 0; i < N; ++i) {
		cout << results[i] << endl;
	}

	return 0;
}
