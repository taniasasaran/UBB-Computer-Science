%euclid(X-Integer,Y-Integer,R-result Integer)
%flow model (i,i,o)

euclid(X,0,X):-!.
euclid(0,Y,Y):-!.

euclid(X,Y,R):-
    X>Y,
    !,
    X1 is X-Y,
    euclid(X1,Y,R).

euclid(X,Y,R):-
    Y1 is Y-X,
    euclid(X,Y1,R).


%gcd(L-list, RG-result Integer)
%flow model (i,o)

gcd([],0):-!.

gcd([H|T], REZ):-
    gcd(T, RG),
    euclid(H,RG,REZ).

test_gcd():-
  gcd([10,30,15],5),
  gcd([20,50,30],10),
  gcd([5],5),
  gcd([55,66,99],11),
  gcd([0,5,7],1),
  gcd([0,5,10],5).