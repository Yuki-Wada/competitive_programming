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

	vector<pair<ll, ll>> ABs(N);
	for (ll i = 0; i < N; ++i) {
		ABs[i] = make_pair(Bs[i], As[i]);
	}
	sort(ABs.begin(), ABs.end());

	vector<pair<ll, ll>> A_index_pairs(N);
	for (ll i = 0; i < N; ++i) {
		A_index_pairs[i] = make_pair(ABs[i].second, i);
	}

	sort(A_index_pairs.begin(), A_index_pairs.end());

	for (ll i = 0; i < N; ++i) {
		if (A_index_pairs[i].first > ABs[i].first) {
			cout << "No" << endl;
			return 0;
		}
	}
	
	ll count = 0;
	ll index = 0;
	while (true) {
		index = A_index_pairs[index].second;
		++count;
		if (index == 0) {
			break;
		}
	}
	if (count < N) {
		cout << "Yes" << endl;
		return 0;
	}

	for (ll i = 0; i + 1 < N; ++i) {
		if (A_index_pairs[i + 1].first <= ABs[i].first) {
			cout << "Yes" << endl;
			return 0;
		}
	}

	cout << "No" << endl;
	return 0;
}
