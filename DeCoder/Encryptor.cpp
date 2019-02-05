#include "Encryptor.h"
#include <iostream>
#include <string.h>
#include "dll.h"

using namespace std;
using namespace CryptoPP;


Encryptor::Encryptor()
{
}


Encryptor::~Encryptor()
{
}

char * Encryptor::encryptXOR(char key[], char * rawData)
{
	cout << "Debugging" << endl;
	int keyLength = sizeof(key);
	int remainingData = sizeof(rawData);
	char encData[1000];
	int step = 0;
	cout << remainingData;

	while (remainingData > 0)
	{
		for (int count = 0; count < keyLength; count++)
		{
			encData[step + count] = (int)rawData[step + count] ^ (int)key[count];
			remainingData = remainingData - 1;
		}
		step = step + keyLength;
	}
	cout << encData << endl;
	//return encData;

	return __nullptr;
}
//CryptoPP::AESEncryption


char * Encryptor::encryptAES(char * rawData)
{
	AutoSeededRandomPool rnd;

	// Generate a random key
	SecByteBlock key(0x00, AES::DEFAULT_KEYLENGTH);
	rnd.GenerateBlock(key, key.size());

	// Generate a random IV
	SecByteBlock iv(AES::BLOCKSIZE);
	rnd.GenerateBlock(iv, iv.size());

	byte plainText[] = "Hello! How are you.";
	size_t messageLen = std::strlen((char*)plainText) + 1;

	//////////////////////////////////////////////////////////////////////////
	// Encrypt

	CFB_Mode<AES>::Encryption cfbEncryption(key, key.size(), iv);
	cfbEncryption.ProcessData(plainText, plainText, messageLen);

	cout << plainText << endl;


	//////////////////////////////////////////////////////////////////////////
	// Decrypt

	CFB_Mode<AES>::Decryption cfbDecryption(key, key.size(), iv);
	cfbDecryption.ProcessData(plainText, plainText, messageLen);
	cout << plainText;
	return nullptr;
}

////////////////////////////
// CAESAR PIN
////////////////////////////


// DEFINITION 
char ch;

//Array for PIN
int cool[5];

//Counter for looping the array
int cc;

// ENCRYPTION
int encrypt(string sourcepath, string destpath) {
	{
		fstream fin(sourcepath, fstream::in);
		fstream fout(destpath, fstream::out);
		//Get PIN
		cout << "Please enter your 5 digit PIN" << endl;

		for (int i = 0; i < 5; i++)
			cin >> cool[i];

		cout << endl;

		//Encrypt
		while (fin >> noskipws >> ch) {
			int ich = (int)ch;
			ich = ich + cool[cc];
			cc = ((++cc) % 5);
			char ch2 = (char)ich;
			cout << ch2;
			fout << ch2;
		}

		cout << endl;
		system("Pause");
	}
	return 0;
}

//DECRYPTION
int decrypt(string sourcepath, string destpath) {
	{
		fstream fin(sourcepath, fstream::in);
		fstream fout(destpath, fstream::out);
		//Get PIN
		cout << "Please enter your 5 digit PIN" << endl;

		for (int i = 0; i < 5; i++)
			cin >> cool[i];

		cout << endl;

		//Encrypt
		while (fin >> noskipws >> ch) {
			int ich = (int)ch;
			ich = ich - cool[cc];
			cc = ((++cc) % 5);
			char ch2 = (char)ich;
			cout << ch2;
			fout << ch2;
		}
		cout << endl;
		system("Pause");
	}
	return 0;
}

// ORIGINAL MAIN FOR EXECUTION

//int main() {
//
//	int choice;
//	cout << "Please select your choice:" << endl << "1) encrypt" << endl << "2) decrypt" << endl;
//
//	cin >> choice;
//
//	if (choice == 1)
//		encrypt("C:\\Users\\bepis\\Desktop\\test.txt", "C:\\Users\\bepis\\Desktop\\testneu.txt");
//	else if (choice == 2)
//		decrypt("C:\\Users\\bepis\\Desktop\\testneu.txt", "C:\\Users\\bepis\\Desktop\\testre.txt");
//	else {
//		cout << "Please enter valid number!" << endl;
//		main();
//	}
//}