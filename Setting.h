#ifndef SETTING_H_INCLUDED
#define SETTING_H_INCLUDED
#include <vector>
#include <string>
#include "Instance.h"

using std::string;
using std::size_t;
using std::vector;

#define numMatrix 6

class CSetting
{
public:
    CSetting() : _isUseThisMatrix(numMatrix){}
    CSetting(const CFileProcess::File_Root &fileName);

    const string & savePath()const{return _savePath;}
    size_t numDistribute()const{return _numDistribute;}

    const string & setTittle(const size_t i)const{return _setTittle[i];}
    const vector<string> & setTittle()const{return _setTittle;}
    size_t numSets()const{return _setTittle.size();}


    const string & insBack()const{return _insBack;}
    size_t runBegin()const{return _runBegin;}
    size_t runEnd()const{return _runEnd;}

    const string & FolderTITTLE()const{return _FolderTITTLE;}

    size_t numAlgos()const{return _numAlgos;}

    const std::pair<string,string> & algoTittleAndPath(const size_t i)const{return _algoTittleAndPath[i];}

private:
    string _savePath;
    size_t _numDistribute;
    vector<bool> _isUseThisMatrix;

    vector<string> _setTittle;

    string _insBack;
    size_t _runBegin;
    size_t _runEnd;

    string _FolderTITTLE;

    size_t _numAlgos;

    vector<std::pair<string,string>> _algoTittleAndPath;

};




#endif // SETTING_H_INCLUDED
