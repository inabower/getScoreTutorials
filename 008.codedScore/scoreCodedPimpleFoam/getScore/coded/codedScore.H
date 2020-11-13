#ifndef codedScore_H
#define codedScore_H

#include "getScore.H"
#include "codedBase.H"

namespace Foam
{
class codedScore
: public getScore,
  protected codedBase
{
protected:
    // Protected data
        word name_;
        string codeCalculate_;

        //- Underlying score
        mutable autoPtr<getScore> redirectScorePtr_;

        //- Adapt the context for the current object
        virtual void prepare(dynamicCode&, const dynamicCodeContext&) const;

        //- Get the loaded dynamic libraries
        dlLibraryTable& libs() const;

        //- Return a description (type + name) for the output
        string description() const;

        //- Clear any redirected objects
        void clearRedirect() const;

        //- Get the dictionary to initialize the codeContext
        const dictionary& codeDict() const;
    
        getScore& redirectScore() const;
public:
    //- Runtime type information
    TypeName("coded");
    // Constructors
        // codedScore(const fvMesh& mesh);
        codedScore(const fvMesh& mesh, const IOdictionary& dict);
    //- Destructor
        ~codedScore()
        {}
    // Member Functions

        virtual void calculate();

        bool readCode(const dictionary& dict);
};
}

#endif