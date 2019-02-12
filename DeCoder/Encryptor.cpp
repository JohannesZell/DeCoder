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




char* Encryptor::encryptAES(char* sourcePath)
{	
	fstream fin(sourcePath, fstream::in);
	fstream fout(sourcePath + 'e', fstream::out);
	fstream keyOut(sourcePath, fstream::out);
	cout << "S: " << sourcePath << " O: " << sourcePath << endl;
	char* c = parse(fin);
	

	AutoSeededRandomPool rnd;
	// Generate a random key
	SecByteBlock key(0x00, AES::DEFAULT_KEYLENGTH);
	rnd.GenerateBlock(key, key.size());
	cout << "Your random key:" << key << endl;
	keyOut << key;

	// Generate a random IV
	SecByteBlock iv(AES::BLOCKSIZE);
	rnd.GenerateBlock(iv, iv.size());

	byte plainText[10];
	for (size_t i = 0; i < sizeof(c); i++)
	{
		plainText[i] = (byte)c[i];
	}
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

char * Encryptor::decryptAES(char* sourcePath)
{
	/*
	fstream fin(sourcePath, fstream::in);
	fstream fout(output, fstream::out);

	CFB_Mode<AES>::Decryption cfbDecryption(key, key.size(), iv);
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

void Encryptor::encryptCesar(char* sourcePath, char* output)
{
	fstream fin(sourcePath, fstream::in);
	fstream fout(output, fstream::out); 
	//Get PIN
	cout << "Please enter your 5 digit PIN" << endl;

	for (int i = 0; i < 5; i++)
		cin >> cesarPinArray[i];

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

void Encryptor::decryptCesar(char* sourcePath, char* output)
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
