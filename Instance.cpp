#include "Instance.h"
#include "fstream"

void CInstanceSet_Setting::Set(const CFileProcess::File_Root &fileName)
{
    std::ifstream file;
    FileProcess.open(fileName,file);
    std::string strTmp;
    while(file >> strTmp)
    {
        this->_insName.push_back(strTmp);
        strTmp.clear();
    }
}
