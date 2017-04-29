#include "algo_Performace.h"
void CPerformace::set(matrix i, CObjType::Tobj per)
{
    if(i == matrix::GD)
        _GD = per;
    if(i ==  matrix::IGD)
        _IGD = per;
    if(i ==  matrix::IGD_Puls)
        _IGD_Puls = per;
    if(i ==  matrix::HV)
        _HV = per;
    if(i ==  matrix::Size)
        _Size = per;
}
CObjType::Tobj CPerformace::get(const matrix i)const
{
    if(i == matrix::GD)
        return _GD;
    if(i ==  matrix::IGD)
        return _IGD;
    if(i ==  matrix::IGD_Puls)
        return _IGD_Puls;
    if(i ==  matrix::HV)
        return _HV;

    return _Size;
}
