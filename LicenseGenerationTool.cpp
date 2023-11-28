#include <iostream>
#include <iomanip>
#include "EncryptDateTime.h"


int main() {
	int year, month, day, hour, minute, second, gracePeriod;
	bool isValidDt(false);
	bool isValidTm(false);
	EncryptDateTime encryptObj;

	std::cout << "Enter grace period in Days: ";
	std::cin >> gracePeriod;

	while (isValidDt != true)
	{
		std::cout << "Enter licence date (YYYY MM DD): ";
		std::cin >> year >> month >> day;

		isValidDt = encryptObj.validateDate(year, month, day);
		if (isValidDt != true)
		{
			std::cout << "Entered date is invalid\n";
		}
	}

	while (isValidTm != true)
	{
		std::cout << "Enter time in 24H format (HH MM SS): ";
		std::cin >> hour >> minute >> second;

		isValidTm = encryptObj.validateTime(hour, minute, second);
		if (isValidTm != true)
		{
			std::cout << "Entered time is invalid.\n";
		}
	}

	encryptObj.convertToJulian(year, month, day, hour, minute, second);

	std::cout << std::fixed << std::setprecision(5);
	std::cout << "\n Julian Date and Time: " << encryptObj.julianDtTm << std::endl;

	encryptObj.encrypt(encryptObj.julianDtTm, gracePeriod);

	return 0;
}
