#include "BitcoinExchange.hpp"
#include <iostream>

int main(int ac, char* av[])
{
    if (ac != 2) {
            std::cerr << "Error: could not open file " << std::endl;
        return 1;
    }

    BitcoinExchange exchange;
    std::string data = "data.csv";
    std::string filename = av[1];
    exchange.loadDataBase(data);
    exchange.processFile(filename);
    return 0;
}
