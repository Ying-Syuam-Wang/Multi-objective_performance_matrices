#include <iostream>
#include "Indicator.h"
#include "Setting.h"
#include "Setting_Problem.h"
//#include <fstream>
//#include <sstream>
//#include <string>
#include <stdlib.h>

using namespace std;

int main()
{
//    ifstream input;
//    input.open("Setting\\j120_40cases.txt");
//    ofstream output;
//    output.open("Setting\\J120.txt");
//    string str;
//    while(input >> str && !input.fail())
//    {
//        str = str.substr(0, str.length() - 7);
//
//        output << str << endl;
//        str.clear();
//    }
//    input.close();
//    output.close();

    CSetting Setting("Setting\\IndicatorSetting.csv");
    CProblem Problem("Setting\\Problem.csv");
    for(size_t s = 0; s < Setting.numSets(); s += 1)
    {
        vector<CAlgo> algos(Setting.numAlgos());
        CInstanceSetNames insSetNames(Setting.setTittle(s),"Setting\\"+Setting.setTittle(s)+".txt");
        for(size_t a = 0; a < Setting.numAlgos(); a += 1)
        {
            algos[a].SetUp(Setting.algoTittleAndPath(s).first,
                           Setting.algoTittleAndPath(s).second,
                           insSetNames,Problem.numObj(),
                           Setting.insBack(),Setting.runBegin(),Setting.runEnd());
    cout<<"SetUp";
    system("PAUSE");
            for(size_t i = 0; i < insSetNames[s].size(); i += 1)
            {
                for(size_t j = 0,numRun = Setting.runEnd()-Setting.runBegin()+1; j < numRun; j += 1)
                {

                }
            }
        }
    }


    system("PAUSE");


}

