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

class UnionFindTree
{
private:
	const unsigned elemCount_;
	vector<unsigned> parentNodeNumbers_;
	vector<unsigned> treeDepths_;
	vector<unsigned> setSizes_;

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
	UnionFindTree(unsigned elemCount) :
		elemCount_(elemCount),
		parentNodeNumbers_(elemCount),
		treeDepths_(elemCount, 0),
		setSizes_(elemCount, 1)
	{
		for (unsigned i = 0; i < parentNodeNumbers_.size(); ++i)
		{
			parentNodeNumbers_[i] = i;
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
			parentNodeNumbers_[x] = y;
			setSizes_[y] = setSizes_[x] + setSizes_[y];
		}
		else
		{
			parentNodeNumbers_[y] = x;
			setSizes_[x] = setSizes_[x] + setSizes_[y];
			if (treeDepths_[x] == treeDepths_[y])
			{
				++treeDepths_[x];
			}
		}
	}

	unsigned getSetSize(unsigned x)
	{
		return setSizes_[getRootNode(x)];
	}

	// Average Computational Complexity: O(log(elemCount_))) 
	bool includedInSameSet(unsigned x, unsigned y)
	{
		return getRootNode(x) == getRootNode(y);
	}
};

//main function
int main()
{
	cin.tie(0);
	ios::sync_with_stdio(false);

	ll N, M, K;
	cin >> N >> M >> K;

	UnionFindTree tree(N);

	ll a, b;
	vector<vector<ll>> friends(N);
	for (ll i = 0; i < M; ++i) {
		cin >> a >> b;
		friends[a - 1].emplace_back(b - 1);
		friends[b - 1].emplace_back(a - 1);
		tree.uniteSet(a - 1, b - 1);
	}

	vector<vector<ll>> blocks(N);
	for (ll i = 0; i < K; ++i) {
		cin >> a >> b;
		if (!tree.includedInSameSet(a - 1, b - 1)) continue;
		blocks[a - 1].emplace_back(b - 1);
		blocks[b - 1].emplace_back(a - 1);
	}

	ll res = 0;


	for (ll i = 0; i < N; ++i) {
		res = tree.getSetSize(i) - friends[i].size() - blocks[i].size() - 1LL;
		cout << res;
		if (i + 1 >= N) break;
		cout << " ";
	}
	cout << endl;

	return 0;
}
