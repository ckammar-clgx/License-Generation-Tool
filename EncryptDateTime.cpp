#include "EncryptDateTime.h"
#include <Windows.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

EncryptDateTime::EncryptDateTime ()
{
  julianDtTm = 0.0;
  for (int i = 0; i <= 9; i++)
    {
      char c = 'a' + i;
      encryptionMap[i] = c;
    }
}

EncryptDateTime::~EncryptDateTime ()
{
}

// Function to convert Gregorian date to Julian date
void
EncryptDateTime::convertToJulian (int year, int month, int day, int hour, int minute,
                                  int second)
{
  int a = (14 - month) / 12;
  int y = year + 4800 - a;
  int m = month + 12 * a - 3;

  this->julianDtTm = day + (153 * m + 2) / 5 + 365 * y + y / 4 - y / 100 + y / 400 - 32045
                     + (hour - 12) / 24.0 + minute / 1440.0 + second / 86400.0;
}

void
EncryptDateTime::encrypt (double julianDtTm, int gracePeriod)
{
  // Convert the double to a string
  std::string stringValue = std::to_string (julianDtTm);
  std::string gracePeriodValue = std::to_string (gracePeriod);

  // Map each digit to a character
  std::string encryptedString;
  for (char digit : stringValue)
    {
      if (std::isdigit (digit))
        {
          int numericDigit = digit - '0';
          char mappedChar = encryptionMap[numericDigit];
          encryptedString += mappedChar;
        }
      else
        {
          // Non-digit characters can be included as-is
          encryptedString += digit;
        }
    }

  // Create a file and add encrypted licence date time
  std::ofstream outFile ("License.txt");

  // Check if the file is successfully opened
  if (!outFile.is_open ())
    {
      std::cerr << "Error opening file for writing!" << std::endl;
      return; // Return an error code
    }

  outFile << "Grace Period in days: " << gracePeriodValue << "\n"
          << encryptedString << std::endl;

  // Close the file
  outFile.close ();

  // Display an alert message box using Windows API
  MessageBox (NULL, L"License.txt has been created!", L"Alert", MB_OK | MB_ICONEXCLAMATION);
}