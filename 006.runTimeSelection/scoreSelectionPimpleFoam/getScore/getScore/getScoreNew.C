#include "getScore.H"

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