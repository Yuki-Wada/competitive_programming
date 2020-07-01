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

	string S;
	cin >> S;

	vector<vector<ll>> encoded_list;
	vector<ll> encoded;
	ll idx = 0;
	while (idx < S.size()) {
		if (S[idx] == 'A') {
			encoded.emplace_back(0);
			++idx;
		}
		else if (idx + 1 < S.size() && S[idx] == 'B' && S[idx + 1] == 'C') {
			encoded.emplace_back(1);
			idx += 2;
		}
		else {
			if (encoded.size() > 0) {
				encoded_list.emplace_back(encoded);
				encoded = vector<ll>();
			}
			++idx;
		}
	}

	if (encoded.size() > 0) {
		encoded_list.emplace_back(encoded);
	}

	ll res = 0;
	ll exchange_count;
	for (ll i = 0; i < encoded_list.size(); ++i) {
		idx = 0;
		exchange_count = 0;
		while (idx < encoded_list[i].size()) {
			if (encoded_list[i][idx] == 1) {
				res += idx - exchange_count;
				++exchange_count;
			}
			++idx;
		}
	}

	cout << res << endl;

	return 0;
}
