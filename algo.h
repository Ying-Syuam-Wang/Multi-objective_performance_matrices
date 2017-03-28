#ifndef ALGO_H_INCLUDED
#define ALGO_H_INCLUDED
#include "FileProcess.h"
#include "Instance.h"
#include "algo_Instance_Result.h"
#include "algo_Performace.h"
#include <vector>
#include <string>
using std::string;
using std::size_t;
using std::vector;

class CAlgo
{
public:
    typedef vector<CInstanceResult> InsRunResults;
    typedef vector<InsRunResults> AllInsWithRunResults;

    CAlgo(){}
    explicit CAlgo(const string &tittle,
                   const string &absPath,
                   const CInstanceSetNames &insSetNames,
                   const size_t numObj,
                   const string & fileBack,
                   const size_t runBegin,
                   const size_t runEnd)
        {SetUp(tittle,absPath,insSetNames,numObj,fileBack,runBegin,runEnd);}
    void SetUp(const string &tittle,
               const string &absPath,
               const CInstanceSetNames &insSetNames,
               const size_t numObj,
               const string & fileBack,
               const size_t runBegin,
               const size_t runEnd);

    const InsRunResults & operator[](size_t i)const{return _allInsRunResults[i];}
    InsRunResults & operator[](size_t i)
        { return const_cast<InsRunResults&>(static_cast<const CAlgo&>(*this)[i]);}

    void SetTittle(const string &tittle){_tittle = tittle;}
    void SetAbsPath(const string &absPath){_absoluteFolderPath = absPath;}

    const string &tittle()const{return _tittle;}
    const string &absPath()const{return _absoluteFolderPath;}


    void Performace(const size_t i);

private:

    string _tittle;
    string _absoluteFolderPath;

    AllInsWithRunResults _allInsRunResults;
};


#endif // ALGO_H_INCLUDED
