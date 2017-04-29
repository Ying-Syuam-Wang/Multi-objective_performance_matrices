#include "Front.h"
#include <algorithm>


void CFront::sortByObj(const std::size_t obj)
{
    sort(_Front.begin(),_Front.end(),doCompare(*this,obj-1));
}
const CFront::SobjInfo & CFront::objExterms(const std::size_t o)
{
    if(!_isUpdateBojInfo)
    {
        for(CSolution sol : _Front)
            updateObjExterms(sol);
        for(std::size_t i = 0; i < _objInfos.size(); i += 1)
            _objInfos[i]._range = _objInfos[i]._MAX - _objInfos[i]._min;
    }

    return _objInfos[o];
}
void CFront::nomalizeBy(const std::vector<SobjInfo> & objInfo)
{
    for(std::size_t f = 0; f < _Front.size(); f += 1)
        for(std::size_t o = 0; o < objInfo.size(); o += 1)
            _Front[f][o] = (_Front[f][o] - objInfo[o].min()) / objInfo[o].range();
}
void CFront::updateObjExterms(const CSolution &sol)
{
    for(std::size_t i = 0; i < sol.numObj(); i += 1)
    {
        if(_objInfos[i]._min > sol[i])
            _objInfos[i]._min = sol[i];
        else if(_objInfos[i]._MAX < sol[i])
            _objInfos[i]._MAX = sol[i];
    }
}
void CFront::push_back(const CSolution &sol)
{
    if(_Front.empty())
    {
        _objInfos.resize(sol.numObj());
        for(std::size_t i = 0; i < sol.numObj(); i += 1)
        {
            _objInfos[i]._min = sol[i];
            _objInfos[i]._MAX = sol[i];
        }
    }
    else
    {
        for(std::size_t i = 0; i < sol.numObj(); i += 1)
        {
            if(_objInfos[i]._min > sol[i])
            {
                _objInfos[i]._min = sol[i];
                _objInfos[i]._range = _objInfos[i]._MAX - _objInfos[i]._min;
            }
            else if(_objInfos[i]._MAX < sol[i])
            {
                _objInfos[i]._MAX = sol[i];
                _objInfos[i]._range = _objInfos[i]._MAX - _objInfos[i]._min;
            }
        }
    }
    _Front.push_back(sol);
}
