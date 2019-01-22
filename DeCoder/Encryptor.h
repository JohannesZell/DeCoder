#pragma once
class Encryptor
{
public:

	//Variables


	//Methods
	Encryptor();
	~Encryptor();

	char* encrypt(char key[], char* rawData);
};

