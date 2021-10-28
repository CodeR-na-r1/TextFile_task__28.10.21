#include <iostream>
#include "TextFile.h"

using namespace std;

int main()
{
	TextFile one("data_1.dat");
	TextFile two("data_2.dat");
	//TextFile res = one + two;
	cout << "operation + completed" << endl;

	cin.get();

	TextFile res = one - two;
	cout << "operation - completed" << endl;
	return 0;
}