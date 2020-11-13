/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2019 OpenCFD Ltd.
    Copyright (C) YEAR AUTHOR, AFFILIATION
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Description
    Template for use with dynamic code generation of a source.
    The hook functions take the following arguments:

    \verbatim
    codeCorrect
    (
        GeometricField<Type, fvPatchField, volMesh>& fld
    )

    codeAddSup
    (
        fvMatrix<Type}>& eqn,
        const label fieldi
    )

    codeConstrain
    (
        fvMatrix<Type>& eqn,
        const label fieldi
    )
    \endverbatim

    where :
        fieldi is the index in the fields entry
        eqn is the fvMatrix

    \verbatim
    energySource
    {
        type            scalarCodedSource;

        active          true;
        selectionMode   all;

        scalarCodedSourceCoeffs
        {
            fields  (h);
            name    sourceTime;

            codeInclude
            #{
            #};

            codeCorrect
            #{
                Pout<< "**codeCorrect**" << endl;
            #};

            codeAddSup
            #{
                const Time& time = mesh().time();
                const scalarField& V = mesh_.V();
                scalarField& heSource = eqn.source();
                heSource -= 0.1*sqr(time.value())*V;
            #};

            codeConstrain
            #{
                Pout<< "**codeConstrain**" << endl;
            #};
        }

        sourceTimeCoeffs
        {
            // Dummy entry
        }
    }
    \endverbatim

SourceFiles
    codedScoreTemplate.C

\*---------------------------------------------------------------------------*/

#ifndef codedScoreTemplate_H
#define codedScoreTemplate_H

#include "getScore.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
class ${typeName}CodedScore
:
    public getScore
{
    // Private Member Functions

    //- Report a message with the SHA1sum
    inline static void printMessage(const char* message)
    {
        Info<< message << " sha1: " << SHA1sum << '\n';
    }

public:

    //- SHA1 representation of the code content
    static constexpr const char* const SHA1sum = "${SHA1sum}";

    //- Runtime type information
    TypeName("${typeName}");


    // Constructors
        ${typeName}CodedScore
        (
            const fvMesh& mesh,
            const IOdictionary& dict
        );

    //- Destructor
    virtual ~${typeName}CodedScore();


    // Member Functions
        virtual void calculate();
};
}

#endif
