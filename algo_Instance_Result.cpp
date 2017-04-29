#include "algo_Instance_Result.h"
#include "Dominace_Relationship.h"
#include "Setting_Problem.h"

#include <iostream>
#include <stdlib.h>
using namespace std;
void CSingleInstanceResult::norPerforamceBy(const CPerformace & extermPerformance)
{
    for(int m = matrix::GD; m != matrix::Size; m += 1)
    {
        const double originalPer = _performance.get((matrix)m);
        const double minmimPer = extermPerformance.get((matrix)m);
        if(m == matrix::GD || m == matrix::IGD || m == matrix::IGD_Puls)
            _performance.set((matrix)m,(1+originalPer)/(1+minmimPer));
        else
            _performance.set((matrix)m,originalPer/minmimPer);
    }
}

void CSingleInstanceResult::SetSolutions(const std::vector<std::vector<double>> &F)
{
    _results.resize(F.size());
    for(std::size_t i = 0; i < F.size(); i += 1)
    {
        _results[i].resize(F[i].size());
        for(std::size_t o = 0; o < F[i].size(); o += 1)
            _results[i][o] = F[i][o];
    }
}
void CInstanceResult::norAllRunPerforamceBy(const CPerformace & extermPerformance)
{
    for(size_t r = 0; r < _Run.size(); r += 1)
        _Run[r].norPerforamceBy(extermPerformance);
}
void CInstanceResult::calAvgPerforamce()
{
    for(int m = matrix::GD; m != matrix::C_Metrix; m += 1)
    {
        double sum = 0.;
        for(size_t r = 0; r < _Run.size(); r += 1)
            sum += _Run[r].Performace().get((matrix)m);

        double average = sum / _Run.size();
        _avgRunPerformance.set((matrix)m,average);
    }
}
void CInstanceResult::calPF(const CProblem & Problem)
{
    CDominace dominated;
    for(size_t r = 0; r < _Run.size(); r += 1)
        dominated.UpdatePF(Problem , _Run[r].front(),_PF);
}
