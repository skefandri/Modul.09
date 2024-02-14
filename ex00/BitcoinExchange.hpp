#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <cstdlib>

class BitcoinExchange
{
    private:
        std::map<std::string, double> map;
    public:
        BitcoinExchange();
        ~BitcoinExchange();
        BitcoinExchange(const BitcoinExchange&);
        BitcoinExchange& operator=(const BitcoinExchange&);

        bool    isValidDate(std::string& date);
        void    loadDataBase(std::string& filename);
        double   getExchangeRate(std::string& data);
        void    processFile(std::string&  filename);
        void    calculateValues();
        double   findClosesPrice(std::string& date);
};

#endif