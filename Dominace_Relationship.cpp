#include "Dominace_Relationship.h"
#include "Front.h"
#include "Solution.h"
#include "Setting_Problem.h"

bool CDominace::operator()(const CProblem &Problem,const CSolution &winner,const CSolution &loser)
{
    for(std::size_t o = 0; o < Problem.numObj(); o += 1)
        if(!Problem.obj(o)->isBetter(winner[o],loser[o]))
            return false;
    return (!isEqual(Problem,winner,loser))?true:false;
}
bool CDominace::isEqual(const CProblem &Problem,const CSolution &winner,const CSolution &loser)
{
    for(std::size_t o = 0; o < Problem.numObj(); o += 1)
        if(winner[o] != loser[o])
            return false;
    return true;
}

bool CDominace::UpdatePF(const CProblem &Problem,const CFront & newFront,CFront & PF)
{
    if(PF.size() == 0)
    {
        PF = newFront;
        return true;
    }

    std::vector<bool> isIntoPF(newFront.size());
    for(std::size_t i = 0; i < newFront.size(); i += 1)
    {
        for(std::size_t j = 0; j < PF.size(); j += 1)
        {
            if((*this)(Problem,newFront[i],PF[j]))
            {
                PF.erase(PF.begin()+j);
                j -= 1;
                isIntoPF[i] = true;
            }
        }

        if(!isIntoPF[i])
        {
            std::size_t count = 0;
            for(std::size_t j = 0; j < PF.size(); j += 1)
                if(!this->isEqual(Problem,PF[j],newFront[i]) &&
                   !(*this)(Problem,PF[j],newFront[i]))
                    count += 1;
                else
                    break;

            if(count == PF.size())
                isIntoPF[i] = true;
        }
    }

    bool isUpdate = false;
    for(std::size_t i = 0; i < newFront.size(); i += 1)
        if(isIntoPF[i] == true)
        {
            PF.push_back(newFront[i]);
            isUpdate = false;
        }
    return isUpdate;
}
