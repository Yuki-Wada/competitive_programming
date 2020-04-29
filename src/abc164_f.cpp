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

	vector<vector<ll>> data(N, vector<ll>(4));
	ll s, t, u, v;
	for (ll i = 0; i < N; ++i) {
		cin >> s >> t >> u >> v;
		data[i][0] = s;
		data[i][1] = t;
		data[i][2] = u;
		data[i][3] = v;
	}

	bool has_prod_1_row, has_sum_0_row, has_prod_1_column, has_sum_0_column;
	vector<vector<ll>> as(N, vector<ll>(N));
	for (ll bit = 0; bit < 64; ++bit) {
		has_prod_1_row = false;
		has_sum_0_row = false;
		has_prod_1_column = false;
		has_sum_0_column = false;
		for (ll i = 0; i < N; ++i) {
			if (data[i][0] == 0 && ((data[i][2] >> bit) & 1LL) == 1LL) {
				has_prod_1_row = true;
			}
			if (data[i][0] == 1 && ((data[i][2] >> bit) & 1LL) == 0LL) {
				has_sum_0_row = true;
			}
			if (data[i][1] == 0 && ((data[i][3] >> bit) & 1LL) == 1LL) {
				has_prod_1_column = true;
			}
			if (data[i][1] == 1 && ((data[i][3] >> bit) & 1LL) == 0LL) {
				has_sum_0_column = true;
			}
		}

		if (has_prod_1_row && has_sum_0_column) {
			cout << -1 << endl;
			return 0;
		}
		if (has_prod_1_column && has_sum_0_row) {
			cout << -1 << endl;
			return 0;
		}
	}

	for (ll i = 0; i < N; ++i) {
		for (ll j = 0; j < N; ++j) {
			cout << as[i][j] << endl;
		}
	}

	return 0;
}
