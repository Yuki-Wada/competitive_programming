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

vector<ll> z_algorithm(vector<ll> S) {
	vector<ll> As(S.size());

	if (S.size() == 0)
	{
		return As;
	}

	ll base_pos = 0;
	for (ll curr_pos = 1; curr_pos < S.size(); curr_pos++)
	{
		if (curr_pos + As[curr_pos - base_pos] < base_pos + As[base_pos])
		{
			As[curr_pos] = As[curr_pos - base_pos];
		}
		else
		{
			ll check_pos = max(0LL, base_pos + As[base_pos] - curr_pos);
			while (curr_pos + check_pos < S.size() && S[check_pos] == S[curr_pos + check_pos])
				++check_pos;
			As[curr_pos] = check_pos;
			base_pos = curr_pos;
		}
	}
	As[0] = S.size();

	return As;
}

ll find(const vector<ll>& pattern, const vector<ll>& str) {
	map<ll, ll> shift;
	ll pattern_idx;
	for (ll i = 0; i < pattern.size(); ++i) {
		pattern_idx = pattern.size() - 1 - i;
		if (shift.count(shift[pattern[pattern_idx]]) == 0) {
			shift[pattern[pattern_idx]] = i;
		}
	}

	ll base_idx = pattern.size() - 1;
	ll curr_idx = base_idx;
	bool found = false;
	while (base_idx < str.size()) {
		for (ll i = 0; i < pattern.size(); ++i) {
			curr_idx = base_idx - i;
			pattern_idx = pattern.size() - 1 - i;

			if (pattern[pattern_idx] != str[curr_idx]) {
				if (shift.count(str[curr_idx]) == 0) {
					curr_idx += pattern.size();
				}
				else {
					curr_idx += shift[str[curr_idx]];
				}
				if (base_idx >= curr_idx) {
					++base_idx;
				}
				else {
					base_idx = curr_idx;
				}
				break;
			}
			if (i + 1 == pattern.size()) {
				found = true;
			}
		}
		if (found) {
			return curr_idx;
		}
	}

	return -1;
}

//main function
int main()
{
	cin.tie(0);
	ios::sync_with_stdio(false);

	ll N;
	cin >> N;
	
	vector<ll> as(N);
	vector<ll> bs(N);

	for (ll i = 0; i < N; ++i) {
		cin >> as[i];
	}
	for (ll i = 0; i < N; ++i) {
		cin >> bs[i];
	}

	vector<ll> diff_as(N * 2 - 1);
	vector<ll> diff_bs(N);
	for (ll i = 0; i < N; ++i) {
		diff_as[i] = as[(i + N) % N] ^ as[(i - 1 + N) % N];
		diff_bs[i] = bs[(i + N) % N] ^ bs[(i - 1 + N) % N];
	}
	for (ll i = 0; i < N - 1; ++i) {
		diff_as[N + i] = diff_as[i];
	}

	ll begin_idx = find(diff_bs, diff_as);
	vector<pair<ll, ll>> results;
	if (begin_idx >= 0) {
		for (ll i = 0; i < N - 1; ++i) {
			diff_bs.emplace_back(diff_bs[i]);
		}
		vector<ll> lengths = z_algorithm(diff_bs);

		ll res_index;
		for (ll i = 0; i < N; ++i) {
			if (lengths[i] >= N) {
				res_index = (begin_idx + i) % N;
				results.emplace_back(res_index, as[res_index] ^ bs[0]);
			}
		}
	}

	sort(results.begin(), results.end());
	for (ll i = 0; i < results.size(); ++i) {
		cout << results[i].first << " " << results[i].second << endl;
	}

	return 0;
}
