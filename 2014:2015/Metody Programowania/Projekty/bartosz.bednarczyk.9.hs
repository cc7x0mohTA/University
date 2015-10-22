{-# OPTIONS_GHC -O3 -fdicts-cheap -fdicts-strict #-}

-- kompilować ghc bartosz.bednarczyk.9.hs -O3 -fdicts-cheap -fdicts-strict -o main
-- przyśpiesznie ponad 300% !!!

------------------------------------------------------------------------------------------

{-Autor : Bartosz Jan Bednarczyk
% Numer indeksu : 273479
% Zadanie : Skarby (9)

% Opis zadania :
% Gramy w sapera. Dostajemy planszę MxN z pewnymi cyframi na planszy oznaczającymi
% liczbę bomb w okolicy. Mamy wygenerować możliwe rozstawienia bomb.

% 1. Typedefy, sprawdzanie danych.

%	- sprawdzDane :: Int -> Int -> [Trojka] -> Bool
%	- sprawdzListe :: Int -> Int -> [Trojka] -> Bool

% 2. Funkcje pomocnicze.

% 	- naPlanszy :: Int -> Int -> Punkt -> Bool
%	- czySasiad :: Int -> Int -> Punkt -> Punkt -> Bool
%	- generatorSasiadow :: Int -> Int -> Punkt -> [Punkt]
%	- nowaPlansza :: Int -> Int -> Plansza
%	- ustawTrojki :: Plansza -> [Trojka] -> Plansza
%	- ustawWartosci :: Plansza -> [Punkt] -> MyField -> Plansza
%	- sublist :: Int -> [a] -> [[a]]
%	- zrzutuj :: Maybe MyField -> Field
%	- zamien :: Int -> Int -> Plansza -> [[Field]]

% 3. Główne funkcje do rozwiązywania zadania

%	- main :: IO ()
%	- solve :: Solver
%	- rozwiazZagadke :: Int -> Int -> [Trojka] -> [Plansza]
%	- rozw :: Int -> Int -> [Trojka] -> Plansza -> [Plansza]

% 4. Testy -}

------------------------------------------------------------------------------------------
--------------------------- 1. Typedefy, sprawdzanie danych. -----------------------------
------------------------------------------------------------------------------------------
		
import Puzzle
import Checker
import Control.Monad
import Data.List
import Data.Map

type Punkt = (Int,Int)
type Trojka = (Int, Int, Int)
type Plansza = Map Punkt MyField

-- Wlasny typ Field - potrzebny bo dodałem nowy typ CC - "nieukonkretniona zmienna"
-- CC - "nieukonkretniona zmienna" czytaj : moze skarb moze puste pole (c od cos)
-- TT - bomba (T od treasure)
-- EE - empty (E od empty)

data MyField = CC | TT | EE | NN Int deriving (Eq, Show)

-- Sprawdzanie czy dane wejsciowe sa poprawne.

sprawdzDane :: Int -> Int -> [Trojka] -> Bool
sprawdzDane m n listaTrojek = and
	[
		n >= 1, n <= 16,
		m >= 1, m <= 16,
		length listaTrojek <= m * n,
		sprawdzListe n m listaTrojek
	]

-- Sprawdzanie czy lista trojek jest poprawna.

sprawdzListe :: Int -> Int -> [Trojka] -> Bool
sprawdzListe _ _ [] = True
sprawdzListe m n ( (x,y,z) : resztaTrojek ) = and
	[
		1 <= x, x <= m,
		1 <= y, y <= n,
		1 <= z, z <= 8,
		sprawdzListe m n resztaTrojek
	]

------------------------------------------------------------------------------------------
--------------------------------- 2. Funkcje pomocnicze. ---------------------------------
------------------------------------------------------------------------------------------

-- Sprawdza czy punkt (x,y) lezy na planszy o wymiarach m x n.

naPlanszy :: Int -> Int -> Punkt -> Bool
naPlanszy m n (x,y) = (x <= m && x >= 1 && y >= 1 && y <= n)

-- Czy (x,y) jest sasiadem punktu (a,b) na planszy o wymiarach m x n?
-- Uwaga : Punkt nie jest swoim wlasnym sasiadem.

czySasiad :: Int -> Int -> Punkt -> Punkt -> Bool

czySasiad m n (x,y) (a,b) = and
	[
		(x-a) `elem` [-1,0,1],
		(y-b) `elem` [-1,0,1],
		(x,y) /= (a,b),
		naPlanszy m n (x,y),
		naPlanszy m n (a,b)
	]

-- Funkcja generuje wszystkich sasiadow punktu (x,y) lezacych na planszy o wymiarach m x n

generatorSasiadow :: Int -> Int -> Punkt -> [Punkt]
generatorSasiadow m n (x,y) = do
	a <- [x-1, x, x+1]
	b <- [y-1, y, y+1]
	guard $ czySasiad m n (x,y) (a,b)
	return (a,b)

-- Tworzenie pustej planszy

nowaPlansza :: Int -> Int -> Plansza
nowaPlansza m n = Data.Map.fromList  [((x,y), CC) | x <- [1..m], y <- [1..n]]

-- Ustawia zadane trójki na planszy

ustawTrojki :: Plansza -> [Trojka] -> Plansza
ustawTrojki plansza [] = plansza
ustawTrojki plansza ((x,y,z):xs) = ustawTrojki (Data.Map.insert (x,y) (NN z) plansza) xs

-- Ustawia wszystkie pola (x,y) z listy na zadaną wartość z typu MyField

ustawWartosci :: Plansza -> [Punkt] -> MyField -> Plansza
ustawWartosci plansza [] _ = plansza
ustawWartosci plansza ((x,y):xs) z = ustawWartosci (Data.Map.insert (x,y) z plansza) xs z

-- Zwraca liste sasiadów na planszy m n wokol punktu, takich ze ich wartosci na planszy to e

listaElem :: Int -> Int -> Punkt -> MyField -> Plansza -> [Punkt]

listaElem m n pkt e plansza = do
	sasiad <- generatorSasiadow m n pkt
	guard $ Data.Map.lookup sasiad plansza == Just e
	return sasiad

-- zwraca listę wszystkich podlist listy o zadanej długości
-- sublist wywoluje funkcje sublist', gdzie
-- sublist ' ilu_elementowe ile_moge_wybrac z_czego
-- To jest przyspieszona wersja :
-- Data.List.filter ((== n) . length) . subsequences

sublist :: Int -> [a] -> [[a]]
sublist n xs  = sublist' n (length xs) xs where
	sublist' 0 _ _ = [[]]
	sublist' n k (x:xs)
		| k > n = [x:ys | ys <- sublist' (n-1) (k-1) xs] ++  sublist' n (k-1) xs
		| otherwise = [x:xs]

-- zrzutuj rzutuje Maybe MyField na Field (z tym że nieukonkretnioną zmienną przerabia na puste pole)

zrzutuj :: Maybe MyField -> Field
zrzutuj x = case x of
	Just TT -> T
	Just (NN y) -> N y
	_ -> E

-- Funkcja zamien przerabia plansze reprezentowana przez mape punktow o wartosciach w MyField
-- na liste list typu Field (potrzebne do zwracania wyniku w rozwiazaniu)

zamien :: Int -> Int -> Plansza -> [[Field]]
zamien m n plansza = [ [zrzutuj (Data.Map.lookup (x,y) plansza) | y <- [1..n]] | x <- [1..m]]

------------------------------------------------------------------------------------------
--------------------- 3. Glowne funkcje rozwiazujace problem -----------------------------
------------------------------------------------------------------------------------------

main :: IO ()
main = checkerMain solve tests

-- sprawdzamy dane, jesli sa poprawne to rozwiazujemy zagadke
-- i zwracamy odpowiedzi w odpowiednim formacie

solve :: Solver
solve m n xs = 
	if (sprawdzDane m n xs) then Data.List.map (zamien m n) (rozwiazZagadke m n xs)
	else [[]]

-- funkcja ktora znajduje wszystkie rozwiazania poprzez rozpatrywanie i ustawianie skarbow
-- wokol kolejnych trojek na nowej ("nieukonkretnionej") planszy

rozwiazZagadke :: Int -> Int -> [Trojka] -> [Plansza]
rozwiazZagadke m n xs = rozw m n xs $ ustawTrojki (nowaPlansza m n) xs

-- Funkcja rozw dziala nastepujaco:
-- Bierzemy m n - rozmiary planszy, liste trojek oraz aktualna plansze.
-- Jezeli dany punkt ma juz wystarczajaca liczbe bomb wokol siebie to
-- wszystkie punkty wokol ustawiamy na puste pola (bo tam juz nie ma nic byc).
-- W pozostalym przypadku sprawdzamy ile mamy wolnych pol wokol punktu i ile bomb
-- nalezy ustawic. Nasze rozw "unifikujemy" z pewna podlista wolnych miejsc i
-- wywolujemy sie rekurencyjnie. 

rozw :: Int -> Int -> [Trojka] -> Plansza -> [Plansza]

rozw _ _ [] plansza = [plansza]

rozw m n ((x,y,z):xs) plansza =

	-- jezeli nie mamy juz nic ustawiac wokol punktu

	if value == 0 then
 		-- to wszystkie wolne punkty wokol ustawiamy na puste pola i przechodzimy dalej
 		let plansza' = ustawWartosci plansza listaWolnychMiejsc (EE) in rozw m n xs plansza'
 	
 	else do

 		-- value = ile jeszcze bomb trzeba ustawic
 		-- sprawdzamy czy mozemy ich ustawic wystarczajaco
 		-- (albo czy nie jest ich ustawione za duzo)

		guard (value >= 0 && value <= ileWolnychMiejsc)

		-- wybieramy pewne miejsca gdzie ustawiamy bomby i wyznaczamy pozostale do wyczyszczenia

		bombyDoUstawienia <- sublist value listaWolnychMiejsc
		let punktyDoWyczyszczenia = listaWolnychMiejsc Data.List.\\ bombyDoUstawienia

		-- ustawiamy bomby i czyscimy

		let plansza' = ustawWartosci plansza bombyDoUstawienia (TT)
		let plansza'' = ustawWartosci plansza' punktyDoWyczyszczenia (EE)

		rozw m n xs plansza''

			where
				listaWolnychMiejsc  = listaElem m n (x,y) CC plansza
				ileWolnychMiejsc = length listaWolnychMiejsc
				bombyWokolPunktu  = listaElem m n (x,y) TT plansza
				ileBomb = length bombyWokolPunktu
				value = z - ileBomb

------------------------------------------------------------------------------------------
------------------------------------------- TESTY ----------------------------------------
------------------------------------------------------------------------------------------

tests :: [Test]
tests = [

-- Male testy i proste poprawnosciowe:

			(CountTest (Puzzle 1 1 [(1,1,1)]) 0),
			(CountTest (Puzzle 3 3 [(2,2,1)]) 8),
			(CountTest (Puzzle 3 3 [(1,1,1), (3,3,1)]) 5),
			(SimpleTest (Puzzle 1 1 []) [[E]]),
			(SimpleTest (Puzzle 3 3 [(1,2,4),(3,2,3)]) [[T, N 4 ,T],[T,E,T],[T, N 3 ,E]]),
			(SimpleTest (Puzzle 7 7 [(1,2,2),(1,5,2),(2,4,2),(2,6,1),(3,4,2),(3,6,2),(4,2,3),(4,4,1),(4,7,2),(6,1,3),(6,3,1),(7,6,2)]) [[E,N 2 ,E,T,N 2 ,E,E],[T,T,E,N 2,T,N 1 ,E],[T,E,E,N 2,E,N 2,E],[E,N 3 ,T,N 1 ,E,T,N 2 ],[T,E,E,E,E,E,T],[N 3 ,E,N 1 ,E,T,E,E],[T,T,E,E,T,N 2,E]]),
			(SimpleTest (Puzzle 5 5 [(2,2,4),(2,4,2),(2,5,1),(4,2,2),(4,4,4),(5,5,1)]) [[T,T,E,E,E],[T,N 4 ,E,N 2 ,N 1 ],[E,E,T,T,E],[E,N 2 ,T,N 4 ,E],[E,E,E,T,N 1 ]]),

-- Duze testy WIZ:

			(CountTest (Puzzle 10 10 [ (1,5,1), (1,8,1), (2,3,1), (2,6,2), (2,10,1), (3,1,1), (3,5,1), (3,8,3),(4,3,3), (4,6,3), (4,7,2), (4,10,3) ,(5,1,1), (5,5,3), (5,8,1),(6,3,4), (6,6,1), (6,10,3),(7,1,1), (7,4,1), (7,5,1), (7,8,1),(8,3,1), (8,6,2), (8,10,2),(9,1,1), (9,5,2), (9,8,1),(10,3,2), (10,6,2), (10,10,1) ]) 2),
			(SimpleTest (Puzzle 10 10 [ (1,5,1), (1,8,1), (2,3,1), (2,6,2), (2,10,1), (3,1,1), (3,5,1), (3,8,3),(4,3,3), (4,6,3), (4,7,2), (4,10,3) ,(5,1,1), (5,5,3), (5,8,1),(6,3,4), (6,6,1), (6,10,3),(7,1,1), (7,4,1), (7,5,1), (7,8,1),(8,3,1), (8,6,2), (8,10,2),(9,1,1), (9,5,2), (9,8,1),(10,3,2), (10,6,2), (10,10,1)]) [[E,E,E,E,N 1,T,E,N 1,E,E],[E,E,N 1,E,E,N 2,E,T,E,N 1],[N 1,T,E,E,N 1,E,T,N 3,T,E],[E,E,N 3,E,T,N 3,N 2,E,E,N 3],[N 1,T,T,E,N 3,T,E,N 1,T,T],[E,E,N 4,T,E,N 1,E,E,E,N 3],[N 1,T,E,N 1,N 1,E,E,N 1,T,E],[E,E,N 1,E,E,N 2,E,E,E,N 2],[N 1,E,E,E,N 2,T,T,N 1,E,T],[E,T,N 2,T,E,N 2,E,E,E,N 1]]),

-- Mega duzy count test - uwaga ! 6720 roznych rozwiazan

			((CountTest (Puzzle 13 13 [(1,1,1),(1,10,2),(1,12,2),(2,2,2),(2,3,3),(2,6,1),(3,1,1),(3,3,3),(3,6,1),(4,1,1),(4,3,3),(4,5,2),(4,10,1),(4,11,2),(4,12,2),(4,13,2),(5,5,1),(5,7,1),(5,9,1),(5,11,2),(6,1,2),(6,3,2),(6,5,1),(6,6,1),(6,8,1),(6,9,1),(6,10,1),(6,13,3),(7,1,1),(7,2,1),(7,5,1),(7,12,2),(7,13,1),(8,1,1),(8,4,1),(8,5,2),(8,6,3),(8,7,2),(8,11,2)    ,(9,4,3),(9,9,2),(9,10,1),(10,5,3),(10,7,4),(10,9,3),(10,11,2),(10,12,2),(11,1,2),(11,2,5),(11,6,1),(11,9,3),(12,4,3),(12,5,1),(12,6,1),(12,8,2),(12,9,2),(12,10,4),(12,12,5),( 13,2,2),(13,13,1)]) 6720)),

-- Pojedynczy max test:

			(SimpleTest (Puzzle 16 16 [(1,4,2),(1,8,2),(1,12,3),(2,1,1),(2,2,2),(2,5,2),(2,6,2),(2,7,2),(2,8,2),(2,10,3),(2,11,3),(2,15,1),(3,14,2),(3,16,2),(4,1,1),(4,2,1),(4,3,1),(4,11,3),(4,12,1),(4,15,3),(5,6,4),(5,10,3),(5,15,3),(5,16,2),(6,1,1),(6,2,1),(6,5,3),(6,6,1),(6,10,1),(6,12,1),(6,16,1),(7,2,1),(7,3,1),(7,10,2),(8,5,2),(8,10,2),(8,11,2),(9,1,1),(9,3,1),(9,5,1),(9,8,4),(9,11,2),(9,12,1),(9,13,3),(9,15,2),(10,2,2),(10,5,1),(10,8,3),(10,9,2),(10,11,1),(10,15,2),(11,1,1),(11,3,1),(11,4,1),(11,6,3),(11,9,1),(11,10,1),(11,11,1),(11,13,2),(12,9,3),(12,13,3),(13,10,3),(13,15,5),(13,16,3),(14,5,1),(14,10,3),(14,12,2),(14,15,2),(15,2,1),(15,9,4),(15,11,2),(15,12,2),(15,13,2),(15,14,2),(15,15,2),(16,6,3),(16,9,3),(16,14,1)]) [[E,E,T,N 2,E,T,T,N 2,T,E,T,N 3,T,E,E,E],[N 1,N 2,E,T,N 2,N 2,N 2,N 2,E,N 3,N 3,T,E,E,N 1,E],[T,E,E,E,E,E,E,E,E,T,E,E,E,N 2,T,N 2],[N 1,N 1,N 1,E,T,T,T,E,T,T,N 3,N 1,E,T,N 3,T],[E,E,E,T,T,N 4,E,E,E,N 3,E,T,E,E,N 3,N 2],[N 1,N 1,E,E,N 3,N 1,E,E,T,N 1,E,N 1,E,E,T,N 1],[T,N 1,N 1,T,E,E,E,E,E,N 2,E,E,E,E,E,E],[E,E,E,E,N 2,T,T,T,T,N 2,N 2,T,E,T,E,E],[N 1,T,N 1,E,N 1,E,T,N 4,E,T,N 2,N 1,N 3,T,N 2,E],[E,N 2,E,E,N 1,E,E,N 3,N 2,E,N 1,E,E,E,N 2,E],[N 1,T,N 1,N 1,T,N 3,T,T,N 1,N 1,N 1,E,N 2,T,E,E],[E,E,E,E,E,T,E,E,N 3,E,T,E,N 3,T,T,T],[E,E,E,E,E,E,E,T,T,N 3,T,T,E,E,N 5,N 3],[T,E,E,E,N 1,E,E,T,E,N 3,E,N 2,E,T,N 2,T],[E,N 1,E,E,T,E,E,T,N 4,T,N 2,N 2,N 2,N 2,N 2,E],[E,E,E,E,T,N 3,T,T,N 3,E,T,E,T,N 1,E,E]])
		]

{- Wynik Chckera - bez optymalizacji podanych na samej górze

======================
Test: 1/11
CPU time:   0.00s
Accept!
======================
Test: 2/11
CPU time:   0.00s
Accept!
======================
Test: 3/11
CPU time:   0.00s
Accept!
======================
Test: 4/11
CPU time:   0.00s
Accept!
======================
Test: 5/11
CPU time:   0.00s
Accept!
======================
Test: 6/11
CPU time:   0.01s
Accept!
======================
Test: 7/11
CPU time:   0.01s
Accept!
======================
Test: 8/11
CPU time:   0.11s
Accept!
======================
Test: 9/11
CPU time:   0.06s
Accept!
======================
Test: 10/11
CPU time:  16.48s
Accept!
======================
Test: 11/11
CPU time:   0.43s
Accept!
Accepted: 11/11
======================-}