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

vector<ull> construct_suffix_array(const vector<ull> &vec)
{
	struct DoublingComparer
	{
		static bool compare(ll i, ll j, vector<ll> &ranks, ll K, ll N)
		{
			if (ranks[i] != ranks[j])
			{
				return ranks[i] < ranks[j];
			}
			ll di = i + K <= N ? ranks[i + K] : -1LL;
			ll dj = j + K <= N ? ranks[j + K] : -1LL;

			return di < dj;
		};
	};

	ll N = vec.size();
	vector<ull> suffix_array(N + 1LL);
	vector<ll> ranks(N + 1LL);

	for (ll i = 0; i <= N; ++i)
	{
		suffix_array[i] = i;
		ranks[i] = i < N ? vec[i] : -1LL;
	}

	vector<ull> tmp_ranks(N);

	for (ll k = 1; k < N; k *= 2LL)
	{
		auto compare = [&ranks, k, N](ll i, ll j)
		{
			return DoublingComparer::compare(i, j, ranks, k, N);
		};
		sort(suffix_array.begin(), suffix_array.end(), compare);

		tmp_ranks[suffix_array[0]] = 0;
		for (ll i = 1; i <= N; ++i)
		{
			tmp_ranks[suffix_array[i]] = tmp_ranks[suffix_array[i - 1LL]];
			if (DoublingComparer::compare(suffix_array[i - 1LL], suffix_array[i], ranks, k, N))
			{
				++tmp_ranks[suffix_array[i]];
			}
		}
		for (ll i = 0; i <= N; ++i)
		{
			ranks[i] = tmp_ranks[i];
		}
	}
	return suffix_array;
}

vector<ull> construct_lcp(const vector<ull> &vec)
{
	ll N = vec.size();
	vector<ull> lcp(N);

	vector<ull> suffix_array = construct_suffix_array(vec);
	vector<ull> ranks(N + 1LL);
	for (ll i = 0; i <= N; ++i)
	{
		ranks[suffix_array[i]] = i;
	}

	lcp[0] = 0;
	ll h = 0;
	for (ll i = 0; i < N; ++i)
	{
		ll j = suffix_array[ranks[i] - 1LL];
		if (h > 0LL)
		{
			--h;
		}
		for (; j + h < N && i + h < N; ++h)
		{
			if (vec[j + h] != vec[i + h])
			{
				break;
			}
		}
		lcp[ranks[i] - 1LL] = h;
	}

	return lcp;
}

int solve()
{
	string S;
	cin >> S;

	auto vec = make_multiple_vector(0ULL, S.size());
	REPD(i, 0, S.size())
	{
		vec[i] = ll(S[i] - 'a');
	}
	auto lcp = construct_lcp(vec);

	ll res = S.size() * (S.size() + 1LL) / 2;
	REPD(i, 0, S.size())
	{
		res -= lcp[i];
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
	// REPD(i, 0, t)
	// {
	// 	solve();
	// }

	return 0;
}
