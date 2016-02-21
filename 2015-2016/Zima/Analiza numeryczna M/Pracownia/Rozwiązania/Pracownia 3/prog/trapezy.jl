# Bartosz Jan Bednarczyk (273 479)
# Analiza numeryczna (M) - Pracownia nr 3 - zadanie P3.9
# Obliczanie calki zlozona metoda trapezow

########################################################################################################################

# Input : lista par liczb rzeczywistych postaci (x, f(x))
# Output : Przyblizona wartosc calki oznaczonej na przedziale x[0], x[n]

function trapeze_method(points)
  integral = zero(Float64)

  for i = 2 : length(points)
    integral = integral + (first(points[i]) - first(points[i-1])) * (last(points[i-1]) + last(points[i]))
  end

  integral = integral / 2.0
  return integral
end

########################################################################################################################

# Input :
# [a,b] - przedzial calkowania
# f - lista wartosci funkcji f w punktach rownoodlegych a, a+h, a+2h, ..., b-h, b

# Output : Przyblizona wartosc calki oznaczonej na przedziale [a,b]

function trapeze_method_equal_length(a::Float64, b::Float64, f :: Array{Float64})
  integral = zero(Float64) + f[1] + f[length(f)]

  for i = 2 : (length(f) - 1)
    integral = integral + 2.0 * f[i]
  end
    integral = integral * ( (b-a) / (2.0 *(length(f)-1)) )

  return integral
end
