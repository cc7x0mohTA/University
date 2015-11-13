# Bartosz Bednarczyk, Jan Gora
# Klayczna Metoda Newtona

# Przyklad : klasyczna_metoda_newtona([-6.0, 11.0, -6.0, 1.0], 3, 0.01, 0.00000000001)
using Polynomials

function klasyczna_metoda_newtona(W, n, p, eps)
  dW = polyint(W)
  x_n = p

  while abs(polyval(W, x_n)) >= eps
    x_n = x_n - (polyval(W, x_n)/polyval(dW, x_n))
  end

  return Float64(x_n)
end

function pierwiastki_wielomianu(a, n, p, eps)

  W = Poly(a)

  while n != 0

    if n == 1
      @printf("%.lf\n", -a[0]/a[1])
    else
      x_n = klasyczna_metoda_newtona(W, n, p, eps)
      @printf("%.16lf\n", x_n)
      return
      n = n - 1
    end
  end
end