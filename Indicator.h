#ifndef INDICATOR_H_INCLUDED
#define INDICATOR_H_INCLUDED
#include <vector>
#include <string>

enum matrix{GD = 0,IGD,IGD_Puls,HV,Size,C_Metrix};

class CInstanceResult;
class CProblem;
class CFront;
class CAlgo;

class CIndicator
{
public:
    static const std::size_t numMatrix = 6;
    static const std::vector<std::string> strMatrix;

    double StandardDeviation();
    double Average(const CAlgo & CAlgo);

    double C_Metrix(const CProblem &Problem, const CFront & A, const CFront & B);
    double GD(const CFront & Front, const CFront & PF){return this->IGD(PF,Front);}
    double IGD(const CFront & Front, const CFront & PF);
    double IGD_Puls(const CFront & Front, const CFront & PF);
    double HV(const CFront & Front,std::pair<double,double> referencePoint);

    double FrontSize(const CFront & Front);

private:
};

#endif // INDICATOR_H_INCLUDED
