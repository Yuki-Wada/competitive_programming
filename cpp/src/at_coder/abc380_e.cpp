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
static const ll MOD = 998244353LL;
static const double PI = 3.14159265358979323846;

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

using ColorInfo = tuple<ll, ll, ll>;

class UnionFindTree
{
private:
	const unsigned elemCount_;
	vector<unsigned> parentNodeNumbers_;
	vector<unsigned> treeDepths_;
	vector<unsigned> colorCounts_;
	vector<ColorInfo> colorInfos_;

	// Average Computational Complexity: O(log(elemCount_)))
	unsigned getRootNode(unsigned x)
	{
		if (parentNodeNumbers_[x] == x)
		{
			return x;
		}
		else
		{
			return getRootNode(parentNodeNumbers_[x]);
		}
	}

public:
	UnionFindTree(unsigned elemCount) : elemCount_(elemCount),
										parentNodeNumbers_(elemCount),
										treeDepths_(elemCount, 0),
										colorCounts_(elemCount, 1),
										colorInfos_(elemCount)
	{
		for (unsigned i = 0; i < parentNodeNumbers_.size(); ++i)
		{
			parentNodeNumbers_[i] = i;
			colorInfos_[i] = {i, i, i};
		}
	}

	// Average Computational Complexity: O(log(elemCount_)))
	void uniteSet(unsigned x, unsigned y)
	{
		x = getRootNode(x);
		y = getRootNode(y);
		if (x == y)
		{
			return;
		}

		if (treeDepths_[x] < treeDepths_[y])
		{

			auto [color_x, xs, xe] = colorInfos_[getRootNode(x)];
			auto [color_y, ys, ye] = colorInfos_[getRootNode(y)];
			colorInfos_[y] = {color_x, min(xs, ys), max(xe, ye)};

			parentNodeNumbers_[x] = y;
		}
		else
		{
			auto [color_x, xs, xe] = colorInfos_[getRootNode(x)];
			auto [color_y, ys, ye] = colorInfos_[getRootNode(y)];
			colorInfos_[x] = {color_x, min(xs, ys), max(xe, ye)};

			parentNodeNumbers_[y] = x;

			if (treeDepths_[x] == treeDepths_[y])
			{
				++treeDepths_[x];
			}
		}
	}

	// Average Computational Complexity: O(log(elemCount_)))
	bool includedInSameColor(unsigned x, unsigned y)
	{
		auto [color_x, _1, _2] = colorInfos_[getRootNode(x)];
		auto [color_y, _3, _4] = colorInfos_[getRootNode(y)];
		return color_x == color_y;
	}

	void paint_color(unsigned x, ll next_c)
	{
		x = getRootNode(x);
		auto [curr_c, s, e] = colorInfos_[x];
		colorCounts_[curr_c] -= (e - s + 1LL);
		colorCounts_[next_c] += (e - s + 1LL);
		colorInfos_[x] = {next_c, s, e};

		if (s - 1LL >= 0 && includedInSameColor(s - 1LL, s))
		{
			uniteSet(s - 1, s);
		}
		if (e + 1LL < elemCount_ && includedInSameColor(e, e + 1LL))
		{
			uniteSet(e, e + 1LL);
		}
	}

	ll get_color_counts(ll c)
	{
		return colorCounts_[c];
	}
};

ll N, Q;
ll1d As;

int solve()
{
	cin >> N >> Q;
	UnionFindTree uft(N);
	REPD(i, 0, Q)
	{
		ll t;
		cin >> t;
		if (t == 1)
		{
			ll x, c;
			cin >> x >> c;
			--x, --c;
			uft.paint_color(x, c);
		}
		else if (t == 2)
		{
			ll c;
			cin >> c;
			--c;
			cout << uft.get_color_counts(c) << endl;
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
