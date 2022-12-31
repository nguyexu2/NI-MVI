#pragma once
#include "include.cpp"
#include "structures.h"

struct config
{
	string instanceLocation;
	string GAParamLocation = "";
	bool verbose = false;
};

config parseParams(int argc, char ** argv)
{
	if(argc < 2)
	{
		cerr << "./a.out [file location] [optional config file]" << endl;
		exit(1);
	}

	config ret;
	ret.instanceLocation = string(argv[1]);
	ret.GAParamLocation = argc >= 3? string(argv[2]) : "";
	if(argc >= 4)
	{
		stringstream ss(argv[3]);
		ss >> ret.verbose;
	}
	return ret;
}

formula loadInstance(const string & location)
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

GAConfig loadConfig(const string & location)
{
	GAConfig ret;
	if(location == "") return ret; // default config

	ifstream in(location);

	while(!in.eof())
	{
		string field;
		double val;
		if(! (in >> field >> val))
		{
			deb(field)
			cerr << "config file is not valid" << endl;
			exit(1);
		}

		if(field == "populationSize")
			ret.populationSize = val;
		else if(field == "restarts")
			ret.restarts = val;
		else if(field == "maxIterations")
			ret.maxIterations = val;
		else if(field == "elitismRate")
			ret.elitismRate = val;
		else if(field == "mutatedIndividuals")
			ret.mutatedIndividuals = val;
		else if(field == "chromosomeChangeRate")
			ret.chromosomeChangeRate = val;
		else if(field == "splits")
			ret.splits = val;
		else{
			cerr << "config file is not valid, got a weird field";
			exit(1);
		}
	}

	return ret;
}

void print(const formula & instance, const assignments & solution, double time, bool verbose = false)
{
	if(verbose)
	{
		cout << "took " << time << "ms" << endl;
		cout << "solved " << instance.solvedClauses(solution) << "/" << instance.clauses.size() << " clauses" << endl;
		cout << (instance.isSat(solution) ? "solved" : "not solved") << endl;
		
		FOR(i, 1, solution.size())
		{
			cout << solution[i] << " ";
		}
		cout << endl;
	}
	else
	{
		cout << instance.isSat(solution);
		cout << "," << instance.solvedClauses(solution);
		cout << "," << instance.clauses.size();
		cout << "," << time << endl;
	}
}