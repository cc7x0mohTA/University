# Bartosz Bednarczyk - zad 5

poczatek:

# s1 = h, s2 = i, s3 = l, s4 = o, s5 = kropka, s6 = puste

li $s1 116
li $s2 16
li $s3 48
li $s4 92
li $s5 128
li $s6 0

losuj:	# losowanie inta z przedzialu [0,255]

	li $a1, 256	# koniec przdzialu + 1
	li $v0, 42	# 42 - random int range
	syscall
	move $s0 $a0	# przenieś wyynik losowanie do s0
	
# s0 - wylosowana liczba
# t7 - liczba losowan
# t6 = 1

gra:
	li $t7 7	# liczba losowan
	li $t6 1	# t6 = 1
	
	li $t3 4294901776  # rejestr prawego wyswietlacza
	li $t4 4294901777  # rejestr lewego wyswietlacza
	
	petla:
		blt $t7 $zero koniecpetli	# jezeli nie mozna juz losowac
		
		li $v0, 5	# read_int
		syscall

		beq $s0 $v0 koniecpetli	# jak zgadlismy to skocz do koniecpetli
		
		blt $v0 $s0 lo # jak mniejsza skocz do lo
		# jak wieksza to idziemy do hi
	
		hi:	# jezeli nasza liczba jest za duza
		
			sb $s1, 0($t4)	# ustaw na h
			sb $s2, 0($t3)	# ustaw na i
			j dalej
		
		lo:	# jezeli nasza liczba jest za mala
		
			sb $s3, 0($t4)	# ustaw na l
			sb $s4, 0($t3)	# ustaw na o
		
		dalej:

			sub $t7 $t7 $t6	# t7--
			j petla
	
	koniecpetli:
	
		li $t7 5
	
		migajacakropka:
		
			beqz $t7 konieckropki
		
			sb $s5, 0($t3)	# ustaw kropke
			sb $s5, 0($t4)
			
			li $a0, 666 # spleep 666ms
			li $v0 32
			syscall
		
			sb $s6, 0($t3)	# ustaw na puste
			sb $s6, 0($t4)
		
		
			li $a0, 666 # spleep 666ms
			li $v0 32
			syscall
			
			sub $t7 $t7 $t6	# t7--
			j migajacakropka
		
		konieckropki:
		
		j poczatek