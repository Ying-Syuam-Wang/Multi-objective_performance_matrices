#ifndef SETTING_PROBLEM_H_INCLUDED
#define SETTING_PROBLEM_H_INCLUDED
#include "Objective_Type.h"
#include <vector>
#include <string>

class CProblem
{
public:
    explicit CProblem(const std::string & problemSetting);

    std::size_t numObj()const{return _numObj;}


private:
    std::size_t _numObj;
    std::vector<CObjType::eObjType> _objType;
};

#endif // SETTING_PROBLEM_H_INCLUDED
