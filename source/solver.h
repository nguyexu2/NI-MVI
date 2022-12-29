#pragma once
#include "include.cpp"
#include "structures.h"

assignments defaultAssigment(const int varCount)
{
	assignments ret(varCount + 1); // reserve 0
	iota(ret.begin(), ret.end(), 0);
	return ret;
}

assignments randomAssigment(const int varCount)
{
	assignments ret(varCount + 1); // reserve 0
	FOR(i, 1, ret.size()) ret[i] = i * ( getrandInt(0, 1) ? 1 : -1 );
	return ret;
}

bool existsSolution(const formula & instance, const vector<assignments> & population)
{
	for(const auto & config : population) if(instance.isSat(config)) return true;
	return false;
}

assignments solve(const formula & instance)
{
	const int populationSize = 100;
	vector<assignments> population;
	FOR(i, 0, populationSize) population.push_back(randomAssigment(instance.variables));
	//creates sorted population by number of solved clauses
	sort(population.begin(), population.end(), [&](const auto &a, const auto &b)
		 { return instance.solvedClauses(a) > instance.solvedClauses(b); });
		 
	const int maxIterations = 5000;
	FOR(it, 0, maxIterations)
	{
		if(existsSolution(instance, population))
			break;

		// selection

		// crossing

		// mutation
	}

	return population.front();
}