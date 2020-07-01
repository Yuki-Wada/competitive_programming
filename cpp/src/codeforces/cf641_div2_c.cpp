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

// computational complexity: o(log(max(a, b))) 
inline ull get_gcd(ull a, ull b)
{
	if (b == 0)
	{
		return a;
	}
	return get_gcd(b, a % b);
}

int solve() {
	ll n;
	cin >> n;

	vector<ll> as(n);
	for (ll i = 0; i < n; ++i) cin >> as[i];

	vector<ll> primes;
	ll as0 = as[0], as1 = as[1];
	vector<bool> is_prime(max(as0, as1) + 1LL, true);
	for (ll p = 2; p * p <= max(as0, as1); ++p) {
		if (is_prime[p] && (as0 % p == 0 || as1 % p == 0)) {
			primes.push_back(p);
			for (ll j = 2; j * p <= max(as0, as1); ++j) {
				is_prime[j * p] = false;
			}
			while (as0 % p == 0) {
				as0 /= p;
			}
			while (as1 % p == 0) {
				as1 /= p;
			}
		}
	}
	if (as0 > 1) primes.push_back(as0);
	if (as1 > 1) primes.push_back(as1);

	ll res = 1;
	vector<ll> exps(n);
	for (ll prime : primes) {
		for (ll i = 0; i < n; ++i) {
			exps[i] = 0;
		}
		for (ll i = 0; i < n; ++i) {
			while (as[i] % prime == 0) {
				++exps[i];
				as[i] /= prime;
			}
		}
		sort(exps.begin(), exps.end());
		for (ll i = 0; i < exps[1]; ++i) {
			res *= prime;
		}
	}



	cout << res << endl;

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
