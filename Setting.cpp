#include "Setting.h"
#include "algo.h"
#include "Indicator.h"
#include "FileProcess_result.h"
#include <fstream>
#include <sstream>

using std::string;
using std::size_t;
using std::vector;

const vector<size_t> length = {1,0,3,2};
CSetting::CSetting(const CFileProcess::File_Root &fileName)
{
    std::ifstream file;
    ResultFileProcess.open(fileName,file);
    string strTmp;
    std::stringstream* ss;
    for(std::size_t i = 0; i < length.size(); i += 1)
    {
        file >> strTmp;
        strTmp.clear();
        file >> strTmp;
        if(i != 1)
            ss = ResultFileProcess.read_CSV_line(length[i],strTmp);
        else
        {
            size_t pos = strTmp.find(',');
            string HowMany(strTmp.substr(0,pos));
            std::stringstream ssHowMany;
            size_t numSet;
            ssHowMany << HowMany;
            ssHowMany >> numSet;
            _setTittle.resize(numSet);
            ss = ResultFileProcess.read_CSV_line(numSet+1,strTmp);
        }

        switch(i)
        {
        case 0:
        {
            ss[0] >> this->_numDistribute;
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

    getline(file,strTmp);
    for(size_t i = 0; i < this->_numAlgos; i += 1)
    {
        getline(file,strTmp);
        ss = ResultFileProcess.read_CSV_line(3,strTmp);
        ss[1] >> _algoTittleAndPath[i].first;
        _algoTittleAndPath[i].second = ss[2].str();
        std::size_t pos = this->_algoTittleAndPath[i].second.find('\\');
        while(pos != std::string::npos)
        {
            _algoTittleAndPath[i].second = _algoTittleAndPath[i].second.substr(0,pos) + "\\\\\\\\" +
                                           _algoTittleAndPath[i].second.substr(pos+1,_algoTittleAndPath[i].second.length() - pos-1);

            pos = _algoTittleAndPath[i].second.find('\\',pos+4);
        }
        ss->clear();
    }
}
