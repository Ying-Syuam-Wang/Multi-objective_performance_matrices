#ifndef FILEPROCESS_RESULT_H_INCLUDED
#define FILEPROCESS_RESULT_H_INCLUDED
#include "FileProcess.h"
#include <fstream>
#include <string.h>
class CFront;
class CAlgo;
class CInstanceSetNames;

class CResultFileProcess: public CFileProcess
{
public:
    void ReadFront(const std::size_t numObj,std::ifstream & file,
                    CFront & points);
    void OutFront(const CFront& points,std::ofstream & file);

    void OutPerformance(const std::vector<CAlgo> & algos, const CInstanceSetNames & insSetNames, std::ofstream & file);
private:
    void OutTittle(const std::vector<CAlgo> & algos, std::ofstream & file);
};
extern CResultFileProcess ResultFileProcess;

#endif // FILEPROCESS_RESULT_H_INCLUDED
