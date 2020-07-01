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

int solve() {
	ll i, j, k;

	ll n;
	cin >> n;
	
	vector<pair<ll, ll>> sus(n);
	vector<pair<ll, ll>> tvs(n);
	REP(i, n) cin >> sus[i].first;
	REP(i, n) cin >> tvs[i].first;
	REP(i, n) cin >> sus[i].second;
	REP(i, n) cin >> tvs[i].second;

	ll s, u, bit_u, t, v, bit_v;
	vector<vector<ll>> matrix(n, vector<ll>(n));
	vector<vector<ll>> bit_matrix(n, vector<ll>(n));
	REP (i, 64) {
		REP(j, n) REP(k, n) {
			bit_matrix[j][k] = -1;
		}

		REP(j, n) {
			tie(s, u) = sus[j];
			bit_u = (u >> i) & 1LL;
			if (s == 0LL && bit_u == 1LL) {
				REP(k, n) {
					if (bit_matrix[j][k] == -1LL) {
						bit_matrix[j][k] = bit_u;
						continue;
					}
					if (bit_matrix[j][k] != bit_u) {
						cout << -1 << endl;
						return 0;
					}
				}
			}
			if (s == 1LL && bit_u == 0LL) {
				REP(k, n) {
					if (bit_matrix[j][k] == -1LL) {
						bit_matrix[j][k] = bit_u;
						continue;
					}
					if (bit_matrix[j][k] != bit_u) {
						cout << -1 << endl;
						return 0;
					}
				}
			}
		}

		REP(k, n) {
			tie(t, v) = tvs[k];
			bit_v = (v >> i) & 1LL;
			if (t == 0LL && bit_v == 1LL) {
				REP(j, n) {
					if (bit_matrix[j][k] == -1LL) {
						bit_matrix[j][k] = bit_v;
						continue;
					}
					if (bit_matrix[j][k] != bit_v) {
						cout << -1 << endl;
						return 0;
					}
				}
			}
			if (t == 1LL && bit_v == 0LL) {
				REP(j, n) {
					if (bit_matrix[j][k] == -1LL) {
						bit_matrix[j][k] = bit_v;
						continue;
					}
					if (bit_matrix[j][k] != bit_v) {
						cout << -1 << endl;
						return 0;
					}
				}
			}
		}

		vector<ll> row_zero_counts(n);
		vector<ll> column_zero_counts(n);
		REP(j, n) REP(k, n) {
			if (bit_matrix[j][k] == -1LL) {
				tie(s, u) = sus[j];
				tie(t, v) = tvs[k];
				bit_u = (u >> i) & 1LL;
				bit_v = (v >> i) & 1LL;
				if (s == 1LL && bit_u == 1LL && t == 1LL && bit_v == 1LL) {
					bit_matrix[j][k] = 1LL;
				}
				else {
					bit_matrix[j][k] = 0LL;
				}
			}
			if (bit_matrix[j][k] == 0LL) {
				++row_zero_counts[j];
				++column_zero_counts[k];
			}
		}

		REP(j, n) {
			tie(s, u) = sus[j];
			bit_u = (u >> i) & 1LL;
			if (s == 0LL && bit_u == 0LL && row_zero_counts[j] == 0LL) {
				cout << -1 << endl;
				return 0;
			}
			if (s == 1LL && bit_u == 1LL && row_zero_counts[j] == n) {
				REP(k, n) {
					tie(t, v) = tvs[k];
					bit_v = (v >> i) & 1LL;
					if (t == 0LL && bit_v == 0LL && bit_matrix[j][k] == 0LL && column_zero_counts[k] > 1LL) {
						bit_matrix[j][k] = 1LL;
						--row_zero_counts[j];
						--column_zero_counts[k];
						break;
					}
				}
				if (row_zero_counts[j] == n) {
					cout << -1 << endl;
					return 0;
				}
			}
		}

		REP(k, n) {
			tie(t, v) = tvs[k];
			bit_v = (v >> i) & 1LL;
			if (t == 0LL && bit_v == 0LL && column_zero_counts[k] == 0LL) {
				cout << -1 << endl;
				return 0;
			}
			if (t == 1LL && bit_v == 1LL && column_zero_counts[k] == n) {
				REP(j, n) {
					tie(s, u) = sus[j];
					bit_u = (u >> i) & 1LL;
					if (s == 0LL && bit_u == 0LL && bit_matrix[j][k] == 0LL && row_zero_counts[j] > 1LL) {
						bit_matrix[j][k] = 1LL;
						--row_zero_counts[j];
						--column_zero_counts[k];
						break;
					}
				}
				if (column_zero_counts[k] == n) {
					cout << -1 << endl;
					return 0;
				}
			}
		}

		REP(j, n) REP(k, n) {
			matrix[j][k] += bit_matrix[j][k] << i;
		}
	}
	
	REP(i, n) {
		REP(j, n) {
			cout << matrix[i][j];
			if (j + 1 < n) cout << " ";
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
