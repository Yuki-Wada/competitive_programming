#define CATCH_CONFIG_MAIN // main の定義を catch に任せる
#include "catch.hpp"

#include <fstream>
#include <string>
#include <data_structure.hpp>

// computational complexity: o(log(max(a, b)))
inline ull get_gcd(ull a, ull b)
{
	if (b == 0)
	{
		return a;
	}
	return get_gcd(b, a % b);
}

TEST_CASE("Segment Tree Test", "[sample]")
{
	SECTION("dmoj")
	{
		struct GCDOp {
			const pair<ll, ll> default_value = {0, 1};
			static pair<ll, ll> Execute(const pair<ll, ll>& a, const pair<ll, ll>& b) {
				ll a1, a2, b1, b2;
				tie(a1, a2) = a;
				tie(b1, b2) = b;
				ll c1 = get_gcd(a1, b1), c2 = 0;
				if (c1 == a1) c2 += a2;
				if (c1 == b1) c2 += b2;
				return {c1, c2};
			};
		};

		ifstream inputs("cpp/test/test_cases/segment_tree_input_dmoj.txt");
		ifstream outputs("cpp/test/test_cases/segment_tree_output_dmoj.txt");

		ll N, M;
		inputs >> N >> M;

		RMQ min_tree(N + 1);
		SegmentTree<pair<ll, ll>, GCDOp> gcd_tree(N + 1);
		ll a;
		for (unsigned i = 0; i < N; ++i) {
			inputs >> a;
			min_tree.update(i + 1, a);
			gcd_tree.update(i + 1, {a, 1LL});
		}

		char type;
		ll l, r;
		ll ans;
		for (unsigned i = 0; i < M; ++i) {
			inputs >> type >> l >> r;
			if (type == 'C') {
				min_tree.update(l, r);
				gcd_tree.update(l, {r, 1});
			}
			if (type == 'M') {
				outputs >> ans;
				REQUIRE(min_tree.query(l, r + 1) == ans);
			}
			if (type == 'G') {
				outputs >> ans;
				REQUIRE(gcd_tree.query(l, r + 1).first == ans);
			}
			if (type == 'Q') {
				outputs >> ans;
				REQUIRE(gcd_tree.query(l, r + 1).second == ans);
			}
		}
	}
	SECTION("TEST 1")
	{
		ifstream inputs("cpp/test/test_cases/segment_tree_input_01.txt");
		ifstream outputs("cpp/test/test_cases/segment_tree_output_01.txt");

		ll N, M;
		inputs >> N >> M;

		RMQ min_tree(N + 1);
		ll a;
		for (unsigned i = 0; i < N; ++i) {
			inputs >> a;
			min_tree.update(i + 1, a);
		}

		ll l, r;
		ll ans;
		for (unsigned i = 0; i < M; ++i) {
			inputs >> l >> r;
			outputs >> ans;
			REQUIRE(min_tree.query(l, r + 1) == ans);
		}
	}
}
