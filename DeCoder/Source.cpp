#include <iostream>
#include <string>
#include "Encryptor.h"
//#include "Source.h"
#include "dll.h"

using namespace std;

void encrypt();
void decrypt();

Encryptor* encryptor = new Encryptor();

int main() {
	
	bool doAgain = false;
	do
	{
		cout << "________         _________            .___            " << endl;
		cout << "\\______ \\   ____ \\_   ___ \\  ____   __| _/___________ " << endl;
		cout << " |    |  \\_/ __ \\/    \\  \\/ /  _ \\ / __ |/ __ \\_  __ \\" << endl;
		cout << " |    `   \\  ___/\\     \\___(  <_> ) /_/ \\  ___/|  | \\/" << endl;
		cout << "/_______  /\\___  >\\______  /\\____/\\____ |\\___  >__|   " << endl;
		cout << "        \\/     \\/        \\/            \\/    \\/       " << endl;
		cout << endl;
		char input;
		char selection;
		do {
			cout << "Select 1 to encrypt a file. Select 2 for decrypting: ";
			cin >> selection;
			switch (selection)
			{
			case '1':
				encrypt();
				break;
			case '2':
				decrypt();
			default:
				cout << "Wrong input!" << endl;
				break;
			}
		} while (selection != '1' && selection != '2');

		do {

			cout << "Do you want to encrypt or decrypt another file? (y/n)" << endl;
			cin >> input;
			if (input == 'y')
			{
				doAgain = true;
				cout << endl << string(55, '*') << endl;
			}
			else if (input == 'n')
			{
				doAgain = false;
			}
			else {
				cout << "Wrong input!" << endl;
			}
		} while (input != 'y' && input != 'n');
	} while (doAgain == true);
	return 0;
}


void encrypt()
{
	char path[100];
	const char *savePathChar;
	string savePath = "";
	char encryptionMethod;
	char abc[] = { 'a' };
	char key[] = { 'f' };

	cout << "Enter path + filename to encrypt the file: ";
	cin >> path;
	cin.clear(); 
	cin.ignore(INT_MAX, '\n');

	cout << "Enter path where the file should be saved (ending with \\): ";
	cin >> savePath;
	cin.clear();
	cin.ignore(INT_MAX, '\n');
	savePath += "encryptedFile.txt";
	savePathChar = savePath.c_str();

	do {
		cout << "Please choose an encryption method (1-3)" << endl;
		cout << "1) XOR" << endl;
		cout << "2) AES encryption" << endl;
		cout << "3) Cesar encryption" << endl;
		cin >> encryptionMethod;

		switch (encryptionMethod)
		{
		case '1':
			encryptor->encryptXOR(path, savePathChar);
			break;
		case '2':
			encryptor->encryptAES(path, savePathChar);
			break;
		case '3':
			encryptor->encryptCesar(path, savePathChar);
			break;
		default:
			cout << "Please enter a valid number!" << endl;
			encryptionMethod = '%';
			break;
		}
	} while (encryptionMethod == '%');
}

void decrypt()
{
	char selection;
	char path[100];
	const char* savePathChar;
	string savePath = "";

	cout << "Enter path to the encrypted file: ";
	cin >> path;

	cout << "Enter path where the file should be saved: ";
	cin >> savePath;
	cin.clear();
	cin.ignore(INT_MAX, '\n');
	savePath += "DecryptedFile.txt";
	savePathChar = savePath.c_str();

	cout << "Please select chosen encryption method: " << endl;
	cout << "1) XOR" << endl;
	cout << "2) AES encryption" << endl;
	cout << "3) Cesar encryption" << endl;
	cin >> selection;
	cin.clear();
	cin.ignore(INT_MAX, '\n');

	switch (selection)
	{
	case '1':
		encryptor->encryptXOR(path,savePathChar);
		break;
	case '2':
		encryptor->decryptAES(path, savePathChar);
		break;
	case '3':
		encryptor->decryptCesar(path, savePathChar);
		break;
	default:
		break;
	}
}
