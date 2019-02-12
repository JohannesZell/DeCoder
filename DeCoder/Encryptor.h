#pragma once
class Encryptor
{
public:

	//Variables

	//Methods
	Encryptor();
	~Encryptor();

	char* encryptXOR(char key[], char* rawData);
	void decryptXOR(char* sourcePath, char* output);
	char* encryptAES(char* sourcePath);
	char* decryptAES(char* sourcePath);
	void encryptCesar(char* sourcePath, char* output);
	void decryptCesar(char* sourcePath, char* output);

};

