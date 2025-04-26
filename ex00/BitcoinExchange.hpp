#ifndef BITCOINEXCHANGE_H
#define BITCOINEXCHANGE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

class BitcoinExchange
{
    private:
        std::map<std::string , float> _database;

    public:
        BitcoinExchange ();
        BitcoinExchange (const BitcoinExchange &ref);
        ~BitcoinExchange ();
        BitcoinExchange & operator = (const BitcoinExchange &ref);

        void    initDatabase(void);
        void    readInput(std::string file);
        int     parsing(int year, int month, int day, std::string rate_str, float rate, std::string     line);
        void    printOuput(std::string inputdate, float bitcoins);
};

#endif

