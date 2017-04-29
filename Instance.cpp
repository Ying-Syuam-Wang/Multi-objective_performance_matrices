#include "Instance.h"
#include "fstream"

void CInstanceSetNames::SetUpNames(const CFileProcess::File_Root &fileName)
{
    std::ifstream file;
    ResultFileProcess.open(fileName,file);
    string strTmp;
    while(file >> strTmp)
    {
        this->_insName.push_back(strTmp);
        strTmp.clear();
    }
    file.close();
}
