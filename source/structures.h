#pragma once 
#include "include.cpp"


using variable = int;

struct assignments
{
	// each value is in range {-1, 1};
	// position[0] is reserved, will not used
	// to see if variable x is set on true or false, use assigment[abs(x)];
	vector<int> assigment;

	int getAssigment(const variable &x) const { return assigment[abs(x)]; }
	bool evaluate(const variable &x) const { return x * getAssigment(x); }
};

// each literal has a label, negative value means the same variable is in negation 
struct literal
{
	variable var;
	bool isSat(const assignments &values) const { return values.evaluate(var); }
};

// a clause is a disjunction of literals
// clause c1 = (x1 v \neg x2 v x3)
struct clause
{
	bool isSat(const assignments & values) const
	{
		for(const auto & lit : literals)
			if(lit.isSat(values)) return true;
		return false;
	}
	vector<literal> literals;
};

// a formula in SAT is a conjunction of different clauses.
struct formula
{
	bool isSat(const assignments & values) const
	{
		for(const auto & clause : clauses)
			if(!clause.isSat(values)) return false;
		return true;
	}
	vector<clause> clauses;	
};