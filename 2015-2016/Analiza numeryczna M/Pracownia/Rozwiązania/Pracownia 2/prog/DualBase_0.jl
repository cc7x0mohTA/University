# Bartosz Bednarczyk, Rafał Kaleta
# zadanie P2.21

using Polynomials

# funkcja obliczająca iloczyn skalarny
# ARGUMENTY:
# w - funkcja wagowa
# p, q - wielomiany
# z1, z2 - granice całkowania (z1 < z2)
# weighted - czy używać funkcji wagowej

function innerprod0(w, p, q, z1, z2, weighted)
	if(weighted)
		FNK=x -> polyval(p*q, x)*w(x)
		return quadgk(FNK, z1, z2)[1]
	else
		INT=polyint(p*q)
		return polyval(INT, z2)-polyval(INT, z1)
	end
end

# funkcja obliczająca bazę dualną metodą macierzy Grama
# ARGUMENTY:
# B - baza wejściowa
# w - funkcja wagowa
# z1, z2 - granice całkowania (z1 < z2)
# weighted - czy używać funkcji wagowej

function dualbase0(B, w, z1, z2, weighted)
	D=[ Poly([0.0]) for i=1:length(B) ]
	G=convert(Array{Float64, 2}, [ innerprod0(w, B[i], B[j], z1, z2, weighted) for i=1:length(B), j=1:length(B) ])
	GI=inv(G)
	
	for j=1:length(B)
		for i=1:length(B)
			D[j]=D[j]+GI[i+length(B)*(j-1)]*B[i]
		end
	end
	
	return D
end

