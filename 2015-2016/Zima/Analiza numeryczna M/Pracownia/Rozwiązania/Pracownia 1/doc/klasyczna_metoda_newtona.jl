using Polynomials
# W - wielomian, n - stopnien wielomianu, p - punkt startowy, eps - dokladnosc

function klasyczna_metoda_newtona(W, n, p, eps)
  dW = polyint(W)	# oblicza pochodna wielomianu
  x_n = p
  
  while bigger(abs(polyval(W, x_n)), eps)
    x_n = x_n - (polyval(W, x_n)/polyval(dW, x_n))
  end
  
  return x_n	# zwroc szukany pierwiastek
end