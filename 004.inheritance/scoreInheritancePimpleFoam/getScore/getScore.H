#ifndef getScore_H
#define getScore_H

#include "fvMesh.H"

namespace Foam
{
class getScore
{
protected:
    // Protected data
        const fvMesh& mesh_;
        scalar score_;
public:
    // Constructors
        getScore(const fvMesh& mesh);
    //- Destructor
        virtual ~getScore()
        {}
    // Member Functions
        virtual void calculate();

        const scalar& value() const
        {
            return score_;
        }
};
}

#endif