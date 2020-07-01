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

	string N;
	cin >> N;
	N = "00" + N;
	reverse(N.begin(), N.end());

	ll no_incre_res, prev_no_incre_res = 0;
	ll incre_res, prev_incre_res = 1LL << 31;
	ll digit;
	bool increment = false;
	for (ll i = 0; i < N.size(); ++i) {
		digit = N[i] - '0';
		no_incre_res = min(prev_no_incre_res + digit, prev_incre_res + digit + 1);
		incre_res = min(prev_no_incre_res + 10 - digit, prev_incre_res + 10 - digit - 1);
		prev_no_incre_res = no_incre_res;
		prev_incre_res = incre_res;
	}

	cout << no_incre_res << endl;

	return 0;
}
