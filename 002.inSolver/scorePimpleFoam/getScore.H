{

    Info << "Running code execute" << endl;

    scalar score = 0.0;

    forAll(phi.boundaryField(), patchI)
    {
        const fvPatch& patch = phi.boundaryField()[patchI].patch();
        const scalarField& pphi =  phi.boundaryField()[patchI];
        if (!(patch.name()=="inlet" || patch.name()=="outlet1" || patch.name()=="outlet2")) continue;
        Info << "    sum(" << patch.name() << ") of phi = " << gSum(pphi) << endl;
        score += gSum(pphi);
    }
    Info << nl << "score: " << runTime.value() << tab << score << nl << endl;
}
