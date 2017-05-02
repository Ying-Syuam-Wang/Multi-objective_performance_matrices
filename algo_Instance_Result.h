#ifndef ALGO_INSTANCE_RESULT_H_INCLUDED
#define ALGO_INSTANCE_RESULT_H_INCLUDED

#include "algo_Performace.h"
#include "Solution.h"
#include "Front.h"
#include <fstream>
#include <vector>
#include <string>

class CSingleInstanceResult
{
    friend std::ostream & operator << (std::ostream & os,const CSingleInstanceResult &insResult)
    {
        os << insResult._results << std::endl;
        os << insResult._performance << std::endl;
        return os;
    }
public:
    CSingleInstanceResult(){}
    explicit CSingleInstanceResult(size_t s){SetNumObjs(s);}

    const CFront & front()const{return _results;}
    CFront & front(){ return const_cast<CFront&>(static_cast<const CSingleInstanceResult&>(*this).front());}

    void SetNumObjs(size_t o){_results.resize(o);}
    void SetSolutions(const std::vector<CSolution> &F){_results.Sols() = F;}
    void SetSolutions(const std::vector<std::vector<double>> &F);
    void SetSolution(const size_t i,const CSolution &P){_results[i] = P;}
    void AddSolution(const CSolution &P){_results.push_back(P);}

    void setPerformace(const CPerformace & per){_performance = per;}
    const CPerformace & Performace()const{return _performance;}
    CPerformace & Performace()
    { return const_cast<CPerformace&>(static_cast<const CSingleInstanceResult&>(*this).Performace());}
    void norPerforamceBy(const CPerformace & extermPerformance);

    void SetUpSolutions(const std::string &fileName, const std::size_t numObj);
private:
    CFront _results;
    CPerformace _performance;
};

class CProblem;
class CInstanceResult
{
    friend std::ostream & operator << (std::ostream & os,const CInstanceResult &insResult)
    {
        os << insResult._PF << std::endl;
        os << insResult._performance << std::endl;
        return os;
    }
public:

    CInstanceResult(){}
    explicit CInstanceResult(std::size_t r):_Run(r){}

    void resizeRuns(std::size_t r){_Run.resize(r);}
    std::size_t numRun()const{return _Run.size();}

    const CSingleInstanceResult & Run(std::size_t i)const{return _Run[i];}
    CSingleInstanceResult & Run(std::size_t i)
        { return const_cast<CSingleInstanceResult&>(static_cast<const CInstanceResult&>(*this).Run(i));}

    const CSingleInstanceResult & operator[](std::size_t i)const{return _Run[i];}
    CSingleInstanceResult& operator[](std::size_t i)
        { return const_cast<CSingleInstanceResult&>(static_cast<const CInstanceResult&>(*this)[i]);}

    void calAvgPerforamce();
    void norAllRunPerforamceBy(const CPerformace & extermPerformance);

    const CPerformace & avgPerformance()const{return _avgRunPerformance;}
    CPerformace & avgPerformance()
        { return const_cast<CPerformace&>(static_cast<const CInstanceResult&>(*this).avgPerformance());}

    void calRunPF(const CProblem & Problem);
    const CPerformace & Performace()const{return _performance;}
    CPerformace & Performace()
    { return const_cast<CPerformace&>(static_cast<const CInstanceResult&>(*this).Performace());}

    const CFront & front()const{return _PF;}
    CFront & front(){ return const_cast<CFront&>(static_cast<const CInstanceResult&>(*this).front());}

    void SetUpSolutions(const std::string &fileName, const std::size_t numObj);
private:
    std::vector<CSingleInstanceResult> _Run;
    CPerformace _avgRunPerformance;

    CFront _PF;
    CPerformace _performance;

};

#endif // ALGO_INSTANCE_RESULT_H_INCLUDED
