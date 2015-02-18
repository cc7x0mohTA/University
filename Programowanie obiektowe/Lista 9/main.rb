
class Proc

	def value(x)
		self.call(x)
	end

	def f_root(a, b, eps)
		x = (a+b)/2.0
		val = value(x)

		if val >= -eps and val <= eps
			return x
		else
			left = value(a)
			rigth = value(b)

			if left < 0 and val > 0
				return f_root(a,x,eps)
			elsif left > 0 and val < 0
				return f_root(a,x,eps)
			elsif rigth > 0 and val < 0
				return f_root(x,b,eps)
			elsif rigth < 0 and val > 0
				return f_root(x,b,eps)
			elsif value == 0 
				return x
			else
				nil
			end
		end
	end

	def derivative(x)
		h = 0.00000000001
		return (0.0+value(x+h)-value(x))/h
	end

	def integral(a, b)
			
		sn = 0.0
		n = 1000
		h = (b-a)/n
	
		for i in 1..n
			yi = value(a + (i-1)*h)
			yi /= 2 if i == 1 or i == n
			sn += h*yi
		end

		return sn
	end

   def plot(a, b, nazwa)

        file = File.open(nazwa, "w")
        file.puts "%!PS"
        
        x = 400
        y = 200
        
        dx = (b - a) / x.to_f
        h = y / 2
        
        file.puts "0 " + (value(a) + h).to_s + " moveto"
       
	for i in 1..x
            file.puts i.to_s + " " + (value(a + i * dx) + h).to_s + " lineto"
        end
        
        file.puts "stroke"
        file.puts "showpage"
        
        file.close
    end

end

puts "Niech f(x) = x^3 - 2x*cos(x) -1"
f = proc { |x| x*x*x - 2 * x * Math.cos(x) -1 }


puts "f(1) = ", f.value(1)
puts "miejsce zerowe na [-2,2] : ", f.f_root(-2, 2.0, 0.000000001)
puts "pochodna w punkcie 3", f.derivative(3)
puts "pole pod wykresem na przedziale [-1, 1] : ", f.integral(-1.0, 1.0)

f.plot(-10.0, 10.0, "plik.PS")
