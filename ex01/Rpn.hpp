#ifndef RPN_H
#define RPN_H

#include <iostream>
#include <stack>

class Rpn
{
    private:
        std::stack<int>     _numbers;
    public:
        Rpn ();
        Rpn (const Rpn& ref);
        ~Rpn ();
        Rpn & operator = (const Rpn& ref);

        void    readInput(std::string input);
        int     result(int n1, int n2, char o);
};

#endif