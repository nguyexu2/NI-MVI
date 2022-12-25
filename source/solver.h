#pragma once
#include "include.cpp"
#include "structures.h"

assignments defaultAssigment(const int varCount)
{
	assignments ret(varCount + 1); // reserve 0
	iota(ret.begin(), ret.end(), 0);
	return ret;
}

assignments solve(const formula & instance)
{
	auto asgn = defaultAssigment(instance.variables);

	while(!instance.isSat(asgn))
	{
		auto prev = asgn;	
	}

	return asgn;
}