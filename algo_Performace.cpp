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

bool CPerformace::isBetter(const matrix i, const CObjType::Tobj compare)
{
    if(i >= matrix::HV)
    {
        if(this->get(i) > compare)
            return true;
    }
    else
    {
        if(this->get(i) < compare)
            return true;
    }
    return false;
}
bool CPerformace::isBetter(const matrix i, const CPerformace & compare)
{
    return isBetter(i,compare.get(i));
}
void CPerformace::norPerforamceBy(const CPerformace & extermPerformance)
{
    for(int m = matrix::GD; m != matrix::Size; m += 1)
    {
        const double originalPer = get((matrix)m);
        const double minmimPer = extermPerformance.get((matrix)m);
        if(m == matrix::GD || m == matrix::IGD || m == matrix::IGD_Puls)
            set((matrix)m,(1+originalPer)/(1+minmimPer));
        else
            set((matrix)m,originalPer/minmimPer);
    }
}
