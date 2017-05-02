#include "FileProcess.h"

#include <stdlib.h>
#include <sstream>
#include <direct.h>
#include <sys/stat.h>

using std::string;
using std::vector;

std::stringstream* CFileProcess::read_CSV_line(const std::size_t length,string & line)
{
    std::stringstream *ss = new std::stringstream[length];
    for(std::size_t col = 0 ; col < length; col += 1)
    {
        int nPos = line.find(',');
        string strTemp(line.substr(0, nPos));
        ss[col] << strTemp;
        line = line.substr(nPos+1, line.length() - nPos);
    }
    return ss;
}
bool CFileProcess::open(const File_Root & fileName,std::ifstream & file, const warningRate wRate)
{
    file.open(fileName.c_str());
    if(file.fail() && wRate != noWarning)
    {
        printf("%s Not found!\n",fileName.c_str());
        if(wRate == repeatShowWithStop)
        {
            do
            {
                printf("If you give me that file,then will read.\n");
                system("PAUSE");
                file.open(fileName.c_str());
            }
            while(file.fail());
        }
        else if(wRate == showWithStop)
            system("PAUSE");
    }
    return !file.fail();
}
bool CFileProcess::open(const File_Root & fileName,std::ofstream & file, const warningRate wRate)
{
    file.open(fileName.c_str());
    if(file.fail() && wRate != noWarning)
    {
        printf("We can`t build %s\n",fileName.c_str());
        if(wRate == repeatShowWithStop)
        {
            do
            {
                printf("Try tturn off.If ok,then will build.\n");
                system("PAUSE");
                file.open(fileName.c_str());
            }
            while(file.fail());
        }
        else if(wRate == showWithStop)
            system("PAUSE");
    }
    return !file.fail();
}

void CFileProcess::ReadPoints(const std::size_t numObj,std::ifstream & file,vector<vector<double>> & points)
{
    vector<double> point(numObj);
    while(file >> point[0])
    {
        for(std::size_t i = 1; i < numObj; i += 1)
            file >> point[i];
        points.push_back(point);
    }
    file.close();
}
void CFileProcess::OutPoints(const std::vector<std::vector<double>> & points,std::ofstream & file)
{
    for(std::vector<double> point: points)
    {
        for(double o: point)
            file << o << " ";
        file << std::endl;
    }
    file.close();
}

int chdir(const char* Path);
/**
check back to current direct
https://msdn.microsoft.com/en-us/library/windows/desktop/aa364934(v=vs.85).aspx
**/
char *getcwd(
    char *buffer,
    int maxlen
);
bool CFileProcess::isDirectExist(const std::string & dir)
{
    char buf[2000];
    getcwd(buf, sizeof(buf)-1);
    if(!chdir(dir.c_str()))
    {
        chdir(buf);
        return true;
    }
    else
        return false;
}
bool CFileProcess::isFileExist(const std::string & file)
{
    struct stat buf;
    if(stat(file.c_str(), &buf) != -1)

        return true;
    else
        return false;
}
