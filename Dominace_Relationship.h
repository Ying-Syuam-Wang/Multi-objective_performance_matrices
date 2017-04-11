#ifndef DOMINACE_RELATIONSHIP_H_INCLUDED
#define DOMINACE_RELATIONSHIP_H_INCLUDED

#include <vector>
class CSolution;
class CProblem;
class CFront;

class CDominace
{
public:

    bool operator()(const CProblem &Problem,const CSolution &winner,const CSolution &loser);
    bool isEqual(const CProblem &Problem,const CSolution &winner,const CSolution &loser);

    bool UpdatePF(const CProblem &Problem,const CFront & newFront,CFront & PF);
private:
};

#endif // DOMINACE_RELATIONSHIP_H_INCLUDED
