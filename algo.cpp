#include "algo.h"
#include "FileProcess_result.h"
#include "Convert.h"
#include "Setting.h"
#include "Setting_Problem.h"
using std::string;
using std::vector;
using std::size_t;

void CAlgo::SetUp(const string &tittle,
                  const string &absPath,
                  const vector<CInstanceSetNames> & insSetNames,
                  const CProblem & Problem,
                  const size_t numSet,
                  const string insBack,
                  const size_t runBegin,
                  const size_t runEnd)
{
    this->_tittle = tittle;
    this->_absoluteFolderPath = absPath;
    this->_insSets.resize(numSet);

    size_t numRun = 1;
    bool isWithBack = true;
    if(!(runBegin ==0 && runEnd == 0 && insBack == "NONE"))
        numRun = runEnd-runBegin+1;
    else
        isWithBack = false;

    for(size_t s = 0; s < numSet; s += 1)
    {
        _insSets[s].resizeIns(insSetNames[s].size());
        for(size_t i = 0; i < insSetNames[s].size(); i += 1)
        {
            _insSets[s][i].resizeRuns(numRun);
            for(size_t r = 0; r < numRun; r += 1)
            {
                if(isWithBack)
                    _insSets[s][i][r].SetUpSolutions(absPath+"\\\\"+insSetNames[s].name()+"\\\\"
                                                     +insSetNames[s][i]+insBack+Convert.toString(runBegin+r)+".txt", Problem.numObj());
                else
                    _insSets[s][i][r].SetUpSolutions(absPath+"\\\\"+insSetNames[s].name()+"\\\\"+insSetNames[s][i]+".txt", Problem.numObj());
            }
            _insSets[s][i].calRunPF(Problem);
        }
    }
}


void CAlgo::calAvgPerforamce()
{
    for(int m = matrix::GD; m != matrix::C_Metrix; m += 1)
    {
        double sum = 0.;
        for(size_t s = 0; s < _insSets.size(); s += 1)
        {
            _insSets[s].calAvgPerforamce();
            sum += _insSets[s].avgPerformance().get((matrix)m);
        }
        double average = sum / _insSets.size();
        _avgSetPerformance.set((matrix)m,average);
    }
}
