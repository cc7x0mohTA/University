# Bartosz Bednarczyk, Rafał Kaleta
# zadanie P2.21

using Polynomials

# funkcja obliczająca iloczyn skalarny
# ARGUMENTY:
# w - funkcja wagowa
# p, q - wielomiany
# z1, z2 - granice całkowania (z1 < z2)
# weighted - czy używać funkcji wagowej

function innerprod1(w, p, q, z1, z2, weighted)
	if(weighted)
		FNK=x -> polyval(p*q, x)*w(x)
		return quadgk(FNK, z1, z2)[1]
	else
		INT=polyint(p*q)
		return polyval(INT, z2)-polyval(INT, z1)	
	end
end

# funkcja obliczająca współczynniki do wyznaczenia nowej bazy dualnej za pomoca odwracania macierzy
# ARGUMENTY:
# B - baza wejściowa
# D - aktualna baza dualna
# n - rozmiar aktualnej bazy dualnej
# w - funkcja wagowa
# z1, z2 - granice całkowania (z1 < z2)
# weighted - czy używać funkcji wagowej

function step1(B, D, n, w, z1, z2, weighted)
	V=[ innerprod1(w, B[n+2], B[i], z1, z2, weighted) for i=1:n+1 ]
	U=[ innerprod1(w, B[n+2], D[i], z1, z2, weighted) for i=1:n+1 ]
	t=innerprod1(w, B[n+2], B[n+2], z1, z2, weighted)-sum([ U[i]*V[i] for i=1:n+1 ])
	C=zeros(n+2, n+2)
	
	for i=1:n+1
		for j=1:n+1
			C[i+(n+2)*(j-1)]=i==j?t+V[i]*U[j]:V[i]*U[j]
		end
	end
	
	for i=1:n+1
		C[i+(n+2)*(n+1)]=-V[i]
	end
	
	for j=1:n+1
		C[(n+2)+(n+2)*(j-1)]=-U[j]
	end	
	
	C[(n+2)+(n+2)*(n+1)]=1
	
	return (1/t)*C
end

# funkcja obliczająca bazę dualną metodą układu równań
# ARGUMENTY:
# B - baza wejściowa
# w - funkcja wagowa
# z1, z2 - granice całkowania (z1 < z2)
# weighted - czy używać funkcji wagowej

function dualbase1(B, w, z1, z2, weighted)
	D=[ Poly([0.0]) for i=1:length(B) ]
	D[1]=(1/innerprod1(w, B[1], B[1], z1, z2, weighted))*B[1]
	
	for n=0:length(B)-2
		C=step1(B, D, n, w, z1, z2, weighted)
		DN=[ Poly([0.0]) for i=1:n+2 ]
		
		for j=1:n+2
			for i=1:n+1
				DN[j]=DN[j]+C[i+(n+2)*(j-1)]*D[i]
			end
			
			DN[j]=DN[j]+C[n+2+(n+2)*(j-1)]*B[n+2]
		end
		
		for i=1:n+2
			D[i]=DN[i]
		end
	end
	
	return D
end

