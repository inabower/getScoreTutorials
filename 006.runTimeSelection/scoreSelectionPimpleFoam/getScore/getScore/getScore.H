#ifndef getScore_H
#define getScore_H

#include "fvMesh.H"
#include "IOdictionary.H"
#include "autoPtr.H"
#include "runTimeSelectionTables.H"

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
    //- Runtime type information
    TypeName("getScore");
    //- Declare runtime constructor selection table
    declareRunTimeSelectionTable
    (
        autoPtr,
        getScore,
        score,
        (const fvMesh& mesh, const IOdictionary& dict),
        (mesh, dict)
    );
    // Constructors
        // getScore(const fvMesh& mesh);
        getScore(const fvMesh& mesh, const IOdictionary& dict);
    //- Destructor
        virtual ~getScore()
        {}
    //- Selector
    static autoPtr<getScore> New
    (
        const fvMesh& mesh
    );
    static autoPtr<getScore> New
    (
        const fvMesh& mesh, 
        const IOdictionary& dict
    );


    // Member Functions
        virtual void calculate();

        const scalar& value() const
        {
            return score_;
        }
};
}

#endif