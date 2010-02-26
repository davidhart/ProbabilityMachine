#include "MathsTests.h"
#include "simulation.h"

#include <iostream>

int main(int argc, char ** argv)
{
	MathsLibTests::DoAllTests(std::cout);

	Simulation sim;
	return sim.Run();;
}
