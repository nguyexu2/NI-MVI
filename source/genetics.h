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

void crossover(assignments & a, assignments & b, int splits = 1)
{
	set<int> splitPos;
	FOR(i, 0, splits) splitPos.insert(getrandInt(0, a.size()));

	vector<int> vSplitPos(splitPos.begin(), splitPos.end());
	for(int i = 0; i < (int)vSplitPos.size() -1; i+=2) //on even swap, on odd keep as it is
	{
		FOR(idx, vSplitPos[i], vSplitPos[i+1])
			swap(a[idx], b[idx]);
	}
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
