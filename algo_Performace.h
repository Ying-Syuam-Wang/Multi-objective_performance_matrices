#ifndef ALGO_PERFORMACE_H_INCLUDED
#define ALGO_PERFORMACE_H_INCLUDED
#include "Indicator.h"
#include "Objective_Type.h"
#include <iostream>
#include <vector>
#include <string>
using std::string;

class CPerformace
{
    friend std::ostream & operator << (std::ostream & os,const CPerformace &insPer)
    {
            os << "GD ,"    << insPer._GD       << ", "
               << "IGD ,"   << insPer._IGD      << ", "
               << "IGD+ ,"  << insPer._IGD_Puls << ", "
               << "HV ,"  << insPer._HV       << ", "
               << "Size ," << insPer._Size     << std::endl;
        return os;
    }
public:
    CPerformace(){}
    void set(const std::vector<CObjType::Tobj> & per);
    void set(matrix i, CObjType::Tobj per);
    void setGD(CObjType::Tobj gd){_GD = gd;}
    void setIGD(CObjType::Tobj igd){_IGD = igd;}
    void setIGD_Puls(CObjType::Tobj igd_plus){_IGD_Puls = igd_plus;}
    void setHV(CObjType::Tobj hv){_HV = hv;}
    void setSize(CObjType::Tobj s){_Size = s;}

    CObjType::Tobj get(const matrix i)const;

    CObjType::Tobj GD(){return _GD;}
    CObjType::Tobj IGD(){return _IGD;}
    CObjType::Tobj IGD_Puls(){return _IGD_Puls;}
    CObjType::Tobj HV(){return _HV;}
    CObjType::Tobj Size(){return _Size;}

    bool isBetter(const matrix i, const CObjType::Tobj compare);
    bool isBetter(const matrix i, const CPerformace & compare);

    void norPerforamceBy(const CPerformace & extermPerformance);
private:
    CObjType::Tobj _GD;
    CObjType::Tobj _IGD;
    CObjType::Tobj _IGD_Puls;
    CObjType::Tobj _HV;
    CObjType::Tobj _Size;
};
#endif // ALGO_PERFORMACE_H_INCLUDED
