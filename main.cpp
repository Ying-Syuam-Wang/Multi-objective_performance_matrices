#include "Indicator.h"
#include "Setting.h"
#include "Setting_Problem.h"
#include "algo.h"
#include "Dominace_Relationship.h"
#include "Convert.h"
#include "gnuplot_interface.h"

#include <iostream>
#include <stdlib.h>
#include <direct.h>
#include <windows.h>
#include <sstream>
using namespace std;

const std::pair<double,double> HV_ReferencePoint(1.2,1.2);

int main()
{
    CSetting Setting("Setting\\IndicatorSetting.csv");
    string answer = "n";
    while(mkdir(Setting.FolderTITTLE().c_str()) != 0 && answer != "y")
    {
        cout << "the folder "<< Setting.FolderTITTLE() <<" is already exist, want to reset? (y/n)...>";
        cin >> answer;
        if(answer != "y")
        {
            cout << "Or you want to change tittle?(y/n)...>";
            cin >> answer;
            if(answer == "y")
            {
                cout << "folder name...>";
                string NewFolderName;
                cin >> NewFolderName;
                Setting.setFolderTITTLE(NewFolderName);
            }
        }
    }

    vector<CAlgo> algos(Setting.numAlgos());
    vector<CInstanceSetNames> setIinsSetNames(Setting.numSets());
    for(size_t s = 0; s < Setting.numSets(); s += 1)
    {
        setIinsSetNames[s].SetName(Setting.setTittle(s));
        setIinsSetNames[s].SetUpNames("Setting\\"+Setting.setTittle(s)+".txt");
    }
    CAlgo allInsPF;
    CProblem Problem("Setting\\Problem.csv");
    allInsPF.SetUp("PF","Setting\\\\PF",setIinsSetNames,Problem.numObj(),
                   Setting.numSets(),"NONE",0,0);
    allInsPF.SetAbsPath(Setting.FolderTITTLE()+"\\\\PF");
    mkdir(allInsPF.absPath().c_str());

    CDominace dominated;
    cout << "Finding PF................................................" <<endl;
    const size_t numRun = Setting.runEnd()-Setting.runBegin()+1;
    for(size_t a = 0; a < Setting.numAlgos(); a += 1)
    {
        algos[a].SetUp(Setting.algoTittleAndPath(a).first,
                       Setting.algoTittleAndPath(a).second,
                       setIinsSetNames,Problem.numObj(),Setting.numSets(),
                       Setting.insBack(),Setting.runBegin(),Setting.runEnd());
        for(size_t s = 0; s < Setting.numSets(); s += 1)
            for(size_t i = 0; i < setIinsSetNames[s].size(); i += 1)
                for(size_t r = 0; r < numRun; r += 1)
                    dominated.UpdatePF(Problem,algos[a].atSet(s).Ins(i).Run(r).front(),allInsPF.atSet(s)[i][r].front());
    }
///find PF----------------------------------------------------------------------------------------
    cout << "Output PF at " << allInsPF.absPath() << "................................................" <<endl;
    for(size_t a = 0; a < Setting.numAlgos(); a += 1)
        for(size_t s = 0; s < Setting.numSets(); s += 1)
            for(size_t i = 0; i < setIinsSetNames[s].size(); i += 1)
            {
                const string strPF = allInsPF.absPath()+"\\\\"+Setting.setTittle(s);
                mkdir(strPF.c_str());
                ofstream outInsPF;
                for(size_t i = 0; i < setIinsSetNames[s].size(); i += 1)
                {
                    ResultFileProcess.open(strPF+"\\"+setIinsSetNames[s][i]+".txt",outInsPF);
                    allInsPF.atSet(s)[i][0].front().sortByObj();
                    ResultFileProcess.OutFront(allInsPF.atSet(s)[i][0].front(),outInsPF);
                }
            }
//output PF-----------------------------------------------------------------------------------------------
    CIndicator indicator;
    cout << "calculate performance................................................" <<endl;
    for(size_t s = 0; s < Setting.numSets(); s += 1)
        for(size_t i = 0; i < setIinsSetNames[s].size(); i += 1)
        {
            ///nomrolized
            for(size_t a = 0; a < Setting.numAlgos(); a += 1)
                for(size_t r = 0; r < numRun; r += 1)
                    algos[a].atSet(s)[i][r].front().nomalizeBy(allInsPF.atSet(s)[i][0].front().objsExterms());
            allInsPF.atSet(s)[i][0].front().nomalizeBy(allInsPF.atSet(s)[i][0].front().objsExterms());

            allInsPF.atSet(s)[i][0].Performace().setHV(indicator.HV(allInsPF.atSet(s)[i][0].front(),HV_ReferencePoint));
            allInsPF.atSet(s)[i][0].Performace().setSize(indicator.FrontSize(allInsPF.atSet(s)[i][0].front()));
            ///calculate performance
            //algos
            for(size_t a = 0; a < Setting.numAlgos(); a += 1)
                for(size_t r = 0; r < numRun; r += 1)
                {
                    algos[a].atSet(s)[i][r].Performace().setSize(indicator.FrontSize(algos[a].atSet(s)[i][r].front()));
                    algos[a].atSet(s)[i][r].Performace().setGD(indicator.GD(algos[a].atSet(s)[i][r].front(),
                            allInsPF.atSet(s)[i][0].front()));
                    algos[a].atSet(s)[i][r].Performace().setIGD(indicator.IGD(algos[a].atSet(s)[i][r].front(),
                            allInsPF.atSet(s)[i][0].front()));
                    algos[a].atSet(s)[i][r].Performace().setIGD_Puls(indicator.IGD_Puls(algos[a].atSet(s)[i][r].front(),
                            allInsPF.atSet(s)[i][0].front()));
                    algos[a].atSet(s)[i][r].Performace().setHV(indicator.HV(algos[a].atSet(s)[i][r].front(),HV_ReferencePoint));

                }
            ///calculate performance---------------------------------------------------------------------------------------------
        }
    cout << "find the minimum performance of all algorithm................................................" <<endl;
    CAlgo minPerformance(Setting.numSets());
    minPerformance.SetTittle("minimumAlgo");
    const string strMiniFPath = Setting.FolderTITTLE()+"\\\\"+minPerformance.tittle();
    mkdir(strMiniFPath.c_str());

    bool isWithBack = true;
    if(Setting.runBegin() ==0 && Setting.runEnd() == 0 && Setting.insBack() == "NONE")
        isWithBack = false;
    for(size_t s = 0; s < Setting.numSets(); s += 1)
    {
        const string strSetMiniFPath = strMiniFPath + "\\\\" + setIinsSetNames[s].name();
        mkdir(strSetMiniFPath.c_str());

        minPerformance.atSet(s).resizeIns(setIinsSetNames[s].size());
        for(size_t i = 0; i < setIinsSetNames[s].size(); i += 1)
        {
            minPerformance.atSet(s).Ins(i).resizeRuns(indicator.numMatrix-1);
            for(int m = matrix::GD; m != matrix::C_Metrix; m += 1)
                minPerformance.atSet(s)[i][m].Performace() = algos[0].atSet(s)[0][0].Performace();

            for(int m = matrix::GD; m != matrix::HV; m += 1)
            {
                int minAlgo = 0, minRun = 0;
                for(size_t a = 0; a < Setting.numAlgos(); a += 1)
                    for(size_t r = 0; r < numRun; r += 1)
                        if(minPerformance.atSet(s)[i][m].Performace().get((matrix)m) > algos[a].atSet(s)[i][r].Performace().get((matrix)m))
                        {
                            minPerformance.atSet(s)[i][m].Performace() = algos[0].atSet(s)[0][0].Performace();
                            minAlgo = a;
                            minRun = r;
                        }
                minPerformance.atSet(s)[i][m].front() = algos[minAlgo].atSet(s)[i][minRun].front();

                ///output minimum
                const string strSetMiniFMatrixPath = strSetMiniFPath + "\\\\" + indicator.strMatrix[m];
                mkdir(strSetMiniFMatrixPath.c_str());
                const string strNewFileName = strSetMiniFMatrixPath+"\\\\"+setIinsSetNames[s][i]+".txt";
                string backRun = "";
                if(isWithBack)
                    backRun = Setting.insBack()+Convert.toString(minRun);
                string strOldFileName = algos[minAlgo].absPath()+"\\\\"
                                        + setIinsSetNames[s].name()+"\\\\"
                                        + setIinsSetNames[s][i]+backRun+".txt";
                if(!CopyFile(strOldFileName.c_str(), strNewFileName.c_str(), FALSE))
                {
                    cout << "We can not crate " << strNewFileName <<endl;
                    system("PAUSE");
                }
                ///output minimum--------------------------------------------------------------------------------
            }
        }
    }
///find the minimum performance of all algorithm-------------------------------------------------------------
    cout << "normalized by the minimum performance of all algorithm, then average all performances..............................................." <<endl;
    for(size_t s = 0; s < Setting.numSets(); s += 1)
    {
        for(size_t i = 0; i < setIinsSetNames[s].size(); i += 1)
        {
            CPerformace extermPerformance;
            for(int m = matrix::GD; m != matrix::HV; m += 1)
            {
                const double minimum = minPerformance.atSet(s)[i][m].Performace().get((matrix)m);
                extermPerformance.set((matrix)m,minimum);
            }
            const double maximumHV = allInsPF.atSet(s)[i][0].Performace().get(matrix::HV);
            extermPerformance.set(matrix::HV,maximumHV);
            for(size_t a = 0; a < Setting.numAlgos(); a += 1)
                algos[a].atSet(s)[i].norAllRunPerforamceBy(extermPerformance);
        }
        for(size_t a = 0; a < Setting.numAlgos(); a += 1)
            algos[a].atSet(s).calAvgPerforamce();
    }
///normalized by the minimum performance of all algorithm, then average all performances----------------------------------------------------------------------------------------------
    cout << "output result..............................................." <<endl;
    const string strPerformacePath = Setting.FolderTITTLE()+"\\\\result";
    mkdir(strPerformacePath.c_str());
    CFileProcess FileProcess;
    ofstream PerfanmaceFile;

    for(size_t s = 0; s < Setting.numSets(); s += 1)
    {
        const string strFilename = strPerformacePath + "\\\\" + setIinsSetNames[s].name() + ".csv";
        FileProcess.open(strFilename,PerfanmaceFile);
        for(int m = matrix::GD; m != matrix::C_Metrix; m += 1)
        {
            PerfanmaceFile << CIndicator::strMatrix.at(m) << ",";
            for(size_t a = 0; a < Setting.numAlgos(); a += 1)
                PerfanmaceFile << algos[a].tittle() << ",";
            PerfanmaceFile << ",";
        }
        PerfanmaceFile << endl;

        for(size_t i = 0; i < setIinsSetNames[s].size(); i += 1)
        {
            for(int m = matrix::GD; m != matrix::C_Metrix; m += 1)
            {
                PerfanmaceFile << setIinsSetNames[s][i]  << ",";
                for(size_t a = 0; a < Setting.numAlgos(); a += 1)
                    PerfanmaceFile << algos[a].atSet(s).Ins(i).avgPerformance().get((matrix)m) << ",";
                PerfanmaceFile << ",";
            }
            PerfanmaceFile << endl;
        }
        PerfanmaceFile.close();
    }

    FileProcess.open(strPerformacePath + "\\\\allPerformance.csv",PerfanmaceFile);
    for(int m = matrix::GD; m != matrix::C_Metrix; m += 1)
    {
        PerfanmaceFile << CIndicator::strMatrix.at(m) <<",";
        for(size_t a = 0; a < Setting.numAlgos(); a += 1)
            PerfanmaceFile << algos[a].tittle() <<",";
        PerfanmaceFile << endl;

        for(size_t s = 0; s < Setting.numSets(); s += 1)
        {
            PerfanmaceFile << setIinsSetNames[s].name() <<",";
            for(size_t a = 0; a < Setting.numAlgos(); a += 1)
                PerfanmaceFile << algos[a].atSet(s).avgPerformance().get((matrix)m) << ",";
            PerfanmaceFile << endl;
        }
        PerfanmaceFile << endl;
    }
    PerfanmaceFile.close();

    cout << "calculate C matrix..............................................." <<endl;
    vector<vector<vector<vector<double>>>> insAlgoCmatrix(Setting.numSets());

    for(size_t s = 0; s < Setting.numSets(); s += 1)
    {
        insAlgoCmatrix[s].resize(setIinsSetNames[s].size());
        for(size_t i = 0; i < setIinsSetNames[s].size(); i += 1)
        {
            insAlgoCmatrix[s][i].resize(Setting.numAlgos());
            for(size_t a = 0; a < Setting.numAlgos(); a += 1)
                insAlgoCmatrix[s][i][a].resize(Setting.numAlgos(),-1.0);
        }
    }
    for(size_t s = 0; s < Setting.numSets(); s += 1)
    {
        for(size_t a = 0; a < Setting.numAlgos(); a += 1)
            for(size_t i = 0; i < setIinsSetNames[s].size(); i += 1)
                algos[a].atSet(s)[i].calPF(Problem);

        //c matrix
        for(size_t a = 0; a < Setting.numAlgos(); a += 1)
            for(size_t i = 0; i < setIinsSetNames[s].size(); i += 1)
                for(size_t compare = 0; compare < Setting.numAlgos(); compare += 1)
                {
                    if(a == compare)
                        insAlgoCmatrix[s][i][a][compare] = -1;
                    else
                        insAlgoCmatrix[s][i][a][compare] = indicator.C_Metrix(Problem ,algos[a].atSet(s)[i].front(),
                                                           algos[compare].atSet(s)[i].front());
                }
        //c matrix----------------------------------------------------------------------------------------------
    }

    cout << "output C matrix..............................................." <<endl;
    const string strCMatrixPath = strPerformacePath+"\\\\C_Matrix";
    mkdir(strCMatrixPath.c_str());

    ofstream CMatrixFile;
    for(size_t s = 0; s < Setting.numSets(); s += 1)
    {
        const string strFilename = strCMatrixPath + "\\\\" + setIinsSetNames[s].name() + ".csv";
        FileProcess.open(strFilename,CMatrixFile);
        for(size_t a = 0; a < Setting.numAlgos(); a += 1)
        {
            CMatrixFile << algos[a].tittle() << ",";
            for(size_t compare = 0; compare < Setting.numAlgos(); compare += 1)
                CMatrixFile << algos[compare].tittle() << ",";
            CMatrixFile << ",";
        }
        CMatrixFile << endl;

        for(size_t i = 0; i < setIinsSetNames[s].size(); i += 1)
        {
            for(size_t a = 0; a < Setting.numAlgos(); a += 1)
            {
                CMatrixFile << setIinsSetNames[s][i]  << ",";
                for(size_t compare = 0; compare < Setting.numAlgos(); compare += 1)
                    CMatrixFile << insAlgoCmatrix[s][i][a][compare] << ",";
                CMatrixFile << ",";
            }
            CMatrixFile << endl;
        }
        CMatrixFile.close();
    }
    ///output C matrix----------------------------------------------------------------------------------------------
///output result----------------------------------------------------------------------------------------------

///plot result
    if(Problem.numObj() <= 3)
    {
        cout << "plot begin.";
        Gnuplot gplot;
        gplot("set terminal png");
        const string strPlotPath = Setting.FolderTITTLE()+"\\\\plot";
        mkdir(strPlotPath.c_str());

        for(size_t a = 0; a < Setting.numAlgos(); a += 1)
        {
            const string strAlgoSetPlotPath = strPlotPath + "\\\\" + algos[a].tittle();
            mkdir(strAlgoSetPlotPath.c_str());
            for(size_t s = 0; s < Setting.numSets(); s += 1)
            {
                const string strSetPlotPath = strAlgoSetPlotPath + "\\\\" + setIinsSetNames[s].name();
                mkdir(strSetPlotPath.c_str());
                for(size_t i = 0; i < setIinsSetNames[s].size(); i += 1)
                {
                    const string Png =  "set output \"" + strSetPlotPath + "\\\\" + setIinsSetNames[s][i] + ".png\"";
                    gplot(Png);
                    for(int obj = 0; obj < (int)Problem.numObj(); obj += 1)
                        gplot.set_axis((dimension)obj, Problem.objName(obj));

                    ostringstream  txt;
                    const string SetInsNmae = setIinsSetNames[s].name() + "\\\\"+
                                              setIinsSetNames[s][i];
                    txt << " \"" << allInsPF.absPath() << "\\\\"
                        << SetInsNmae << ".txt \" pt 2"
                        << " title \""<< allInsPF.tittle() <<"\"";
                    if(!isWithBack)
                        txt << " ,\"" << algos[a].absPath() << "\\\\"
                            << SetInsNmae << ".txt \" pt 4"
                            << " title \""<< algos[a].tittle() <<"\"";
                    else
                        for(size_t r = 0; r < numRun; r += 1)
                        {
                            txt << ",\"" << algos[a].absPath() << "\\\\"
                                << SetInsNmae << Setting.insBack() << r << ".txt\" pt " << 4+2*r
                                << " title \""<< algos[a].tittle() << Setting.insBack() << r << "\"";
                        }
                    gplot.plot(txt.str());
                }
            }
        }
///output algos PF

////set/ins/algo.png(allrun
////set/ins/AllAlgos.png(allrun
//
//        const string strPlotALLPFPath = strPlotPath + "\\\\ALL_algo_PF";
//        mkdir(strPlotALLPFPath.c_str());
//        const string strAlgoSetPlotPath = strPlotPath + "\\\\" + algos[a].tittle();
//        mkdir(strAlgoSetPlotPath.c_str());
//        for(size_t s = 0; s < Setting.numSets(); s += 1)
//        {
//            const string strSetPlotPath = strAlgoSetPlotPath + "\\\\" + setIinsSetNames[s].name();
//            mkdir(strSetPlotPath.c_str());
//            for(size_t i = 0; i < setIinsSetNames[s].size(); i += 1)
//            {
//                const string Png =  "set output \"" + strSetPlotPath + "\\\\" + setIinsSetNames[s][i] + ".png\"";
//                gplot(Png);
//                for(int obj = 0; obj < (int)Problem.numObj(); obj += 1)
//                    gplot.set_axis((dimension)obj, Problem.objName(obj));
//
//                ostringstream  txt;
//                txt << " \"" << allInsPF.absPath() << "\\\\"
//                    << setIinsSetNames[s].name() << "\\\\"
//                    << setIinsSetNames[s][i] << ".txt \" pt 2"
//                    << " title \""<< allInsPF.tittle() <<"\"";
//                for(size_t a = 0; a < Setting.numAlgos(); a += 1)
//                    for(size_t r = 0; r < numRun; r += 1)
//                    {
//                        txt << ",\"" << algos[a].absPath() << "\\\\"
//                            << setIinsSetNames[s].name() << "\\\\"
//                            << setIinsSetNames[s][i] << Setting.insBack() << r << ".txt\" pt " << 4+2*r
//                            << " title \""<< algos[a].tittle() << Setting.insBack() << r << "\"";
//                    }
//
//                gplot.plot(txt.str());
//            }
//        }
///output cmatrix---------------------------------------------------------------------------------------------
        gplot("exit");
    }
///output result----------------------------------------------------------------------------------------------


}

