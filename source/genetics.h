#pragma once
#include "include.cpp"
#include "structures.h"

//------------------------------
//fitness

int getFitness(const formula & instance, const assignments & solution)
{
	return instance.solvedClauses(solution);
}

//------------------------------
// operators

pair<assignments, assignments> crossover(assignments a, assignments b, int splits = 1)
{
	set<int> splitPos;
	FOR(i, 0, splits) splitPos.insert(getrandInt(0, a.size()));

	vector<int> vSplitPos(splitPos.begin(), splitPos.end());
	for(int i = 0; i < (int)vSplitPos.size() -1; i+=2) //on even swap, on odd keep as it is
	{
		FOR(idx, vSplitPos[i], vSplitPos[i+1])
			swap(a[idx], b[idx]);
	}
	return {a, b};
}

void fillThePopulation(const formula &instance, vector<assignments> &population, const GAConfig & conf)
{
	int oldCnt = population.size(), cnt = conf.populationSize - oldCnt;
	FOR(i, 0, cnt)
	{
		int first, second;
		do {first = getrandInt(0, oldCnt), second = getrandInt(0, oldCnt);} while(first == second);
		auto [ch1, ch2] = crossover(population[first], population[second]); //todo

		//take the better of 2 children
		population.push_back(instance.solvedClauses(ch1) > instance.solvedClauses(ch2) ? ch1 : ch2);
	}
}

//------------------------------

//selection of population
vector<assignments> roulette(const formula &instance, const vector<assignments> &population,
							 const GAConfig & conf)
{
	vector<assignments> ret;

	vector<int> wheel;
	//cumulated sum to find where a number is on the wheel using binary search
	wheel.push_back(getFitness(instance, population.front()));
	FOR(i, 1, population.size())
		wheel.push_back(getFitness(instance, population[i]) + wheel.back());

	//select the with bias towards the better
	FOR(i, 0, conf.elitismRate*population.size())
	{
		int score = getrandInt(0, wheel.back());
		auto find = lower_bound(wheel.begin(), wheel.end(), score);
		int idx = find - wheel.begin();
		ret.push_back(population[idx]);
	}

	return ret;
}

// vector<assignments> tournament(const formula &instance, const vector<assignments> &population,
// 							   double probability, double elitismRate)
// {

// }

//------------------------------

assignments mutation(const assignments & config, const GAConfig & conf)
{
	//at least 1 flip
	const int cnt = max(1, (int)(conf.chromosomeChangeRate * config.size()));

	set<int> flipPos;
	FOR(i, 0, cnt) flipPos.insert(getrandInt(1, config.size()));

	assignments ret = config;
	for(auto pos : flipPos) ret[pos] = -ret[pos];
	return ret;
}

void mutatePopulation(vector<assignments> & population, const GAConfig & conf)
{
	int changedIndividuals = population.size() * conf.mutatedIndividuals;

	FOR(i, 0, changedIndividuals)
	{
		int idx = getrandInt(0, population.size());
		population[idx] = mutation(population[idx], conf);
	}
}
