
etat9.

etat7([andre]):- etat9.

etat8([bernard]):-etat9.

etat8([babar]):- etat9.

etat8([caroline]):- etat9.

etat8([l|L]):- etat5(L).

etat8([la|L]):- etat10(L).

etat6([du|L]):- etat4(L).

etat6([d|L]):- etat7(L).

etat6([de|L]):- etat8(L).

etat4([neveu|L]):- etat6(L).

etat4([frere|L]):- etat6(L).

etat5([oncle|L]):- etat6(L).

etat5([ancetre|L]):- etat6(L).

etat10([mere|L]):- etat6(L).

etat10([soeur|L]):- etat6(L).

etat3([le|L]):- etat4(L).

etat3([l|L]):- etat5(L).

etat3([la|L]):- etat10(L).

etat1([qui,est|L]):- etat3(L).

analyse(L) :- etat1(L).

