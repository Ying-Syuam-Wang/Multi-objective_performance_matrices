#include <iostream>
#include "Indicator.h"
#include "Setting.h"
#include "Setting_Problem.h"
#include "Dominace_Relationship.h"
#include <stdlib.h>

using namespace std;

int main()
{
    CSetting Setting("Setting\\IndicatorSetting.csv");
    CProblem Problem("Setting\\Problem.csv");
    CDominace dominated;

    for(size_t s = 0; s < Setting.numSets(); s += 1)
    {
        vector<CAlgo> algos(Setting.numAlgos());
        CInstanceSetNames insSetNames(Setting.setTittle(s),"Setting\\"+Setting.setTittle(s)+".txt");

        CAlgo allInsPF;
        allInsPF.SetUp("PF","Setting\\PF",
                       insSetNames,Problem.numObj(),
                       "NONE",0,0);

        for(size_t a = 0; a < Setting.numAlgos(); a += 1)
        {
            algos[a].SetUp(Setting.algoTittleAndPath(s).first,
                           Setting.algoTittleAndPath(s).second,
                           insSetNames,Problem.numObj(),
                           Setting.insBack(),Setting.runBegin(),Setting.runEnd());
            ///update PF
            for(size_t i = 0; i < insSetNames[s].size(); i += 1)
                for(size_t r = 0,numRun = Setting.runEnd()-Setting.runBegin()+1; r < numRun; r += 1)
                    dominated.UpdatePF(Problem,algos[a][i][r].front(),allInsPF[i][0].front());
        }
        //output PF
        for(size_t i = 0; i < insSetNames[s].size(); i += 1)
        {

        }
        ///nomrolized
        for(size_t a = 0; a < Setting.numAlgos(); a += 1)
            for(size_t i = 0; i < insSetNames[s].size(); i += 1)
                for(size_t r = 0,numRun = Setting.runEnd()-Setting.runBegin()+1; r < numRun; r += 1)
//                    normalize(allInsPF[i][r].front(),algos[a][i][r].front());
        cout << "SetUp";
        system("PAUSE");
    }
    system("PAUSE");
}

