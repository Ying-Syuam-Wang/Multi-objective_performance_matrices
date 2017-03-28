#ifndef ALGO_PERFORMACE_H_INCLUDED
#define ALGO_PERFORMACE_H_INCLUDED

#include <iostream>
#include <vector>
#include <string>
using std::string;

class CAlgoPerformace
{
    friend std::ostream & operator << (std::ostream & os,const CAlgoPerformace &insPer)
    {
        for(std::size_t i = 0; i < insPer.performace.size(); i += 1)
            os << insPer.performace[i] << " ";
        return os;
    }
public:
    CAlgoPerformace(){}
    explicit CAlgoPerformace(size_t s){SetNumMatrix(s);}
    void SetNumMatrix(size_t s){performace.resize(s,-1);}

    const double & operator[](std::size_t i)const{return performace[i];}
    double & operator[](std::size_t i)
        { return const_cast<double&>(static_cast<const CAlgoPerformace&>(*this)[i]);}
private:
    std::vector<double> performace;
};


#endif // ALGO_PERFORMACE_H_INCLUDED
