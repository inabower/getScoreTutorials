#ifndef getScore_H
#define getScore_H

#include "fvMesh.H"
#include "IOdictionary.H"

namespace Foam
{
class getScore
:
    public IOdictionary
{
protected:
    // Protected data
        const fvMesh& mesh_;
        scalar score_;
public:
    // Constructors
        getScore(const fvMesh& mesh);
        getScore(const fvMesh& mesh, const IOdictionary& dict);
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