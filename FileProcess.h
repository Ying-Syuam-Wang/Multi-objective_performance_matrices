#ifndef FILEPROCESS_H_INCLUDED
#define FILEPROCESS_H_INCLUDED

#include <string>
#include <vector>
#include <fstream>

class CFileProcess
{
public:
    typedef std::string File_Root;

    void open(const File_Root & fileName,std::ifstream & file);
    void open(const File_Root & fileName,std::ofstream & file);
    std::stringstream* read_CSV_line(const std::size_t length,std::string & line);
    void ReadPoints(const std::size_t numObj,
                    std::ifstream & file,
                    std::vector<std::vector<double>> & points);
    void OutPoints(const std::vector<std::vector<double>> & points,
                   std::ofstream & file);
};


#endif // FILEPROCESS_H_INCLUDED
