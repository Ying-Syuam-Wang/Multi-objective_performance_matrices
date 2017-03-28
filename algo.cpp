#include "algo.h"
#include "FileProcess.h"
#include "Convert.h"
void CAlgo::SetUp(const string & tittle,
                  const string & absPath,
                  const CInstanceSetNames &insSetNames,
                  const size_t numObj,
                  const string & fileBack,
                  const size_t runBegin,
                  const size_t runEnd)
{
    _allInsRunResults.resize(insSetNames.size());
    this->_tittle = tittle;
    this->_absoluteFolderPath = absPath;
    std::ifstream ins;
    std::vector<std::vector<double>> tmpPoints;
    if(runBegin ==0 && runEnd == 0 && fileBack == "NONE")
    {
        for(size_t i = 0; i < insSetNames.size(); i += 1)
        {
            _allInsRunResults[i].resize(1);
            FileProcess.open(absPath+"\\"+insSetNames.name()+"\\"+insSetNames[i]+".txt",ins);
            FileProcess.ReadPoints(numObj,ins,tmpPoints);
            _allInsRunResults[i][0].SetSolutions(tmpPoints);
            tmpPoints.clear();
            ins.close();
        }
    }
    else
    {
        for(size_t i = 0, numRun = runEnd-runBegin+1; i < insSetNames.size(); i += 1)
        {
            _allInsRunResults[i].resize(numRun);
            for(size_t r = 0; r < numRun; r += 1)
            {
                FileProcess.open(absPath+"\\"+insSetNames.name()+"\\"+insSetNames[i]+fileBack+Convert.toString(runBegin+r)+".txt",ins);
                FileProcess.ReadPoints(numObj,ins,tmpPoints);
                _allInsRunResults[i][0].SetSolutions(tmpPoints);
                tmpPoints.clear();
                ins.close();
            }
        }
    }
}

