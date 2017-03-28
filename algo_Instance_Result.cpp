#include "algo_Instance_Result.h"


void CInstanceResult::SetSolutions(const std::vector<std::vector<double>> &F)
{
    _results.resize(F.size());
    for(std::size_t i = 0; i < F.size(); i += 1)
    {
        _results[i].resize(F[i].size());
        for(std::size_t o = 0; o < F[i].size(); o += 1)
            _results[i][o] = F[i][o];
    }
}
