#pragma once
#include <map>

class EncryptDateTime
{
private:
	std::map<int, char> encryptionMap;

public:
	EncryptDateTime();
	~EncryptDateTime();
	void convertToJulian(int year, int month, int day, int hour, int minute, int second);
	void encrypt(double julianDtTm, int gracePeriod);
	double julianDtTm;
};