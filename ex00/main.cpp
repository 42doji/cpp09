#include "BitcoinExchange.hpp"

int main(int ac, char *av[])
{
    BitcoinExchange A;
    if (ac == 2)
    {
        try
        {
            A.initDatabase();
            A.readInput(av[1]);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }
    else
        std::cerr << "Error: could not open file";
}

