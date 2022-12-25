#pragma once 
#include "include.cpp"

// each value is in range {-1, 1};
// position[0] is reserved, will not used
// to see if variable x is set on true or false, use assigment[abs(x)];
using assignments = vector<int>;

using variable = int;

// each literal has a label, negative value means the same variable is in negation 
struct literal
{
	variable var;
	bool isSat(const assignments &values) const
	{
		return var * values[abs(var)];
	}
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

	int solvedClauses(const assignments & values) const
	{
		int ret = 0;
		for(const auto & clause : clauses)
			if(clause.isSat(values)) ret++;
		return ret;
	}
	vector<clause> clauses;
	int variables;

	formula(const int varCount) : variables(varCount){}
};