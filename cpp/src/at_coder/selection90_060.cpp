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

//debug
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

vector<ll> get_lis_length(const vector<ll> &seq, bool strictly = true, bool ascending = true)
{
	vector<ll> min_last_seq_elem;
	using iter_type = decltype(min_last_seq_elem.begin());
	auto get_iter = [&strictly, &ascending](iter_type begin, iter_type end, ll elem)
	{
		if (strictly)
		{
			if (ascending)
				return lower_bound(begin, end, elem, less<ll>());
			else
				return lower_bound(begin, end, elem, greater<ll>());
		}
		else
		{
			if (ascending)
				return upper_bound(begin, end, elem, less<ll>());
			else
				return upper_bound(begin, end, elem, greater<ll>());
		}
	};

	vector<ll> res;
	res.reserve(seq.size());
	for (const auto &elem : seq)
	{
		auto iter = get_iter(min_last_seq_elem.begin(), min_last_seq_elem.end(), elem);
		if (iter == min_last_seq_elem.end())
			min_last_seq_elem.emplace_back(elem);
		else
			*iter = elem;

		res.emplace_back(min_last_seq_elem.size());
	}

	return res;
}

int solve()
{
	ll n;
	cin >> n;

	vector<ll> as(n);
	REPD(i, 0, n)
	cin >> as[i];

	auto a = get_lis_length(as);
	reverse(as.begin(), as.end());
	auto b = get_lis_length(as);

	ll res = 0;
	REPD(i, 0, n)
	{
		res = max(res, a[i] + b[n - i - 1LL] - 1LL);
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
