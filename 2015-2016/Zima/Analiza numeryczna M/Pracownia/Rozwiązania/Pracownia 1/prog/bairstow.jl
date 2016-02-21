# Metoda bairstowa

# a-> Lista wspolczynnikow wielomianu, np [1, 2, 3], (u, v) -> punkty poczatkowe, M -> liczba operacji
function bairstow(a, u, v, M)
  n = length(a)-1
  a = map(x->parse(BigFloat, string(x)), a)
  u = parse(BigFloat, string(u))
  v = parse(BigFloat, string(u))
  w = Array(Complex{BigFloat}, 0)
  J = BigFloat(0)

  while n > 0

    if n == 1
      append!(w, [Complex(-a[1]/a[2])]) # x = -b/a
      break
    end

    if n == 2

      append!(w, solveQuadratic(a[3], a[2], a[1]))
      break
    end

    b  = [zero(BigFloat) for i in 1:(n+3)]
    c  = [zero(BigFloat) for i in 1:(n+3)]
    b[n+1] = a[n+1]
    c[n] = a[n+1]

    for j in 1:M
      b[n] = a[n] + u * b[n+1]

      k = n-2

      while k >= 0
        b[k+1] = a[k+1] + u * b[k+2] + v * b[k+3]
        c[k+1] = b[k+2] + u * c[k+2] + v * c[k+3]
        k = k - 1
      end

      if abs(b[1]) + abs(b[2]) <= EPS
        break
      end

      J = c[1] * c[3] - c[2] * c[2]

      if abs(J) <= EPS
        warn("JAKOBIAN zero")
        break
      end

      u = u + (c[2]*b[2] - c[3] * b[1] ) / J
      v = v + (c[2]*b[1] - c[1] * b[2]) / J

    end

    ## Przykładowe usprawnienie metody:
    # if M > 100 && abs(b[1]) + abs(b[2]) > EPS
    #   u = rand(-10:10)*rand(Float64)
    #   v = rand(-10:10)*rand(Float64)
    #   warn("Nowe punkty (u,v): "*string(u)*" "*string(v))  
    # else
    #   append!(w, solveQuadratic(1, -u, -v))
    #   n-=2
    #   a = copy(b[3:end])
    # end

    append!(w, solveQuadratic(1, -u, -v))
    n-=2
    a = copy(b[3:end])
  end
  
  return w
end


# Lista współczynikków np, a => "1 2 3 4"
function bairstow(a::ASCIIString)
  bairstow(strb(a), 0, 0, 300)
end


function bairstow(a::ASCIIString, M::Int)
  bairstow(strb(a), 0, 0, M)
end

function bairstow(a::ASCIIString, M::Int, u, v)
  bairstow(strb(a), M, u, v)
end