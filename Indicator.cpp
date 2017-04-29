#include "Indicator.h"
#include "algo.h"
#include "Front.h"
#include "aux_math.h"
#include "Dominace_Relationship.h"

const std::vector<std::string> CIndicator::strMatrix = {"GD", "IGD", "IGD_Puls", "HV", "Size", "C_Metrix"};
double CIndicator::IGD_Puls(const CFront & Front, const CFront & PF)
{
    return 1;
}
double CIndicator::IGD(const CFront & Front, const CFront & PF)
{
    double sum = 0.0;
    for(CSolution sPF : PF.Sols())
    {
        double distance = MathAux::EuclideanDistance(PF[0].objs(),Front[0].objs());
        for(CSolution sF : Front.Sols())
        {
            double compare = MathAux::EuclideanDistance(sPF.objs(),sF.objs());
            if(distance > compare)
                distance = compare;
        }
        sum += distance;

    }
    return sum /(double) PF.numSols();
}


double CIndicator::HV(const CFront & Front,std::pair<double,double> referencePoint)
{
    CFront outFreeFront(Front);
    std::size_t i = 0;
    while(i < outFreeFront.numSols())
        if(outFreeFront[i][0] > referencePoint.first || outFreeFront[i][1] > referencePoint.second)
            outFreeFront.erase(outFreeFront.begin()+i);
        else
            i += 1;
    double tempHV = 0.;
    for(size_t h = 0; h < outFreeFront.numSols(); h += 1)
    {
        tempHV += (referencePoint.first - outFreeFront[h][0]) * (referencePoint.second - outFreeFront[h][1]);
        referencePoint.second = outFreeFront[h][1];
    }
    return tempHV;
}

double CIndicator::C_Metrix(const CProblem &Problem, const CFront & A, const CFront & B)
{
    CDominace dominated;
    double winNu = 0.0;
    for(size_t L = 0; L < B.numSols(); L +=1)
    {
        for(size_t W = 0; W < A.numSols(); W += 1)
        {
            if(dominated(Problem,A[W],B[L]))
            {
                winNu = winNu + 1.0;
                break;
            }
        }
    }
    return (double)winNu / (double) B.numSols();
}
double CIndicator::FrontSize(const CFront & Front)
{
    return Front.numSols();
}
