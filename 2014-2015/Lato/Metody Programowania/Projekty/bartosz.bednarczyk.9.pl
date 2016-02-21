%%%%%%%%%%%%%%

% Autor : Bartosz Jan Bednarczyk
% Numer indeksu :  273479
% Zadanie : Skarby (9)

% Ocena : 19/20 - "bo 20 tylko dla Tomka Wierzbickiego"

% Opis zadania :
% Gramy w sapera. Dostajemy planszę MxN z pewnymi cyframi na planszy oznaczającymi liczbę bomb w okolicy.
% Mamy wygenerować możliwe rozstawienia bomb. 

% Algorytm :
% Tworzymy pewną planszę (listę list) z nieukonkretnionymi zmiennymi oraz w pewnych miejscach
% dodajemy punkty z cyferkami. Następnie przeglądamy listę tych punktów i dla każdego z nich
% ustawiamy bomby i sąsiednie pola "nie-bomby" uzupełniamy spacjami.
% Wszystko to trzymamy w akumulatorze, który potem unifikujemy z wyjściową planszą.

% Jak uruchomić program?
% Wywołujemy predykat solve(+M, +N, +ListaTrojek, ?Rozwiazanie).

/*

Podział programu :

1. Predykaty sprawdzające błędy na wejściu

	- sprawdzDane( +(M, N), +ListaTrojek ) - czy dane wejsciowe są poprawne (+,+,+) ?
	- sprawdzListe( +(M, N), +ListaTrojek) - sprawdzanie listy trojek (czy trojki są poprawne)

2. Predykaty pomocnicze (dla czytelności i ułatwienia pracy)

	- element( +(I, J), +Plansza, ?E ) - (I,J)-tym elementem na Planszy jest E
	- sublist( ?L1, +L2 ) - sprawdza czy lista L1 jest podlistą listy L2 (było na ćw) 

3. Predykaty do tworzenia planszy i jej modyfikacji

	- stworzPlansze( +(M, N), +ListaTrojek, ?Plansza ) - tworzenie planszy MxN z trójkami
	- ustawNaWartosc(+Punkty, +V, ?Plansza ) - ustawia nieukonkretnione punkty na planszy na V 
	- wyczyscPlansze( +Plansza ) - ustawia nieukonkretnione zmienne na spacje
	- oraz mniejsze predykaty będące częścią większych

4. Predykaty generujące punkty. 

	- generowanie( +(M, N), +(X, Y), +Plansza, -ListaWolnychMiejsc, -IleWolnych, -IleBomb).
		* oblicza listę wolnych miejsc wokół punktu (X,Y), ich liczbę
		  oraz liczbę bomb  sąsiedztwie.

	- oblicz(+Lista, -IleWolnych, -IleBomb, -ListaWolnychMiejsc)
		* przeglądając listę oblicza wymienione rzeczy.

5. Główne predykaty do rozwiązywania zadania

	- solve(+M, +N, +ListaTrojek, ?Rozwiazanie) - rozwiązuje zadanie Skarby i unifikuje je z Rozwiązaniem
		* sa dwie wersje - jedna dla +Rozwiazanie, a inna dla -Rozwiazanie

6. Testy. 

*/

%%%%%%%%%%%%%%% 1. Predykaty sprawdzające błędy na wejściu. 

% Predykat sprawdza czy podane dane są poprawne (+,+,+)

sprawdzDane( (M, N), ListaTrojek ) :- 
	N >= 1, 16 >= N,
	M >= 1, 16 >= M,
	length(ListaTrojek, L),
	L >= 0, L =< M * N,
	sprawdzListe((M,N), ListaTrojek).

% Sprawdzanie czy dana lista +L zawiera poprawne trójki na planszy +(M,N).

sprawdzListe(_,[]).

sprawdzListe((M,N), [(X,Y,Z)|ResztaTrojek]):-
	X >= 1, M >= X,
	Y >= 1, N >= Y,
	Z >= 1, 8 >= Z,
	sprawdzListe((M,N), ResztaTrojek).

%%%%%%%%%%%%%%% 2. Predykaty pomocnicze (dla czytelności i ułatwienia pracy)

% ?E jest (I,J)-tym elementem listy list L
% nth1(A, B, C) bierze A-ty element z B i zwraca jako C.

element( (I, J), L, E) :-  
	nth1(I, L, L1),
	nth1(J, L1, E).

