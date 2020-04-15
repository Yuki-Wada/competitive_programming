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

template<class Integer>
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
using bit = BinaryIndexedTree<ll>;

//main function
int main()
{
	cin.tie(0);
	ios::sync_with_stdio(false);

	ll N, D, A;
	cin >> N >> D >> A;

	ll x, h;
	vector<pair<ll, ll>> xhs;
	xhs.reserve(N);
	for (ll i = 0; i < N; ++i) {
		cin >> x >> h;
		xhs.emplace_back(x, h / A + (h % A == 0 ? 0LL : 1LL));
	}
	sort(xhs.begin(), xhs.end());

	vector<ll> range_indices(N);
	for (ll i = 0; i < N; ++i) {
		range_indices[i] = distance(
			xhs.begin(),
			upper_bound(
				xhs.begin(), xhs.end(),
				make_pair(xhs[i].first + D * 2LL, 10000000000000000LL)
			)
		);
	}

	ll res = 0LL;
	ll incr = 0LL;
	bit bit(N);
	for (ll i = 0; i < N; ++i) {
		incr = xhs[i].second - bit.query(i);
		if (incr < 0LL) continue;
		res += incr;
		bit.update(i, incr);
		if (range_indices[i] < N) {
			bit.update(range_indices[i], -incr);
		}
	}
	cout << res << endl;

	return 0;
}
