#include "Instance.h"
#include "fstream"

void CInstanceSetNames::Set(const CFileProcess::File_Root &fileName)
{
    std::ifstream file;
    FileProcess.open(fileName,file);
    string strTmp;
    while(file >> strTmp)
    {
        this->_insName.push_back(strTmp);
        strTmp.clear();
    }
}
