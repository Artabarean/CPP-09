#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
}

BitcoinExchange::~BitcoinExchange()
{
}

void BitcoinExchange::loadDatabase(const std::string &filename)
{
	std::ifstream file(filename.c_str());
	
	if (!file.is_open())
		throw std::runtime_error("Error: could not open file.");
	
	std::string line;
	std::getline(file, line);
	
	while (std::getline(file, line))
	{
		if (line.empty())
			continue;
		
		size_t pos = line.find(',');
		if (pos == std::string::npos)
			continue;
		
		std::string date = line.substr(0, pos);
		std::string rate = line.substr(pos + 1);
		
		try
		{
			float exchangeRate = _stringToFloat(rate);
			_priceDB[date] = exchangeRate;
		}
		catch (std::exception &e)
		{
			std::cerr << "Warning: " << e.what() << std::endl;
		}
	}
	
	file.close();
}

void BitcoinExchange::processInput(const std::string &filename)
{
	std::ifstream file(filename.c_str());
	
	if (!file.is_open())
	{
		std::cout << "Error: could not open file." << std::endl;
		return;
	}
	
	std::string line;
	std::getline(file, line); // Skip header line
	
	while (std::getline(file, line))
	{
		if (!line.empty())
			_processLine(line);
	}
	
	file.close();
}

bool BitcoinExchange::_isValidDate(const std::string &date)
{
	// Format: YYYY-MM-DD
	if (date.length() != 10)
		return false;
	
	if (date[4] != '-' || date[7] != '-')
		return false;
	
	for (int i = 0; i < 10; i++)
	{
		if (i == 4 || i == 7)
			continue;
		if (!isdigit(date[i]))
			return false;
	}
	
	int year = atoi(date.substr(0, 4).c_str());
	int month = atoi(date.substr(5, 2).c_str());
	int day = atoi(date.substr(8, 2).c_str());
	
	if (month < 1 || month > 12)
		return false;
	
	if (day < 1 || day > 31)
		return false;
	
	// Validation for specific months
	if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
		return false;
	
	if (month == 2)
	{
		bool isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
		if (day > (isLeap ? 29 : 28))
			return false;
	}
	
	return true;
}

bool BitcoinExchange::_isValidValue(const std::string &value)
{
	if (value.empty())
		return false;
	
	// Check if it's a valid number
	size_t dotCount = 0;
	for (size_t i = 0; i < value.length(); i++)
	{
		if (value[i] == '.')
		{
			dotCount++;
			if (dotCount > 1)
				return false;
		}
		else if (!isdigit(value[i]))
			return false;
	}
	
	try
	{
		float numValue = _stringToFloat(value);
		
		// Check if value is between 0 and 1000
		if (numValue < 0 || numValue > 1000)
			return false;
	}
	catch (std::exception &e)
	{
		return false;
	}
	
	return true;
}

float BitcoinExchange::_stringToFloat(const std::string &str)
{
	char *end = NULL;
	float result = strtof(str.c_str(), &end);
	
	if (*end != '\0')
		throw std::invalid_argument("Invalid number format");
	
	return result;
}

void BitcoinExchange::_processLine(const std::string &line)
{
	// Format: "date | value"
	size_t pos = line.find(" | ");
	
	if (pos == std::string::npos)
	{
		std::cout << "Error: bad input => " << line << std::endl;
		return;
	}
	
	std::string date = line.substr(0, pos);
	std::string value = line.substr(pos + 3);
	
	// Validate date
	if (!_isValidDate(date))
	{
		std::cout << "Error: bad input => " << date << std::endl;
		return;
	}
	
	// Validate value
	if (!_isValidValue(value))
	{
		if (value.find('-') != std::string::npos)
			std::cout << "Error: not a positive number." << std::endl;
		else
		{
			try
			{
				float numValue = _stringToFloat(value);
				if (numValue > 1000)
					std::cout << "Error: too large a number." << std::endl;
				else
					std::cout << "Error: bad input => " << line << std::endl;
			}
			catch (std::exception &e)
			{
				std::cout << "Error: bad input => " << line << std::endl;
			}
		}
		return;
	}
	
	try
	{
		float btcAmount = _stringToFloat(value);
		
		// Find the exact date or the closest lower date
		std::map<std::string, float>::iterator it = _priceDB.upper_bound(date);
		
		if (it != _priceDB.begin())
		{
			--it;
			float exchangeRate = it->second;
			float result = btcAmount * exchangeRate;
			
			std::cout << date << " => ";
			
			// Print the value without decimals if it's an integer
			if (btcAmount == (int)btcAmount)
				std::cout << (int)btcAmount;
			else
				std::cout << std::fixed << std::setprecision(1) << btcAmount;
			
			std::cout << " = " << std::fixed << std::setprecision(2) << result << std::endl;
		}
		else
		{
			std::cout << "Error: date too early => " << date << std::endl;
		}
	}
	catch (std::exception &e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}
}
