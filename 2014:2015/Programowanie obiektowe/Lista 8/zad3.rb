class Jawna

	def initialize(text)
		@text = text
	end

	def to_s
		@text
	end

	def zaszyfruj(klucz)

		pom = ""

		for i in 0..@text.length-1
			pom += (@text[i].ord + klucz).chr
		end

		return Zaszyfrowane.new(pom)

	end
end

class Zaszyfrowane

	def initialize(text)
		@text = text
	end

	def to_s
		@text
	end

	def odszyfruj(klucz)

		pom = ""

		for i in 0..@text.length-1
			pom += (@text[i].ord + klucz).chr
		end

		return Jawna.new(pom)
	end
end

lol = Jawna.new("abc")
puts lol
puts lol.zaszyfruj(3)

