# Bartosz Bednarczyk
# Jan Gora
# Implementacja algorytmu Lagguerre'a (opis podany w sprawozdaniu)


# Funkcja glowna, wyznaczajaca miejsca zerowe wielomianu o wspolczynnikach zespolonych
# Opis argumentow
### a - lista wspolczynnikow wielomianu (np. [1,2,3] reprezentuje wielomian 1 + 2x + 3x^2)

function lagguerre(a, M)
  n = length(a) - 1
  # a = map(Complex{BigFloat}, a) 
  w = Array(Complex{BigFloat}, 0)

  while n>=1
    z0 = Complex(BigFloat(0))

    for k in 1:M
      p1 = p2 = p3 = A = Complex(BigFloat(0))
      p1 = a[n+1]

      for _j in 1:n
        i = n - _j
        p3 = z0*p3 + p2
        p2 = z0*p2 + p1
        p1 = z0*p1 + a[i+1]
      end

      if abs(p1) < EPS
        break
      end

      A = -p2/p1
      B = A*A - (2*p3)/p1
      E = sqrt(BigFloat(n-1)*(n*B - A*A))
      D = (abs(A+E) > abs(A-E) ? A+E : A-E)
      C = BigFloat(n) / D
      z0 += C

      if abs(C) < EPS
        break
      end
    end
    n-=1
    push!(w, z0)
    a = horner(a, z0)  
  end

  return w
  # @printf("%.30f + %.1fi\n", real(z0), imag(z0))
  # lagguerre(horner(a, z0))
end

function lagguerre(a::ASCIIString)
  lagguerre(strb(a), 300)
end

function lagguerre(a::ASCIIString, M)
  lagguerre(strb(a), M)
end





