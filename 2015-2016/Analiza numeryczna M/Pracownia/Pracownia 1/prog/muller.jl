
# a-> lista wspolczynnikow, M->ilosc iteracji
function muller(a, M)
  x0 = Complex(BigFloat(0))
  n = length(a) - 1
  w = Array(Complex{BigFloat}, 0)

  while n > 0
    for step in 1:M
      p0 = p1 = p2 = Complex(BigFloat(0))

      for _j in 0:n
        i = n - _j
        p2 = x0*p2 + p1         # p2 - 1/2 f''(x)
        p1 = x0*p1 + p0         # p1 - f'(x)
        p0 = x0*p0 + a[i+1]     # p0 - f(x)  
      end

      if abs(p0) <= EPS
        break
      end
      c = (real(p1)>=EPS ? 1.0 : -1.0)
      d = (p0*2.0)/(p1 + c*sqrt(p1*p1 - 4.0*p0*p2))
      x0 -= d

      if abs(d) <= EPS
        break
      end

    end
    push!(w, x0)
    a = horner(a, x0)
    n-=1
  end
  return w
end

# Lista współczynikków np, a => "1 2 3 4"
function muller(a::ASCIIString)
  muller(strb(a), 300)
end

function muller(a::ASCIIString, M)
  muller(strb(a), M)
end


