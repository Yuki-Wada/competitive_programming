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

//main function
int main()
{
	cin.tie(0);
	ios::sync_with_stdio(false);

	ll N, A, B, C;
	cin >> N >> A >> B >> C;

	vector<string> Ss(N);
	for (ll i = 0; i < N; ++i) {
		cin >> Ss[i];
	}
	
	if (A + B + C == 0) {
		cout << "No" << endl;
		return 0;
	}
	if (A + B + C >= 3) {
		vector<string> queue;
		for (ll i = 0; i < N; ++i) {
			if (Ss[i] == "AB") {
				if (A == 0 && B == 0) {
					cout << "No" << endl;
					return 0;
				}
				if (A >= B) {
					--A;
					++B;
					queue.emplace_back("B");
				}
				else {
					++A;
					--B;
					queue.emplace_back("A");
				}
			}
			else if (Ss[i] == "AC") {
				if (A == 0 && C == 0) {
					cout << "No" << endl;
					return 0;
				}
				if (A >= C) {
					--A;
					++C;
					queue.emplace_back("C");
				}
				else {
					++A;
					--C;
					queue.emplace_back("A");
				}
			}
			else if (Ss[i] == "BC") {
				if (B == 0 && C == 0) {
					cout << "No" << endl;
					return 0;
				}
				if (B >= C) {
					--B;
					++C;
					queue.emplace_back("C");
				}
				else {
					++B;
					--C;
					queue.emplace_back("B");
				}
			}
		}

		cout << "Yes" << endl;
		for (ll i = 0; i < N; ++i) {
			cout << queue[i] << endl;
		}
		return 0;
	}
	if (A + B + C == 1) {
		vector<string> queue;
		for (ll i = 0; i < N; ++i) {
			if (A == 1) {
				if (Ss[i] == "BC") {
					cout << "No" << endl;
					return 0;
				}
				if (Ss[i] == "AB") {
					A = 0;
					B = 1;
					queue.emplace_back("B");
				}
				else if (Ss[i] == "AC") {
					A = 0;
					C = 1;
					queue.emplace_back("C");
				}
			}
			else if (B == 1) {
				if (Ss[i] == "AC") {
					cout << "No" << endl;
					return 0;
				}
				if (Ss[i] == "AB") {
					B = 0;
					A = 1;
					queue.emplace_back("A");
				}
				else if (Ss[i] == "BC") {
					B = 0;
					C = 1;
					queue.emplace_back("C");
				}
			}
			else if (C == 1) {
				if (Ss[i] == "AB") {
					cout << "No" << endl;
					return 0;
				}
				if (Ss[i] == "AC") {
					C = 0;
					A = 1;
					queue.emplace_back("A");
				}
				else if (Ss[i] == "BC") {
					C = 0;
					B = 1;
					queue.emplace_back("B");
				}
			}
		}

		cout << "Yes" << endl;
		for (ll i = 0; i < N; ++i) {
			cout << queue[i] << endl;
		}
		return 0;
	}
	if (A + B + C == 2) {
		vector<string> queue;
		for (ll i = 0; i < N; ++i) {
			if (A == 2) {
				if (Ss[i] == "BC") {
					cout << "No" << endl;
					return 0;
				}
				if (Ss[i] == "AB") {
					A = 1;
					B = 1;
					queue.emplace_back("B");
				}
				else if (Ss[i] == "AC") {
					A = 1;
					C = 1;
					queue.emplace_back("C");
				}
			}
			else if (B == 2) {
				if (Ss[i] == "AC") {
					cout << "No" << endl;
					return 0;
				}
				if (Ss[i] == "AB") {
					B = 1;
					A = 1;
					queue.emplace_back("A");
				}
				else if (Ss[i] == "BC") {
					B = 1;
					C = 1;
					queue.emplace_back("C");
				}
			}
			else if (C == 2) {
				if (Ss[i] == "AB") {
					cout << "No" << endl;
					return 0;
				}
				if (Ss[i] == "AC") {
					C = 1;
					A = 1;
					queue.emplace_back("A");
				}
				else if (Ss[i] == "BC") {
					C = 1;
					B = 1;
					queue.emplace_back("B");
				}
			}
			else if (A == 1 && B == 1) {
				if (Ss[i] == "AB") {
					if (i + 1 < N) {
						if (Ss[i + 1] == "AB") {
							A = 2;
							B = 0;
							queue.emplace_back("A");
						}
						else if (Ss[i + 1] == "AC") {
							A = 2;
							B = 0;
							queue.emplace_back("A");
						}
						else if (Ss[i + 1] == "BC") {
							A = 0;
							B = 2;
							queue.emplace_back("B");
						}
					}
				}
				else if (Ss[i] == "AC") {
					A = 0;
					C = 1;
					queue.emplace_back("C");
				}
				else if (Ss[i] == "BC") {
					B = 0;
					C = 1;
					queue.emplace_back("C");
				}
			}
			else if (B == 1 && C == 1) {
				if (Ss[i] == "BC") {
					if (i + 1 < N) {
						if (Ss[i + 1] == "BC") {
							B = 2;
							C = 0;
							queue.emplace_back("B");
						}
						else if (Ss[i + 1] == "AC") {
							B = 0;
							C = 2;
							queue.emplace_back("C");
						}
						else if (Ss[i + 1] == "AB") {
							B = 2;
							C = 0;
							queue.emplace_back("B");
						}
					}
					else {
						queue.emplace_back("B");
					}
				}
				else if (Ss[i] == "AC") {
					A = 1;
					C = 0;
					queue.emplace_back("A");
				}
				else if (Ss[i] == "AB") {
					A = 1;
					B = 0;
					queue.emplace_back("A");
				}
			}
			else if (A == 1 && C == 1) {
				if (Ss[i] == "AC") {
					if (i + 1 < N) {
						if (Ss[i + 1] == "BC") {
							C = 2;
							A = 0;
							queue.emplace_back("C");
						}
						else if (Ss[i + 1] == "AC") {
							A = 2;
							C = 0;
							queue.emplace_back("A");
						}
						else if (Ss[i + 1] == "AB") {
							A = 2;
							C = 0;
							queue.emplace_back("A");
						}
					}
					else {
						queue.emplace_back("A");
					}
				}
				else if (Ss[i] == "AB") {
					B = 1;
					A = 0;
					queue.emplace_back("B");
				}
				else if (Ss[i] == "BC") {
					B = 1;
					C = 0;
					queue.emplace_back("B");
				}
			}
		}

		cout << "Yes" << endl;
		for (ll i = 0; i < N; ++i) {
			cout << queue[i] << endl;
		}
		return 0;
	}
}
