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

char * Encryptor::encrypt(char key[], char * rawData)
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

