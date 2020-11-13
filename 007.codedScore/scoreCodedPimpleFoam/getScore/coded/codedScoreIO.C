#include "codedScore.H"

bool Foam::codedScore::readCode(const dictionary& dict)
{
    dict.readCompat<word>("name", {{"redirectType", 1706}}, name_);

    // Code chunks
    codedBase::append("<codeCalculate>");
    {
        const entry& e =
            dict.lookupEntry("codeCalculate", keyType::LITERAL);

        e.readEntry(codeCalculate_);
        dynamicCodeContext::inplaceExpand(codeCalculate_, dict);

        codedBase::append(codeCalculate_);

        dynamicCodeContext::addLineDirective
        (
            codeCalculate_,
            e.startLineNumber(),
            dict
        );
    }

    return true;
}
