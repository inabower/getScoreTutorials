#include "getScore.H"
#include "surfaceFields.H"


Foam::getScore::getScore
(
    const fvMesh& mesh
)
:
    IOdictionary
    (
        IOobject
        (
            "scoreDict",
            mesh.time().constant(),
            mesh,
            IOobject::MUST_READ_IF_MODIFIED,
            IOobject::AUTO_WRITE
        )
    ),
    mesh_(mesh)
{
    Info << "Set getScore constructor from only mesh" << endl;
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
    Info << "Set getScore constructor from mesh and dict" << endl;
}

void Foam::getScore::calculate()
{
    Info << "Here will be overwritten by inheritance function" << endl;
}
