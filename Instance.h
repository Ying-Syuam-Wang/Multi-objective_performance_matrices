#ifndef INSTANCE_H_INCLUDED
#define INSTANCE_H_INCLUDED
#include <vector>
#include <string>
#include "FileProcess.h"

class CInstanceSet_Setting
{
public:
    CInstanceSet_Setting(){}
    explicit CInstanceSet_Setting(const CFileProcess::File_Root &fileName)
        {Set(fileName);}

    void Set(const CFileProcess::File_Root &fileName);

    void SetName(const std::string & n){_name = n;}
    const std::string & name()const{return _name;}

    const std::string & operator[](std::size_t i)const{return _insName[i];}
    std::string & operator[](std::size_t i)
        { return const_cast<std::string&>(static_cast<const CInstanceSet_Setting&>(*this)[i]);}
private:
    std::string _name;
    std::vector<std::string> _insName;
};


#endif // INSTANCE_H_INCLUDED
