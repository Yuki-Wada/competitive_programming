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

	if (N == 3) {
		cout << 2 << " " << 3 << " " << 25 << endl;
		return 0;
	}
	vector<ll> results;

	ll num_3 = 2;
	for (; num_3 + 2 <= N - 2 && num_3 + 2 <= 5000; num_3 += 2);
	for (ll i = 0; i < num_3; ++i) {
		results.emplace_back(i * 6 + 3);
	}

	N -= num_3;
	for (ll i = 0; i < N / 3; ++i) {
		results.emplace_back(i * 6 + 2);
		results.emplace_back(i * 6 + 4);
		results.emplace_back(i * 6 + 6);
	}
	if (N - 3 * (N / 3) == 1) {
		results.emplace_back((N / 3) * 6 + 6);
	}
	else if (N - 3 * (N / 3) == 2) {
		results.emplace_back((N / 3) * 6 + 2);
		results.emplace_back((N / 3) * 6 + 4);
	}

	sort(results.begin(), results.end());

	for (ll i = 0; i < results.size(); ++i) {
		cout << results[i];
		if (i + 1 != results.size()) {
			cout << " ";
		}
		else {
			cout << endl;
		}
	}

	return 0;
}
