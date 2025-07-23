// include
//------------------------------------------
#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <unordered_set>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>

#include <numeric>
#include <utility>
#include <complex>
#include <random>

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

// type alias
using ll = long long;
using ull = unsigned long long;
using comp = complex<double>;
using llpair = pair<ll, ll>;
template <class T>
using vector2d = vector<vector<T>>;
template <class T>
using vector3d = vector<vector<vector<T>>>;
using ll1d = vector<ll>;
using ll2d = vector2d<ll>;
using ll3d = vector3d<ll>;
using pair1d = vector<llpair>;
using pair2d = vector2d<llpair>;

// constant
static constexpr ll MOD = 998244353LL;
static constexpr double PI = 3.14159265358979323846;

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

ll N, K;

int solve()
{
	cin >> N >> K;
	ll1d As(N), Bs(N), Cs(N);
	REPD(i, 0, N)
	cin >> As[i];
	REPD(i, 0, N)
	cin >> Bs[i];
	REPD(i, 0, N)
	cin >> Cs[i];

	sort(As.begin(), As.end()), reverse(As.begin(), As.end());
	sort(Bs.begin(), Bs.end()), reverse(Bs.begin(), Bs.end());
	sort(Cs.begin(), Cs.end()), reverse(Cs.begin(), Cs.end());

	auto calc = [](ll a, ll b, ll c)
	{
		return a * b + b * c + c * a;
	};

	priority_queue<tuple<ll, ll, ll, ll>> pq;
	set<tuple<ll, ll, ll>> added;
	pq.emplace(
		calc(As[0], Bs[0], Cs[0]),
		0,
		0,
		0);
	added.emplace(0, 0, 0);
	while (true)
	{
		auto [res, ia, ib, ic] = pq.top();
		pq.pop();

		--K;
		if (K <= 0)
		{
			cout << res << endl;
			break;
		}
		if (ia + 1 < N && added.count(make_tuple(ia + 1LL, ib, ic)) == 0)
		{
			pq.emplace(
				calc(As[ia + 1], Bs[ib], Cs[ic]),
				ia + 1,
				ib,
				ic);
			added.emplace(ia + 1LL, ib, ic);
		}
		if (ib + 1 < N && added.count(make_tuple(ia, ib + 1LL, ic)) == 0)
		{
			pq.emplace(
				calc(As[ia], Bs[ib + 1], Cs[ic]),
				ia,
				ib + 1,
				ic);
			added.emplace(ia, ib + 1LL, ic);
		}
		if (ic + 1 < N && added.count(make_tuple(ia, ib, ic + 1LL)) == 0)
		{
			pq.emplace(
				calc(As[ia], Bs[ib], Cs[ic + 1]),
				ia,
				ib,
				ic + 1);
			added.emplace(ia, ib, ic + 1LL);
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
	// REPD(i, 0, t)
	// {
	// 	solve();
	// }

	return 0;
}
