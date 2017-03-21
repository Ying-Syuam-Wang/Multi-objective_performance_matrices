#ifndef SETTING_H_INCLUDED
#define SETTING_H_INCLUDED
#include <vector>
#include <string>
#include "Instance.h"
#include "algo.h"

class CSetting
{
public:
    explicit CSetting(const CFileProcess::File_Root &fileName);

    const std::string & savePath()const{return _savePath;}
    std::size_t numDistribute()const{return _numDistribute;}
    const std::string IGDpfCHOOSE()const{return _IGDpfCHOOSE;}

    const CInstanceSet_Setting & instances(const std::size_t i)const{return _instances[i];}

    const std::string & insBack()const{return _insBack;}
    std::size_t runFront()const{return _runFront;}
    std::size_t runBack()const{return _runBack;}

    const std::string & FolderTITTLE()const{return _FolderTITTLE;}

    const CAlgo & algos(const std::size_t i)const{return _algos[i];}

private:
    std::string _savePath;
    std::size_t _numDistribute;
    std::string _IGDpfCHOOSE;

    std::vector<CInstanceSet_Setting> _instances;

    std::string _insBack;
    std::size_t _runFront;
    std::size_t _runBack;

    std::string _FolderTITTLE;

    std::vector<CAlgo> _algos;

};




#endif // SETTING_H_INCLUDED
