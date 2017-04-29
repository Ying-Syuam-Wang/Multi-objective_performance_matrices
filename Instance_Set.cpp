#include "Instance_Set.h"
#include "algo_Instance_Result.h"

void CInstanceSet::calAvgPerforamce()
{
    for(int m = matrix::GD; m != matrix::C_Metrix; m += 1)
    {
        double sum = 0.;
        for(size_t i = 0; i < _insResult.size(); i += 1)
        {
            _insResult[i].calAvgPerforamce();
            sum += _insResult[i].avgPerformance().get((matrix)m);
        }
        double average = sum / _insResult.size();
        _avgInsPerformance.set((matrix)m,average);
    }
}
