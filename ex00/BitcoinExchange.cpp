#include "BitcoinExchange.hpp"
#include<sstream>

BitcoinExchange::BitcoinExchange()
{}

BitcoinExchange::~BitcoinExchange()
{}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other)
{
    *this = other;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& src)
{
    if (this != &src)
        this->map = src.map;
    return *this;
}
bool BitcoinExchange::isValidDate(std::string& date)
{
    if (date.length() != 10)
        return false;
    if (date[4] != '-' || date[7] != '-')
        return false;

    int year = atoi(date.substr(0, 4).c_str());
    int month = atoi(date.substr(5, 2).c_str());
    int day = atoi(date.substr(8, 2).c_str());

    if (month < 1 || month > 12)
        return false;
    if (day < 1 || day > 31)
        return false;
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
        return false;
    if (month == 2)
    {
        bool isLeapYear;
        if (year % 4 == 0)
        {
            if (year % 100 != 0)
                isLeapYear = true;
            else if (year % 400 == 0)
                isLeapYear = true;
            else
                isLeapYear = false;
        }
        else
            isLeapYear = false;
        if (day > 29 || (day > 28 && !isLeapYear))
            return false;
    }
    return true;
}

void removeAllSpaces(std::string &str)
{
    std::string::iterator newEnd = std::remove(str.begin(), str.end(), ' ');
    str.erase(newEnd, str.end());
}

void BitcoinExchange::processFile(std::string& filename)
    {
        std::ifstream infile(filename.c_str());
        if (!infile)
        {
            std::cerr << "Error: could not open file " << filename << std::endl;
            return;
        }
        std::string line;
        while (getline(infile, line))
        {
            std::string::size_type pipePos = line.find('|');
            if (pipePos == std::string::npos)
            {
                std::cerr << "Error: bad input => " << line << std::endl;
                continue;
            }
            std::string date = line.substr(0, pipePos - 1);
            double value = atof(line.substr(pipePos + 1).c_str());
            removeAllSpaces(date);
            if (!isValidDate(date))
            {
                std::cerr << "Error: bad input => " << line << std::endl;
                continue;
            }
            if (value > 1000)
            {
                std::cerr << "Error: too large a number." << std::endl;
                continue ;
            }
            if (value < 0)
            {
                std::cerr << "Error: not a positive number." << std::endl;
                continue;
            }
            double rate = getExchangeRate(date);
            if (rate != -1)
                std::cout << std::setprecision(15) << date << " => " << value << " = " << (value * rate) << std::endl;
            else
                std::cout << "No price available for date: " << date << std::endl;
        }
    }

void BitcoinExchange::loadDataBase(std::string& filename)
{
        std::ifstream file(filename.c_str());
        if (!file)
        {
            std::cerr << "Error: could not open file " << filename << std::endl;
            return ;
        }
        std::string line, date;
        double rate;
        while (getline(file, line)) 
        {
            std::string::size_type commaPos = line.find(',');
            date = line.substr(0, commaPos);
            rate = static_cast<double>(atof(line.substr(commaPos + 1).c_str()));
            map[date] = rate;
        }
        file.close();
}

double BitcoinExchange::getExchangeRate(std::string& date)
{
    std::map<std::string, double>::iterator it = map.lower_bound(date);
    if ((it != map.begin()) && it->first != date)
        --it;
    if (it != map.end() && it->first <= date)
        return it->second;
    return -1;
}
