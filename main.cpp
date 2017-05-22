#include "Indicator.h"
#include "Setting.h"
#include "Setting_Problem.h"
#include "algo.h"
#include "Dominace_Relationship.h"
#include "Convert.h"
#include "gnuplot_interface.h"
#include "FileProcess_result.h"

#include <iostream>
#include <stdlib.h>
#include <direct.h>
#include <windows.h>
#include <sstream>
using namespace std;

//enum matrix{GD = 0,IGD,IGD_Puls,HV,Size,C_Metrix};
const int matrixFront = matrix::GD;
const int matrixEnd = matrix::HV;

const std::pair<double,double> HV_ReferencePoint(1.2,1.2);
int main()
{
    CSetting Setting("Setting\\IndicatorSetting.csv");
    string answer("n");
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

    cout << "Result output to " << Setting.FolderTITTLE() << "................................................" <<endl;

    vector<CAlgo> norAlgos(Setting.numAlgos());
    vector<CInstanceSetNames> setIinsSetNames(Setting.numSets());
    for(size_t s = 0; s < Setting.numSets(); s += 1)
    {
        setIinsSetNames[s].SetName(Setting.setTittle(s));
        setIinsSetNames[s].SetUpNames("Setting\\"+Setting.setTittle(s)+".txt");
    }
    CAlgo setPF;
    CProblem Problem("Setting\\Problem.csv");
    setPF.SetUp("PF","Setting\\\\PF",setIinsSetNames,Problem,
                Setting.numSets(),"NONE",0,0);
    setPF.SetAbsPath(Setting.FolderTITTLE()+"\\\\PF");
    mkdir(setPF.absPath().c_str());

    CDominace dominated;
    cout << "Finding PF................................................" <<endl;
    const size_t numRun = Setting.runEnd()-Setting.runBegin()+1;
    for(size_t a = 0; a < Setting.numAlgos(); a += 1)
    {
        norAlgos[a].SetUp(Setting.algoTittleAndPath(a).first,
                          Setting.algoTittleAndPath(a).second,
                          setIinsSetNames,Problem,Setting.numSets(),
                          Setting.insBack(),Setting.runBegin(),Setting.runEnd());
        for(size_t s = 0; s < Setting.numSets(); s += 1)
            for(size_t i = 0; i < setIinsSetNames[s].size(); i += 1)
                for(size_t r = 0; r < numRun; r += 1)
                {
                    cout << s <<i <<r<<endl;

                    dominated.UpdatePF(Problem,norAlgos[a].atSet(s).Ins(i).Run(r).front(),setPF.atSet(s)[i].front());
                }
    }

///find PF----------------------------------------------------------------------------------------
    cout << "Output PF at " << setPF.absPath() << "................................................" <<endl;

    ofstream outInsPF;
    for(size_t s = 0; s < Setting.numSets(); s += 1)
    {
        const string strPF(setPF.absPath()+"\\\\"+Setting.setTittle(s));
        mkdir(strPF.c_str());
        for(size_t i = 0; i < setIinsSetNames[s].size(); i += 1)
        {
            ResultFileProcess.open(strPF+"\\"+setIinsSetNames[s][i]+".txt",outInsPF);
            setPF.atSet(s)[i].front().sortByObj();
            ResultFileProcess.OutFront(setPF.atSet(s)[i].front(),outInsPF);
        }
    }
    cout << "Output PF_Size.csv at " << setPF.absPath() << "................................................" <<endl;
    ofstream outInsPF_Size;
    for(size_t s = 0; s < Setting.numSets(); s += 1)
    {
        ResultFileProcess.open(setPF.absPath()+"\\\\"+Setting.setTittle(s)+"_PF_Size.csv",outInsPF_Size);
        outInsPF_Size << Setting.setTittle(s) << ",size" << endl;
        for(size_t i = 0; i < setIinsSetNames[s].size(); i += 1)
        {
            outInsPF_Size << setIinsSetNames[s][i] << ","
                          << setPF.atSet(s)[i].front().numSols() << endl;
        }
        outInsPF_Size.close();
    }
///output PF-----------------------------------------------------------------------------------------------

    cout << "check PF size................................................" <<endl;
    bool isOnlyOneSolInPF = false;
    for(size_t s = 0; s < Setting.numSets(); s += 1)
        for(size_t i = 0; i < setIinsSetNames[s].size(); i += 1)
            if(setPF.atSet(s)[i].front().numSols() == 1)
            {
                isOnlyOneSolInPF = true;
                cout << setIinsSetNames[s][i] << " only has one solution in PF." << endl;
            }
    while(isOnlyOneSolInPF)
    {
        cout << "Please remove above instances from setting, then restart." << endl;
        system("PAUSE");
    }

///check PF size-----------------------------------------------------------------------------------------------
    //for output Extreme----------------------------------------
    const vector<CAlgo> norFreeAlgos(norAlgos);
    const CAlgo norFreeSetPF(setPF);
    //for output Extreme-----------------------------------------

    CIndicator indicator;
    cout << "calculate performance................................................" <<endl;
    for(size_t s = 0; s < Setting.numSets(); s += 1)
        for(size_t i = 0; i < setIinsSetNames[s].size(); i += 1)
        {
            ///nomrolized
            for(size_t a = 0; a < Setting.numAlgos(); a += 1)
                for(size_t r = 0; r < numRun; r += 1)
                    norAlgos[a].atSet(s)[i][r].front().nomalizeBy(setPF.atSet(s)[i].front().objsExtremes());

            setPF.atSet(s)[i].front().nomalizeBy(setPF.atSet(s)[i].front().objsExtremes());
            setPF.atSet(s)[i].Performace().setHV(indicator.HV(setPF.atSet(s)[i].front(),HV_ReferencePoint));
            setPF.atSet(s)[i].Performace().setSize(indicator.FrontSize(setPF.atSet(s)[i].front()));
            ///calculate performance
            //algos
            for(size_t a = 0; a < Setting.numAlgos(); a += 1)
                for(size_t r = 0; r < numRun; r += 1)
                {
                    norAlgos[a].atSet(s)[i][r].Performace().setSize(indicator.FrontSize(norAlgos[a].atSet(s)[i][r].front()));
                    norAlgos[a].atSet(s)[i][r].Performace().setGD(indicator.GD(norAlgos[a].atSet(s)[i][r].front(),
                            setPF.atSet(s)[i].front()));
                    norAlgos[a].atSet(s)[i][r].Performace().setIGD(indicator.IGD(norAlgos[a].atSet(s)[i][r].front(),
                            setPF.atSet(s)[i].front()));
                    norAlgos[a].atSet(s)[i][r].Performace().setIGD_Puls(indicator.IGD_Puls(norAlgos[a].atSet(s)[i][r].front(),
                            setPF.atSet(s)[i].front()));
                    norAlgos[a].atSet(s)[i][r].Performace().setHV(indicator.HV(norAlgos[a].atSet(s)[i][r].front(),HV_ReferencePoint));
                }
        }
///calculate performance---------------------------------------------------------------------------------------------
    cout << "find the minimum/maximum  performance of all algorithm................" <<endl;
    //read form Setting\\\\ExtremePerformance
    string strExtremePerformancePath("Setting\\\\extremePerformance");
    bool isExtremePerformancePathExist = true;
    if(ResultFileProcess.isDirectExist(strExtremePerformancePath))
        cout << "reading minimum/maximum performance from " << strExtremePerformancePath <<"........" <<endl;
    else
    {
        cout << "There is no minimum/maximum performance in " << strExtremePerformancePath <<"...." <<endl;
        isExtremePerformancePathExist = false;
    }
    CAlgo extremeResult(Setting.numSets());
    extremeResult.SetTittle("extremePF");
    const string strExtremeFPath(Setting.FolderTITTLE()+"\\\\"+extremeResult.tittle());
    mkdir(strExtremeFPath.c_str());
    for(size_t s = 0; s < Setting.numSets(); s += 1)
    {
        string strExtremePerformanceSetPath(strExtremePerformancePath+"\\\\"+setIinsSetNames[s].name());
        if(isExtremePerformancePathExist && !ResultFileProcess.isDirectExist(strExtremePerformanceSetPath))
        {
            cout << "There is no minimum/maximum performance in " << strExtremePerformanceSetPath <<"....." <<endl;
            isExtremePerformancePathExist = false;
        }
        extremeResult.atSet(s).resizeIns(setIinsSetNames[s].size());
        for(size_t i = 0; i < setIinsSetNames[s].size(); i += 1)
        {
            extremeResult.atSet(s).Ins(i).resizeRuns(indicator.numMatrix-1);
            for(int m = matrixFront; m != matrixEnd; m += 1)
            {

                const string strReadExtremeFile(strExtremePerformancePath + "\\\\"
                                                + indicator.strMatrix[m] + "\\\\"
                                                + setIinsSetNames[s][i] + ".txt");
                if(isExtremePerformancePathExist
                        && ResultFileProcess.isFileExist(strReadExtremeFile))
                {
                    //read Extreme
                    extremeResult.atSet(s)[i][m].SetUpSolutions(strReadExtremeFile,Problem.numObj());
                    const CFront tmpFront(extremeResult.atSet(s)[i][m].front());
                    extremeResult.atSet(s)[i][m].front().nomalizeBy(norFreeSetPF.atSet(s)[i].front().objsExtremes());
///maybe users file would be smaller than PF
                    extremeResult.atSet(s)[i][m].Performace().setSize(indicator.FrontSize(extremeResult.atSet(s)[i][m].front()));
                    extremeResult.atSet(s)[i][m].Performace().setGD(indicator.GD(extremeResult.atSet(s)[i][m].front(),
                            setPF.atSet(s)[i].front()));
                    extremeResult.atSet(s)[i][m].Performace().setIGD(indicator.IGD(extremeResult.atSet(s)[i][m].front(),
                            setPF.atSet(s)[i].front()));
                    extremeResult.atSet(s)[i][m].Performace().setIGD_Puls(indicator.IGD_Puls(extremeResult.atSet(s)[i][m].front(),
                            setPF.atSet(s)[i].front()));

                    extremeResult.atSet(s)[i][m].front() = tmpFront;
                }
                else
                {
                    extremeResult.atSet(s)[i][m].Performace() = norAlgos[0].atSet(s)[i][0].Performace();
                    extremeResult.atSet(s)[i][m].front() = norFreeAlgos[0].atSet(s)[i][0].front();
                }
///find extreme from new fronts
/*
                for(size_t a = 0; a < Setting.numAlgos(); a += 1)
                    for(size_t r = 0; r < numRun; r += 1)
                        if(norAlgos[a].atSet(s)[i][r].Performace().isBetter((matrix)m, extremeResult.atSet(s)[i][m].Performace()))
                        {
                            extremeResult.atSet(s)[i][m].Performace() = norAlgos[a].atSet(s)[i][r].Performace();
                            extremeResult.atSet(s)[i][m].front() = norFreeAlgos[a].atSet(s)[i][r].front();
                        }
*/
            }
        }
    }
///find the extreme performance of all algorithm-------------------------------------------------------------
    cout << "output extreme Performance front..............................................." <<endl;
    ofstream oExtremeFile;
    for(size_t s = 0; s < Setting.numSets(); s += 1)
    {
        const string strSetOutExtremeFPath(strExtremeFPath + "\\\\" + setIinsSetNames[s].name());
        mkdir(strSetOutExtremeFPath.c_str());
        for(int m = matrixFront; m != matrixEnd; m += 1)
        {
            const string strSetOutExtremeFMatrixPath(strSetOutExtremeFPath + "\\\\" + indicator.strMatrix[m]);
            mkdir(strSetOutExtremeFMatrixPath.c_str());
            for(size_t i = 0; i < setIinsSetNames[s].size(); i += 1)
            {
                const string strExtremeFile(strSetOutExtremeFMatrixPath+"\\\\"+setIinsSetNames[s][i]+".txt");
                ResultFileProcess.open(strExtremeFile,oExtremeFile);
                ResultFileProcess.OutFront(extremeResult.atSet(s)[i][m].front(),oExtremeFile);
            }
        }
    }
///output extreme performance--------------------------------------------------------------------------------
    cout << "normalized by the extreme performance of all algorithm, " << endl
         << "then average all performances.........." << endl;
    for(size_t s = 0; s < Setting.numSets(); s += 1)
    {
        for(size_t i = 0; i < setIinsSetNames[s].size(); i += 1)
        {
            CPerformace ExtremePerformance;
            for(int m = matrixFront; m != matrixEnd; m += 1)
            {
                const double extreme = extremeResult.atSet(s)[i][m].Performace().get((matrix)m);
                ExtremePerformance.set((matrix)m,extreme);
            }
            const double maximumHV = setPF.atSet(s)[i].Performace().get(matrix::HV);
            ExtremePerformance.set(matrix::HV,maximumHV);
            for(size_t a = 0; a < Setting.numAlgos(); a += 1)
                norAlgos[a].atSet(s)[i].norAllRunPerforamceBy(ExtremePerformance);
        }
        for(size_t a = 0; a < Setting.numAlgos(); a += 1)
            norAlgos[a].atSet(s).calAvgPerforamce();
    }
///normalized by the extreme performance of all algorithm, then average all performances----------------------------------------------------------------------------------------------
    cout << "output result..............................................." <<endl;
    const string strPerformacePath(Setting.FolderTITTLE()+"\\\\result");
    mkdir(strPerformacePath.c_str());
    ofstream PerfanmaceFile;

    for(size_t s = 0; s < Setting.numSets(); s += 1)
    {
        const string strFilename(strPerformacePath + "\\\\" + setIinsSetNames[s].name() + ".csv");
        ResultFileProcess.open(strFilename,PerfanmaceFile);
        for(int m = matrix::GD; m != matrix::C_Metrix; m += 1)
        {
            PerfanmaceFile << CIndicator::strMatrix.at(m) << ",";
            for(size_t a = 0; a < Setting.numAlgos(); a += 1)
                PerfanmaceFile << norAlgos[a].tittle() << ",";
            PerfanmaceFile << ",";
        }
        PerfanmaceFile << endl;

        for(size_t i = 0; i < setIinsSetNames[s].size(); i += 1)
        {
            for(int m = matrix::GD; m != matrix::C_Metrix; m += 1)
            {
                PerfanmaceFile << setIinsSetNames[s][i]  << ",";
                for(size_t a = 0; a < Setting.numAlgos(); a += 1)
                    PerfanmaceFile << norAlgos[a].atSet(s).Ins(i).avgPerformance().get((matrix)m) << ",";
                PerfanmaceFile << ",";
            }
            PerfanmaceFile << endl;
        }
        PerfanmaceFile.close();
    }

    ResultFileProcess.open(strPerformacePath + "\\\\allPerformance.csv",PerfanmaceFile);
    for(int m = matrix::GD; m != matrix::C_Metrix; m += 1)
    {
        PerfanmaceFile << CIndicator::strMatrix.at(m) <<",";
        for(size_t a = 0; a < Setting.numAlgos(); a += 1)
            PerfanmaceFile << norAlgos[a].tittle() <<",";
        PerfanmaceFile << endl;

        for(size_t s = 0; s < Setting.numSets(); s += 1)
        {
            PerfanmaceFile << setIinsSetNames[s].name() <<",";
            for(size_t a = 0; a < Setting.numAlgos(); a += 1)
                PerfanmaceFile << norAlgos[a].atSet(s).avgPerformance().get((matrix)m) << ",";
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
                norAlgos[a].atSet(s)[i].calRunPF(Problem);

        //c matrix
        for(size_t a = 0; a < Setting.numAlgos(); a += 1)
            for(size_t i = 0; i < setIinsSetNames[s].size(); i += 1)
                for(size_t compare = 0; compare < Setting.numAlgos(); compare += 1)
                {
                    if(a == compare)
                        insAlgoCmatrix[s][i][a][compare] = -1;
                    else
                        insAlgoCmatrix[s][i][a][compare] = indicator.C_Metrix(Problem ,norAlgos[a].atSet(s)[i].front(),
                                                           norAlgos[compare].atSet(s)[i].front());
                }
        //c matrix----------------------------------------------------------------------------------------------
    }

    cout << "output C matrix..............................................." <<endl;
    const string strCMatrixPath(strPerformacePath+"\\\\C_Matrix");
    mkdir(strCMatrixPath.c_str());

    ofstream CMatrixFile;
    for(size_t s = 0; s < Setting.numSets(); s += 1)
    {
        const string strFilename(strCMatrixPath + "\\\\" + setIinsSetNames[s].name() + ".csv");
        ResultFileProcess.open(strFilename,CMatrixFile);
        for(size_t a = 0; a < Setting.numAlgos(); a += 1)
        {
            CMatrixFile << norAlgos[a].tittle() << ",";
            for(size_t compare = 0; compare < Setting.numAlgos(); compare += 1)
                CMatrixFile << norAlgos[compare].tittle() << ",";
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
    bool isWithBack = true;
    if(Setting.runBegin() ==0 && Setting.runEnd() == 0 && Setting.insBack() == "NONE")
        isWithBack = false;
    if(Problem.numObj() <= 3)
    {
        const string strPlotPath(Setting.FolderTITTLE()+"\\\\plot");
        mkdir(strPlotPath.c_str());

        cout << "plot begin.";
        Gnuplot gplot;
        gplot("set terminal png");
        for(size_t a = 0; a < Setting.numAlgos(); a += 1)
        {
            const string strnorAlgosetPlotPath(strPlotPath + "\\\\" + norAlgos[a].tittle());
            mkdir(strnorAlgosetPlotPath.c_str());
            for(size_t s = 0; s < Setting.numSets(); s += 1)
            {
                const string strSetPlotPath(strnorAlgosetPlotPath + "\\\\" + setIinsSetNames[s].name());
                mkdir(strSetPlotPath.c_str());
                for(size_t i = 0; i < setIinsSetNames[s].size(); i += 1)
                {
                    gplot("set output \"" + strSetPlotPath + "\\\\" + setIinsSetNames[s][i] + ".png\"");
//                    gplot.set_title(setIinsSetNames[s][i]);
                    for(int obj = 0; obj < (int)Problem.numObj(); obj += 1)
                        gplot.set_axis((dimension)obj, Problem.objName(obj));

                    ostringstream  txt;
                    const string SetInsNmae(setIinsSetNames[s].name() + "\\\\"+
                                            setIinsSetNames[s][i]);
                    txt << " \"" << setPF.absPath() << "\\\\"
                        << SetInsNmae << ".txt \" pt 2"
                        << " title \""<< setPF.tittle() <<"\"";
                    if(!isWithBack)
                        txt << " ,\"" << norAlgos[a].absPath() << "\\\\"
                            << SetInsNmae << ".txt \" pt 4"
                            << " title \""<< norAlgos[a].tittle() <<"\"";
                    else
                        for(size_t r = Setting.runBegin(); r < Setting.runEnd(); r += 1)
                        {
                            txt << ",\"" << norAlgos[a].absPath() << "\\\\"
                                << SetInsNmae << Setting.insBack() << r << ".txt\" pt " << 4+2*r
                                << " title \""<< norAlgos[a].tittle() << Setting.insBack() << r << "\"";
                        }
                    gplot.plot(txt.str());
                }
            }
        }
///plot all ins PF
        ofstream outNorFreeAlgosInsPF;
        const string strALLAlgoSetPlotPath(strPlotPath + "\\\\algoInsPF");
        mkdir(strALLAlgoSetPlotPath.c_str());
        const string strALLAlgoSetPlotTxtPath(strALLAlgoSetPlotPath + "\\\\algoInsPF_txt");
        mkdir(strALLAlgoSetPlotTxtPath.c_str());
        for(size_t a = 0; a < Setting.numAlgos(); a += 1)
        {
            const string strAlgoPath(strALLAlgoSetPlotTxtPath + "\\\\" + norAlgos[a].tittle());
            mkdir(strAlgoPath.c_str());
            for(size_t s = 0; s < Setting.numSets(); s += 1)
            {
                const string strSetPath(strAlgoPath + "\\\\" + setIinsSetNames[s].name());
                mkdir(strSetPath.c_str());
                for(size_t i = 0; i < setIinsSetNames[s].size(); i += 1)
                {
                    ResultFileProcess.open(strSetPath+"\\\\"+setIinsSetNames[s][i]+".txt",outNorFreeAlgosInsPF);
                    ResultFileProcess.OutFront(norFreeAlgos[a].atSet(s)[i].front(),outNorFreeAlgosInsPF);
                }
            }
        }

        for(size_t s = 0; s < Setting.numSets(); s += 1)
        {
            const string strSetPlotPath(strALLAlgoSetPlotPath + "\\\\" + setIinsSetNames[s].name());
            mkdir(strSetPlotPath.c_str());
            for(size_t i = 0; i < setIinsSetNames[s].size(); i += 1)
            {
                gplot("set output \"" + strSetPlotPath + "\\\\" + setIinsSetNames[s][i] + ".png\"");
                for(int obj = 0; obj < (int)Problem.numObj(); obj += 1)
                    gplot.set_axis((dimension)obj, Problem.objName(obj));
                ostringstream  txt;
                const string SetInsNmae(setIinsSetNames[s].name() + "\\\\"+
                                        setIinsSetNames[s][i]);
                txt << " \"" << setPF.absPath() << "\\\\"
                    << SetInsNmae << ".txt \"  pt 2"
                    << " title \""<< setPF.tittle() <<"\"";
                for(size_t a = 0; a < Setting.numAlgos(); a += 1)
                {
                    txt << ",\"" << strALLAlgoSetPlotTxtPath << "\\\\" << norAlgos[a].tittle() << "\\\\"
                        << SetInsNmae << ".txt\"  pt " << 4+2*a
//                        << SetInsNmae << ".txt\" w lp  lw 2  pt " << 4+2*a
                        << " title \""<< norAlgos[a].tittle() << "\"";
                }
                gplot.plot(txt.str());
            }
        }

        gplot("exit");
    }
///output result----------------------------------------------------------------------------------------------


}

