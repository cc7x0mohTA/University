# Bartosz Bednarczyk, Rafał Kaleta
# zadanie P2.21

using Polynomials

# funkcja obliczająca iloczyn skalarny
# ARGUMENTY:
# w - funkcja wagowa
# p, q - wielomiany
# z1, z2 - granice całkowania (z1 < z2)
# weighted - czy używać funkcji wagowej

function innerprod2(w, p, q, z1, z2, weighted)
	if(weighted)
		FNK=x -> polyval(p*q, x)*w(x)
		return quadgk(FNK, z1, z2)[1]
	else
		INT=polyint(p*q)
		return polyval(INT, z2)-polyval(INT, z1)	
	end
end

# funkcja obliczająca bazę dualną metodą iteracyjnego wyznaczania elementów
# ARGUMENTY:
# B - baza wejściowa
# w - funkcja wagowa
# z1, z2 - granice całkowania (z1 < z2)
# weighted - czy używać funkcji wagowej

function dualbase2(B, w, z1, z2, weighted)
	D=[ Poly([0.0]) for i=1:length(B) ]
	D[1]=(1/innerprod2(w, B[1], B[1], z1, z2, weighted))*B[1]
	
	for n=0:length(B)-2
		V=[ innerprod2(w, B[n+2], B[i], z1, z2, weighted) for i=1:n+1 ]
		W=[ innerprod2(w, B[n+2], D[i], z1, z2, weighted) for i=1:n+1 ]
		t=innerprod2(w, B[n+2], B[n+2], z1, z2, weighted)-sum([ W[i]*V[i] for i=1:n+1 ])		
		C=[ i==n+2?1/t:-V[i]/t for i=1:n+2 ]		
		DN=[ Poly([0.0]) for i=1:n+2 ]
		DN[n+2]=sum([ C[k]*D[k] for k=1:n+1 ])+C[n+2]*B[n+2]
		
		for i=n+1:-1:1
			DN[i]=D[i]-W[i]*DN[n+2]
		end
		
		for i=1:n+2
			D[i]=DN[i]
		end
	end
	
	return D
end

