#include "getScore.H"
#include "surfaceFields.H"

Foam::getScore::getScore
(
    const fvMesh& mesh
)
:
    mesh_(mesh)
{
    Info << "Set constructor" << endl;
}

void Foam::getScore::calculate()
{
    Info << "Here will be overwritten by inheritance function" << endl;
}
