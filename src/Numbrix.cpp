// In the name of God
// Numbrix v1.0
// Ehsan Marufi Azar, Apr 2013

#include "stdafx.h"
#include "NumbrixGenerator.h"
#include "debugging.h"

#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	cout << "In the name of God" << endl
		<<  "Numbrix v1.0" << endl
		<<  "Ehsan Marufi Azar, Apr 17, 2013 (c)" << endl << endl
		<<  "Please enter the number of runs: ";
	
	//srand( (unsigned)time(0) );
	unsigned int uiTestRunCount = 101, startTime = 0;
	cin >> uiTestRunCount;
	cout << endl;

	for ( unsigned int i = 0; i < uiTestRunCount; i++ )
	{
		startTime = (unsigned)time( 0 );
		NumbrixGenerator::CNumbrixGenerator oNumbrixGenerator;
		cout << endl << ">> Run #" << i +1 << ": (" << (unsigned)time(0) - startTime << "s)" << endl;
		Numbrix::displayNumbrix( oNumbrixGenerator );
	}
	return 0;
}

