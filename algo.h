#ifndef ALGO_H_INCLUDED
#define ALGO_H_INCLUDED
#include "FileProcess.h"

class CAlgo
{
public:
    CAlgo(){}
    explicit CAlgo(const CFileProcess::File_Root &fileName)
        {Set(fileName);}
    void Set(const CFileProcess::File_Root &fileName);

    void SetTittle(const std::string & tittle){_tittle = tittle;}
    void SetAbsPath(const std::string & absPath){_absoluteFolderPath = absPath;}

    const std::string & tittle()const{return _tittle;}
    const std::string & absoluteFolderPath()const{return _absoluteFolderPath;}

private:

    std::string _tittle;
    std::string _absoluteFolderPath;
};

#endif // ALGO_H_INCLUDED
