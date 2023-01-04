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

double getAverageFitness(const formula & instance, const vector<assignments> & population)
{
	double sum = 0;
	for(const auto & x : population) sum += getFitness(instance, x);
	return sum / population.size();
}


assignments solve1Iteration(const formula &instance, const GAConfig & conf)
{
	vector<assignments> population;
	FOR(i, 0, conf.populationSize) population.push_back(randomAssigment(instance.variables));

	assignments best =  getBestAssignment(instance, population);

	cerr << "it:" << 0 << "," << getAverageFitness(instance, population) << "," << getFitness(instance, best) << '\n';
	// deb(getAverageFitness(instance, population));
	// deb(getFitness(instance, best));

	FOR(it, 1, conf.maxIterations)
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

		cerr << "it:" << it << "," << getAverageFitness(instance, population) << "," << getFitness(instance, best) << '\n';
		if(it %20) cerr.flush();

		if(getFitness(instance, newBest) > getFitness(instance, best))
		{
			best = newBest;
			// deb(it);
			// deb(getFitness(instance, best));
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