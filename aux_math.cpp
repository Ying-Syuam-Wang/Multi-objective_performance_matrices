#include <vector>
#include <limits>
#include "aux_math.h"
#include <cmath>
using namespace std;

namespace MathAux
{

// ----------------------------------------------------------------------
// EuclideanDistance
// ----------------------------------------------------------------------
double EuclideanDistance(std::vector<double> from, std::vector<double> to)
{
    double powSum = 0;
    for(size_t i = 0; i < from.size(); i += 1)
        powSum += pow(from[i] - to[i],2);
    return sqrt(powSum);
}
}// namespace MathAux
