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

// temporary
#include <atcoder/all>
using namespace atcoder;

// type alias
using ll = long long;
using ull = unsigned long long;
using comp = complex<double>;

// constant
static const ll MOD = 998244353LL;
static const double PI = 3.14159265358979323846;

// conversion
inline ll toint(string s) { ll v; istringstream sin(s); sin >> v; return v; }
template<class t> inline string tostring(t x) { ostringstream sout; sout << x; return sout.str(); }

// print
#define RET(x) return cout << x << endl, 0;

// for loop
#define REP(i, a, b) for ((i) = (ll)(a);(i) < (ll)(b);(i)++)
#define REPD(i, a, b) for (ll i = (ll)(a);(i) < (ll)(b);(i)++)
#define REPI(v, vs) for (auto& v : vs)

//debug
#ifdef LOCAL_ENV
#define DUMP(x)  cerr << #x << " = " << (x) << endl
#define DEBUG(x) cerr << #x << " = " << (x) << " (l" << __LINE__ << ")" << " " << __FILE__ << endl
#else
#define DUMP(x)
#define DEBUG(x)
#endif

#define MAX_VALUE 9223372036854775807LL

template <ull N, class T, class... Args, std::enable_if_t<N == 0, int> = 0>
auto make_multiple_vector(Args... args) {
    return T(args...);
}

template <ull N, class T, class... Args, std::enable_if_t<N != 0, int> = 0>
auto make_multiple_vector(ull size, Args... args) {
    using value_type = std::decay_t<decltype(make_multiple_vector<N - 1, T>(args...))>;
    return vector<value_type>(size, make_multiple_vector<N - 1, T>(args...));
}

int solve() {
	ll N, M;
	cin >> N >> M;
    vector<string> board(N);
    REPD(i, 0, N) cin >> board[i];

    vector<pair<ll, ll>> pieces;
    REPD(i, 0, N) {
        REPD(j, 0, M) {
            if (board[i][j] == 'o') pieces.emplace_back(i, j);
        }
    }

    auto get_node = [&](ll i, ll j) {
        return i * M + j;
    };

    ll S = pieces.size() + N * M, T = pieces.size() + N * M + 1LL;
    mcf_graph<int, ll> g(pieces.size() + N * M + 2LL);

    REPD(i, 0, pieces.size()) {
        g.add_edge(S, i + N * M, 1, 0);
    }
    REPD(i, 0, N * M) {
        g.add_edge(i, T, 1, 0);
    }

    const ll BIG = 1LL << 32LL;
    vector<vector<ll>> bfs(N, vector<ll>(M));
    REPD(i, 0, pieces.size()) {
        REPD(j, 0, N) REPD(k, 0, M) {
            bfs[j][k] = -1;
        }
        queue<tuple<ll, ll, ll>> que;
        ll x = pieces[i].first, y = pieces[i].second, dist;
        bfs[x][y] = 0;
        que.emplace(x, y, 0);
        while (!que.empty()) {
            tie(x, y, dist) = que.front();
            que.pop();
            if (x + 1 < N) {
                if (bfs[x + 1][y] == -1LL && board[x + 1][y] != '#') {
                    bfs[x + 1][y] = dist + 1LL;
                    que.emplace(x + 1, y, dist + 1LL);
                }
            }
            if (y + 1 < M) {
                if (bfs[x][y + 1] == -1LL && board[x][y + 1] != '#') {
                    bfs[x][y + 1] = dist + 1LL;
                    que.emplace(x, y + 1, dist + 1LL);
                }
            }
        }

        REPD(j, 0, N) REPD(k, 0, M) {
            if (bfs[j][k] == -1LL) continue;
            g.add_edge(i + N * M, get_node(j, k), 1, BIG - bfs[j][k]);
        }
    }

    pair<int, ll> flow_result = g.flow(S, T, pieces.size());
    ll result = BIG * pieces.size() - flow_result.second;

    RET(result);

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
