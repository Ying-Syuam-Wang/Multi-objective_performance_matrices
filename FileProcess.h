#ifndef FILEPROCESS_H_INCLUDED
#define FILEPROCESS_H_INCLUDED

#include <string>
#include <vector>
#include <fstream>

class CFileProcess
{
public:
    enum warningRate{repeatShowWithStop = 0, showWithStop, show, noWarning};

    typedef std::string File_Root;

    bool open(const File_Root & fileName,std::ifstream & file, const warningRate wRate = repeatShowWithStop);
    bool open(const File_Root & fileName,std::ofstream & file, const warningRate wRate = repeatShowWithStop);
    std::stringstream* read_CSV_line(const std::size_t length,std::string & line);
    void ReadPoints(const std::size_t numObj,
                    std::ifstream & file,
                    std::vector<std::vector<double>> & points);
    void OutPoints(const std::vector<std::vector<double>> & points,
                   std::ofstream & file);

    bool isDirectExist(const std::string & dir);
    bool isFileExist(const std::string & file);
};


#endif // FILEPROCESS_H_INCLUDED
