#ifndef INDICATOR_H_INCLUDED
#define INDICATOR_H_INCLUDED
#include <vector>
#include "algo.h"

enum matrix{GD = 1 ,IGD,IGD_Puls,HV,C_Metrix,Size};

class CInstanceResult;

class CIndicator
{
public:
    double operator()(const matrix m,const CInstanceResult & result);
    double StandardDeviation();
    double Average(const CAlgo & CAlgo);

    double C_Metrix();
    double GD();
    double IGD();
    double IGD_Puls();
    double HV();
    double Size();

private:
};

#endif // INDICATOR_H_INCLUDED
