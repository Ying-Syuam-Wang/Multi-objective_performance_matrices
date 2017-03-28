#ifndef CONVERT_H_INCLUDED
#define CONVERT_H_INCLUDED
#include <string>

class CConvert
{
public:
    std::string toString(const std::size_t i);
    std::size_t toSize_t(const std::string &str);
};

extern CConvert Convert;

#endif // CONVERT_H_INCLUDED
