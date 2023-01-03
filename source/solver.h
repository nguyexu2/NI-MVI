#pragma once
#include "include.cpp"
#include "structures.h"
#include "genetics.h"

assignments defaultAssigment(const int varCount)
{
	assignments ret(varCount + 1); // reserve 0
	iota(ret.begin(), ret.end(), 0);
	return ret;
}

assignments randomAssigment(const int varCount)
{
	assignments ret(varCount + 1); // reserve 0
	FOR(i, 1, ret.size()) ret[i] = i * ( getrandInt(0, 2) ? 1 : -1 );
	return ret;
}

bool existsSolution(const formula & instance, const vector<assignments> & population)
{
	for(const auto & config : population) if(instance.isSat(config)) return true;
	return false;
}

assignments getBestAssignment(const formula & instance, const vector<assignments> & population)
{
	assignments ret = population[0];
	auto score = getFitness(instance, ret);
	FOR(i, 1, population.size())
	{
		auto nScore = getFitness(instance, population[i]);
		if(nScore > score)
		{
			score = nScore;
			ret = population[i];
			if(instance.isSat(ret)) return ret;
		}
	}
	return ret;
}

assignments solve1Iteration(const formula &instance, const GAConfig & conf)
{
	vector<assignments> population;
	FOR(i, 0, conf.populationSize) population.push_back(randomAssigment(instance.variables));
	//creates sorted population by number of solved clauses to get the best solution
	sort(population.begin(), population.end(), [&](const auto &a, const auto &b)
		{ return getFitness(instance, a) > getFitness(instance, b); });

	assignments best = population.front();
		 
	FOR(it, 0, conf.maxIterations)
	{
		if(existsSolution(instance, population))
			break;

		// selection
		population = roulette(instance, population, conf);

		// crossover
		fillThePopulation(instance, population, conf);

		// mutations
		mutatePopulation(population, conf);

		auto newBest = getBestAssignment(instance, population);

		if(getFitness(instance, newBest) > getFitness(instance, best))
		{
			best = newBest;
			// deb(it);
			deb(getFitness(instance, best));
		}
	}

	return best;
}

assignments solve(const formula & instance, const GAConfig & conf)
{
	vector<assignments> solutions;
	FOR(i, 0, conf.restarts +1)
	{
		auto res = solve1Iteration(instance, conf);
		if(instance.isSat(res)) return res;
		solutions.push_back(res);
	}

	return getBestAssignment(instance, solutions);
}