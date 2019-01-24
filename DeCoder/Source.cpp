#include <iostream>
#include <string>
using namespace std;




void main() {

	char filename;
	char encryptionMethod;
	cout << "________         _________            .___            " << endl;
	cout << "\\______ \\   ____ \\_   ___ \\  ____   __| _/___________ " << endl;
	cout << " |    |  \\_/ __ \\/    \\  \\/ /  _ \\ / __ |/ __ \\_  __ \\" << endl;
	cout << " |    `   \\  ___/\\     \\___(  <_> ) /_/ \\  ___/|  | \\/" << endl;
	cout << "/_______  /\\___  >\\______  /\\____/\\____ |\\___  >__|   " << endl;
	cout << "        \\/     \\/        \\/            \\/    \\/       " << endl;
	cout << endl;
	cout << "Enter path + filename to encrypt the file: ";
	cin >> filename;
	cin.clear(); cin.ignore(INT_MAX, '\n');
/*if (strlen(filename) == 0) {

}*/
	cout << "Please choose an encryption method (1-3)" << endl;
	cout << "1) XOR" << endl;
	cout << "2) ..." << endl;
	cout << "3) ..." << endl;
	cin >> encryptionMethod;
	switch (encryptionMethod)
	{
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	default:
		cout << "Please enter a valid number!"  + encryptionMethod<< endl;
		break;
	}

	system("pause");

}


