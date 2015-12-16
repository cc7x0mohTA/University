# Bartosz Bednarczyk, Rafał Kaleta
# zadanie P2.21

# UWAGI:
# - język programowania: Julia 0.4
# - napisano i uruchomiono w środowisku Linux Ubuntu 14.04
# - obliczenia wykonywane są w arytmetyce Float64

using Polynomials

include("DualBase_0.jl")
include("DualBase_1.jl")
include("DualBase_2.jl")
include("OptimalPoly.jl")

# funkcja obliczająca bazy dualne do bazy wejściowej
# algorytm 0 wykorzystuje odwracanie macierzy Grama
# algorytm 1 wykorzystuje układ równań do obliczenia elementów bazy dualnej
# algorytm 2 wykorzystuje iteracyjne wyznaczanie elementów bazy dualnej za pomocą elementu n+1.
# ARGUMENTY:
# B - baza wejściowa
# w - funkcja wagowa iloczynu skalarnego
# z1, z2 - granice całkowania dla iloczynu skalarnego (z1 < z2)
# weighted - czy używać funkcji wagowej

function test_DB(B, w, z1, z2, weighted)
	print("ALGORYTM 0:\n")
	D0=dualbase0(B, w, z1, z2, weighted)
	
	for i in D0	
		print(i, "\n")
	end
	
	print("\n", "ALGORYTM 1:\n")
	D1=dualbase1(B, w, z1, z2, weighted)
	
	for i in D1	
		print(i, "\n")
	end
	
	print("\n", "ALGORYTM 2:\n")
	D2=dualbase2(B, w, z1, z2, weighted)
	
	for i in D2	
		print(i, "\n")
	end	
	
	print("\n")
	return D0
end

BaseStd=[Poly([1.0]), Poly([0.0, 1.0]), Poly([0.0, 0.0, 1.0]), Poly([0.0, 0.0, 0.0, 1.0]), Poly([0.0, 0.0, 0.0, 0.0, 1.0]), Poly([0.0, 0.0, 0.0, 0.0, 0.0, 1.0])]
BaseOne=[Poly([1.0]), Poly([-1.0, 1.0]), Poly([1.0, -1.0, 1.0]), Poly([-1.0, 1.0, -1.0, 1.0]), Poly([1.0, -1.0, 1.0, -1.0, 1.0])]
BaseLeg=[Poly([1.0]), Poly([0.0, 1.0]), Poly([-0.5, 0.0, 1.5]), Poly([0.0, -1.5, 0.0, 2.5])]
BaseLegNorm=[Poly([sqrt(1/2)]), Poly([0.0, sqrt(3/2)]), Poly([-0.5*sqrt(5/2), 0.0, 1.5*sqrt(5/2)]), Poly([0.0, -1.5*sqrt(7/2), 0.0, 2.5*sqrt(7/2)])]

# przykład 1: BAZA STANDARDOWA - przybliżamy funkcje cos(x) orax 7*x^3 + 4*x^2 - 13

print("BAZA STANDARDOWA:\n")

for i in BaseStd
	print(i, "\n")
end

print("\n\n", "BAZA DUALNA DO BAZY STANDARDOWEJ:\n")
DualStd=test_DB(BaseStd, x -> 1, -1, 1, false)

print("WIELOMIAN OPTYMALNY DLA f(x) = cos(x) NA PRZEDZIALE [-1, 1]\n")
OptStd1=optimalpoly(x -> cos(x), BaseStd, DualStd, x -> 1, -1, 1)
NSKStd1=normasred(x -> cos(x), OptStd1, x -> 1, -1, 1)
print("\t", OptStd1, "\n")
print("\t NORMA BŁĘDU: ", NSKStd1, "\n\n\n")

print("WIELOMIAN OPTYMALNY DLA f(x) = 7*x^3 + 4*x^2 - 13 NA PRZEDZIALE [-1, 1]\n")
OptStd2=optimalpoly(x -> 7*x*x*x+4*x*x-13, BaseStd, DualStd, x -> 1, -1, 1)
NSKStd2=normasred(x -> 7*x*x*x+4*x*x-13, OptStd2, x -> 1, -1, 1)
print("\t", OptStd2, "\n")
print("\t NORMA BŁĘDU: ", NSKStd2, "\n\n\n")

# przykład 2: ZABURZONA BAZA STANDARDOWA - przybliżamy funkcje cbrt(x^2) orax 7*x^3 + 4*x^2 - 13

