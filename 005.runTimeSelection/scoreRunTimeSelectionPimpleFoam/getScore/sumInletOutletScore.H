#ifndef sumInletOutletScore_H
#define sumInletOutletScore_H

#include "getScore.H"

namespace Foam
{
class sumInletOutletScore
: public getScore
{
protected:
    // Protected data
public:
    // Constructors
        sumInletOutletScore(const fvMesh& mesh);
    //- Destructor
        ~sumInletOutletScore()
        {}
    // Member Functions
        virtual void calculate();
};
}

#endif