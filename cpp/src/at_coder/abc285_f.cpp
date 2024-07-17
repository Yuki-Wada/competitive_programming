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

template <class Integer>
class BinaryIndexedTree
{
private:
	ull maxSize_;
	vector<Integer> values_;

public:
	BinaryIndexedTree(ull maxSize) : maxSize_(maxSize), values_(maxSize_, 0) {}

	void update(ll index, Integer increment)
	{
		if (maxSize_ <= index)
		{
			throw invalid_argument("Index should be less than maxSize.");
		}
		++index;

		while (index <= maxSize_)
		{
			values_[index - 1] += increment;
			index += index & -index;
		}
	}

	Integer query(ll index)
	{
		if (index < 0LL)
			return 0;
		if (maxSize_ <= index)
		{
			throw invalid_argument("Index should be less than maxSize.");
		}
		++index;

		Integer res = 0;
		while (index > 0)
		{
			res += values_[index - 1];
			index -= index & -index;
		}
		return res;
	}
};
using BIT = BinaryIndexedTree<ll>;

class Solver
{
private:
	string S;
	ll N;
	vector<ll> As;
	vector<BIT> accum_char_counts;
	set<ll> sort_idxs;

public:
	Solver(string S) : S(S), N(S.size()), As(N), accum_char_counts(26LL, BIT(N + 1LL))
	{
		for (ll i = 0; i < N; ++i)
		{
			As[i] = char_to_ll(S[i]);
			accum_char_counts[As[i]].update(i + 1, 1);
		}

		ll idx = 0, prev_a = As[0];
		sort_idxs.insert(0LL);
		for (ll i = 1; i < N; ++i)
		{
			if (prev_a > As[i])
			{
				idx = i;
				sort_idxs.insert(idx);
			}
			prev_a = As[i];
		}
		sort_idxs.insert(N);
	}

	ll char_to_ll(char ch)
	{
		return ll(ch - 'a');
	}

	bool judge_sort(ll l, ll r)
	{
		auto r_interval = *sort_idxs.upper_bound(l);
		if (r <= r_interval)
		{
			return true;
		}
		return false;
	}

	bool judge_counts(ll l, ll r)
	{
		ll sub_count, all_count;
		ll count_state = 0;
		for (ll i = 0; i < 26LL; ++i)
		{
			sub_count = accum_char_counts[i].query(r) - accum_char_counts[i].query(l);
			all_count = accum_char_counts[i].query(N);

			if (count_state == 0)
			{
				if (sub_count > 0)
				{
					count_state = 1;
				}
			}
			else if (count_state == 1)
			{
				if (sub_count < all_count)
				{
					count_state = 2;
				}
			}
			else
			{
				if (sub_count > 0)
				{
					return false;
				}
			}
		}
		return true;
	}

	bool judge(ll l, ll r)
	{
		return judge_sort(l, r) && judge_counts(l, r);
	}

	void update_sort_idxs(ll x, ll c)
	{
		if (x > 0LL)
		{
			if (As[x - 1LL] > c)
			{
				sort_idxs.insert(x);
			}
			else
			{
				sort_idxs.erase(x);
			}
		}

		if (x + 1LL < N)
		{
			if (c > As[x + 1LL])
			{
				sort_idxs.insert(x + 1LL);
			}
			else
			{
				sort_idxs.erase(x + 1LL);
			}
		}
	}

	void
	update(ll x, char c)
	{
		auto llc = char_to_ll(c);
		update_sort_idxs(x, llc);
		accum_char_counts[llc].update(x + 1LL, 1LL);
		accum_char_counts[As[x]].update(x + 1LL, -1LL);

		As[x] = llc;
	}
};

int solve()
{
	ll N, Q;
	string S;
	cin >> N >> S >> Q;
	Solver solver(S);

	ll a, b, c;
	char ch;
	for (ll i = 0; i < Q; ++i)
	{
		cin >> a;
		if (a == 1)
		{
			cin >> b >> ch;
			--b;
			solver.update(b, ch);
		}
		else
		{
			cin >> b >> c;
			--b;
			if (solver.judge(b, c))
			{
				cout << "Yes" << endl;
			}
			else
			{
				cout << "No" << endl;
			}
		}
	}

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
