# Bartosz Jan Bednarczyk (273 479)
# Analiza numeryczna (M) - Pracownia nr 3 - zadanie P3.9
# Obliczanie calki zlozona metoda Simpsona

########################################################################################################################

# Input : lista par liczb rzeczywistych postaci (x, f(x))
# Output : Przyblizona wartosc calki oznaczonej na przedziale x[0], x[n]

function simpson_method(points)

  m = (length(points)-1) >> 1
  integral = zero(Float64)

  for k in 1:m

    a = first(points[2*k-2+1])
    b = first(points[2*k-1+1])
    c = first(points[2*k+1])

    fa = last(points[2*k-2+1])
    fb = last(points[2*k-1+1])
    fc = last(points[2*k+1])

    integral += fa * ( (a-c)*(2*a-3*b+c) )/((b-a))
    integral += fb * ( (a-c)*(a-c)*(a-c) )/((b-a)*(b-c))
    integral += fc * ( (a-c)*(a-3*b+2*c) )/((b-c))
  end

  return integral/6.0

end

########################################################################################################################

# Input :
# [a,b] - przedzial calkowania
# f - lista wartosci funkcji f w punktach rownoodlegych a, a+h, a+2h, ..., b-h, b

# Output : Przyblizona wartosc calki oznaczonej na przedziale [a, b]

function simpson_method_equal_length(a::Float64, b::Float64, f)
  integral = zero(Float64)

  n = (length(f)-1) >> 1
  h = (b-a)/(2*n)

  for j = 1:n
    integral += f[2*j-2+1] + 4*f[2*j-1+1] + f[2*j+1]
  end

  integral *= h/3.0
  return integral
end
