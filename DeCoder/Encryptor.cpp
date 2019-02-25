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


//***** Methode für XOR Verschlüsselung *****//
void Encryptor::encryptXOR(char* sourcePath, const char* output)
{
// Initialisierung der lokalen Variablen
	fstream fin(sourcePath, fstream::in);
	fstream fout;
	char key[10];			// Array für verwendetes Passwort
	char rawData;			// Character-Variable für das originale Zeichen
	char encData;			// Character-Variable für das verschlüsselte Zeichen
	int count = 0;			// Zählvariable

	cout << "Please enter an Key up to 10 Digits" << endl;
	cin >> key;				// Einlesen des Passworts

	fout.open(output, ios::out);	// Öffnen der Ausgabedatei

	cout << "------------------------------ENCRYPTED------------------------------" << endl;

		while (fin.get(rawData))	// Einlesen eines Zeichens
	{
		encData = int(rawData) ^ ( (int)key[count % sizeof(key)] +96);	// XOR Verknüpfung
		cout << rawData;			
		fout << (char)encData;		// Schreibvorgang des verschlüsselten Zeichens
		count++;
	}
	cout << endl;
	fout.close();			// Schließen der Ausgabedatei
	fin.close();			// Schließen der Originaldatei
}


SecByteBlock key(0x00, AES::DEFAULT_KEYLENGTH);
SecByteBlock iv(AES::BLOCKSIZE);

void Encryptor::encryptAES(char* sourcePath, const char* output)
{	
	string input;
	fstream fin(sourcePath, fstream::in);
	fstream keyOut;
	fstream ivOut;
	fstream fOut;
	getline(fin, input);
	vector<char> bytes(input.begin(), input.end());
	AutoSeededRandomPool rnd;

	// Generate a random key
	rnd.GenerateBlock(key, key.size());
	cout << "Your random key:" << key << endl;

	// Generate a random IV
	rnd.GenerateBlock(iv, iv.size());
	FileSink* iv_out = new FileSink("C:\\Users\\johan\\Desktop\\IV.bin");
	iv_out->Put(iv, iv.size());
	iv_out->MessageEnd();

	FileSink* key_out = new FileSink("C:\\Users\\johan\\Desktop\\AESKey.bin");
	key_out->Put(key, key.size());
	key_out->MessageEnd();


	/*keyOut.open("C:\\Users\\johan\\Desktop\\AESKey.bin",fstream::out | fstream::trunc | fstream::binary);
	keyOut << key;
	keyOut.close();
	ivOut.open("C:\\Users\\johan\\Desktop\\IV.bin", fstream::out | fstream::trunc | fstream::binary);
	ivOut << iv;
	ivOut.close();
	*/

	
	byte *plainText = new byte[input.size()];


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

	fOut.open(output, fstream::out | fstream::trunc | fstream::binary);
	for (size_t i = 0; i < length; i++)
	{
		fOut << plainText[i];
	}
	fOut.close();
	cout << endl;

	delete[] plainText;
}

void Encryptor::decryptAES(char* sourcePath, const char* output)
{
	string input;
	char keyFileDirectory[100];
	char ivFileDirectory[100];

	cout << "Please enter the Key file: ";
	cin >> keyFileDirectory;
	cout << "Please enter the IV file: ";
	cin >> ivFileDirectory;

	fstream fin(sourcePath, fstream::in | fstream::binary);
	fstream fOut;
	getline(fin, input);
	vector<char> bytes(input.begin(), input.end());


	//Save Key in Key variable
	//SecByteBlock key(AES::MAX_KEYLENGTH);
	//ArraySink* arr_key_in = new ArraySink(key, key.size());
	//FileSource source(keyFileDirectory, false);
	//source.PumpMessages();
	//FileSource fs_key(keyFileDirectory, true, new ArraySink(key.begin(), key.size()));
	//fs_key.PumpAll();
	//cout << "Key: " << key;


	//Save IV in iv variable
	//SecByteBlock iv(AES::BLOCKSIZE);
	//FileSource fs_iv(ivFileDirectory, true, new ArraySink(iv.begin(), iv.size()));
	//fs_iv.PumpAll();

//	cout << "Key: " << read_key << " IV: " << iv << endl;

	byte* plainText = new byte[input.size()];

	int length = input.size();
	for (size_t i = 0; i < length; i++)
	{
		plainText[i] = bytes[i];
	}

	CFB_Mode<AES>::Decryption cfbDecryption(key, key.size(),iv);
	cfbDecryption.ProcessData(plainText, plainText, length);
	cout << "------------------------------DECRYPTED------------------------------" << endl;
	for (size_t i = 0; i < length; i++)
	{
		cout << plainText[i];
	}
	cout << endl;
	fOut.open(output, fstream::out | fstream::trunc | fstream::binary);
	for (size_t i = 0; i < length; i++)
	{
		fOut << plainText[i];
	}
	
	fOut.close();
	delete[] plainText;
}

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

void Encryptor::encryptCesar(char* sourcePath, const char* output)
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
	cout << "------------------------------ENCRYPTED------------------------------" << endl;

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

void Encryptor::decryptCesar(char* sourcePath, const char* output)
{
	fstream fin(sourcePath, fstream::in);
	fstream fout(output, fstream::out); 
	//Get PIN
	cout << "Please enter your 5 digit PIN choosen for this file" << endl;

	for (int i = 0; i < 5; i++)
		cin >> cesarPinArray[i];

	cout << endl;

	cout << "------------------------------DECRYPTED------------------------------" << endl;
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
