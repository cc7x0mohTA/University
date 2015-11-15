# funkcja obliczająca wspolczynniki wielomianu na podstawie miejsc zerowych
function wielomian(a) 
  a = map(x -> -parse(BigFloat, string(x)), a)
  n = length(a); s = copy(a); w = Array(typeof(a[1]), n + 1)
  w[n+1]=1 ; w[n]=sum(a)

  i=n-1
  while i>0
    wynik = Complex(BigFloat(0))
    p = s[i+1]
    j = i
    while j>0
      k = p + s[j]
      wynik += s[j] = a[j]*p
      p = k
      j -= 1
    end
    w[i]=wynik
    i-=1
  end
 return w
end


#funkcja losujaca pierwiastki typu BigFloat
function los(n)
  prec = get_bigfloat_precision()
  set_bigfloat_precision(1024)
  s = Array(BigFloat, 0)
  for i in 1:n
    a = parse(BigFloat, string(rand(Float64)))
    b = rand(Float64)
    c = rand(Float64)
    push!(s, parse(BigFloat, @sprintf("%.30f", rand([-1,-1,1,1,1,-1,1,-1])*a*b*c)))
  end

  return s
end

#funkcja losujaca pierwiastki typu Int
function los2(n)
  s = Array(Int, 0)
  for i in 1:n
    a = rand(-10:10)
    push!(s, a)
  end

  return s
end

#funkcja zapisujaca wspolczynniki i pierwiastki wielomianu do pliku
function toFile(name::ASCIIString, n, k)
  fin = open("testy/"*name*".in", "w")
  fout = open("testy/"*name*".out", "w")

  for i in 1:n
    s = sort(los(k))
    #s = sort(los2(k))
    write(fout, map(x->string(x)*" ", s), "\n")
    write(fin, map(x->string(x)*" ", wielomian(s)), "\n")
    #write(fin, map(x->@sprintf("%d ", x), wielomian(s)), "\n")
  end
  close(fin)
  close(fout)
end


#funkcja wczytujaca wspolczynniki i pierwiastki z pliku
function getData(name::ASCIIString)

  fin = open("testy/"*name*".in")
  fout = open("testy/"*name*".out")
  a = Array(Array{BigFloat}, 0)
  w = Array(Array{BigFloat}, 0)

  for ln in eachline(fin)
    push!(a, strb(ln))
  end
  for ln in eachline(fout)
    push!(w, strb(ln))
  end
  close(fin)
  close(fout)
  return tuple(a, w)
end


#funkcja do obliczenia srednich bledow bezwzglednych pierwiastkow otrzymanych przez metody
function test(data, N)

  a = data[1]
  w = data[2]
  out = Array(Tuple, 0)
  for ii in eachindex(a)
    L = lagguerre(a[ii], N)
    B = bairstow(a[ii], 0, 0, N)
    M = muller(a[ii], N)
    oL = oB = oM = -typemax(Int)

    for i in 1:length(L)
      dL = dB = dM = typemax(BigFloat)
      for j in 1:length(L)
        dL = min(dL, abs(real(L[i])-w[ii][j]))
        dB = min(dB, abs(real(B[i])-w[ii][j]))
        dM = min(dM, abs(real(M[i])-w[ii][j]))
      end
      oL = max(oL, round(Int, log10(dL+EPS)))
      oM = max(oM, round(Int, log10(dM+EPS)))
      oB = max(oB, round(Int, log10(dB+EPS)))
     
    end
    push!(out, tuple(oL, oM, oB))
  end
  return out;
end

#funkcja tworzaca tabele bledow srednich
function toTable(name::ASCIIString, p, q)
  f = open(name*".wykres", "w")
  set_bigfloat_precision(1024)
  write(f, "Test: "*name*"\n")
  write(f, @sprintf(" \tLagguerre\tMuller\tBairstow\n"))
  @printf(" \tLagguerre\tMuller\tBairstow\n")
  data = getData(name)
  for i in p:q
    oL = oM = oB = 0
    g = test(data, i)
    for j in eachindex(g)
      oL+=g[j][1]
      oM+=g[j][2]
      oB+=g[j][3]
    end
    oL = oL / length(g)
    oB = oB / length(g)
    oM = oM / length(g)
    @printf("%d\t%f\t%f\t%f\n", i, -oL, -oM, -oB)
    write(f, @sprintf("%d\t%f\t%f\t%f\n", i, -oL, -oM, -oB))
  end
  close(f)
end

function wykresy()
  set_bigfloat_precision(1024)
  toTable("testFloat", 1, 30)
  toTable("testFloat2", 1, 30)
  toTable("testFloat3", 1, 30)
  toTable("testInt", 1, 50)
  toTable("testInt2", 1, 50)
  toTable("testInt3", 1, 50)
end


#funkcja do przyjaznego testowania metody bairstowa
function testBairstow(a::ASCIIString, u::Int, v::Int, p::Int, q::Int)
  set_bigfloat_precision(1024)
  for i in p:q
    @printf("Iteracja: %d\n", i)
    s = bairstow(a, u, v, i)
    for j in eachindex(s)
      @printf("%.30f, %.30fi\n", real(s[j]), imag(s[j]))
    end

  end
end

function testBairstow(a::ASCIIString, u::Int, v::Int, M::Int)
    testBairstow(a, u, v, M, M)
end

#funkcja do przyjaznego testowania wszystkich metod rownoczesnie
function testAll(a::ASCIIString, u::Int, v::Int, p::Int, q::Int)
  set_bigfloat_precision(1024)
  for i in p:q
    B = bairstow(a, u, v, i)
    L = lagguerre(a, i)
    M = muller(a, i)
    @printf("\n#############################################\nIteracja: %d\n", i)
    @printf("\nLagguerre: \n")
    for j in eachindex(L)
      @printf("%.30f, %.30fi\n", real(L[j]), imag(L[j]))
    end
    @printf("\nMuller: \n")
    for j in eachindex(M)
      @printf("%.30f, %.30fi\n", real(M[j]), imag(M[j]))
    end
    @printf("\nBairstow: \n")
    for j in eachindex(B)
      @printf("%.30f, %.30fi\n", real(B[j]), imag(B[j]))
    end
    @printf("\n#############################################\n")
  end
end

function testAll(a::ASCIIString, u::Int, v::Int, M::Int)
  testAll(a, u, v, M, M)
end