% Czy ?(A,B) jest sąsiadem +(X,Y) na planszy o wymiarach +(M,N)?
% Działanie raczej oczywiste. Punkt nie jest swoim sąsiadem!

sasiad( (M,N), (X,Y), (A,B) ) :-
        Dir = [-1, 0, 1],
        member(I, Dir), member(J, Dir),
        A is I + X, B is J + Y,
        (X,Y) \= (A,B),
	A >= 1, M >= A,
	B >= 1, N >= B.

% sublist(?L1, +L2) - czy L1 jest podlistą L2 - było na ćw.

sublist( [], _ ).
sublist( [X|XS], [X|XSS] ) :- sublist( XS, XSS ).
sublist( [X|XS], [_|XSS] ) :- sublist( [X|XS], XSS ).

%%%%%%%%%%%%%%% 3. Predykaty do tworzenia planszy i jej modyfikacji

% Tworzenie planszy o rozmiarze MxN (niektóre pola nieukonkretnione, inne z numerkami)
% Pobieramy wymiary planszy +(M,N), +Listę Trojek i zwracamy ?Plansze.
% Działa to tak, że generujemy sobie nieukonkretnioną listę o rozmiarze M,
% a następnie dla każdego jej elementu tworzymy nową listę o rozmiarze N.
% Następnie ustawiamy pola z cyframi w odpowiednie miejsca.

stworzPlansze( (M, N), ListaTrojek, Plansza ) :-
	length(Plansza, M),
	stworzPodlisty(Plansza, N),
	ustawPunkty(Plansza, ListaTrojek).

stworzPodlisty([], _).
stworzPodlisty([H|T], N) :- 
	length(H, N),
	stworzPodlisty(T, N).

% Predykat ustawia trojki z tresci zadania na naszej planszy.

ustawPunkty(_, []).
ustawPunkty(Plansza, [(X,Y, Val)|Reszta]) :-
	element( (X, Y), Plansza, Val),
	ustawPunkty(Plansza, Reszta).

% ustawNaWartosc( +Punkty, +Wartosc, ?Plansza )
% Ukonkretnia każdy punkt z listy Punkty z podanym tekstem Wartosc.
% Jeśli dany punkty jest już ukonkretniony to go opuszcza. 

ustawNaWartosc([], _, _).

ustawNaWartosc( [(I, J) | T], V, Plansza ) :-
	element( (I, J), Plansza, E), 
	var(E), E = V, !,
	ustawNaWartosc(T, V, Plansza).

ustawNaWartosc( [ (I,J)|T], V, Plansza ) :-
	element( (I,J), Plansza, E), nonvar(E),
	ustawNaWartosc(T, V, Plansza).

% Poniższy przedykat działa następująco. Podajemy Planszę, a on przechodzi
% przez jej elementy i nieukonkretnione zmienne ustawia na spacje.
% Potrzebne to na sam koniec, bo niektóre pola na planszy mogłyby nie
% zostać odwiedzone. Predykat działa w trybie +.

wyczyscPlansze([]).
wyczyscPlansze([Lista|ResztaList]) :- wyczyscPodliste(Lista), wyczyscPlansze(ResztaList).

wyczyscPodliste([]).

wyczyscPodliste([H|T]) :-
	var(H), H = ' ', !, wyczyscPodliste(T).

wyczyscPodliste([H|T]) :-
	nonvar(H), wyczyscPodliste(T).

%%%%%%%%%%%%%%% 4. Predykaty generujące punkty.

% generowanie( +wymiary, +punkt, +plansza, -, -, - ).
% Za pomocą tego predykatu obliczamy listę wolnych miejsc wokół pewnego punktu (X,Y) na
% planszy o wymiarach M x N (tj ile nieukonkretnionych zmiennych jest wokół punktu i
% zwracamy listę ich współrzędnych). Ponadto oblicza również długość wspomnianej listy
% oraz informację o liczbę bomb w okolicy.
% Dlaczego jest tego tyle naraz?
% Poniważ predykat findall nie jest zbyt szybki i nie opłaca się używać go dwukrotnie
% go generowania listy bomb oraz listy wolnych miejsc (wzrost wydajność aż o 246% !!!).

