#pragma once
#include "include.cpp"
#include "structures.h"

//------------------------------
//fitness

int getFitness(const formula & instance, const assignments & config)
{
	return instance.solvedClauses(config);
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

void fillThePopulation(const formula &instance, vector<assignments> &population, int finalPopulationSize)
{
	int oldCnt = population.size(), cnt = finalPopulationSize - oldCnt;
	FOR(i, 0, cnt)
	{
		int first, second;
		do {first = getrandInt(0, oldCnt), second = getrandInt(0, oldCnt);} while(first == second);
		auto [ch1, ch2] = crossover(population[first], population[second]);

		//take the better of 2 children
		population.push_back(instance.solvedClauses(ch1) > instance.solvedClauses(ch2) ? ch1 : ch2);
	}
}

//------------------------------

//selection of population
vector<assignments> roulette(const formula &instance, const vector<assignments> &population,
							 double elitismRate)
{
	vector<assignments> ret;

	vector<pair<int, int>> sortIdx;
	FOR(i, 0, population.size())
		sortIdx.push_back({getFitness(instance, population[i]), i});

	//sort by number of solved clauses
	sort(sortIdx.begin(), sortIdx.end(), std::greater<pair<int, int>>{});

	//select the best only
	FOR(i, 0, elitismRate*population.size())
		ret.push_back(population[sortIdx[i].second]);

	int goalSize = population.size();
	fillThePopulation(instance, ret, goalSize);

	return ret;
}

vector<assignments> tournament(const formula &instance, const vector<assignments> &population,
							   double probability, double elitismRate)
{

}

//------------------------------

assignments mutation(const assignments & config, double changeRate)
{
	assignments ret = config;
	int cnt = 1; //todo: generate

	set<int> flipPos;
	FOR(i, 0, cnt) flipPos.insert(getrandInt(1, config.size()));

	for(auto pos : flipPos) ret[pos] = -ret[pos];
	return ret;
}

void mutatePopulation(vector<assignments> & population, double changeRate)
{
	int changedIndividuals = population.size()/4; //todo:

	FOR(i, 0, changedIndividuals)
	{
		int idx = getrandInt(0, population.size());
		population[idx] = mutation(population[idx], changeRate); //set change rate
	}
}
