#include "codedScore.H"
#include "addToRunTimeSelectionTable.H"
#include "dynamicCode.H"
#include "dynamicCodeContext.H"

namespace Foam
{
    defineTypeNameAndDebug(codedScore, 0);
    addToRunTimeSelectionTable
    (
        getScore,
        codedScore,
        score
    );
}

void Foam::codedScore::prepare
(
    dynamicCode& dynCode,
    const dynamicCodeContext& context
) const
{
    // Set additional rewrite rules
    dynCode.setFilterVariable("typeName", name_);
    //dynCode.removeFilterVariable("code");
    dynCode.setFilterVariable("codeCalculate", codeCalculate_);

    // compile filtered C template
    dynCode.addCompileFile("codedScoreTemplate.C");
    // copy filtered H template
    dynCode.addCopyFile("codedScoreTemplate.H");
    
    // define Make/options
    dynCode.setMakeOptions
    (
        "EXE_INC = -g \\\n"
        "-I$(LIB_SRC)/finiteVolume/lnInclude \\\n"
        "-I$(LIB_SRC)/fvOptions/lnInclude \\\n"
        "-I$(LIB_SRC)/meshTools/lnInclude \\\n"
        "-I$(LIB_SRC)/sampling/lnInclude \\\n"
        "-I"+word(getScoreLibDir_)+"/lnInclude \\\n"
      + context.options()
      + "\n\nLIB_LIBS = \\\n"
        "    -lfvOptions \\\n"
        "    -lmeshTools \\\n"
        "    -lsampling \\\n"
        "    -lfiniteVolume \\\n"
        "    -L$(FOAM_USER_LIBBIN) \\\n"
        "    -lgetScore \\\n"
      + context.libs()
    );
}

Foam::dlLibraryTable& Foam::codedScore::libs() const
{
    return const_cast<Time&>(mesh_.time()).libs();
}

Foam::string Foam::codedScore::description() const
{
    return "codedScore::" + name_;
}

void Foam::codedScore::clearRedirect() const
{
    redirectScorePtr_.clear();
}

const Foam::dictionary& Foam::codedScore::codeDict() const
{
    return *this;
}

Foam::codedScore::codedScore
(
    const fvMesh& mesh,
    const IOdictionary& dict
)
:
    getScore(mesh, dict),
    name_(dict.get<word>("name")),
    getScoreLibDir_(dict.get<fileName>("getScoreLibDir"))
{
    Info << "Set codedScore constructor from mesh and dictionary" << endl;
    Foam::codedScore::readCode(dict);
}

Foam::getScore& Foam::codedScore::redirectScore() const
{
    if (!redirectScorePtr_.valid())
    {
        IOdictionary constructDict
        (
            IOobject
            (
                "scoreTmpDict",
                mesh_.time().constant(),
                mesh_
            )
        );
        constructDict.set("type", name_);

        redirectScorePtr_ = getScore::New
        (
            mesh_,
            constructDict
        );
    }
    return *redirectScorePtr_;
}

void Foam::codedScore::calculate()
{
    Info << "Running coded calculate function" << endl;
    
    updateLibrary(name_);
    Foam::getScore& tmp = redirectScore();
    tmp.calculate();
    score_ = tmp.value();
}
