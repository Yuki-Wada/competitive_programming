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

#define MAX_VALUE 9223372036854775807LL

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

int solve()
{
	ll N;
	cin >> N;

	string T;
	vector<string> Ss(N);
	cin >> T;
	REPD(i, 0, N)
	{
		cin >> Ss[i];
	}

	vector<ll> forward_lengths;
	vector<ll> backward_lengths;
	REPD(i, 0, N)
	{
		ll target_forward_idx = 0;
		ll target_backward_idx = 0;
		for (int j = 0; j < Ss[i].length(); ++j)
		{
			if (target_forward_idx < T.length() && Ss[i][j] == T[target_forward_idx])
			{
				++target_forward_idx;
			}
			if (target_backward_idx < T.length() && Ss[i][Ss[i].length() - j - 1] == T[T.length() - target_backward_idx - 1])
			{
				++target_backward_idx;
			}
		}
		forward_lengths.emplace_back(target_forward_idx);
		backward_lengths.emplace_back(target_backward_idx);
	}

	vector<ll> forward_length_counts(T.size() + 1LL);
	vector<ll> backward_length_counts(T.size() + 1LL);
	for (ll i = 0; i < N; ++i)
	{
		++forward_length_counts[forward_lengths[i]];
		++backward_length_counts[backward_lengths[i]];
	}

	ll sum = 0;
	for (ll i = 0; i < backward_length_counts.size(); ++i)
	{
		ll idx = backward_length_counts.size() - i - 1LL;
		sum += backward_length_counts[idx];
		backward_length_counts[idx] = sum;
	}

	ll res = 0;
	for (ll i = 0; i < forward_length_counts.size(); ++i)
	{
		res += forward_length_counts[i] * backward_length_counts[T.size() - i];
	}

	cout << res << endl;

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
