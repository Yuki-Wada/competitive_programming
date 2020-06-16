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

// for loop
#define REP(i, n) for ((i) = 0;(i) < (ll)(n);(i)++)

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
public:
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

int solve() {
	ll n, m;
	cin >> n >> m;

	vector<string> cells(n);
	for (ll i = 0; i < n; ++i) {
		cin >> cells[i];
	}

	int status;
	bool exists_all_white_row = false;
	for (ll i = 0; i < n; ++i) {
		status = 0;
		for (ll j = 0; j < m; ++j) {
			if (status == 0 && cells[i][j] == '#') {
				status = 1;
			}
			else if (status == 1 && cells[i][j] == '.') {
				status = 2;
			}
			else if (status == 2 && cells[i][j] == '#') {
				cout << -1 << endl;
				return 0;
			}
		}
		if (status == 0) {
			exists_all_white_row = true;
		}
	}

	bool exists_all_white_column = false;
	for (ll j = 0; j < m; ++j) {
		status = 0;
		for (ll i = 0; i < n; ++i) {
			if (status == 0 && cells[i][j] == '#') {
				status = 1;
			}
			else if (status == 1 && cells[i][j] == '.') {
				status = 2;
			}
			else if (status == 2 && cells[i][j] == '#') {
				cout << -1 << endl;
				return 0;
			}
		}
		if (status == 0) {
			exists_all_white_column = true;
		}
	}

	if (exists_all_white_row ^ exists_all_white_column) {
		cout << -1 << endl;
		return 0;
	}

	UnionFindTree uft(m * n + 1LL);
	for (ll i = 0; i < n; ++i) {
		for (ll j = 0; j < m; ++j) {
			auto index = i * m + j;
			if (cells[i][j] == '.') {
				uft.uniteSet(index, m * n);
			}
			else {
				if (i - 1LL >= 0LL){
					auto target_index = (i - 1) * m + j;
					if (cells[i - 1][j] == '#') {
						uft.uniteSet(index, target_index);
					}
				}
				if (i + 1LL < n) {
					auto target_index = (i + 1) * m + j;
					if (cells[i + 1][j] == '#') {
						uft.uniteSet(index, target_index);
					}
				}
				if (j - 1LL >= 0LL) {
					auto target_index = i * m + (j - 1);
					if (cells[i][j - 1] == '#') {
						uft.uniteSet(index, target_index);
					}
				}
				if (j + 1LL < m) {
					auto target_index = i * m + (j + 1);
					if (cells[i][j + 1] == '#') {
						uft.uniteSet(index, target_index);
					}
				}
			}
		}
	}

	set<ll> rootNodes;
	rootNodes.insert(uft.getRootNode(m * n));
	for (ll i = 0; i < n; ++i) {
		for (ll j = 0; j < m; ++j) {
			auto index = i * m + j;
			auto root_node = uft.getRootNode(index);
			rootNodes.insert(root_node);
		}
	}

	cout << rootNodes.size() - 1 << endl;

	return 0;
}

//main function
int main()
{
	cin.tie(0);
	ios::sync_with_stdio(false);

	solve();

	return 0;
}
