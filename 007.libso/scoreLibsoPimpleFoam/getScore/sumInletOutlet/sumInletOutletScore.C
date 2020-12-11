#include "sumInletOutletScore.H"
#include "surfaceFields.H"
#include "addToRunTimeSelectionTable.H"

namespace Foam
{
    defineTypeNameAndDebug(sumInletOutletScore, 0);
    addToRunTimeSelectionTable
    (
        getScore,
        sumInletOutletScore,
        score
    );
}

/*
Foam::sumInletOutletScore::sumInletOutletScore
(
    const fvMesh& mesh
)
:
    getScore(mesh)
{
    Info << "Set sumInletOutletScore constructor from only mesh" << endl;
}
*/

Foam::sumInletOutletScore::sumInletOutletScore
(
    const fvMesh& mesh,
    const IOdictionary& dict
)
:
    getScore(mesh, dict)
{
    Info << "Set sumInletOutletScore constructor from mesh and dictionary" << endl;
}

void Foam::sumInletOutletScore::calculate()
{

    Info << "Running inheritance function with dictionary" << endl;

    const wordList targetPatches = get<wordList>("targetPatches");

    const surfaceScalarField& phi = mesh_.lookupObject<surfaceScalarField>("phi");
    score_ = 0.0;

    forAll(phi.boundaryField(), patchI)
    {
        const fvPatch& patch = phi.boundaryField()[patchI].patch();
        const scalarField& pphi =  phi.boundaryField()[patchI];
        bool isTargetPatch = false;
        forAll(targetPatches, i)
        {
            if (patch.name()==targetPatches[i]) isTargetPatch = true;
        }
        if (!isTargetPatch) continue;
        Info << "    sum(" << patch.name() << ") of phi = " << gSum(pphi) << endl;
        score_ += gSum(pphi);
    }

    const word message = get<word>("message");
    Info << "message in scoreDict is " << message << endl;
    // Info << nl << "score: " << mesh_.time().value() << tab << score_ << nl << endl;
}
