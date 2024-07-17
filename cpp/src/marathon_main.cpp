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

#include <sstream>
#include <iostream>
#include <iomanip>

#include <complex>
#include <numeric>
#include <utility>

#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cctype>
#include <cstring>
#include <ctime>

#include <random>

// namespace
using namespace std;

// type alias
using ll = long long;
using ull = unsigned long long;
using comp = complex<double>;

// constant
const ll MOD = 1000000007LL;
const double PI = 3.14159265358979323846;
const double TLE = 2.0;

// conversion
inline ll toint(string s)
{
	ll v;
	istringstream sin(s);
	sin >> v;
	return v;
}
template <class t>
inline string tostring(t x)
{
	ostringstream sout;
	sout << x;
	return sout.str();
}

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

#define MAX_VALUE 9223372036854787LL

template <class T, class... Args>
auto make_multiple_vector(T default_value)
{
	return T(default_value);
}

template <class T, class... Args>
auto make_multiple_vector(T default_value, ull size, Args... args)
{
	using value_type = std::decay_t<decltype(make_multiple_vector<T>(default_value, args...))>;
	return vector<value_type>(size, make_multiple_vector<T>(default_value, args...));
}

enum struct CommandType
{
	DirectionUp,
	DirectionDown,
	DirectionLeft,
	DirectionRight,
	Load,
	Unload,
};

struct Command
{
	CommandType command_type;
	ll value = 0;
	Command(CommandType command_type) : command_type(command_type), value(0) {}
	Command(CommandType command_type, ll value) : command_type(command_type), value(value) {}
};

string to_string(Command command)
{
	if (command.command_type == CommandType::DirectionUp)
	{
		return "U";
	}
	if (command.command_type == CommandType::DirectionDown)
	{
		return "D";
	}
	if (command.command_type == CommandType::DirectionLeft)
	{
		return "L";
	}
	if (command.command_type == CommandType::DirectionRight)
	{
		return "R";
	}
	if (command.command_type == CommandType::Load)
	{
		ll value = command.value;
		return "+" + tostring(value);
	}
	if (command.command_type == CommandType::Unload)
	{
		ll value = command.value;
		return "-" + tostring(value);
	}
}

Command create_luggage_change(ll value)
{
	if (value > 0)
	{
		return Command(CommandType::Load, value);
	}
	return Command(CommandType::Unload, -value);
}

class Car
{
private:
	ll luggage;
	ll cost;
	vector<vector<ll>> hs;
	ll _i, _j;
	ll N;

public:
	vector<Command> commands;
	Car(vector<vector<ll>> hs) : luggage(0), cost(0), hs(hs), _i(0), _j(0), N(hs.size()) {}
	Command select_command()
	{
		if (hs[_i][_j] != 0LL)
		{
			return create_luggage_change(hs[_i][_j]);
		}

		if (_i % 2LL == 0LL)
		{
			if (_j + 1LL == N)
			{
				return Command(CommandType::DirectionDown);
			}
			return Command(CommandType::DirectionRight);
		}
		else
		{
			if (_j <= 0LL)
			{
				return Command(CommandType::DirectionDown);
			}
			return Command(CommandType::DirectionLeft);
		}
	};

	bool end()
	{
		REPD(i, 0, N)
		REPD(j, 0, N)
		{
			if (hs[i][j] != 0LL)
			{
				return false;
			}
		}
		return true;
	}

	bool process_command(Command command)
	{
		if (command.command_type == CommandType::DirectionUp)
		{
			if (_i <= 0LL)
			{
				return false;
			}
			--_i;
			return true;
		}
		if (command.command_type == CommandType::DirectionDown)
		{
			if (_i >= N)
			{
				return false;
			}
			++_i;
			return true;
		}
		if (command.command_type == CommandType::DirectionLeft)
		{
			if (_j <= 0LL)
			{
				return false;
			}
			--_j;
			return true;
		}
		if (command.command_type == CommandType::DirectionRight)
		{
			if (_j >= N)
			{
				return false;
			}
			++_j;
			return true;
		}
		if (command.command_type == CommandType::Load)
		{
			auto value = command.value;
			hs[_i][_j] -= value;
			cost += value;
			return true;
		}
		if (command.command_type == CommandType::Unload)
		{
			auto value = command.value;
			hs[_i][_j] += value;
			cost += value;
			return true;
		}
		return false;
	};

	bool action()
	{
		auto command = select_command();
		if (!process_command(command))
		{
			return false;
		}
		commands.push_back(command);
		return true;
	}
};

int solve()
{
	// random_device seed_gen;
	// mt19937_64 engine(seed_gen());

	ll N;
	cin >> N;
	auto hs = make_multiple_vector(0LL, N, N);
	REPD(i, 0, N)
	REPD(j, 0, N)
	cin >> hs[i][j];

	Car car(hs);
	while (!car.end())
	{
		car.action();
	}
	for (ll i = 0; i < car.commands.size(); ++i)
	{
		cout << to_string(car.commands[i]) << endl;
	}

	return 0;
}

int main()
{
	cin.tie(0);
	ios::sync_with_stdio(false);

	solve();

	return 0;
}
