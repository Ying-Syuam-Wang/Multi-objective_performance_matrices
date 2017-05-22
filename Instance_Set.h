#ifndef INSTANCE_SET_H_INCLUDED
#define INSTANCE_SET_H_INCLUDED

#include "algo_Instance_Result.h"

class CInstanceSet
{
public:
    CInstanceSet(){}
    explicit CInstanceSet(size_t s):_insResult(s){}
    void resizeIns(size_t s){_insResult.resize(s);}

    const CInstanceResult & Ins(size_t i)const{return _insResult[i];}
    CInstanceResult & Ins(size_t i)
        { return const_cast<CInstanceResult&>(static_cast<const CInstanceSet&>(*this).Ins(i));}
    const CInstanceResult & operator[](size_t i)const{return _insResult[i];}
    CInstanceResult& operator[](size_t i)
        { return const_cast<CInstanceResult&>(static_cast<const CInstanceSet&>(*this)[i]);}

    void calAvgPerforamce();

    const CPerformace & avgPerformance()const{return _avgInsPerformance;}
    CPerformace & avgPerformance()
        { return const_cast<CPerformace&>(static_cast<const CInstanceSet&>(*this).avgPerformance());}

    size_t numIns(){return _insResult.size();}
private:
    std::vector<CInstanceResult> _insResult;
    CPerformace _avgInsPerformance;
};

#endif // INSTANCE_SET_H_INCLUDED
