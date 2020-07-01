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


template<class Integer>
class RangedMinimumQuery
{
private:
	ull maxSize_;
	vector<Integer> values_;

	const Integer defaultValue_ = 0x7FFFFFFFFFFFFFFF;
	const function<Integer(const Integer&, const Integer&)> func =
		[](const Integer& a, const Integer& b) { return min(a, b); };

	Integer _query(ll start, ll end, ll searchStart, ll searchEnd, ll node)
	{
		if (searchEnd <= start || end <= searchStart)
		{
			return defaultValue_;
		}
		if (start <= searchStart && searchEnd <= end)
		{
			return values_[node];
		}

		return func(
			_query(start, end, searchStart, (searchStart + searchEnd) / 2, node * 2 + 1),
			_query(start, end, (searchStart + searchEnd) / 2, searchEnd, node * 2 + 2)
		);
	}

public:
	RangedMinimumQuery(ull maxSize) : maxSize_(1)
	{
		while (maxSize_ < maxSize)
		{
			maxSize_ *= 2;
		}
		values_ = vector<Integer>(ll(maxSize_) * 2 - 1, defaultValue_);
	}

	void update(ll index, Integer value)
	{
		if (index >= maxSize_)
		{
			throw invalid_argument("Index should be less than maxSize.");
		}
		index += maxSize_ - 1;
		values_[index] = value;
		while (index > 0)
		{
			index = (index - 1) / 2;
			values_[index] = func(values_[2 * index + 1], values_[index * 2 + 2]);
		}
	}

	Integer query(ll start, ll end)
	{
		if (start < 0)
		{
			throw invalid_argument("Start should be non-negative.");
		}
		if (maxSize_ < end)
		{
			throw invalid_argument("End should be less than or equal to maxSize.");
		}
		if (start > end)
		{
			throw invalid_argument("End should be more than start.");
		}

		return _query(start, end, 0, maxSize_, 0);
	}
};
using rmq = RangedMinimumQuery<ll>;

int solve() {
	ll n;
	cin >> n;
	
	vector<tuple<ll, ll, ll>> abs;
	abs.reserve(n);
	ll a, b;
	for (ll i = 0; i < n; ++i) {
		cin >> a >> b;
		abs.emplace_back(--a, --b, i);
	}
	sort(abs.begin(), abs.end());

	auto comp = [](const auto& a, const auto& b) {
		if (get<1>(a) < get<1>(b)) {
			return false;
		}
		else if (get<1>(a) > get<1>(b)) {
			return true;
		}

		if (get<0>(a) < get<0>(b)) {
			return false;
		}
		else if (get<0>(a) > get<0>(b)) {
			return true;
		}
		if (get<2>(a) < get<2>(b)) {
			return false;
		}
		return true;
	};
	priority_queue<
		tuple<ll, ll, ll>,
		vector<tuple<ll, ll, ll>>,
		decltype(comp)
	> queue(comp);

	vector<tuple<ll, ll, ll>> rearranged;
	rearranged.reserve(n);
	ll abs_index = 0;
	for (ll i = 0; i < n; ++i) {
		while (abs_index < n && get<0>(abs[abs_index]) <= i) {
			queue.emplace(abs[abs_index++]);
		}
		rearranged.emplace_back(queue.top());
		queue.pop();
	}

	rmq rmq(n);
	pair<ll, ll> replace_pair(-1, -1);
	for (ll i = 0; i < n; ++i) {
		if (get<0>(rearranged[i]) <= (-rmq.query(i, n))) {
			replace_pair = make_pair(i, (-rmq.query(i, n)));
			break;
		}
		rmq.update(get<1>(rearranged[i]), -i);
	}

	vector<ll> results(n);
	for (ll i = 0; i < n; ++i) {
		results[get<2>(rearranged[i])] = i + 1;
	}

	cout << (replace_pair.first == -1 ? "Yes" : "No") << endl; 

	for (ll i = 0; i < n; ++i) {
		cout << results[i];
		if (i + 1 < n) {
			cout << " ";
		}
		else {
			cout << endl;
		}
	}

	if (replace_pair.first != -1) {
		ll temp = results[get<2>(rearranged[replace_pair.first])];
		results[get<2>(rearranged[replace_pair.first])] = results[get<2>(rearranged[replace_pair.second])];
		results[get<2>(rearranged[replace_pair.second])] = temp;
		for (ll i = 0; i < n; ++i) {
			cout << results[i];
			if (i + 1 < n) {
				cout << " ";
			}
			else {
				cout << endl;
			}
		}
	}

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