generowanie( (M, N), (X, Y), Plansza, ListaWolnychMiejsc, IleWolnych, IleBomb) :-

	findall( (XX,YY,E), (
		sasiad( (M,N), (X, Y), (XX, YY) ),
		element( (XX, YY), Plansza, E)
	), Lista ),

	oblicz(Lista, IleWolnych, IleBomb, ListaWolnychMiejsc).

% Oblicz bierze listę trójek typu (X,Y,E), gdzie X,Y to wspólrzędne punktu E na planszy, a
% E to sam punkt. Następnie przechodzimy tą listę i utawiamy do odpowiednich miejsc ile
% z tych elementów to bomby, a ile nieukokretnione zmienne (w przypadku nieukonkretnionych
% zmiennych dodatkowo dodajemy parę (X,Y) do listy wolnych miejsc).

oblicz(Lista, IleWolnych, IleBomb, ListaWolnych) :-
	oblicz(Lista, 0, IleWolnych, 0, IleBomb, [], ListaWolnych).

% Odpowiednie pozycje to +Lista, Akumulator dla Liczby wolnych miejsc,
% liczba wolnych miejsc, następnie akumulator dla liczby bomb,
% liczba bomb, akumulator dla listy wolnych miejsc i w końcu
% lista wolnych miejsc.

oblicz([], IleWolnych, IleWolnych, IleBomb, IleBomb, LWM, LWM) :- !.

% dla oproszczenia korzystam ze skrótów - AccX - akumulator dla X
% LWM - lista wolnych miejsc, IW - ile wolnych, IB - ileBomb
% Odcięcia poniżej stosuję po to, by Prolog nie nawracał
% i nie sprawdzał niepotrzebnie 3 różnych wersji tego samego predykatu.

% Jeżeli na danej pozycji jest nieukonkretniona zmienna to robimy trzy rzeczy :
% 1) Oblicza Nowy akumulator dla liczby wolnych miejsc, bo właśnie je znaleźliśmy :)
% 2) Dodaje punkt (X,Y) do do akumulatora listy wolnych miejsc.
% 3) Przechodzi do kolejnego elementu z listy.

oblicz( [(X,Y,H)|T], AccIW, IW, AccIB, IB, AccLWM, LWM) :-
	var(H), !, NowyAccIW is AccIW + 1,
	oblicz( T, NowyAccIW, IW, AccIB, IB, [(X,Y)|AccLWM], LWM).

% Jeżeli na polu jest bomba (czyli *) to dodajemy wartość 1 do
% akumulatora liczby bomb i przechodzimy do kolejnego elementu
% listy ( z nowym akumulatorem ).

oblicz( [(_,_,H)|T], AccIW, IW, AccIB, IB, AccLWM, LWM) :-
	H = '*', !, NowyAccIB is AccIB +1,
	oblicz(T, AccIW, IW, NowyAccIB, IB, AccLWM, LWM).

% Jeżeli na danym polu jest cyfra to przechodzimy po prostu dalej.

oblicz([_|T], AccIW, IW, AccIB, IB, AccLWM, LWM) :-
	oblicz(T, AccIW, IW, AccIB, IB, AccLWM, LWM).

%%%%%%%%%%%%%%% 5. Główne predykaty do rozwiązywania zadania.

% Predykat solve(+,+,+,?) rozwiązuje zadanie Skarby następująco :
% a) sprawdza czy dane na wejściu są poprawne
% b) tworzy planszę jako listę list
% c) ustawia bomby na planszy w Acc
% d) unifikuje Acc z Rozwiazaniem (pomocne w trybie sprawdzania)

solve( M, N, ListaTrojek, Rozwiazanie ) :-
	sprawdzDane( (M,N), ListaTrojek ),
	stworzPlansze( (M, N), ListaTrojek, Acc ),
	main( (M,N), ListaTrojek, Acc ),
	Acc = Rozwiazanie.

% Przypadek bazowy to kiedy mamy pustą liczbę trójek i pewną planszę.
% Wystarczy wtedy wszystkie nieodwiedzone pola ustawić na spacje.
% "czyścimy ją z nieukonkretnionych zmiennych"

main(_, [], Plansza) :- 
	wyczyscPlansze(Plansza).