print("ZABURZONA BAZA STANDARDOWA:\n")

for i in BaseOne
	print(i, "\n")
end

print("\n\n", "BAZA DUALNA DO ZABURZONEJ BAZY STANDARDOWEJ:\n")
DualOne=test_DB(BaseOne, x -> 1, -1, 1, false)

print("WIELOMIAN OPTYMALNY DLA f(x) = cbrt(x^2) NA PRZEDZIALE [-1, 1]\n")
OptOne1=optimalpoly(x -> cbrt(x^2), BaseOne, DualOne, x -> 1, -1, 1)
NSKOne1=normasred(x -> cbrt(x^2), OptOne1, x -> 1, -1, 1)
print("\t", OptOne1, "\n")
print("\t NORMA BŁĘDU: ", NSKOne1, "\n\n\n")

print("WIELOMIAN OPTYMALNY DLA f(x) = 7*x^3 + 4*x^2 - 13 NA PRZEDZIALE [-1, 1]\n")
OptOne2=optimalpoly(x -> 7*x*x*x+4*x*x-13, BaseOne, DualOne, x -> 1, -1, 1)
NSKOne2=normasred(x -> 7*x*x*x+4*x*x-13, OptOne2, x -> 1, -1, 1)
print("\t", OptOne2, "\n")
print("\t NORMA BŁĘDU: ", NSKOne2, "\n\n\n")

# przykład 3: NIEZNORMALIZOWANA BAZA LEGENDRE'A - przybliżamy funkcje sqrt(e^x) oraz sin(x^3 + 8)

print("NIEZNORMALIZOWANA BAZA LEGENDRE'A:\n")

for i in BaseLeg
	print(i, "\n")
end

print("\n\n", "BAZA DUALNA:\n")
DualLeg=test_DB(BaseLeg, x -> 1, -1, 1, false)

print("WIELOMIAN OPTYMALNY DLA f(x) = sqrt(e^x) NA PRZEDZIALE [-1, 1]\n")
OptLeg1=optimalpoly(x -> sqrt(exp(x)), BaseLeg, DualLeg, x -> 1, -1, 1)
NSKLeg1=normasred(x -> sqrt(exp(x)), OptLeg1, x -> 1, -1, 1)
print("\t", OptLeg1, "\n")
print("\t NORMA BŁĘDU: ", NSKLeg1, "\n\n\n")

print("WIELOMIAN OPTYMALNY DLA f(x) = sin(x^3 + 8) NA PRZEDZIALE [-1, 1]\n")
OptLeg2=optimalpoly(x -> sin(x*x*x+8), BaseLeg, DualLeg, x -> 1, -1, 1)
NSKLeg2=normasred(x -> sin(x*x*x+8), OptLeg2, x -> 1, -1, 1)
print("\t", OptLeg2, "\n")
print("\t NORMA BŁĘDU: ", NSKLeg2, "\n\n\n")

# przykład 4: ZNORMALIZOWANA BAZA LEGENDRE'A - przybliżamy funkcje sqrt(e^x) oraz x*sin(e^x)

print("ZNORMALIZOWANA BAZA LEGENDRE'A:\n")

for i in BaseLegNorm
	print(i, "\n")
end

print("\n\n", "BAZA DUALNA:\n")
DualLegNorm=test_DB(BaseLegNorm, x -> 1, -1, 1, false)

print("WIELOMIAN OPTYMALNY DLA f(x) = sqrt(e^x) NA PRZEDZIALE [-1, 1]\n")
OptLegNorm1=optimalpoly(x -> sqrt(exp(x)), BaseLegNorm, DualLegNorm, x -> 1, -1, 1)
NSKLegNorm1=normasred(x -> sqrt(exp(x)), OptLegNorm1, x -> 1, -1, 1)
print("\t", OptLegNorm1, "\n")
print("\t NORMA BŁĘDU: ", NSKLegNorm1, "\n\n\n")

print("WIELOMIAN OPTYMALNY DLA f(x) = x*sin(e^x)-176 NA PRZEDZIALE [-1, 1]\n")
OptLegNorm2=optimalpoly(x -> x*sin(exp(x))-176, BaseLegNorm, DualLegNorm, x -> 1, -1, 1)
NSKLegNorm2=normasred(x -> x*sin(exp(x))-176, OptLegNorm2, x -> 1, -1, 1)
print("\t", OptLegNorm2, "\n")
print("\t NORMA BŁĘDU: ", NSKLegNorm2, "\n\n\n")

