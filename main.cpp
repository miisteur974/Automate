#include "Automate.h"

int main(int argc, char** argv)
{
	Automate n1 = Automate("automate.conf", "abcdefghijklmnopqrstuvwxyz ");

	status result = n1.send("a", "abcdef");

	switch(result)
	{
	case noresult:
		cout << " No match found !" << endl;
		break;
	case found:
		cout << " A match is found ! " << endl;
		break;
	case error:
		cout << " An error as occured ! " << endl;
	}
	
	system("pause");
	return EXIT_SUCCESS;
}
