#include "include.cpp"
#include "timer.h"
#include "structures.h"
#include "loader.h"
#include "solver.h"

int main(int argc, char ** argv)
{
	initRNG();
	auto conf = parseParams(argc, argv);
	auto instance = load(conf.location); 
	auto solution = solve(instance);
	print(instance, solution);
}