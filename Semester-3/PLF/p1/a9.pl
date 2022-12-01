%addPos(L-list, E-integer, N-integer, R-result List, NL-neighbours List)
%flow model (i,i,i,o,o)

addPos([],E,1,[E],[]):- !.
addPos([],_,N,[],[]):- 
    N=\=1,
    !.

addPos([H|T], E, N, [HR,H|T],[H]):-
    N =:= 1,
    !,
    HR is E.

addPos([H|T], E, N, [H|TR],[H|NL]):-
    N =:= 2, 
    !,
    N1 is N-1,
    addPos(T, E, N1, TR, NL).

addPos([H|T], E, N, [H|TR],NL):-
    N =\= 1,
    !,
	N1 is N-1,
    addPos(T, E, N1, TR, NL).

test_addPos():-
    addPos([1, 2, 3],5,1,[5, 1, 2, 3],[1]),
    addPos([1,2,3],5,2,[1, 5, 2, 3], [1,2]),
    addPos([1,2,3],5,3,[1, 2, 5, 3], [2,3]),
    addPos([1,2,3],5,4,[1, 2, 3, 5],[3]),
    addPos([1,2,3],5,5, [1,2,3], []),
    addPos([1,2,4,6,2],11,5,[1, 2, 4, 6, 11, 2], [6, 2]),
    addPos([1,2,4,6,2],11,9,[1,2,4,6,2], []),
    addPos([56,8,84,6],1,1,[1, 56, 8, 84, 6], [56]),
    addPos([56,8,84,6],1,2,[56, 1, 8, 84, 6], [56, 8]),
    addPos([56,8,84,6],1,-4,[56, 8, 84, 6], []).
