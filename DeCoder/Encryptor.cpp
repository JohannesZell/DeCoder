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


//***** Methode für XOR Verschluesselung *****//
void Encryptor::encryptXOR(char* sourcePath, const char* output)
{
// Initialisierung der lokalen Variablen
	fstream fin(sourcePath, fstream::in);
	fstream fout;
	char key[10];			// Array für verwendetes Passwort
	char rawData;			// Character-Variable für das originale Zeichen
	char encData;			// Character-Variable für das verschluesselte Zeichen
	int count = 0;			// Zaehlvariable

	cout << "Please enter an Key up to 10 Digits" << endl;
	cin >> key;				// Einlesen des Passworts

	fout.open(output, ios::out);	// Oeffnen der Ausgabedatei

	cout << "------------------------------ENCRYPTED------------------------------" << endl;

		while (fin.get(rawData))	// Einlesen eines Zeichens
	{
		encData = int(rawData) ^ ( (int)key[count % sizeof(key)] +96);	// XOR Verknuepfung
		cout << rawData;			
		fout << (char)encData;		// Schreibvorgang des verschluesselten Zeichens
		count++;
	}
	cout << endl;
	fout.close();			// Schließen der Ausgabedatei
	fin.close();			// Schließen der Originaldatei
}

//***** Methode für AES Verschluesselung *****//
SecByteBlock key(0x00, AES::DEFAULT_KEYLENGTH); //Variable für den AES-Key
SecByteBlock iv(AES::BLOCKSIZE); //Variable für den Initialisierungs Vektor

void Encryptor::encryptAES(char* sourcePath, const char* output)
{	
	string input;
	fstream fin(sourcePath, fstream::in);
	fstream keyOut;
	fstream ivOut;
	fstream fOut;
	getline(fin, input);
	vector<char> bytes(input.begin(), input.end()); //Byte Vector um Dateiinhalt abzuspeichern
	AutoSeededRandomPool rnd; 

	// Generate a random key
	rnd.GenerateBlock(key, key.size()); //Einen zufaelligen AES-Key generieren
	cout << "Your random key:" << key << endl;

	// Generate a random IV
	rnd.GenerateBlock(iv, iv.size()); //Einen zufaelligen Initialisierungs Vektor generieren
	FileSink* iv_out = new FileSink("C:\\Users\\johan\\Desktop\\IV.bin"); //FileSink aus der Crypto++ Lib um IV abzuspeichern
	iv_out->Put(iv, iv.size()); //IV Bytweise abspeichern
	iv_out->MessageEnd(); //FileSink "schließen"

	FileSink* key_out = new FileSink("C:\\Users\\johan\\Desktop\\AESKey.bin");  //FileSink aus der Crypto++ Lib um Key abzuspeichern
	key_out->Put(key, key.size());  //Key Bytweise abspeichern
	key_out->MessageEnd();  //FileSink "schließen"
	

	byte *plainText = new byte[input.size()];  //byte Array fuer den Dateiinput
	int length = input.size(); 
	for (size_t i = 0; i < length; i++)
	{
		plainText[i] = bytes[i]; //Dateien aus dem Vektor in das Byte Array schreiben
	}

	//////////////////////////////////////////////////////////////////////////
	// Encrypt

	CFB_Mode<AES>::Encryption cfbEncryption(key, key.size(), iv); //Erzeugen einer neuen cfbEncryption Klasse
	cfbEncryption.ProcessData(plainText, plainText, length); //Dateiinhalt verschluesseln


	cout << "------------------------------ENCRYPTED------------------------------" << endl;
	for (size_t i = 0; i < length; i++)
	{
		cout << plainText[i]; //Ausgabe des verschluesselten Inhalts
	}

	fOut.open(output, fstream::out | fstream::trunc | fstream::binary);
	for (size_t i = 0; i < length; i++)
	{
		fOut << plainText[i]; //Speichern des verschluesselten Inhalts in der Datei
	}
	fOut.close();
	cout << endl;

	delete[] plainText;  //Loeschen des plainText Arrays um Speicher wieder freizugeben
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
	vector<char> bytes(input.begin(), input.end());  //Byte Vector um Dateiinhalt abzuspeichern


	if (empty(key) & empty(iv))
	{
		FileSource fs_key(keyFileDirectory, true, new ArraySink(key.begin(), key.size())); //Key aus File auslesen und in Variable abspeichern
		fs_key.PumpAll();

		FileSource fs_iv(ivFileDirectory, true, new ArraySink(iv.begin(), iv.size()));  //IV aus File auslesen und in Variable abspeichern
		fs_iv.PumpAll();
	}

	byte* plainText = new byte[input.size()];	//byte Array fuer den Dateiinput

	int length = input.size();
	for (size_t i = 0; i < length; i++)
	{
		plainText[i] = bytes[i];
	}

	CFB_Mode<AES>::Decryption cfbDecryption(key, key.size(),iv);  //Erzeugen einer neuen cfbEncryption Klasse
	cfbDecryption.ProcessData(plainText, plainText, length);  //Dateiinhalt entschluesseln

	cout << "------------------------------DECRYPTED------------------------------" << endl;
	for (size_t i = 0; i < length; i++)
	{
		cout << plainText[i];  //Ausgabe des entschluesselten Inhalts
	}
	cout << endl;
	fOut.open(output, fstream::out | fstream::trunc | fstream::binary);
	for (size_t i = 0; i < length; i++)
	{
		fOut << plainText[i];  //Abspeichern des entschluesselten Inhalts
	}
	
	fOut.close();
	delete[] plainText;  //Loeschen des plainText Arrays um Speicher wieder freizugeben
}

//***** Methode für Caesar Verschluesselung *****//
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
