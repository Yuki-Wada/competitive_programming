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
#define REP(i, n) for (ll i = 0;(i) < (ll)(n);(i)++)

//debug
#define DUMP(x)  cerr << #x << " = " << (x) << endl
#define DEBUG(x) cerr << #x << " = " << (x) << " (l" << __line__ << ")" << " " << __file__ << endl

int solve() {
	ll n;
	cin >> n;

	vector<ll> ss(n);
	vector<vector<ll>> us(n, vector<ll>(64));
	vector<ll> ts(n);
	vector<vector<ll>> vs(n, vector<ll>(64));

	{
		ull u, v;
		REP(i, n) cin >> ss[i];
		REP(i, n) cin >> ts[i];
		REP(i, n) {
			cin >> u;
			REP(bit, 64) us[i][bit] = (u >> bit) & 1LL;
		}
		REP(i, n) {
			cin >> v;
			REP(bit, 64) vs[i][bit] = (v >> bit) & 1LL;
		}
	}

	vector<vector<ull>> matrix(n, vector<ull>(n));
	vector<vector<ll>> bit_matrix(n, vector<ll>(n));
	REP(bit, 64) {
		REP(row, n) REP(col, n) {
			bit_matrix[row][col] = 0LL;
		}

		REP(row, n) {
			ll s = ss[row];
			ll u = us[row][bit];
			if (s == 0LL && u == 1LL) REP(col, n) bit_matrix[row][col] = u;
			if (s == 1LL && u == 0LL) REP(col, n) bit_matrix[row][col] = u;
		}
		REP(col, n) {
			ll t = ts[col];
			ll v = vs[col][bit];
			if (t == 0LL && v == 1LL) REP(row, n) bit_matrix[row][col] = v;
			if (t == 1LL && v == 0LL) REP(row, n) bit_matrix[row][col] = v;
		}

		vector<ll> row_zero_counts(n);
		vector<ll> column_zero_counts(n);
		REP(row, n) REP(col, n) {
			ll u = us[row][bit];
			ll v = vs[col][bit];
			if (u == v) bit_matrix[row][col] = u;
		}

		REP(row, n) REP(col, n) {
			if (bit_matrix[row][col] == 0LL) {
				++row_zero_counts[row];
				++column_zero_counts[col];
			}
		}

		REP(row, n) {
			ll s = ss[row];
			ll u = us[row][bit];
			if (s == 1LL && u == 1LL && row_zero_counts[row] == n) {
				REP(col, n) {
					ll t = ts[col];
					ll v = vs[col][bit];
					if (t == 0LL && v == 0LL && column_zero_counts[col] > 1LL) {
						bit_matrix[row][col] = 1LL;
						--row_zero_counts[row];
						--column_zero_counts[col];
						break;
					}
				}
			}
		}

		REP(col, n) {
			ll t = ts[col];
			ll v = vs[col][bit];
			if (t == 1LL && v == 1LL && column_zero_counts[col] == n) {
				REP(row, n) {
					ll s = ss[row];
					ll u = us[row][bit];
					if (s == 0LL && u == 0LL && row_zero_counts[row] > 1LL) {
						bit_matrix[row][col] = 1LL;
						--row_zero_counts[row];
						--column_zero_counts[col];
						break;
					}
				}
			}
		}

		REP(row, n) {
			ll s = ss[row];
			ll u = us[row][bit];
			if (s == 0) {
				ll prod = 1;
				REP(col, n) prod &= bit_matrix[row][col];
				if (prod != u) {
					cout << -1 << endl;
					return 0;
				}
			}
			if (s == 1) {
				ll sum = 0;
				REP(col, n) sum |= bit_matrix[row][col];
				if (sum != u) {
					cout << -1 << endl;
					return 0;
				}
			}
		}
		REP(col, n) {
			ll t = ts[col];
			ll v = vs[col][bit];
			if (t == 0) {
				ll prod = 1;
				REP(row, n) prod &= bit_matrix[row][col];
				if (prod != v) {
					cout << -1 << endl;
					return 0;
				}
			}
			if (t == 1) {
				ll sum = 0;
				REP(row, n) sum |= bit_matrix[row][col];
				if (sum != v) {
					cout << -1 << endl;
					return 0;
				}
			}
		}

		REP(row, n) REP(col, n) {
			matrix[row][col] ^= ull(ull(bit_matrix[row][col]) << bit);
		}
	}

	REP(row, n) {
		REP(col, n) {
			cout << matrix[row][col];
			if (col + 1 < n) cout << " ";
		}
		cout << endl;
	}

	return 0;
}

//main function
int main()
{
	cin.tie(0);
	ios::sync_with_stdio(false);

	solve();

	return 0;
}
