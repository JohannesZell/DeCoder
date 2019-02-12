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
	char* encryptAES(char* sourcePath, const char* output);
	char* decryptAES(char* sourcePath, const char* output);
	void encryptCesar(char* sourcePath, char* output);
	void decryptCesar(char* sourcePath, char* output);

};

