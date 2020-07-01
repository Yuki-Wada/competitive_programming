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

	map<ll, ll> as;
	as[0] = 0;
	ll a;
	for (ll i = 0; i < N; ++i) {
		cin >> a;
		if (as.count(a) == 0) {
			as[a] = 0;
		}
		++as[a];
	}

	if (as[0] == N) {
		cout << "Yes" << endl;
	}
	else {
		if (N % 3 != 0) {
			cout << "No" << endl;
		}
		else {
			if (as[0] == (N / 3)) {
				bool can_wear = false;
				for (auto iter = as.begin(); iter != as.end(); ++iter) {
					if (iter->first != 0 && iter->second == (N / 3) * 2) {
						can_wear = true;
						break;
					}
				}
				cout << (can_wear ? "Yes" : "No") << endl;
			}
			else if (as[0] == 0) {
				vector<ll> count_to_wear;
				for (auto iter = as.begin(); iter != as.end(); ++iter) {
					if (iter->first != 0 && iter->second == (N / 3)) {
						count_to_wear.emplace_back(iter->first);
					}
				}
				if (count_to_wear.size() == 3 && (count_to_wear[0] ^ count_to_wear[1]) == count_to_wear[2]) {
					cout << "Yes" << endl;
				}
				else {
					cout << "No" << endl;
				}
			}
			else {
				cout << "No" << endl;
			}
		}
	}

	return 0;
}
