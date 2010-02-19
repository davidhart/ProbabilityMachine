#include "MathsTests.h"

#include <iostream>

using std::cout;
using std::endl;

void main()
{
	cout<<"Tests Start" << endl;
	MathsLibTests::DoAllTests(cout);
	cout<<"All Tests Complete"<<endl;
}
