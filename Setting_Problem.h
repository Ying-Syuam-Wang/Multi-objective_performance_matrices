#ifndef SETTING_PROBLEM_H_INCLUDED
#define SETTING_PROBLEM_H_INCLUDED
#include "Objective_Type.h"
#include <vector>
#include <string>

class CProblem
{
public:
    explicit CProblem(const std::string & problemSetting);
    ~CProblem();

    std::size_t numObj()const{return _numObj;}

    const std::vector<CObjType*> & obj()const{return _objType;}
    std::vector<CObjType*> & obj()
    { return const_cast<std::vector<CObjType*>&>(static_cast<const CProblem&>(*this).obj());}

    CObjType* obj(std::size_t o)const{return _objType[o];}
private:
    std::size_t _numObj;
    std::vector<CObjType*> _objType;
};

#endif // SETTING_PROBLEM_H_INCLUDED
