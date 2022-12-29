#pragma once
#include "include.cpp"
#include "structures.h"

//------------------------------
//selection of population
vector<assignments> roulette(const formula &instance, const vector<assignments> &population,
							 double elitismRate)
{
	vector<assignments> ret;

	return ret;
}

vector<assignments> tournament(const formula &instance, const vector<assignments> &population,
							   double probability, double elitismRate)
{

}

//------------------------------
// operators

assignments crossover(const assignments & a, const assignments & b, int splits)
{
	assignments ret = a;
	set<int> splitPos;
	FOR(i, 0, splits) splitPos.insert(getrandInt(0, a.size()));

	vector<int> vSplitPos(splitPos.begin(), splitPos.end());
	FOR(i, 0, vSplitPos.size() - 1)
	{
		auto s = vSplitPos[i], e = vSplitPos[i+1];
		FOR(j, s, e) ret[j] = i % 2? a[j] : b[j];
	}
	
	return ret;
}

assignments mutation(const assignments & config, double changeRate)
{

}

//------------------------------
//fitness

int getFitness(const formula & instance, const assignments & config)
{
	return instance.solvedClauses(config);
}
