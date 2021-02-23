//include
//------------------------------------------
#include <string>
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
#include <cstring>
#include <ctime>

// namespace
using namespace std;

// type alias
using ll = long long;
using ull = unsigned long long;
using comp = complex<double>;

// constant
static const ll MOD = 1000000007LL;
// static const ll MOD = (1LL << 61LL) - 1LL;
static const double PI = 3.14159265358979323846;

// conversion
inline ll toint(string s) { ll v; istringstream sin(s); sin >> v; return v; }
template<class t> inline string tostring(t x) { ostringstream sout; sout << x; return sout.str(); }

// print
#define RET(x) return cout << x << endl, 0;

// for loop
#define REP(i, a, b) for ((i) = (ll)(a);(i) < (ll)(b);(i)++)
#define REPD(i, a, b) for (ll i = (ll)(a);(i) < (ll)(b);(i)++)
#define REPI(v, vs) for (auto& v : vs)

//debug
#ifdef LOCAL_ENV
#define DUMP(x)  cerr << #x << " = " << (x) << endl
#define DEBUG(x) cerr << #x << " = " << (x) << " (l" << __LINE__ << ")" << " " << __FILE__ << endl
#else
#define DUMP(x)
#define DEBUG(x)
#endif

#define MAX_VALUE 9223372036854775807LL

template <ull N, class T, class... Args, std::enable_if_t<N == 0, int> = 0>
auto make_multiple_vector(Args... args) {
    return T(args...);
}

template <ull N, class T, class... Args, std::enable_if_t<N != 0, int> = 0>
auto make_multiple_vector(ull size, Args... args) {
    using value_type = std::decay_t<decltype(make_multiple_vector<N - 1, T>(args...))>;
    return vector<value_type>(size, make_multiple_vector<N - 1, T>(args...));
}

map<ll, ll> get_prime_factors(ll a, const vector<bool>& is_primes){
	ll sqrt_a = sqrt(double(a));
	while ((sqrt_a + 1) * (sqrt_a + 1) <= a) ++sqrt_a;
	while (sqrt_a * sqrt_a > a) --sqrt_a;

	map<ll, ll> prime_factors;
	REPD(p, 2, sqrt_a + 1) {
		if (!is_primes[p]) continue;
		while (a % p == 0LL) {
			if (prime_factors.count(p) == 0) prime_factors[p] = 0;
			++prime_factors[p];
			a /= p;
		}
	}
	if (a != 1LL) prime_factors[a] = 1;

	return prime_factors;
}

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
	REPD(i, 0, n) cin >> as[i];
	ll max_a = *max_element(as.begin(), as.end());
	ll min_a = *min_element(as.begin(), as.end());

	ll sqrt_a = sqrt(double(max_a));
	while ((sqrt_a + 1) * (sqrt_a + 1) <= max_a) ++sqrt_a;
	while (sqrt_a * sqrt_a > max_a) --sqrt_a;

	vector<bool> is_primes(sqrt_a + 1, true);
	is_primes[1] = is_primes[0] = false;
	REPD(p, 2, sqrt_a + 1) {
		if (!is_primes[p]) continue;
		ll i = 2;
		while(p * i <= sqrt_a) is_primes[p * i++] = false;
	}

	map<ll, ll> num_to_gcd;
	ll prime, exponent;
	REPD(i, 0, n) {
		auto prime_factors = get_prime_factors(as[i], is_primes);
		ll multiple_count = 1;
		REPI(prime_info, prime_factors) {
			tie(prime, exponent) = prime_info;
			multiple_count *= exponent + 1LL;
		}
		REPD(j, 0, multiple_count) {
			ll j0 = j;
			ll multiple = 1;
			REPI(prime_info, prime_factors) {
				tie(prime, exponent) = prime_info;
				REPD(k, 0, j0 % (exponent + 1LL)) multiple *= prime;
				j0 /= exponent + 1LL;
			}
			if (multiple > min_a) continue;
			if (num_to_gcd.count(multiple) == 0) num_to_gcd[multiple] = as[i];
			num_to_gcd[multiple] = get_gcd(num_to_gcd[multiple], as[i]);
		}
	}
	ll res = 0;
	ll num, gcd;
	REPI(num_gcd, num_to_gcd) {
		tie(num, gcd) = num_gcd;
		if (num == gcd) ++res;
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
	// ll t;
	// cin >> t;
	// REPD(i, 0, t) solve();

	return 0;
}
