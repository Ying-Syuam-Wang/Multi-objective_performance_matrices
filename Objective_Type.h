#ifndef OBJECTIVE_TYPE_H_INCLUDED
#define OBJECTIVE_TYPE_H_INCLUDED

#include <string>

class CObjType
{
public:
    typedef double Tobj;
    virtual ~CObjType(){}

    bool isEqual(const Tobj & smaller,const Tobj & bigger)const
        {return (smaller==bigger);}
    virtual bool isBetter(const Tobj & smaller,const Tobj & bigger)const = 0;
};

class CObjMinimize:public CObjType
{
public:
    virtual bool isBetter(const CObjType::Tobj & smaller,const CObjType::Tobj & bigger)const
        {return (smaller<bigger);}
};

class CObjMaximize:public CObjType
{
public:
    virtual bool isBetter(const CObjType::Tobj & bigger,const CObjType::Tobj & smaller)const
        {return (smaller<bigger);}
};

#endif // OBJECTIVE_TYPE_H_INCLUDED
