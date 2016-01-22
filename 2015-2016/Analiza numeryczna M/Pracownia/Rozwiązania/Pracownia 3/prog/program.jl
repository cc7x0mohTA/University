# Bartosz Jan Bednarczyk (273 479)
# Analiza numeryczna (M) - Pracownia nr 3 - zadanie P3.9
# Testy numeryczne

include("trapezy.jl")
include("simpson.jl")

function generate_equal_length_points(a::Float64, b::Float64, n::Int64, f::Function)
  h = Float64(abs(b-a)/n)
  return [Float64(f(a+h*i)) for i in 0:n]
end

# tylko dla n >= 2
function generate_random_points(a::Float64, b::Float64, n::Int64, f::Function)
  L = [(0.0,0.0) for i in 1:n]
  L[1] = (a, f(a))
  L[n] = (b, f(b))
  for i in 2:(n-1)
    randX = Float64(rand() * (b-a) + a)
    L[i] = (randX, f(randX))
  end
  return sort(L)
end




function single_test(a::Float64, b::Float64, f::Function)
  @printf("QUADGK : int_a^b f dx = %.12lf\n", first(quadgk(f, a, b)))

  @printf("\nSIMPSON\n")

  for i in 1:25
      @printf("SIMPSON ROWNOODLEGLE dla %d wezlow : dokladnosc = %d : wynik %lf\n", 2*i,
              -log(abs(first(quadgk(f, a, b))-simpson_method_equal_length(a,b,generate_equal_length_points(a,b,2*i,f)))),
              simpson_method_equal_length(a,b,generate_equal_length_points(a,b,2*i,f)))
  end

  @printf("\nTRAPEZY\n")

    for i in 1:25
      @printf("TRAPEZY ROWNOODLEGLE dla %d wezlow : dokladnosc = %d : wynik = %lf \n", 2*i,
              floor(-log(abs(first(quadgk(f, a, b))-trapeze_method_equal_length(a,b,generate_equal_length_points(a,b,2*i,f))))),
              trapeze_method_equal_length(a,b,generate_equal_length_points(a,b,2*i,f)))
  end

  @printf("\nLOSOWE\n")

  for i in 1:100
    LOS = generate_random_points(a,b, 2*i, f)
    @printf("DOKLADNOSC TRAPEZOW : %d, DOKLADNOSC SIMPSONA %d\n",
            floor(-log(abs(first(quadgk(f, a, b))-trapeze_method(LOS)))),
            floor(-log(abs(first(quadgk(f, a, b))-simpson_method(LOS)))))
  end
end

function single_test_print(a::Float64, b::Float64, f::Function)
  @printf("QUADGK : int_a^b f dx = %.12lf\n", first(quadgk(f, a, b)))

  @printf("\nSIMPSON\n")

  for i in 1:25
      @printf("%d\t%d\n", 2*i,
              -log(abs(first(quadgk(f, a, b))-simpson_method_equal_length(a,b,generate_equal_length_points(a,b,2*i,f)))))
  end

  @printf("\nTRAPEZY\n")

    for i in 1:25
      @printf("%d\t%d\n", 2*i,
              floor(-log(abs(first(quadgk(f, a, b))-trapeze_method_equal_length(a,b,generate_equal_length_points(a,b,2*i,f))))))
    end

  @printf("\nLOSOWE\n")

  for i in 1:100
    LOS = generate_random_points(a,b, 2*i, f)
    @printf("%d\t%d\t%d\n", 2*i,
            floor(-log(abs(first(quadgk(f, a, b))-trapeze_method(LOS)))),
            floor(-log(abs(first(quadgk(f, a, b))-simpson_method(LOS)))))
  end
end

function test()
  @printf("\nTEST 1 x -> 7*x^5 + 2*x^4 + 3*x^3 - 12* - 2 na [-1,1]\n")
  single_test(-1.0, 1.0, x -> 7*x^5 + 2*x^4 + 3*x^3 - 12* - 2)
  @printf("\nTEST 2 x -> sin(x^2) - cos(sin(x)) + 1 na [-1,1]\n")
  single_test(-1.0, 1.0, x -> sin(x^2) - cos(sin(x)) + 1)
  @printf("\nTEST 3 x -> 1/(1+25*x^2) na [-1,1]")
  single_test(-1.0, 1.0, x -> 1/(1+25*x^2))
  @printf("\nTEST 4 x -> -x^2 + 5 ma [0,10]\n")
  single_test(0.0, 10.0, x -> -x^2 + 5)
  @printf("\nTEST 5 x -> 1/(1-x-x^2) na [-1, 0.5]\n")
  single_test(-1.0, 0.5, x -> 1/(1-x-x^2))
  @printf("\nTEST 6 x -> 7*x^5 + 2*x^4 + 3*x^3 - 12* - 2")
  single_test(-1.0, 1.0, x -> exp(x^7) + cos(2*x) + atan(5*x))
end

function test_print()
  @printf("\nTEST 1 x -> 7*x^5 + 2*x^4 + 3*x^3 - 12* - 2 na [-1,1]\n")
  single_test_print(-1.0, 1.0, x -> 7*x^5 + 2*x^4 + 3*x^3 - 12* - 2)
  @printf("\nTEST 2 x -> sin(x^2) - cos(sin(x)) + 1 na [-1,1]\n")
  single_test_print(-1.0, 1.0, x -> sin(x^2) - cos(sin(x)) + 1)
  @printf("\nTEST 3 x -> 1/(1+25*x^2) na [-1,1]")
  single_test_print(-1.0, 1.0, x -> 1/(1+25*x^2))
  @printf("\nTEST 4 x -> -x^2 + 5 ma [0,10]\n")
  single_test_print(0.0, 10.0, x -> -x^2 + 5)
  @printf("\nTEST 5 x -> 1/(1-x-x^2) na [-1, 0.5]\n")
  single_test_print(-1.0, 0.5, x -> 1/(1-x-x^2))
  @printf("\nTEST 6 x -> 7*x^5 + 2*x^4 + 3*x^3 - 12* - 2")
  single_test_print(-1.0, 1.0, x -> exp(x^7) + cos(2*x) + atan(5*x))
end

test_print()
