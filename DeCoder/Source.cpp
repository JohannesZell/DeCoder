#include <iostream>
#include <string>
#include "Encryptor.h"
//#include "Source.h"
#include "dll.h"

using namespace std;

void encrypt();
void decrypt();

Encryptor* encryptor = new Encryptor();

void main() {
	char selection;

	cout << "________         _________            .___            " << endl;
	cout << "\\______ \\   ____ \\_   ___ \\  ____   __| _/___________ " << endl;
	cout << " |    |  \\_/ __ \\/    \\  \\/ /  _ \\ / __ |/ __ \\_  __ \\" << endl;
	cout << " |    `   \\  ___/\\     \\___(  <_> ) /_/ \\  ___/|  | \\/" << endl;
	cout << "/_______  /\\___  >\\______  /\\____/\\____ |\\___  >__|   " << endl;
	cout << "        \\/     \\/        \\/            \\/    \\/       " << endl;
	cout << endl;
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
		break;
	}
	system("pause");
}


void encrypt()
{
	char path[100];
	const char *c;
	string savePath = "";
	char encryptionMethod;
	char abc[] = { 'a' };
	char key[] = { 'f' };

	cout << "Enter path + filename to encrypt the file: ";
	cin >> path;
	cin.clear(); 
	cin.ignore(INT_MAX, '\n');

	cout << "Enter path where the file should be saved: ";
	cin >> savePath;
	cin.clear();
	cin.ignore(INT_MAX, '\n');
	savePath += "encryptedFile.txt";
	c = savePath.c_str();

	cout << "Please choose an encryption method (1-3)" << endl;
	cout << "1) XOR" << endl;
	cout << "2) AES encryption" << endl;
	cout << "3) Cesar encryption" << endl;
	cin >> encryptionMethod;

	switch (encryptionMethod)
	{
	case '1':
		cout << "Hallo" << endl;
		encryptor->encryptXOR(path, path);
		break;
	case '2':
		encryptor->encryptAES(path, c);
		break;
	case '3':
		encryptor->encryptCesar(path, path);
		break;
	default:
		cout << "Please enter a valid number!"<< endl;
		break;
	}

}

void decrypt()
{
	char selection;
	char path[100];
	cout << "Enter path to the encrypted file: ";
	cin >> path;
	cout << "Please ....: " << endl;
	cin >> selection;
	cin.clear();
	cin.ignore(INT_MAX, '\n');

	switch (selection)
	{
	case '1':

		break;
	case '2':

		break;
	case '3':
		encryptor->decryptCesar(path, path + 'd');
		break;
	default:
		break;
	}


}