main( (M,N), [ (X,Y,Val) | ResztaTrojek ], Plansza ) :-
	
	generowanie((M,N), (X,Y), Plansza, ListaWolnychMiejsc, IleWolnychMiejsc, IleBomb),
	% oblicza trzy ostatnie argumenty predykatu, na potrzeby dalszych operacji	

	Value is (Val - IleBomb),	% Value = ile bomb jeszcze trzeba ustawić
	Value >= 0, Value =< IleWolnychMiejsc,	
	(
		Value is 0 ->
			% jeśli nie mamy ustawiać bomby to zerujemy wolne miejsca i rozważamy kolejny punkt.
			ustawNaWartosc(ListaWolnychMiejsc, ' ', Plansza),
			main( (M, N), ResztaTrojek, Plansza );
		%else
		(
			length(Bomby, Value), sublist(Bomby, ListaWolnychMiejsc),
			% Bomby to podlista listy bomb (jest ich tyle ile trzeba)

			ustawNaWartosc(Bomby, '*', Plansza),
			ustawNaWartosc(ListaWolnychMiejsc, ' ', Plansza),

			% ustawiamy bomby na '*' na Planszy, potem "zerujemy" pozostałe wolne miejsca
			% ... i zabieramy się za kolejną trójkę.

			main( (M,N), ResztaTrojek, Plansza)
		)
	).

% 6. Testy - kolejność musi taka być, bo inaczej są warningi!
% Duże testy, więc będzie działać wolno (ale i tak szybko jak na te testy).

/*
?- check_solution.
START TESTING
simple_test [ok]
simple_test [ok]
student_simple_test [ok]
student_simple_test [ok]
student_simple_test [ok]
student_simple_test [ok]
student_simple_test [ok]
student_simple_test [ok]
student_simple_test [ok]
count_test [ok]
student_count_test [ok]
student_count_test [ok]
student_count_test [ok]
student_count_test [ok]
DONE IN 39.652190000000004s
true.
*/

% Duży test 3 (count):

student_count_test(13,13,[(1,1,1),(1,10,2),(1,12,2),(2,2,2),(2,3,3),(2,6,1),(3,1,1),(3,3,3),(3,6,1),(4,1,1),(4,3,3),(4,5,2),(4,10,1),(4,11,2),(4,12,2),(4,13,2),(5,5,1),(5,7,1),(5,9,1),(5,11,2),(6,1,2),(6,3,2),(6,5,1),(6,6,1),(6,8,1),(6,9,1),(6,10,1),(6,13,3),(7,1,1),(7,2,1),(7,5,1),(7,12,2),(7,13,1),(8,1,1),(8,4,1),(8,5,2),(8,6,3),(8,7,2),(8,11,2),(9,4,3),(9,9,2),(9,10,1),(10,5,3),(10,7,4),(10,9,3),(10,11,2),(10,12,2),(11,1,2),(11,2,5),(11,6,1),(11,9,3),(12,4,3),(12,5,1),(12,6,1),(12,8,2),(12,9,2),(12,10,4),(12,12,5),(13,2,2),(13,13,1)], 6720).

% Małe testy - count

student_count_test(1,1,[(1,1,1)], 0).
student_count_test(3,3,[(2,2,1)], 8).
student_count_test(3,3,[(1,1,1), (3,3,1)], 5).
student_simple_test(1,1,[],[[' ']]).

% Mały 1 :

student_simple_test(3,3,[(3,1,1),(3,3,1)],[
[' ',' ',' '],
[' ',' ',' '],
[ 1 ,'*', 1 ]]).

% Mały 2 :

student_simple_test(3,3,[(1,2,4),(3,2,3)],[
['*', 4 ,'*'],
['*',' ','*'],
['*', 3 ,' ']]).

% Mały 3 :

student_simple_test(5,5,[(2,2,4),(2,4,2),(2,5,1),(4,2,2),(4,4,4),(5,5,1)],[
['*','*',' ',' ',' '],
['*', 4 ,' ', 2 , 1 ],
[' ',' ','*','*',' '],
[' ', 2 ,'*', 4 ,' '],
[' ',' ',' ','*', 1 ]]).

% Mały 4 :

student_simple_test(7,7,[(1,2,2),(1,5,2),(2,4,2),(2,6,1),(3,4,2),(3,6,2),(4,2,3),(4,4,1),(4,7,2),(6,1,3),(6,3,1),(7,6,2)],[
[' ', 2 ,' ','*', 2 ,' ',' '],
['*','*',' ', 2 ,'*', 1 ,' '],
['*',' ',' ', 2 ,' ', 2 ,' '],
[' ', 3 ,'*', 1 ,' ','*', 2 ],
['*',' ',' ',' ',' ',' ','*'],
[ 3 ,' ', 1 ,' ','*',' ',' '],
['*','*',' ',' ','*', 2 ,' ']]).

