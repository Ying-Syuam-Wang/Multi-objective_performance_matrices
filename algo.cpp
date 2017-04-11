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
    this->_tittle = tittle);
    this->_absoluteFolderPath = absPath;

    size_t numRun = 1;
    if(!(runBegin ==0 && runEnd == 0 && fileBack == "NONE"))
        numRun = runEnd-runBegin+1;
    _allInsRunResults.resize(insSetNames.size(),vector<CInstanceResult>(numRun));

    for(size_t i = 0, numRun = runEnd-runBegin+1; i < insSetNames.size(); i += 1)
        for(size_t r = 0; r < numRun; r += 1)
            this->SetUpSolutions(absPath+"\\"+insSetNames.name()+"\\"+insSetNames[i]+fileBack+Convert.toString(runBegin+r)+".txt",
                            numObj,_allInsRunResults[i][0]);
//    this->SetUpSolutions(absPath+"\\"+insSetNames.name()+"\\"+insSetNames[i]+".txt",
//                    numObj,_allInsRunResults[i][0]);
//            FileProcess.open(absPath+"\\"+insSetNames.name()+"\\"+insSetNames[i]+".txt",ins);
//            FileProcess.ReadPoints(numObj,ins,tmpPoints);
//            _allInsRunResults[i][0].SetSolutions(tmpPoints);
//            tmpPoints.clear();
//            ins.close();
}
void CAlgo::SetUpSolutions(const string &fileName,
                           const size_t numObj,
                           CInstanceResult &insResult)
{
    std::ifstream ins;
    std::vector<std::vector<double>> tmpPoints;

    FileProcess.open(fileName,ins);
    FileProcess.ReadPoints(numObj,ins,tmpPoints);
    insResult.SetSolutions(tmpPoints);
    ins.close();
}
