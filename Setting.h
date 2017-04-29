#ifndef SETTING_H_INCLUDED
#define SETTING_H_INCLUDED
#include <vector>
#include <string>
#include "FileProcess.h"
#include "Instance.h"
#include "Indicator.h"

class CSetting
{
public:
    CSetting(const CFileProcess::File_Root &fileName);
    std::size_t numDistribute()const{return _numDistribute;}

    const std::string & setTittle(std::size_t i)const{return _setTittle[i];}
    const std::vector<std::string> & setTittle()const{return _setTittle;}
    std::size_t numSets()const{return _setTittle.size();}


    const std::string & insBack()const{return _insBack;}
    std::size_t runBegin()const{return _runBegin;}
    std::size_t runEnd()const{return _runEnd;}

    const std::string & FolderTITTLE()const{return _FolderTITTLE;}
    void setFolderTITTLE(const string & tittle){ _FolderTITTLE = tittle;}

    std::size_t numAlgos()const{return _numAlgos;}

    const std::pair<std::string,std::string> & algoTittleAndPath(std::size_t i)const{return _algoTittleAndPath[i];}

private:
    std::size_t _numDistribute;

    std::vector<std::string> _setTittle;

    std::string _insBack;
    std::size_t _runBegin;
    std::size_t _runEnd;

    std::string _FolderTITTLE;

    std::size_t _numAlgos;

    std::vector<std::pair<std::string,std::string>> _algoTittleAndPath;

};




#endif // SETTING_H_INCLUDED