% Duży 1 :

student_simple_test(10, 10, [ (1,5,1), (1,8,1), (2,3,1), (2,6,2), (2,10,1), (3,1,1), (3,5,1), (3,8,3),
(4,3,3), (4,6,3), (4,7,2), (4,10,3) ,(5,1,1), (5,5,3), (5,8,1),
(6,3,4), (6,6,1), (6,10,3),
(7,1,1), (7,4,1), (7,5,1), (7,8,1),
(8,3,1), (8,6,2), (8,10,2),
(9,1,1), (9,5,2), (9,8,1),
(10,3,2), (10,6,2), (10,10,1) ],
[[' ',' ',' ',' ',1,'*',' ',1,' ',' '],['*',' ',1,' ',' ',2,' ','*',' ',1],[1,' ','*',' ',1,' ','*',3,'*',' '],[' ',' ',3,' ','*',3,2,' ',' ',3],[1,'*','*',' ',3,'*',' ',1,'*','*'],[' ',' ',4,'*',' ',1,' ',' ',' ',3],[1,'*',' ',1,1,' ',' ',1,'*',' '],[' ',' ',1,' ',' ',2,' ',' ',' ',2],[1,' ',' ',' ',2,'*','*',1,' ','*'],[' ','*',2,'*',' ',2,' ',' ',' ',1]]).

% Duży 2 :

student_simple_test(13,13,[(1,1,1),(1,10,2),(1,12,2),(2,2,2),(2,3,3),(2,6,1),(3,1,1),(3,3,3),(3,6,1),(4,1,1),(4,3,3),(4,5,2),(4,10,1),(4,11,2),(4,12,2),(4,13,2),(5,5,1),(5,7,1),(5,9,1),(5,11,2),(6,1,2),(6,3,2),(6,5,1),(6,6,1),(6,8,1),(6,9,1),(6,10,1),(6,13,3),(7,1,1),(7,2,1),(7,5,1),(7,12,2),(7,13,1),(8,1,1),(8,4,1),(8,5,2),(8,6,3),(8,7,2),(8,11,2),(9,4,3),(9,9,2),(9,10,1),(10,5,3),(10,7,4),(10,9,3),(10,11,2),(10,12,2),(11,1,2),(11,2,5),(11,6,1),(11,9,3),(12,4,3),(12,5,1),(12,6,1),(12,8,2),(12,9,2),(12,10,4),(12,12,5),(13,2,2),(13,13,1)],[
[ 1 ,' ','*',' ',' ',' ',' ',' ',' ', 2 ,'*', 2 ,' '],
['*', 2 , 3 ,'*','*', 1 ,' ',' ',' ','*',' ',' ','*'],
[ 1 ,' ', 3 ,'*',' ', 1 ,' ',' ',' ','*',' ',' ',' '],
[ 1 ,' ', 3 ,'*', 2 ,' ',' ',' ',' ', 1 , 2 , 2 , 2 ],
['*',' ','*',' ', 1 ,' ', 1 ,'*', 1 ,' ', 2 ,'*','*'],
[ 2 ,'*', 2 ,' ', 1 , 1 ,' ', 1 , 1 , 1 ,' ','*', 3 ],
[ 1 , 1 ,' ',' ', 1 ,'*',' ',' ',' ',' ','*', 2 , 1 ],
[ 1 ,' ',' ', 1 , 2 , 3 , 2 ,' ',' ','*', 2 ,' ',' '],
[' ','*',' ', 3 ,'*',' ','*',' ', 2 , 1 ,' ',' ',' '],
[' ','*','*','*', 3 ,' ', 4 ,'*', 3 ,' ', 2 , 2 ,' '],
[ 2 , 5 ,'*','*',' ', 1 ,'*','*', 3 ,'*','*',' ','*'],
['*',' ','*', 3 , 1 , 1 ,' ', 2 , 2 , 4 ,'*', 5 ,' '],
[' ', 2 ,' ',' ',' ',' ',' ',' ',' ',' ','*','*', 1 ]]).
