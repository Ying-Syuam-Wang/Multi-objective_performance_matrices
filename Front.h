#ifndef FRONT_H_INCLUDED
#define FRONT_H_INCLUDED

#include "Solution.h"
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
    bool CompareAsThis(const CSolution& i, const CSolution& j){}
};

#endif // FRONT_H_INCLUDED
