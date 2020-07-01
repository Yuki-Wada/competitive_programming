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

	ll N, Q;
	string S;
	cin >> N >> S >> Q;

	map<char, set<ll>> char_to_set;
	for (ll i = 0; i < N; ++i) {
		if (char_to_set.count(S[i]) == 0) {
			char_to_set[S[i]] = set<ll>();
		}
		char_to_set[S[i]].insert(i);
	}

	ll type, iq, lq, rq, res;
	char cq;
	for (ll i = 0; i < Q; ++i) {
		cin >> type;
		if (type == 1) {
			cin >> iq >> cq;
			--iq;
			char_to_set[S[iq]].erase(iq);
			char_to_set[cq].insert(iq);
			S[iq] = cq;
		}
		else if (type == 2) {
			cin >> lq >> rq;
			--lq, --rq;
			res = 0;
			for (auto iter = char_to_set.begin(); iter != char_to_set.end(); ++iter) {
				auto set_iter = (iter->second).lower_bound(lq);
				if (set_iter != iter->second.cend() && (*set_iter) <= rq) {
					++res;
				}
			}
			cout << res << endl;
		}
	}


	return 0;
}
