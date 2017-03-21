#include "Setting.h"
#include <fstream>
#include <sstream>

const std::vector<std::size_t> length = {3,0,3,2};

CSetting::CSetting(const CFileProcess::File_Root &fileName)
{
    std::ifstream file;
    FileProcess.open(fileName,file);
    std::string strTmp;
    std::stringstream* ss;
    for(std::size_t i = 0; i < length.size(); i += 1)
    {
        file >> strTmp;
        strTmp.clear();
        file >> strTmp;
        if(i != 1)
            ss = FileProcess.read_CSV_line(length[i],strTmp);
        else
        {
            std::size_t pos = strTmp.find(',');
            std::string HowMany(strTmp.substr(0,pos));
            std::stringstream ssHowMany;
            std::size_t numSet;
            ssHowMany << HowMany;
            ssHowMany >> numSet;

            ss = FileProcess.read_CSV_line(numSet+1,strTmp);
            this->_instances.resize(numSet);
        }

        switch(i)
        {
        case 0:
            ss[0] >> this->_savePath;
            ss[1] >> this->_numDistribute;
            ss[2] >> this->_IGDpfCHOOSE;
            break;
        case 1:
            for(std::size_t i = 1; i < _instances.size(); i += 1)
            {
                std::string strTmp2;
                ss[i] >> strTmp2;
                this->_instances[i].SetName(strTmp2);
                this->_instances[i].Set("Setting\\"+this->_instances[i].name()+".txt");
            }
            break;
        case 2:
            ss[0] >> this->_insBack;
            ss[1] >> this->_runFront;
            ss[2] >> this->_runBack;
            break;
        case 3:
        {
            std::size_t tmp;
            ss[0] >> tmp;
            this->_algos.resize(tmp);
            ss[1] >> this->_FolderTITTLE;
        }
            break;
        }
        ss->clear();
    }

    for(std::size_t i = 0; i < _algos.size(); i += 1)
    {
        file >> strTmp;
        ss = FileProcess.read_CSV_line(3,strTmp);
        std::string strTmp2;
        ss[1] >> strTmp2;
        _algos[i].SetTittle(strTmp2);
        strTmp2.clear();
        ss[2] >> strTmp2;
        _algos[i].SetAbsPath(strTmp2);
        ss->clear();
    }
}
