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
	return NULLPTR;
}