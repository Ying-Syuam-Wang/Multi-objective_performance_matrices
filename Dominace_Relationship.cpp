#include "Dominace_Relationship.h"

#include "Solution.h"
#include "Setting_Problem.h"

bool CDominace::operator()(const CProblem &Problem,const CSolution &winner,const CSolution &loser)
{
    std::size_t equalCounter = 0;
    for(std::size_t o = 0; o < Problem.numObj(); o += 1)
    {
        if(!Problem.obj(o)->isBetter(winner[o],loser[o]))
            return false;
        else if(Problem.obj(o)->isEqual(winner[o],loser[o]))
            equalCounter += 1;
    }
    return (equalCounter != Problem.numObj())?true:false;
}
