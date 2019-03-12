#include "abmSimulator.h"


int main()
{
	abmSimulator *prototype = new abmSimulator();

	//This function is the main "loop" of the program.
	prototype->run();
	
	delete prototype;

	return 0;
}
