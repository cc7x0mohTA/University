using MultiPoly
### a - lista wspolczynnikow wielomianu (np. [1,2,3] reprezentuje wielomian 1 + 2x + 3x^2)
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

# W - wspolczynniki wielomianu jw, n - stopien wielomianu, x0 + i y0 - punkt startowy, eps - dokladnosc
function complex_newton(W, n::Int, x0::Float64, y0::Float64, eps::Float64)

  if n == 0
    return
  elseif n == 1
    w = Complex128(-W[1])/Complex128(W[2])
    @printf("%.16lf +\t %.16lf i\n ", real(w), imag(w))
    return
  end

  x, y = generators(MPoly{Float64}, :x, :y) # zmienne w wielomianie
  p = zero(MPoly{Complex128})

  for i in 1:(n+1)
    p = p + W[i] * (x+y*im)^(i-1)
  end

  xn = x0; yn = y0; P = real(p); Q = imag(p-P)
  Px = diff(P, :x); Py = diff(P, :y)
  Qx = diff(Q, :x); Qy = diff(Q, :y)

  while( abs( evaluate(p, xn, yn) ) >= eps )
    eP = evaluate(P, xn, yn); eQ = evaluate(Q, xn, yn)
    ePx = evaluate(Px, xn, yn); eQy = evaluate(Qy, xn, yn)
    ePy = evaluate(Py, xn, yn); eQx = evaluate(Qx, xn, yn)
    xn = xn - (eP * ePx + eQ * eQx)/(ePx^2 + eQx^2)
    yn = yn - (eP * ePy + eQ * eQy)/(ePx^2 + eQx^2)
  end

  @printf("%.16lf +\t %.16lf i\n ", xn, yn)
  complex_newton(horner(W, complex(xn, yn)), n-1, x0, y0, eps)
end