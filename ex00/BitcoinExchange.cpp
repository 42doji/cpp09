#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange ()
{
}

/*--------------------------------------------------------*/
BitcoinExchange::BitcoinExchange (const BitcoinExchange &ref)
{
	this->operator=(ref);
}

/*--------------------------------------------------------*/
BitcoinExchange::~BitcoinExchange ()
{
}

/*--------------------------------------------------------*/
BitcoinExchange & BitcoinExchange::operator = (const BitcoinExchange &ref)
{
	(void)ref;
	return (*this);
}

void    BitcoinExchange::initDatabase()
{
    std::ifstream   input;
    std::string     temp_database;

    input.open("./data.csv");
    while (!input.eof())
    {
        input >> temp_database;
        std::string extracted_date = temp_database.substr(0,10).erase(4,1).erase(6,1);
        float      rate = 0.0;
        std::stringstream convert;
        convert << temp_database.substr(11);
        convert >> rate;
        _database.insert(std::make_pair(extracted_date,rate));
    }
    input.close();
}

int BitcoinExchange::parsing(int year, int month, int day, std::string rate_str ,float rate, std::string line)
{
    size_t idx;
    int count = 0;
    int maximum_days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    idx = line.find("|");
    if (line[idx + 1] != ' ' || line[idx - 1] != ' ')
    {
        std::cerr << "Invalid Pipe\n";
        return (-1);
    }
    count = 0;
    if (line.substr(4,1) != "-" && line.substr(7,1) != "-")
    {
        std::cerr << "Invalid Date Format\n";
        return (-1);
    }
    for (size_t i = 0; i < rate_str.length(); i++)
    {
        if (rate_str[0] == '.')
        {
            std::cerr << "Invalid Rate Format\n";
            return (-1);
        }
        if (rate_str[i] == '.')
            count++;
        if (!(isdigit(rate_str[i])) && rate_str[i] != '.' && (count == 1 || count == 0))
        {
            std::cerr << "Invalid Rate Format\n";
            return (-1);
        }
    }
    if (year < 2009 || month < 1 || month > 12)
    {
        std::cerr << "Invalid Date Format\n";
        return (-1);
    }
    if (day > maximum_days[month - 1] || day < 1)
    {
        std::cerr << "Out of month range\n";
        return (-1);
    }
    if (rate < 0.00 || rate > 1000.00 )
    {
        std::cerr << "Rate out of range\n";
        return (-1);
    }
    return (0);
}

void    BitcoinExchange::printOuput(std::string inputdate, float bitcoins)
{
    std::map<std::string, float>::iterator begin = this->_database.begin();
    std::map<std::string, float>::iterator end = this->_database.end();
    bool    flag = false;

    for (; begin != end; begin++)
    {
        if (begin->first == inputdate)
        {
            flag = true;
            break;
        }
    }
    if (flag == true)
    {
        std::cout << inputdate.insert(4,"-").insert(7,"-") << " => " << bitcoins << " = " <<  std::fixed << std::setprecision(2) << bitcoins * begin->second << "\n";
        flag = false;
    }
    else
    {
        end = this->_database.lower_bound(inputdate);
        std::cout << inputdate.insert(4,"-").insert(7,"-") << " => " << bitcoins << " = " << std::fixed << std::setprecision(2) << bitcoins * end->second << "\n";
    }
}

void    BitcoinExchange::readInput(std::string file)
{
    std::ifstream   input;
    std::string     line;

    input.open(file);

    if (input.fail())
    {
        std::cerr << "Cannot Open File\n";
        input.close();
        exit(0);
    }

    while (!input.eof())
    {
        int                 year, month, day = 0;
        std::stringstream   y, m, d;
        std::string         fulldate;
        std::getline(input, line);
        std::stringstream   bit;
        std::string         rate_str;
        float                bitcoins;

        y << line.substr(0,4);
        m << line.substr(5,2);
        d << line.substr(8,2);
        y >> year;
        m >> month;
        d >> day;
        if (line.length() < 14)
        {
            std::cerr << "Invalid Format\n";
            continue ;
        }
        rate_str = line.substr(13, line.find('\0'));
        bitcoins = 0.00;
        bit << rate_str;
        bit >> bitcoins;
        if (month < 10 && day < 10)
            fulldate = std::to_string(year * 10) + std::to_string(month * 10) + std::to_string(day);
        else if (day < 10)
            fulldate = std::to_string(year) + std::to_string(month * 10) + std::to_string(day);
        else if (month < 10)
            fulldate = std::to_string(year * 10) + std::to_string(month) + std::to_string(day);
        else
            fulldate = std::to_string(year) + std::to_string(month) + std::to_string(day);
        if (parsing(year, month, day, rate_str, bitcoins, line) == 0)
            printOuput(fulldate, bitcoins);
    }
}
