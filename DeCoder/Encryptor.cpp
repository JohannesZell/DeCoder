#include "Encryptor.h"
#include <iostream>
#include <string.h>

using namespace std;


Encryptor::Encryptor()
{
}


Encryptor::~Encryptor()
{
}

char * Encryptor::encryptXOR(char key[], char * rawData)
{
	cout << endl << "DEBUGGING";
	int keyLength = sizeof(key);
	int remainingData = strlen(rawData);
	char encData[10];																	//Ausgabe Array zum debuggen auf size 10
	int step = 0;
	cout << remainingData;

	while (remainingData > 0)															//while raw data remains
	{
		for (int count = 0; count < keyLength; count++)									//encrypt raw bits with key, for the size of the key
		{
			encData[step + count] = (int) rawData[step + count] ^ (int) key[count];
			remainingData = remainingData - 1;
		}
		step = step + keyLength;

	}
	cout <<endl<< encData[0];
	//return encData;
	return __nullptr;
}

char* Encryptor::encryptBitAdd(char pin[], char * rawData)
{/*
	int keyLength = sizeof(pin);
	int remainingData = strlen(rawData);
	char * encData;
	int step = 0;

	while (remainingData > 0)
	{
		for (int count = 0; count < keyLength; count++)
		{
			encData[step + count] = (int)rawData[step + count] ^ (int)key[count];
		}
		step = step + keyLength;
		remainingData = remainingData - count;
	}

	return encData; */
	return __nullptr;
}

char* Encryptor::encryptAES(char key[], char * rawData)
{


	return __nullptr;
}

