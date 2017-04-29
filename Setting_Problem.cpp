#include "Setting_Problem.h"
#include "FileProcess_result.h"
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
    ResultFileProcess.open(problemSetting,file);
    std::string firstLine;
    file >> firstLine;
    std::string secondLine;
    file >> secondLine;

    std::size_t ipos = secondLine.find(",");
    if(ipos == std::string::npos)
        repeatWarning(problemSetting);

    _numObj = Convert.toSize_t(secondLine.substr(0,ipos));
    _objType.resize(_numObj);

    secondLine = secondLine.substr(ipos+1,secondLine.length()-ipos-1);
    ipos = secondLine.find(",");

    for(std::size_t i = 0; i < _numObj; i += 1)
    {
        if(ipos == std::string::npos)
            repeatWarning(problemSetting);
        if(secondLine.substr(0,ipos) == "MAX")
            _objType[i] = new CObjMaximize;
        else
            _objType[i] = new CObjMinimize;
        secondLine = secondLine.substr(ipos+1,secondLine.length()-ipos-1);
    }
    _objNames.resize(_numObj);
    for(std::string name: _objNames)
    {
        ipos = firstLine.find(",");
        name = firstLine.substr(0,ipos-1);
        firstLine = firstLine.substr(ipos+1,secondLine.length()-ipos-1);
    }
}
CProblem::~CProblem()
{
    for(std::vector<CObjType*>::iterator it = _objType.begin(); it != _objType.end(); it += 1)
        delete (*it);
    _objType.clear();
}
