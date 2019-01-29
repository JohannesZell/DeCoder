#pragma once
class Encryptor
{
public:

	//Variables


	//Methods
	Encryptor();
	~Encryptor();

	char* encryptXOR(char key[], char* rawData);
	char* encryptBitAdd(char pin[], char* rawData);
	char* encryptAES(char key[], char* rawData);

};

