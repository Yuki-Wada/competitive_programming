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

// temporary
#include <atcoder/all>
using namespace atcoder;

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

// constant
static const ll MOD = 998244353LL;
static const double PI = 3.14159265358979323846;

template <ull N, class T, class... Args, std::enable_if_t<N == 0, int> = 0>
auto make_multiple_vector(Args... args)
{
    return T(args...);
}

template <ull N, class T, class... Args, std::enable_if_t<N != 0, int> = 0>
auto make_multiple_vector(ull size, Args... args)
{
    using value_type = std::decay_t<decltype(make_multiple_vector<N - 1, T>(args...))>;
    return vector<value_type>(size, make_multiple_vector<N - 1, T>(args...));
}

using rll = modint998244353;

ll N, M;

vector<rll> compute_inverse_power_series(
    const vector<rll> &original_power_series,
    ull required_degree)
{
    vector<rll> g = {1};
    vector<rll> f = {1};

    while (g.size() < required_degree + 1LL)
    {
        f.resize(g.size() * 2ULL);
        for (ll j = 0; j < f.size(); ++j)
        {
            if (j >= original_power_series.size())
            {
                break;
            }
            f[j] = original_power_series[j];
        }
        auto ggf = convolution(convolution(g, g), f);
        g.resize(g.size() * 2ULL);
        for (ull j = 0; j < g.size(); ++j)
        {
            g[j] = g[j] * 2LL - ggf[j];
        }
    }

    return g;
}

vector<rll> compute_pow_sums()
{
    vector<rll> numerator_series(N + 1LL);
    vector<rll> denominator_series(N + 1LL);

    rll excl = 1;
    rll m_pow = M + 1LL;
    REPD(i, 1, N + 2LL)
    {
        numerator_series[i - 1] = ((m_pow - rll(1)) / excl).val();
        denominator_series[i - 1] = (rll(1) / excl).val();
        excl *= rll(i + 1LL);
        m_pow *= rll(M + 1LL);
    }
    denominator_series = compute_inverse_power_series(denominator_series, N);
    auto series = convolution(numerator_series, denominator_series);

    vector<rll> results(N);
    excl = 1;
    REPD(i, 0, N)
    {
        results[i] = series[i + 1LL] * excl;
        excl *= rll(i + 2LL);
    }

    return results;
}

rll pow(rll base, ll t)
{
    rll res = 1;
    while (t > 0LL)
    {
        if (t % 2LL == 1LL)
        {
            res *= base;
        }
        base *= base;
        t >>= 1LL;
    }
    return res;
}

int solve()
{
    cin >> N >> M;

    rll res = 0;

    auto pow_sums = compute_pow_sums();

    ll a, b;
    REPD(i, 0, N)
    {
        cin >> a;
        res += rll(a) * pow_sums[i];
    }

    REPD(i, 0, N)
    {
        cin >> b;
        if (i > 0)
        {
            rll k = i + 1;
            res += rll(b) * (pow(k, M + 1LL) - k) / (k - rll(1));
        }
        else
        {
            res += rll(b) * rll(M);
        }
    }

    cout << res.val() << endl;

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
