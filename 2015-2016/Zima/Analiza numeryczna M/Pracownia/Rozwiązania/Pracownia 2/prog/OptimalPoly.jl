# Bartosz Bednarczyk, Rafał Kaleta
# zadanie P2.21

using Polynomials

# funkcja obliczająca iloczyn skalarny
# ARGUMENTY:
# w - funkcja wagowa
# f - funkcja przybliżana
# p - wielomian
# z1, z2 - granice całkowania (z1 < z2)

function innerprod(w, f, p, z1, z2)
	FNK=x -> polyval(p, x)*f(x)*w(x)
	return quadgk(FNK, z1, z2)[1]
end

# funkcja obliczająca wielomian optymalny przybliżający daną funkcję
# ARGUMENTY:
# f - funkcja przybliżana
# B - baza wejściowa
# D - baza dualna
# w - funkcja wagowa
# z1, z2 - granice całkowania (z1 < z2)

function optimalpoly(f, B, D, w, z1, z2)
	return sum([ innerprod(w, f, D[i], z1, z2)*B[i] for i=1:length(B) ])
end

# funkcja obliczająca normę średniokwadratową dla wielominau optymalnego
# ARGUMENTY:
# f - funkcja przybliżana
# p - wielomian optymalny
# w - funkcja wagowa
# z1, z2 - granice całkowania (z1 < z2)

function normasred(f, p, w, z1, z2)
	FNK=x -> (f(x)-polyval(p, x))*(f(x)-polyval(p, x))*w(x)
	return quadgk(FNK, z1, z2)[1]
end
