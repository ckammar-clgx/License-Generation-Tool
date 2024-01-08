#include "EncryptDateTime.h"
#include <cctype>
#include <iomanip>
#include <iostream>
#include <sstream>

bool
isValidDateFormat (const std::string &input, int &year, int &month, int &day)
{
  // Check if the string has the correct length
  if (input.size () != 10)
    {
      return false;
    }

  // Use a stringstream to extract year, month, and day
  std::stringstream ss (input);
  char delimiter1, delimiter2;

  // Try to extract values and delimiters
  if (!(ss >> year >> delimiter1 >> month >> delimiter2 >> day) || delimiter1 != '-'
      || delimiter2 != '-')
    {
      return false;
    }

  // Check if the values are within valid ranges
  if (year < 1000 || year > 9999 || month < 1 || month > 12 || day < 1 || day > 31)
    {
      return false;
    }

  return (year > 1000 && year < 9999) && (month >= 1 && month <= 12) && (day >= 1 && day <= 31);
}

bool
isValidTimeFormat (const std::string &input, int &hour, int &minute, int &second)
{
  // Check if the string has the correct length
  if (input.size () != 8)
    {
      return false;
    }

  // Use a stringstream to extract hour, minute, and seconds.
  std::stringstream ss (input);
  char delimiter1, delimiter2;

  // Try to extract values and delimiters
  if (!(ss >> hour >> delimiter1 >> minute >> delimiter2 >> second) || delimiter1 != ':'
      || delimiter2 != ':')
    {
      return false;
    }

  // Check if the values are within valid ranges
  return (hour >= 0 && hour < 24) && (minute >= 0 && minute < 60)
         && (second >= 0 && second < 60);
}

int
main ()
{
  int year, month, day, hour, minute, second, gracePeriod;
  std::string inputDate;
  std::string inputTime;
  EncryptDateTime encryptObj;

  // Keep prompting until a valid days are entered
  while (true)
    {
      std::cout << "Enter grace period in Days: ";

      // Check if the input is a valid integer
      if (std::cin >> gracePeriod)
        {
          // Input is a valid integer, break out of the loop
          break;
        }
      else
        {
          // Clear the error flag for cin
          std::cin.clear ();

          // Ignore the invalid input in the buffer
          std::cin.ignore (std::numeric_limits<std::streamsize>::max (), '\n');

          // Prompt the user again
          std::cout << "Invalid Days.\n";
        }
    }

  while (true)
    {
      year = month = day = 0;
      std::cout << "Enter license date (YYYY-MM-DD): ";
      std::getline (std::cin >> std::ws, inputDate);

      // Check if the input string is a valid date format
      if (isValidDateFormat (inputDate, year, month, day))
        {
          break;
        }
      else
        {
          // Clear the error flag for cin
          std::cin.clear ();

          std::cerr << "Invalid date format. Please enter a date in the format YYYY-MM-DD.\n";
        }
    }

  while (true)
    {
      std::cout << "Enter time in 24H format (HH:MM:SS): ";
      std::getline (std::cin >> std::ws, inputDate);

      if (isValidTimeFormat (inputDate, hour, minute, second))
        break;
      else
        {
          // Clear the error flag for cin
          std::cin.clear ();

          std::cerr << "Invalid time format. Please enter a time in the format HH:MM:SS \n";
        }
    }

  encryptObj.convertToJulian (year, month, day, hour, minute, second);

  std::cout << std::fixed << std::setprecision (5);
  std::cout << "\n Julian Date and Time: " << encryptObj.julianDtTm << std::endl;

  encryptObj.encrypt (encryptObj.julianDtTm, gracePeriod);

  return 0;
}
