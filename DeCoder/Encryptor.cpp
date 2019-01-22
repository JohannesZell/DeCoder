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
	int keyLength = sizeof(key);
	int remainingData = strlen(rawData);
	char * encData;
	int step = 0;
	cout << remainingData;

	while (remainingData > 0)
	{
		for (int count = 0; count < keyLength; count++) 
		{
			encData[step + count] = (int) rawData[step + count] ^ (int) key[count];
		}
		step = step + keyLength;
	}

	return encData;
}

