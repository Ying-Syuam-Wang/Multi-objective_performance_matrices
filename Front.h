#ifndef FRONT_H_INCLUDED
#define FRONT_H_INCLUDED

#include <iostream>
#include "Solution.h"
#include "Objective_Type.h"


/**
sorting-using-member-function-as-comparator
from
http://stackoverflow.com/questions/1902311/problem-sorting-using-member-function-as-comparator
**/
class CFront
{
    friend std::ostream & operator << (std::ostream & os,const CFront &f)
    {
        for(CSolution sol : f._Front)
            os << sol << std::endl;
        return os;
    }
public:
    struct SobjInfo
    {
        CObjType::Tobj _min = -INT_MAX;
        CObjType::Tobj _MAX = 0;
        CObjType::Tobj _range = 0;

        CObjType::Tobj min()const{return _min;}
        CObjType::Tobj MAX()const{return _MAX;}
        CObjType::Tobj range()const{return _range;}
    };

    const CSolution & operator[](std::size_t i)const{return _Front[i];}
    CSolution& operator[](std::size_t i)
        { _isUpdateBojInfo = false;
            return const_cast<CSolution&>(static_cast<const CFront&>(*this)[i]);}

    const std::vector<CSolution> & Sols()const{return _Front;}
    std::vector<CSolution> & Sols()
        { _isUpdateBojInfo = false;
            return const_cast<std::vector<CSolution>&>(static_cast<const CFront&>(*this).Sols());}

    std::size_t numSols()const{return _Front.size();}
    void resize(const std::size_t i){_Front.resize(i);_isUpdateBojInfo = false;}
    void erase(const std::vector<CSolution>::iterator i){_Front.erase(i);_isUpdateBojInfo = false;}

    void push_back(const CSolution &sol);
    std::vector<CSolution>::iterator begin(){return _Front.begin();}
    std::vector<CSolution>::iterator end(){return _Front.end();}

    void sortByObj(const std::size_t obj = 1);

    const SobjInfo & objExtremes(const std::size_t o);
    const std::vector<SobjInfo> & objsExtremes()const{return _objInfos;}

    void nomalizeBy(const std::vector<SobjInfo> & objInfo);

private:
    std::vector<CSolution> _Front;
    bool _isUpdateBojInfo = true;

    std::vector<SobjInfo> _objInfos;

    struct doCompare {
        doCompare(const CFront & f,const std::size_t o): front(f),obj(o){}
        bool operator()(const CSolution & i, const CSolution & j) {return (i[obj]<j[obj]);}
        const CFront& front;
        const std::size_t obj;
    };
    void updateObjExtremes(const CSolution &sol);
};


#endif // FRONT_H_INCLUDED
