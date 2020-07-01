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

ll calc_seq9(ll n, ll k) {
	if (n < k) {
		return 0LL;
	}

	ll res = 1LL;
	for (ll i = 0; i < k; ++i)
	{
		res *= 9LL;
		res *= n - i;
	}
	for (ll i = 0; i < k; ++i)
	{
		res /= i + 1LL;
	}

	return res;
}

ll calc(string n, ll k, vector<vector<ll>>& dp) {
	if (dp[n.size()][k] != -1) {
		return dp[n.size()][k];
	}
	if (k == 0) {
		return 1LL;
	}
	if (n.size() == 0) {
		return 0LL;
	}
	
	ll top_digit = (ll)(n[0] - '0');
	ll res = 0LL;
	if (top_digit >= 1) {
		res += calc_seq9(n.size() - 1, k);
		res += calc_seq9(n.size() - 1, k - 1) * (top_digit - 1);
		res += calc(n.substr(1), k - 1, dp);
	}
	else {
		res += calc(n.substr(1), k, dp);
	}

	dp[n.size()][k] = res;

	return res;
}

//main function
int main()
{
	cin.tie(0);
	ios::sync_with_stdio(false);

	string N;
	ll K;
	cin >> N >> K;

	vector<vector<ll>> dp(N.size() + 1);
	for (ll i = 0; i < dp.size(); ++i)
	{
		dp[i] = vector<ll>(K + 1, -1LL);
		dp[i][0] = 1LL;
	}

	ll res = 0LL;
	res = calc(N, K, dp);

	cout << res << endl;

	return 0;
}
