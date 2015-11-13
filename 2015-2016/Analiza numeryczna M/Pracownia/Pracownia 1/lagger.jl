# Bartosz Bednarczyk
# Jan Gora
# Implementacja algorytmu Lagguerre'a (opis podany w sprawozdaniu)
 
 
 
# M -> Liczba iteracji, eps -> Minimalna roznica przy porownywaniu
set_bigfloat_precision(128)
M = 100
eps = BigFloat(1e-16)
 
 
# Funkcja glowna, wyznaczajaca miejsca zerowe wielomianu o wspolczynnikach zespolonych
# Opis argumentow
### a - lista wspolczynnikow wielomianu (np. [1,2,3] reprezentuje wielomian 1 + 2x + 3x^2)
 
function lagguerre(a)
  n = length(a) - 1
 
  z0 = Complex(BigFloat(0))
  map(Complex{BigFloat}, a)
 
  if n<1
    return
  end
 
 
  for k in 1:1
    p1 = p2 = p3 = A = Complex(BigFloat(0))
    p1 = a[n+1]
 
    for _j in 0:n
      i = n - _j
      p3 = z0*p3 + p2
      p2 = z0*p2 + p1
      p1 = z0*p1 + a[i+1]
    end
 
    if abs(p1) < eps
      break
    end
 
    A = -p2/p1
    B = A*A - (2*p3)/p1
    E = sqrt(BigFloat(n-1)*(BigFloat(n)*B - A*A))
    D = (abs(A+E) > abs(A-E) ? A+E : A-E)
    C = BigFloat(n) / D
    z0 += C
    if abs(C) < eps  
      break
    end
  end
 
  @printf("%.20f + %.20fi\n", real(z0), imag(z0))
   lagguerre(horner(a, z0))
end
 
 
# Funkcja dzielaca wielomian przez pierwiastek uzywajac schematu Hornera
function horner(a, x0)
  n = length(a) - 1
  b = Array(Complex{BigFloat}, n)
  b[n] = a[n+1]
  for _k in 0:(n-2)
    i = n - _k
    b[i-1] = a[i] + b[i]*x0
  end
  return b
end