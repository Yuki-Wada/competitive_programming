// include
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
static const ll MOD = 998244353LL;
// static const ll MOD = (1LL << 61LL) - 1LL;
static const double PI = 3.14159265358979323846;

// conversion
inline ll toint(string s)
{
	ll v;
	istringstream sin(s);
	sin >> v;
	return v;
}
template <class t>
inline string tostring(t x)
{
	ostringstream sout;
	sout << x;
	return sout.str();
}

// print
#define RET(x) return cout << x << endl, 0;

// for loop
#define REP(i, a, b) for ((i) = (ll)(a); (i) < (ll)(b); (i)++)
#define REPD(i, a, b) for (ll i = (ll)(a); (i) < (ll)(b); (i)++)
#define REPI(v, vs) for (auto &v : vs)

// debug
#ifdef LOCAL_ENV
#define DUMP(x) cerr << #x << " = " << (x) << endl
#define DEBUG(x) cerr << #x << " = " << (x) << " (l" << __LINE__ << ")" \
					  << " " << __FILE__ << endl
#else
#define DUMP(x)
#define DEBUG(x)
#endif

#define MAX_VALUE 9223372036854787LL

template <class T, class... Args>
auto make_multiple_vector(T default_value)
{
	return T(default_value);
}

template <class T, class... Args>
auto make_multiple_vector(T default_value, ull size, Args... args)
{
	using value_type = std::decay_t<decltype(make_multiple_vector<T>(default_value, args...))>;
	return vector<value_type>(size, make_multiple_vector<T>(default_value, args...));
}

ll vec2idx(vector<ll> v, ll P)
{
	ll res_idx = 0;
	for (ll i = 0; i < v.size(); ++i)
	{
		res_idx *= P + 1LL;
		res_idx += v[i];
	}

	return res_idx;
}

ll add_idx(ll idx1, ll idx2, ll K, ll P)
{
	vector<ll> res_v;
	for (ll i = 0; i < K; ++i)
	{
		ll tmp = idx1 % (P + 1LL) + idx2 % (P + 1LL);
		tmp = min(tmp, P);
		res_v.emplace_back(tmp);
		idx1 /= P + 1LL;
		idx2 /= P + 1LL;
	}
	reverse(res_v.begin(), res_v.end());

	return vec2idx(res_v, P);
}

int solve()
{
	ll N, K, P;
	cin >> N >> K >> P;

	vector<ll> Cs(N);
	vector<ll> As(N);
	for (ll i = 0; i < N; ++i)
	{
		cin >> Cs[i];
		vector<ll> A_sub(K);
		for (ll j = 0; j < K; ++j)
		{
			cin >> A_sub[j];
		}
		As[i] = vec2idx(A_sub, P);
	}

	ll res_size = 1LL;
	for (ll i = 0; i < K; ++i)
	{
		res_size *= P + 1LL;
	}
	vector<ll> prev_res(res_size, MAX_VALUE);
	vector<ll> curr_res(res_size, MAX_VALUE);
	prev_res[0] = 0LL;
	curr_res[0] = 0LL;
	for (ll i = 0; i < N; ++i)
	{
		for (ll j = 0; j < res_size; ++j)
		{
			auto new_idx = add_idx(j, As[i], K, P);
			curr_res[new_idx] = min(prev_res[j] + Cs[i], curr_res[new_idx]);
		}
		for (ll j = 0; j < res_size; ++j)
		{
			prev_res[j] = curr_res[j];
		}
	}

	cout << (curr_res[res_size - 1LL] != MAX_VALUE ? curr_res[res_size - 1LL] : -1LL) << endl;

	return 0;
}

// main function
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
