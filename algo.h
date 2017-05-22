#ifndef ALGO_H_INCLUDED
#define ALGO_H_INCLUDED
#include "FileProcess.h"
#include "Instance_Set.h"
#include "algo_Performace.h"
#include "FileProcess_result.h"
#include <vector>
#include <string>

class CSetting;
class CSingleInstanceResult;
class CProblem;

class CAlgo
{
public:
    CAlgo(){}
    explicit CAlgo(std::size_t s) : _insSets(s){}
    explicit CAlgo(const std::string & tittle) : _tittle(tittle){}
    explicit CAlgo(const std::string & tittle,const std::string & absPath) :
                   _tittle(tittle), _absoluteFolderPath(absPath){}
    void SetUp(const std::string & tittle,
               const std::string & absPath,
               const std::vector<CInstanceSetNames> & insSetNames,
               const CProblem & Problem,
               const std::size_t numSet,
               const std::string insBack,
               const std::size_t runBegin,
               const std::size_t runEnd);

    void SetTittle(const std::string &tittle){_tittle = tittle;}
    void SetAbsPath(const std::string &absPath){_absoluteFolderPath = absPath;}
    void resizeSet(const std::size_t i){_insSets.resize(i);}


    const CInstanceSet & atSet(std::size_t i)const{return _insSets[i];}
    CInstanceSet & atSet(std::size_t i)
        { return const_cast<CInstanceSet&>(static_cast<const CAlgo&>(*this).atSet(i));}

    const std::string &tittle()const{return _tittle;}
    const std::string &absPath()const{return _absoluteFolderPath;}

    void calAvgPerforamce();
    const CPerformace & avgPerformance()const{return _avgSetPerformance;}
    CPerformace & avgPerformance()
        { return const_cast<CPerformace&>(static_cast<const CAlgo&>(*this).avgPerformance());}

    size_t numInsSet(){return _insSets.size();}
private:
    std::string _tittle;
    std::string _absoluteFolderPath;

    CPerformace _avgSetPerformance;
    std::vector<CInstanceSet> _insSets;
};


#endif // ALGO_H_INCLUDED
