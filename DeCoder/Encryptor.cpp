#include "Encryptor.h"
#include <iostream>
#include <string.h>
#include "dll.h"
#include <fstream>

using namespace std;
using namespace CryptoPP;


Encryptor::Encryptor()
{
}


Encryptor::~Encryptor()
{
}

char* parse(istream &input) {
	char c[100];
	while (input >> c)
	{
		cout << c << endl;
	}
	return c;
}


char* Encryptor::encryptXOR(char* sourcePath, char* output)
{
	char key[10];
	fstream fin(sourcePath, fstream::in);
	ofstream outfile;
	//fstream fout(output, fstream::out);
	//char* rawData = fin;			//parse(fin);
	char rawData;
	char encData;
	int count = 0;

	cout << "Please enter an Key up to 10 Digits" << endl;
	cin >> key;
	outfile.open("C:\\Users\\gross\\XORe.txt");

	while (fin >> noskipws >> rawData) 
	{
		encData = int(rawData) ^ (int)key[count % sizeof(key)];
		cout << encData;
		outfile << encData;
		count++;
	}
	outfile.close();
	


	/*
	fin >> noskipws >> rawData;

	cout << "Please enter an Key up to 10 Digits" << endl;
	
	cin >> key;
	for (int i = 0; i < 10; i++) { //Intelligenter den Pin einlesen
		cin >> key[i];
	}
	
	cout << endl;
	cout << key << endl << rawData << endl;

	int keyLength = sizeof(key);
	int remainingData = sizeof(fin);
	char encData[1000];
	int iteration = 0;
	
	while (remainingData > 0)
	{
		for (int count = 0; count < keyLength; count++)
		{
			encData[iteration + count] = (int)rawData[iteration + count] ^ (int)key[count];
			remainingData = remainingData - 1;
		}
		iteration = iteration + keyLength;
	}
	cout << encData << endl;
	fout << encData;

	*/
	return __nullptr;
}

void Encryptor::decryptXOR(char * sourcePath, char * output)
{
}



char* Encryptor::encryptAES(char* sourcePath, const char* output)
{	
	string input;
	fstream fin(sourcePath, fstream::in);
	fstream fout;
	fstream keyOut;
	getline(fin, input);
	vector<char> bytes(input.begin(), input.end());
	AutoSeededRandomPool rnd;

	// Generate a random key
	SecByteBlock key(0x00, AES::DEFAULT_KEYLENGTH);
	rnd.GenerateBlock(key, key.size());
	cout << "Your random key:" << key << endl;
	keyOut.open("C:\\Users\\johan\\Desktop\\AESKey.txt",fstream::out | fstream::trunc);
	keyOut << key;
	keyOut.close();

	// Generate a random IV
	SecByteBlock iv(AES::BLOCKSIZE);
	rnd.GenerateBlock(iv, iv.size());

	byte* plainText = new byte[input.size()];

	int length = input.size();
	for (size_t i = 0; i < length; i++)
	{
		plainText[i] = bytes[i];
	}

	//////////////////////////////////////////////////////////////////////////
	// Encrypt

	CFB_Mode<AES>::Encryption cfbEncryption(key, key.size(), iv);
	cfbEncryption.ProcessData(plainText, plainText, length);

	cout << "------------------------------ENCRYPTED------------------------------" << endl;
	for (size_t i = 0; i < length; i++)
	{
		cout << plainText[i];
	}
	fout.open("C:\\Users\\johan\\Desktop\\EncryptedFile.txt", fstream::out | fstream::trunc | fstream::binary);
	fout << plainText;
	fout.close();
	cout << endl;
	//////////////////////////////////////////////////////////////////////////
	// Decrypt

	CFB_Mode<AES>::Decryption cfbDecryption(key, key.size(), iv);
	cfbDecryption.ProcessData(plainText, plainText, length);
	cout << "------------------------------DECRYPTED------------------------------" << endl;
	for (size_t i = 0; i < length; i++)
	{
		cout << plainText[i];
	}
	cout << endl;
	//fout << plainText;
	delete[] plainText;
	return nullptr;
}

char * Encryptor::decryptAES(char* sourcePath, const char* output)
{
	/*char* keyFile;
	cout << "Please enter the Key file: ";
	cin >> keyFile;
	fstream fin(sourcePath, fstream::in);
	fstream fout;
	fstream key(keyFile, fstream::in);
	string input;
	getline(key, input);


	CFB_Mode<AES>::Decryption cfbDecryption(input, input.size, iv); 
	cfbDecryption.ProcessData(plainText, plainText, messageLen);
	cout << plainText;*/
	return nullptr;
}

////////////////////////////
// CAESAR PIN
////////////////////////////


// DEFINITION 
char inputData;

//Array for PIN
int cesarPinArray[5];

//Counter for looping the array
int cesarCounterArray;

//Char for PIN reading
char pin;

//Bool for correct PIN entry
bool crEntry;

void Encryptor::encryptCesar(char* sourcePath, char* output)
{
	fstream fin(sourcePath, fstream::in);
	fstream fout(output, fstream::out); 

	//Get PIN
	while (crEntry == false) {
		cout << "Please enter your 5 digit PIN" << endl;
		cin >> pin;
		if (sizeof(pin)> 5) {
			crEntry = true;
		}
	}

	for (int i = 0; i < 5; i++)
		pin >> cesarPinArray[i];

	cout << endl;
	
	//Encrypt
	while (fin >> noskipws >> inputData) {
		int ich = (int)inputData;
		ich = ich + cesarPinArray[cesarCounterArray];
		cesarCounterArray = ((++cesarCounterArray) % 5);
		char ch2 = (char)ich;
		cout << ch2;
		fout << ch2;
	}
	cout << endl;
}

void Encryptor::decryptCesar(char* sourcePath, char*	output)
{
	fstream fin(sourcePath, fstream::in);
	fstream fout(output, fstream::out); 
	//Get PIN
	cout << "Please enter your 5 digit PIN" << endl;

	for (int i = 0; i < 5; i++)
		cin >> cesarPinArray[i];

	cout << endl;

	//Decrypt
	while (fin >> noskipws >> inputData) {
		int intCastedData = (int)inputData;
		intCastedData = intCastedData - cesarPinArray[cesarCounterArray];
		cesarCounterArray = ((++cesarCounterArray) % 5);
		char outputData = (char)intCastedData;
		cout << outputData;
		fout << outputData;
	}
	cout << endl;
}
