#include "Setting_Problem.h"
#include "FileProcess.h"
#include <fstream>
#include <string>
#include "Convert.h"
//CProblem Problem;

void repeatWarning(const std::string & problemSetting)
{
    while(true)printf("Restart and set up %s\n",problemSetting.c_str());
}

CProblem::CProblem(const std::string & problemSetting)
{
    std::ifstream file;
    FileProcess.open(problemSetting,file);
    std::string strTmp;
    file >> strTmp;
    file >> strTmp;

    std::size_t ipos = strTmp.find(",");
    if(ipos == std::string::npos)
        repeatWarning(problemSetting);

    _numObj = Convert.toSize_t(strTmp.substr(0,ipos));
    _objType.resize(_numObj);

    strTmp = strTmp.substr(ipos+1,strTmp.length()-ipos-1);
    ipos = strTmp.find(",");

    for(std::size_t i = 0; i < _numObj; i += 1)
    {
        if(ipos == std::string::npos)
            repeatWarning(problemSetting);
        if(strTmp.substr(0,ipos) == "MAX")
            _objType[i] = new CObjMaximize;
        else
            _objType[i] = new CObjMinimize;
        strTmp = strTmp.substr(ipos+1,strTmp.length()-ipos-1);
    }

}
CProblem::~CProblem()
{
    for(std::vector<CObjType*>::iterator it = _objType.begin(); it != _objType.end(); it += 1)
        delete (*it);
    _objType.clear();
}
