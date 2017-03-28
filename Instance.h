#ifndef INSTANCE_H_INCLUDED
#define INSTANCE_H_INCLUDED
#include <vector>
#include <string>
#include "FileProcess.h"
using std::string;

class CInstanceSetNames
{
public:
    CInstanceSetNames(){}
    explicit CInstanceSetNames(const std::string &setName,const CFileProcess::File_Root &fileName)
        {Set(fileName);
         SetName(setName);}

    void Set(const CFileProcess::File_Root &fileName);
    std::size_t size()const{return _insName.size();}

    void SetName(const string &n){_name = n;}
    const string &name()const{return _name;}

    const string & operator[](std::size_t i)const{return _insName[i];}
    string & operator[](std::size_t i)
        { return const_cast<string&>(static_cast<const CInstanceSetNames&>(*this)[i]);}
private:
    string _name;
    std::vector<string> _insName;
};

#endif // INSTANCE_H_INCLUDED
