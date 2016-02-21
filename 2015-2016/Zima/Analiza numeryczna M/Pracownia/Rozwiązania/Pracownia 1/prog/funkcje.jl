function solveQuadratic(a, b, c)

  delta = b*b - 4 * a * c

  if delta < 0
    x1 = Complex(-b/(2*a), -sqrt(-delta)/(2*a))
    x2 = Complex(-b/(2*a), +sqrt(-delta)/(2*a))
    return [x1, x2]

  else
    x1 = Complex((-b - sqrt(delta))/(2*a))
    x2 = Complex((-b + sqrt(delta))/(2*a))
    return [x1, x2]
  end

end

#funkcja konwertujaca String na Array{BigFloat}
function strb(a::ASCIIString)
  prec = get_bigfloat_precision()
  set_bigfloat_precision(1024)
  a = replace(a, "[", "") 
  a = replace(a, "]", "") 
  a = replace(a, ",", " ") 
  a = split(a)

  a = map(x -> parse(BigFloat, x), a)

  set_bigfloat_precision(prec)
  return a
end

#funkcja dzielaca wielomian przez czynnik (x-x0)
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