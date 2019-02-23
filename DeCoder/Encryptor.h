#pragma once
class Encryptor
{
public:

	//Variables

	//Methods
	Encryptor();
	~Encryptor();

	void encryptXOR(char* sourcePath, const char* outputs);
	void encryptAES(char* sourcePath, const char* output);
	void decryptAES(char* sourcePath, const char* output);
	void encryptCesar(char* sourcePath, const char* output);
	void decryptCesar(char* sourcePath, const char* output);

};

