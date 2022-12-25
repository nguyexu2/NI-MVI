#pragma once
#include "include.cpp"
#include "structures.h"

formula load(const string & location)
{
	ifstream is(location);
	auto get_uc_line = [](ifstream & is) {
		stringstream ss;
		string line;
		do getline(is, line); while(line[0] == 'c');
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
		while(ls >> lit)
		{
			assert(-n <= lit && lit <= n && lit != 0);
			c.literals.push_back({lit});
		}
		instance.clauses.push_back(move(c));
	}
	return instance;
}