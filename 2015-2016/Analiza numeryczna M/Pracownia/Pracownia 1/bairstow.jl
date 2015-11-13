# Bartosz Bednarczyk
# Jan Gora
# Implementacja algorytmu Bairstowa (opis podany w sprawozdaniu)

# pomocnicza funkcja do wyznaczania miejsc zerowych wielomianu w postaci ax^2 + bx + c
function solveQuadratic(a, b, c)

  delta = b*b - 4 * a * c

  if delta < 0
    Re_x1 = -b/(2*a)
    Re_x2 = -b/(2*a)
    Im_x1 = -sqrt(-delta)/(2*a)
    Im_x2 = +sqrt(-delta)/(2*a)
    @printf("%.16lf + (%.16lf)i\n%.16lf + (%.16lf)i\n", Re_x1, Im_x1, Re_x2, Im_x2)
  else
    x1 = (-b - sqrt(delta))/(2*a)
    x2 = (-b + sqrt(delta))/(2*a)
    @printf("%.16f\n%.16lf\n", x1, x2)
  end

end

# Metoda bairstowa
# Opis argumentow
### n - stopien wielomianu
### a - lista wspolczynnikow wielomianu (np. [1,2,3] reprezentuje wielomian 1 + 2x + 3x^2)
### (u,v) punkt startowy od ktorego zaczynamy metode
### M - liczba interacji

function bairstow(n, a, u, v, M)

  set_bigfloat_precision(128)
  map(BigFloat, a)
  u = BigFloat(u)
  v = BigFloat(v)

  if n == 0
      return
  end

  if n == 1
    @printf("%.16lf\n", -a[2]/a[1]) # x = -b/a
    return
  end

  if n == 2
    solveQuadratic(a[3], a[2], a[1])
    return
  end

  b  = [BigFloat(0.0) for i in 1:(n+3)]
  c  = [BigFloat(0.0) for i in 1:(n+3)]
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

    J = c[1] * c[3] - c[2] * c[2]
    u = u + (c[2]*b[2] - c[3] * b[1] ) / J
    v = v + (c[2]*b[1] - c[1] * b[2]) / J

  end

  solveQuadratic(1, -u, -v)
  bairstow(n-2, b[3:end], u, v, M)

end
