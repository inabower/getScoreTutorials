#include "getScore.H"
#include "surfaceFields.H"

namespace Foam
{
    defineTypeNameAndDebug(getScore, 0);
    defineRunTimeSelectionTable(getScore, score);
}

Foam::getScore::getScore
(
    const fvMesh& mesh,
    const IOdictionary& dict
)
:
    IOdictionary(dict),
    mesh_(mesh)
{
    Info << "Set getScore constructor from only mesh" << endl;
}

void Foam::getScore::calculate()
{
    Info << "Here will be overwritten by inheritance function" << endl;
}
