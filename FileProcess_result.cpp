#include "FileProcess_result.h"
#include "Front.h"
#include "Solution.h"
#include "algo.h"
#include "Instance.h"

CResultFileProcess ResultFileProcess;

void CResultFileProcess::ReadFront(const std::size_t numObj,std::ifstream & file,CFront & Front)
{
    CSolution sol(numObj);
    while(file >> sol[0])
    {
        for(std::size_t i = 1; i < numObj; i += 1)
            file >> sol[i];
        Front.push_back(sol);
    }
    Front.sortByObj();
    file.close();
}
void CResultFileProcess::OutFront(const CFront & Front,std::ofstream & file)
{
    for(std::size_t s = 0; s < Front.numSols(); s += 1)
    {
        for(std::size_t o = 0; o < Front[s].objSize(); o += 1)
            file << Front[s][o] << " ";
        file << std::endl;
    }
    file.close();
}
void CResultFileProcess::OutPerformance(const std::vector<CAlgo> & algos, const CInstanceSetNames & insSetNames, std::ofstream & file)
{
    OutTittle(algos,file);
    file.close();
}
void CResultFileProcess::OutTittle(const std::vector<CAlgo> & algos, std::ofstream & file)
{
    file << ",";
    for(CAlgo algo: algos)
        file << algo.tittle() << ",";
}
