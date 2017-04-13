#ifndef FRONT_H_INCLUDED
#define FRONT_H_INCLUDED

#include "Solution.h"

/**
sorting-using-member-function-as-comparator
from
http://stackoverflow.com/questions/1902311/problem-sorting-using-member-function-as-comparator
**/
class CFront
{
public:
    const CSolution & operator[](std::size_t i)const{return _Front[i];}
    CSolution& operator[](std::size_t i)
        { return const_cast<CSolution&>(static_cast<const CFront&>(*this)[i]);}

    std::vector<CSolution> & Front(){return _Front;}
    std::size_t size()const{return _Front.size();}
    void resize(const std::size_t i){_Front.resize(i);}
    void push_back(const CSolution &sol){_Front.push_back(sol);}
    void erase(const std::vector<CSolution>::iterator i){_Front.erase(i);}
    std::vector<CSolution>::iterator begin(){return _Front.begin();}
    std::vector<CSolution>::iterator end(){return _Front.end();}

    void sortByObj(const std::size_t obj);

private:
    std::vector<CSolution> _Front;

    struct doCompare {
        doCompare(const CFront & f,const std::size_t o): front(f),obj(o){}
        bool operator()(const CSolution & i, const CSolution & j) {return (i[obj]<j[obj]);}
        const CFront& front;
        const std::size_t obj;
    };
};


#endif // FRONT_H_INCLUDED
