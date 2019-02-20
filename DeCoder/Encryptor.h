#pragma once
class Encryptor
{
public:

	//Variables

	//Methods
	Encryptor();
	~Encryptor();

	char* encryptXOR(char* sourcePath, const char* outputs);
	void decryptXOR(char* sourcePath, const char* output);
	char* encryptAES(char* sourcePath, const char* output);
	char* decryptAES(char* sourcePath, const char* output);
	void encryptCesar(char* sourcePath, const char* output);
	void decryptCesar(char* sourcePath, const char* output);

};

