#include "Setting.h"
#include "algo.h"
#include "Indicator.h"
#include <fstream>
#include <sstream>
const vector<size_t> length = {8,0,3,2};
CSetting::CSetting(const CFileProcess::File_Root &fileName) : _isUseThisMatrix(numMatrix)
{
    std::ifstream file;
    FileProcess.open(fileName,file);
    string strTmp;
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
            size_t pos = strTmp.find(',');
            string HowMany(strTmp.substr(0,pos));
            std::stringstream ssHowMany;
            size_t numSet;
            ssHowMany << HowMany;
            ssHowMany >> numSet;
            _setTittle.resize(numSet);
            ss = FileProcess.read_CSV_line(numSet+1,strTmp);
        }

        switch(i)
        {
        case 0:
        {
            ss[0] >> this->_savePath;
            ss[1] >> this->_numDistribute;
            for(size_t x = 0; x < _isUseThisMatrix.size(); x += 1)
            {
                bool is;
                ss[x+2] >> is;
                this->_isUseThisMatrix[x] = is;
            }
        }
        break;
        case 1:
            for(size_t i = 0; i < _setTittle.size(); i += 1)
                ss[i+1] >> _setTittle[i];
        break;
        case 2:
            ss[0] >> this->_insBack;
            ss[1] >> this->_runBegin;
            ss[2] >> this->_runEnd;
        break;
        case 3:
            ss[0] >> this->_numAlgos;
            _algoTittleAndPath.resize(this->_numAlgos);
            ss[1] >> this->_FolderTITTLE;
        break;
        }
        ss->clear();
    }

    file >> strTmp;

    for(size_t i = 0; i < this->_numAlgos; i += 1)
    {
        file >> strTmp;
        ss = FileProcess.read_CSV_line(3,strTmp);
        ss[1] >> _algoTittleAndPath[i].first;
        ss[2] >> _algoTittleAndPath[i].second;
        ss->clear();
    }
}
