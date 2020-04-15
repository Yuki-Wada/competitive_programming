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

	set<ll> res;
	ll q = N - 1;
	for (ll i = 1; i * i <= q; ++i) {
		if (q % i == 0) {
			res.insert(i);
			res.insert(q / i);
		}
	}

	map<ll, ll> prime_to_count;
	vector<bool> is_prime(sqrt(N) + 1, true);
	q = N;
	for (ll p = 2; p * p <= q; ++p) {
		if (!is_prime[p]) continue;
		for (ll i = 2; p * i < is_prime.size(); ++i) is_prime[p * i] = false;

		while (q % p == 0) {
			if (prime_to_count.count(p) == 0) prime_to_count[p] = 0;
			++prime_to_count[p];
			q /= p;
		}
	}
	if (q != 1) {
		if (prime_to_count.count(q) == 0) prime_to_count[q] = 0;
		++prime_to_count[q];
	}

	ll divisor_count = 1;
	for (auto iter = prime_to_count.begin(); iter != prime_to_count.end(); ++iter) {
		divisor_count *= iter->second + 1;
	}

	ll divisor, idx, mult_count;
	for (ll i = 1; i < divisor_count; ++i) {
		idx = i;
		divisor = 1;
		for (auto iter = prime_to_count.begin(); iter != prime_to_count.end(); ++iter) {
			mult_count = idx % (iter->second + 1);
			for (ll j = 0; j < mult_count; ++j) {
				divisor *= iter->first;
			}
			idx /= iter->second + 1;
		}

		q = N;
		while (q % divisor == 0) {
			q /= divisor;
		}
		if (q % divisor == 1) {
			res.insert(divisor);
		}
	}

	if (res.count(1)) res.erase(1);
	cout << res.size() << endl;

	return 0;
}
