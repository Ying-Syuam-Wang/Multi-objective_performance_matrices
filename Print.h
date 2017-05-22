#ifndef PRINT_H_INCLUDED
#define PRINT_H_INCLUDED
#include <stdlib.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using std::vector;
using std::string;
using std::size_t;

class CPrint
{
public:

    static void XD(){std::cout << "XD";system("PAUSE");}

    template<typename T>
    static void anything(const T &  t)
    {
        std::cout << t << "XD";
        system("PAUSE");
    }

    template<typename T>
    static void anyVec(const vector<T> & vecT)
    {
        for(T t : vecT)
            std::cout << t << " ";
        std::cout << "XD";
        system("PAUSE");
    }

};

#endif // PRINT_H_INCLUDED
