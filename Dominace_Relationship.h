#ifndef DOMINACE_RELATIONSHIP_H_INCLUDED
#define DOMINACE_RELATIONSHIP_H_INCLUDED

class CSolution;
class CProblem;

class CDominace
{
public:
    bool operator()(const CProblem &Problem,const CSolution &winner,const CSolution &loser);
private:
};

#endif // DOMINACE_RELATIONSHIP_H_INCLUDED
