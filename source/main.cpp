#include "include.cpp"
#include "timer.h"
#include "structures.h"
#include "loader.h"
#include "solver.h"

int main(int argc, char ** argv)
{
	initRNG();
	auto conf = parseParams(argc, argv);
	auto instance = loadInstance(conf.instanceLocation);
	auto GAParams = loadConfig(conf.GAParamLocation);

	TIMER t;
	t.start(true);
	auto solution = solve(instance, GAParams);
	t.stop(false);
	
	print(instance, solution, t.get(), conf.verbose);
}