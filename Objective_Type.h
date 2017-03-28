#ifndef OBJECTIVE_TYPE_H_INCLUDED
#define OBJECTIVE_TYPE_H_INCLUDED

#include <string>

class CObjType
{
public:
    enum eObjType{min = 1,MAX};
    static const char strMAX[];//MAX
    static const char strMin[];//min
    std::string operator()(const eObjType &o)const{return (o == eObjType::min)?strMin:strMAX;}
    eObjType operator()(const std::string &o)const{return (o == strMin)?eObjType::min:eObjType::MAX;}
};

extern CObjType objType;
#endif // OBJECTIVE_TYPE_H_INCLUDED
