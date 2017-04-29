#ifndef SOLUTION_H_INCLUDED
#define SOLUTION_H_INCLUDED
#include <vector>
#include <iostream>
#include "Objective_Type.h"

class CSolution
{
    friend std::ostream & operator << (std::ostream & os,const CSolution &sol)
    {
        for(CObjType::Tobj o: sol._objs)
            os << o << " ";
        return os;
    }
public:
    typedef std::vector<CObjType::Tobj> Tobjs;

    std::size_t objSize()const{return _objs.size();}

    CSolution(){}
    explicit CSolution(std::size_t s){SetNumObjs(s);}
    void SetObjs(const Tobjs &s){_objs = s;}
    void SetNumObjs(std::size_t o){resize(o);}
    void resize(std::size_t o){_objs.resize(o,-1);}

    Tobjs & objs(){return _objs;}
    const Tobjs & objs()const{return _objs;}

    const CObjType::Tobj & operator[](std::size_t i)const{return _objs[i];}
    CObjType::Tobj & operator[](std::size_t i)
        { return const_cast<CObjType::Tobj&>(static_cast<const CSolution&>(*this)[i]);}

    std::size_t numObj()const{return _objs.size();}
private:
    Tobjs _objs;
};

#endif // SOLUTION_H_INCLUDED
