#include "MathsTests.h"
#include "simulation.h"

#include <iostream>

int main(int, char **)
{
	MathsLibTests::DoAllTests(std::cout);

	Simulation sim;
	return sim.Run();
}
