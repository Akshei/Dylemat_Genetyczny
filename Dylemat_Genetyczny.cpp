// Dylemat_Genetyczny.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Prisoner.h"
#include "God.h"
int main()
{
	srand(time(NULL));
	God* x = new God(20, 0,3,4,16,10,"Alcatraz");
	x->run();
	delete(x);


	string a;
	cin >> a;
    return 0;
}

