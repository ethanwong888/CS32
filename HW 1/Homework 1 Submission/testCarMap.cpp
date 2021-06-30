#include "CarMap.h"
#include <iostream>
#include <cassert>
using namespace std;


int main()
{
	CarMap test;  
	if (test.fleetSize() == 0)
		cout << "fleetsize passes" << endl;
	test.addCar("john");
	test.addCar("robert");
	test.addCar("jose");
	test.addCar("kirby");

	test.drive("john", 69.0);
	test.drive("robert", 42.0);
	test.drive("jose", 78.0);
	test.drive("kirby", 19.5);
	test.print();
	
}




