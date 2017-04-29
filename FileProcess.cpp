#include "FileProcess.h"

#include <stdlib.h>
#include <sstream>

using std::string;
using std::vector;

std::stringstream* CFileProcess::read_CSV_line(const std::size_t length,string & line)
{
    std::stringstream *ss = new std::stringstream[length];
    for(std::size_t col = 0 ; col < length; col += 1)
    {
        int nPos = line.find(',');
        string strTemp = line.substr(0, nPos);
        ss[col] << strTemp;
        line = line.substr(nPos+1, line.length() - nPos);
    }
    return ss;
}
void CFileProcess::open(const File_Root & fileName,std::ifstream & file)
{
    file.open(fileName.c_str());
    while(file.fail())
    {
        printf("We need %s\n",fileName.c_str());
        printf("If you give me that file,then will read.\n");
        system("PAUSE");
        file.open(fileName.c_str());
    }
}
void CFileProcess::open(const File_Root & fileName,std::ofstream & file)
{
    file.open(fileName.c_str());
    while(file.fail())
    {
        printf("We can`t build %s\n",fileName.c_str());
        printf("Try tturn off.If ok,then will build.\n");
        system("PAUSE");
    }
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
