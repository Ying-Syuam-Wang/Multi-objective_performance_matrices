#include "algo.h"

void CAlgo::Set(const CFileProcess::File_Root &fileName)
{
    std::ifstream file;
    FileProcess.open(fileName,file);
    std::string strTmp;
    while(file >> strTmp)
    {
        strTmp.clear();
    }
}
