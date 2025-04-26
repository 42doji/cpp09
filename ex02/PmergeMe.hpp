#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <utility> // std::pair
#include <algorithm> // std::sort, std::lower_bound, std::swap
#include <sys/time.h> // gettimeofday
#include <cstdlib> // exit, atoi, EXIT_FAILURE
#include <cctype> // isdigit

class PmergeMe
{
public:
    static bool flag;
    static unsigned int tmp;

    PmergeMe();
    PmergeMe(const PmergeMe &a);
    ~PmergeMe();
    PmergeMe &operator=(const PmergeMe &a);

    void checkInput(char *av1, char *av2);

    template <typename T, typename S, typename V>
    void calc(int ac, char *av[], T &container, S &cont, V &conta, char choice)
    {
        struct timeval start;
        struct timeval end;
        long sec;
        long micro;

        gettimeofday(&start, NULL);
        for (size_t i = 0; i < container.size(); i++)
        {
            if (container[i].first > container[i].second)
                std::swap(container[i].first, container[i].second);
        }
        for (size_t i = 0; i < container.size(); i++)
            conta.push_back(container[i].first);

        for (size_t i = 0; i < container.size(); i++)
            cont.push_back(container[i].second);
        std::sort(conta.begin(), conta.end());
        for (size_t i = 0; i < cont.size(); i++)
            conta.insert(std::lower_bound(conta.begin(), conta.end(), cont[i]), cont[i]);
        if (flag)
            conta.insert(std::lower_bound(conta.begin(), conta.end(), tmp), tmp);
        std::cout << "\n다음  : ";
        for (size_t i = 0; i < conta.size(); i++)
            std::cout << conta[i] << " ";
        std::cout << std::endl;
        gettimeofday(&end, NULL);
        sec = end.tv_sec - start.tv_sec;
        micro = end.tv_usec - start.tv_usec;
        long diff = (sec * 1000000) + micro;
        if (choice == 'v')
            std::cout << "범위: " << ac - 1 + (flag ? 1 : 0) << "개, std::vector: " << diff << " us" << "\n";
        if (choice == 'd')
            std::cout << "범위: " << ac - 1 + (flag ? 1 : 0) << "개, std::deque: " << diff << " us" << "\n";
    }
};

#endif
