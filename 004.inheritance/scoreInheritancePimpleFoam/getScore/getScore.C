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

    Info << "Running calculate function" << endl;

    const surfaceScalarField& phi = mesh_.lookupObject<surfaceScalarField>("phi");
    score_ = 0.0;

    forAll(phi.boundaryField(), patchI)
    {
        const fvPatch& patch = phi.boundaryField()[patchI].patch();
        const scalarField& pphi =  phi.boundaryField()[patchI];
        if (!(patch.name()=="inlet" || patch.name()=="outlet1" || patch.name()=="outlet2")) continue;
        Info << "    sum(" << patch.name() << ") of phi = " << gSum(pphi) << endl;
        score_ += gSum(pphi);
    }
    // Info << nl << "score: " << mesh_.time().value() << tab << score_ << nl << endl;
}
