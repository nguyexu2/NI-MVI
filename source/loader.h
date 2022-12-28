#pragma once
#include "include.cpp"
#include "structures.h"

struct config
{
	string location;
};

config parseParams(int argc, char ** argv)
{
	if(argc != 2)
	{
		cerr << "./a.out [file location]" << endl;
		exit(1);
	}

	config ret;
	ret.location = string(argv[1]);
	return ret;
}

formula load(const string & location)
{
	ifstream is(location);
	auto get_uc_line = [](ifstream & is) {
		stringstream ss;
		string line;
		do {getline(is, line); } while(line[0] == 'c');
		return stringstream(move(line));
	};

	auto ls = get_uc_line(is);
	string p, cnf;
	int n = 0, m = 0;

	ls >> p >> cnf >> n >> m;
	assert(ls && p == "p" && cnf == "cnf");
	
	formula instance(n);
	FOR(i, 0, m)
	{
		ls = get_uc_line(is);
		clause c;
		int lit;
		while(ls >> lit && lit != 0)
		{
			assert(-n <= lit && lit <= n);
			c.literals.push_back({lit});
		}
		instance.clauses.push_back(move(c));
	}
	return instance;
}

void print(const formula & instance, const assignments & solution)
{
	cout << (instance.isSat(solution) ? "solved" : "not solved") << endl;
	
	FOR(i, 1, solution.size())
	{
		cout << solution[i] << " ";
	}
	cout << endl;
}