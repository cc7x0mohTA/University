M = 10
eps = Float64(1e-16)

function muller(a)
  x0 = Complex(Float64(0))
  n = length(a) - 1

  if n<1 
    return
  end

  for step in 1:M
    p0 = p1 = p2 = Complex(Float64(0))

    for _j in 0:n
      i = n - _j
      p2 = x0*p2 + p1         # p2 - 1/2 f''(x)
      p1 = x0*p1 + p0         # p1 - f'(x)
      p0 = x0*p0 + a[i+1]     # p0 - f(x)  
    end



    if abs(p0) <= eps
      break
    end
    c = (real(p1)>=eps ? 1.0 : -1.0)
    d = (p0*2.0)/(p1 + c*sqrt(p1*p1 - 4.0*p0*p2))
    x0 -= d
    if abs(d) <= eps
      break
    end

  end
  println(x0)
  return muller(horner(a, x0))
end

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

