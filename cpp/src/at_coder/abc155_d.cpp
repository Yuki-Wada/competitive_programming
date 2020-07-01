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

// functions and classes
using Edge = pair<ll, ll>;

//main function
int main()
{
	cin.tie(0);
	ios::sync_with_stdio(false);

	ll N, K;
	cin >> N >> K;

	ll zero_count = 0;
	vector<ll> pas, nas;
	pas.reserve(N);
	nas.reserve(N);
	ll a;
	for (ll i = 0; i < N; ++i)
	{
		cin >> a;
		if (a > 0LL){
			pas.emplace_back(a);
		}
		else if (a < 0LL) {
			nas.emplace_back(-a);
		}
		else{
			++zero_count;
		}
	}
	sort(pas.begin(), pas.end());
	sort(nas.begin(), nas.end());

	ll low = 0LL;
	ll high = 1000000000000000000LL;
	ll mid = (low + high) / 2LL;
	ll val;
	if (K <= pas.size() * nas.size()) {
		K = pas.size() * nas.size() + 1 - K;

		while(high - low > 1) {
			ll res = 0;
			for (ll i = 0; i < pas.size(); ++i){
				res += distance(nas.begin(), upper_bound(nas.begin(), nas.end(), mid / pas[i]));
			}

			if (K <= res) {
				high = mid;
			}
			else {
				low = mid;
			}
			mid = (low + high) / 2LL;
		}

		val = - high;
	}
	else if (K <= pas.size() * nas.size() + zero_count * (zero_count - 1LL) / 2LL + zero_count * (pas.size() + nas.size()) )
	{
		val = 0;
	}
	else {
		K -= pas.size() * nas.size() + zero_count * (zero_count - 1LL) / 2LL + zero_count * (pas.size() + nas.size());

		while (high - low > 1) {
			ll res = 0;
			for (auto iter = pas.begin(); iter != pas.end(); ++iter) {
				res += distance(pas.begin(), upper_bound(pas.begin(), iter, mid / *iter));
			}
			for (auto iter = nas.begin(); iter != nas.end(); ++iter) {
				res += distance(nas.begin(), upper_bound(nas.begin(), iter, mid / *iter));
			}

			if (K <= res) {
				high = mid;
			}
			else {
				low = mid;
			}
			mid = (low + high) / 2LL;
		}

		val = high;
	}
	cout << val << endl;;

	return 0;
}
