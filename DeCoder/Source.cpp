#include <iostream>
#include <string>
#include "Encryptor.h"
#include "dll.h"

using namespace std;

void encrypt();
void decrypt();
char selection;
Encryptor* encryptor = new Encryptor();

void main() {
	cout << "________         _________            .___            " << endl;
	cout << "\\______ \\   ____ \\_   ___ \\  ____   __| _/___________ " << endl;
	cout << " |    |  \\_/ __ \\/    \\  \\/ /  _ \\ / __ |/ __ \\_  __ \\" << endl;
	cout << " |    `   \\  ___/\\     \\___(  <_> ) /_/ \\  ___/|  | \\/" << endl;
	cout << "/_______  /\\___  >\\______  /\\____/\\____ |\\___  >__|   " << endl;
	cout << "        \\/     \\/        \\/            \\/    \\/       " << endl;
	cout << endl;
	cout << "Select 1 to encrypt a file. Select 2 for decrypting" << endl;
	cin >> selection;
	switch (selection)
	{
	case '1':
		encrypt();
		break;
	case '2':
		decrypt();
	default:
		break;
	}

	system("pause");
}


void encrypt()
{
	char filename;
	char encryptionMethod;
	char abc[] = { 'a' };
	char key[] = { 'f' };

	

	cout << "Enter path + filename to encrypt the file: ";
	cin >> filename;
	cin.clear(); cin.ignore(INT_MAX, '\n');
	/*if (strlen(filename) == 0) {

	}*/
	cout << "Please choose an encryption method (1-3)" << endl;
	cout << "1) XOR" << endl;
	cout << "2) AES encryption" << endl;
	cin >> encryptionMethod;
	switch (encryptionMethod)
	{
	case '1':
		cout << "Hallo" << endl;
		encryptor->encryptXOR(key, abc);
		break;
	case '2':

		break;
	default:
		cout << "Please enter a valid number!" + encryptionMethod << endl;
		break;
	}



}

void decrypt()
{
	char path;
	cout << "Enter path to the encrypted file: ";
	cin >> path;

}
