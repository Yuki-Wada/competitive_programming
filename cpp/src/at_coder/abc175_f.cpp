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

// type alias
using ll = long long;
using ull = unsigned long long;
using comp = complex<double>;

// constant
static const ll MOD = 1000000007LL;
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
#define DUMP(x)  cerr << #x << " = " << (x) << endl
#define DEBUG(x) cerr << #x << " = " << (x) << " (l" << __LINE__ << ")" << " " << __FILE__ << endl

#define MAX_VALUE 9223372036854775807


using Edge = pair<ll, ll>;

struct Graph
{
	using Vertex = ll;
	ll vertex_count;
	vector<Edge> edges;

	Graph() : vertex_count(0LL), edges(0LL) {}
	Graph(ll vertex_count) : vertex_count(vertex_count), edges(0LL) {}

	void add_edge(const Edge& edge)
	{
		edges.emplace_back(edge);
	}

	vector<vector<tuple<Vertex, Vertex>>> get_adjacency_list() const
	{
		using EdgeWithInfo = tuple<Vertex, Vertex>;
		// 辺の隣接リストを作成
		vector<vector<EdgeWithInfo>> adjancency_list(vertex_count);
		for (ll i = 0; i < edges.size(); ++i)
		{
			Vertex from, to;
			tie(from, to) = edges[i];
			adjancency_list[from].emplace_back(from, to);
		}
		return move(adjancency_list);
	}

	template<class EdgeInfo>
	vector<vector<tuple<Vertex, Vertex, EdgeInfo>>> get_adjacency_list(const vector<EdgeInfo>& infos) const
	{
		using EdgeWithInfo = tuple<Vertex, Vertex, EdgeInfo>;
		// 辺の隣接リストを作成
		vector<vector<EdgeWithInfo>> adjancency_list(vertex_count);
		for (ll i = 0; i < edges.size(); ++i)
		{
			Vertex from, to;
			tie(from, to) = edges[i];
			const EdgeInfo& info = infos[i];
			adjancency_list[from].emplace_back(from, to, info);
		}
		return move(adjancency_list);
	}
};

// 始点 s から各点への最短距離を返します。
// パス自体が存在しない場合は -1 を返します。
// 距離 lengths の各要素は非負である必要があります。
pair<vector<ll>, vector<ll>> dijkstra(const Graph& graph, const vector<ll>& lengths, ll s = 0LL)
{
	using Vertex = ll;
	using Length = ll;

	if (graph.edges.size() != lengths.size())
		throw runtime_error("グラフの辺の要素数と辺の長さの要素数は一致している必要があります。");

	// 辺の隣接リストを作成
	auto adjacency_list = graph.get_adjacency_list(lengths);

	// アルゴリズム本体
	using VertexInfo = pair<Length, Vertex>;
	priority_queue<VertexInfo, vector<VertexInfo>, greater<VertexInfo>> queue;
	vector<Length> dists(graph.vertex_count, 1LL << 60);
	vector<Vertex> prev_vertices(graph.vertex_count, -1LL);

	dists[s] = 0LL;
	queue.emplace(dists[s], s);
	prev_vertices[s] = s;
	while (!queue.empty())
	{
		Length l;
		Vertex v;
		tie(l, v) = queue.top();
		queue.pop();
		if (dists[v] < l) continue;
		for (auto& edge : adjacency_list[v])
		{
			Vertex to = get<1>(edge);
			Length length = get<2>(edge);
			if (dists[to] > dists[v] + length)
			{
				dists[to] = dists[v] + length;
				queue.emplace(dists[to], to);
				prev_vertices[to] = v;
			}
		}
	}
	for (ll i = 0; i < graph.vertex_count; ++i)
	{
		if (prev_vertices[i] == -1LL)
			dists[i] = -1LL;
	}

	return { dists, prev_vertices };
}

int solve() {
	ll N;
	cin >> N;

	vector<string> Ss(N + 1);
	vector<string> rev_Ss(N + 1);
	vector<ll> Cs(N + 1);
	REPD(i, 1, N + 1) cin >> Ss[i] >> Cs[i], rev_Ss[i] = Ss[i], reverse(rev_Ss[i].begin(), rev_Ss[i].end());

	map<string, ll> left_str_to_idx, right_str_to_idx;
	string key;
	REPD(i, 1, N + 1) {
		ll length = Ss[i].size();
		REPD(j, 1, length) {
			key = Ss[i].substr(length - j, j);
			if (left_str_to_idx.count(key) == 0) left_str_to_idx[key] = left_str_to_idx.size();
		}
		REPD(j, 1, length) {
			key = Ss[i].substr(0, j);
			reverse(key.begin(), key.end());
			if (right_str_to_idx.count(key) == 0) right_str_to_idx[key] = right_str_to_idx.size();
		}
	}

	auto get_index = [&](string remains, bool is_left = true) {
		if (remains == "<START>") return 0LL;
		if (remains == "<END>") return 1LL;
		if (is_left) {
			if (left_str_to_idx.count(remains) == 0) return -1LL;
			return left_str_to_idx[remains] + 2LL;
		}
		if (right_str_to_idx.count(remains) == 0) return -1LL;
		return right_str_to_idx[remains] + ll(left_str_to_idx.size()) + 2LL;
	};

	Graph g(left_str_to_idx.size() + right_str_to_idx.size() + 2);
	vector<ll> lengths;
	auto register_edges = [&](string remains, string token, bool is_left) {
		vector<string>& ss = (is_left ? Ss : rev_Ss);
		vector<string>& rev_ss = (is_left ? rev_Ss: Ss);

		ll src_idx = get_index(token, is_left); 
		string tmp, rev;
		REPD(i, 0, rev_ss.size()) {
			REPD(j, 0, ss.size()) {
				if (i == 0 && j == 0) continue;
 				string concat = remains + ss[j];
				if (concat.size() >= rev_ss[i].size()) {
					if (concat.substr(0, rev_ss[i].size()) == rev_ss[i]) {
						rev = tmp = concat.substr(rev_ss[i].size());
						reverse(rev.begin(), rev.end());
						if (rev == tmp) tmp = "<END>";
						ll tgt_idx = get_index(tmp, is_left); 
						if (tgt_idx == -1) continue;
						g.add_edge({src_idx, tgt_idx});
						lengths.emplace_back(Cs[i] + Cs[j]);
					}
				}
				else if (concat.size() < rev_ss[i].size()) {
					if (concat == rev_ss[i].substr(0, concat.size())) {
						rev = tmp = rev_ss[i].substr(concat.size());
						reverse(rev.begin(), rev.end());
						if (rev == tmp) tmp = "<END>";
						ll tgt_idx = get_index(tmp, !is_left); 
						if (tgt_idx == -1) continue;
						g.add_edge({src_idx, tgt_idx});
						lengths.emplace_back(Cs[i] + Cs[j]);
					}
				}
			}
		}
	};

	register_edges("", "<START>", true);
	register_edges("", "<START>", false);

	REPI(iter, left_str_to_idx) register_edges(iter.first, iter.first, true);
	REPI(iter, right_str_to_idx) register_edges(iter.first, iter.first, false);

	auto dists = dijkstra(g, lengths).first;

	RET(dists[1]);

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
