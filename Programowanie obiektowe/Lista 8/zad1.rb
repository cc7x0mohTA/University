class Fixnum

	def prime?
		n = self
		return false if n < 2
		for i in 2...n
			return false if n % i == 0
		end
		return true
	end

	def ack(y)
		return y+1 if self == 0
		return (self - 1).ack(1) if y == 0
		return (self-1).ack(self.ack(y-1))
	end

	def doskonala?
	
		s = 0
		for i in 1...(self-1)
			s = s + i if self % i == 0
		end
		
		return true if s == self
		return false
	end

	Cyfry = ["zero", "jeden", "dwa", "trzy", "cztery", "piec", "szesc", "siedem", "osiem", "dziewiec"]

	def slownie
		return "" if self == 0
		a = self % 10
		b = self / 10
		return "" + b.slownie + Cyfry[a] + " "
	end

end

puts 7.prime?
puts 53321.prime?
puts 8.prime?

puts 6.doskonala?
puts 28.doskonala?
puts 32.doskonala?

puts 123.slownie 
