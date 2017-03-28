#include "Convert.h"
#include <sstream>
CConvert Convert;

std::string CConvert::toString(const size_t i)
{
    std::stringstream ss;
    ss << i;
    return ss.str();
}
std::size_t CConvert::toSize_t(const std::string &str)
{
    std::stringstream ss(str);
    std::size_t tmp;
    ss >> tmp;
    return tmp;
}
