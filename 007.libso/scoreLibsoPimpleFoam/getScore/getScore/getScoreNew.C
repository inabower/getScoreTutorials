#include "getScore.H"

Foam::autoPtr<Foam::getScore>
Foam::getScore::New
(
    const fvMesh& mesh
)
{
    IOdictionary dict
    (
        IOobject
        (
            "scoreDict",
            mesh.time().constant(),
            mesh,
            IOobject::MUST_READ_IF_MODIFIED,
            IOobject::AUTO_WRITE
        )
    );

    const word scoreType(dict.get<word>("name"));

    Info<< "Selecting scoring method" << scoreType << endl;

    auto cstrIter = scoreConstructorTablePtr_->cfind(scoreType);

    if (!cstrIter.found())
    {
        FatalIOErrorInLookup
        (
            dict,
            "getScore",
            scoreType,
            *scoreConstructorTablePtr_
        ) << exit(FatalIOError);
    }

    return autoPtr<Foam::getScore>(cstrIter()(mesh, dict));
}

Foam::autoPtr<Foam::getScore>
Foam::getScore::New
(
    const fvMesh& mesh,
    const IOdictionary& dict
)
{
    const word scoreType(dict.get<word>("type"));

    Info<< "Selecting scoring method" << scoreType << endl;

    auto cstrIter = scoreConstructorTablePtr_->cfind(scoreType);

    if (!cstrIter.found())
    {
        FatalIOErrorInLookup
        (
            dict,
            "getScore",
            scoreType,
            *scoreConstructorTablePtr_
        ) << exit(FatalIOError);
    }

    return autoPtr<Foam::getScore>(cstrIter()(mesh, dict));
}