#ifndef ALGO_H_INCLUDED
#define ALGO_H_INCLUDED
#include "FileProcess.h"
#include "Instance_Set.h"
#include "algo_Performace.h"
#include "FileProcess_result.h"
#include <vector>
#include <string>
using std::string;
using std::size_t;
using std::vector;

class CSetting;
class CSingleInstanceResult;

class CAlgo
{
public:
    CAlgo(){}
    explicit CAlgo(size_t s) : _insSets(s){}
    explicit CAlgo(const string & tittle) : _tittle(tittle){}
    explicit CAlgo(const string & tittle,const string & absPath) :
                   _tittle(tittle), _absoluteFolderPath(absPath){}
    void SetUp(const string & tittle,
               const string & absPath,
               const vector<CInstanceSetNames> & insSetNames,
               const size_t numObj,
               const size_t numSet,
               const string insBack,
               const size_t runBegin,
               const size_t runEnd);

    void SetUpSolutions(const string &fileName, const size_t numObj, CSingleInstanceResult &insResult);
    void SetTittle(const string &tittle){_tittle = tittle;}
    void SetAbsPath(const string &absPath){_absoluteFolderPath = absPath;}
    void resizeSet(const size_t i){_insSets.resize(i);}


    const CInstanceSet & atSet(size_t i)const{return _insSets[i];}
    CInstanceSet & atSet(size_t i)
        { return const_cast<CInstanceSet&>(static_cast<const CAlgo&>(*this).atSet(i));}

    const string &tittle()const{return _tittle;}
    const string &absPath()const{return _absoluteFolderPath;}

    void calAvgPerforamce();
    void Performace(const size_t i);

private:
    string _tittle;
    string _absoluteFolderPath;

    CPerformace _avgSetPerformance;
    vector<CInstanceSet> _insSets;
};


#endif // ALGO_H_INCLUDED
