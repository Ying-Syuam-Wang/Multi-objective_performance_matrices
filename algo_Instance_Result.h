#ifndef ALGO_INSTANCE_RESULT_H_INCLUDED
#define ALGO_INSTANCE_RESULT_H_INCLUDED

#include "algo_Performace.h"
#include "Solution.h"
#include <fstream>
#include <vector>
#include <string>
using std::string;

class CInstanceResult
{
    friend std::ostream & operator << (std::ostream & os,const CInstanceResult &insResult)
    {
        for(std::size_t i = 0; i < insResult._results.size(); i += 1)
        {
            for(std::size_t j = 0; j < insResult[i].objSize(); j += 1)
                os << insResult._results[i][j] << " ";
            os << std::endl;
        }
        return os;
    }
public:
    typedef std::vector<CSolution> Front;


    CAlgoPerformace insPerformace;

    CInstanceResult(){}
    explicit CInstanceResult(size_t s){SetNumObjs(s);}

    const CSolution & operator[](std::size_t i)const{return _results[i];}
    CSolution& operator[](std::size_t i)
        { return const_cast<CSolution&>(static_cast<const CInstanceResult&>(*this)[i]);}

    std::size_t size(){return _results.size();}

    Front & front(){return _results;}

    void SetNumObjs(size_t o){_results.resize(o);}
    void SetSolutions(const std::vector<CSolution> &F){_results = F;}
    void SetSolutions(const std::vector<std::vector<double>> &F);
    void SetSolution(const size_t i,const CSolution &P){_results[i] = P;}
    void AddSolution(const CSolution &P){_results.push_back(P);}

private:
    Front _results;

};



#endif // ALGO_INSTANCE_RESULT_H_INCLUDED
