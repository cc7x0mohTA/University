# Bartosz Bednarczyk, zadanie 3

	# t6 = 1
	# war1, war2, war3 = t3, f4, f5
	# t2 = wynik
	# t1 = czylitera
	# t0 = kolejne znaki pliku

		.data

plik:	.asciiz "plik.txt"
noFile:	.asciiz  "Nie znaleziono pliku docelowego."
result:	.asciiz  "Liczba niepustych linii to: "
buffor:	.space   1 # Buffor, do ktorego bedziemy czytac znak po znaku

		.text
		
	li $t8 10	# t8 = 10
	li $t7 32	# t7 = 32
	li $t6 1	# t6 = 1
		
	li $v0, 13
	la $a0, plik
	li $a1, 0 # Flaga: czytaj plik
	li $a2, 0
	li $s0, 0 # Licznik linii
	syscall
	bltz $v0, error # $v0 zwraca -1 jesli nie znaleziono pliku
	move $a0, $v0
	la $a1, buffor
	li $a2, 1


loop:

	li $v0, 14		
	syscall
	beqz $v0, end # Jesli $v0 = 0, to nie ma juz w pliku zadnych znakow
	lb $t0, buffor	

	war1:
	
		beq $t0, $t8, war1true
		j war1false
	
	war1true:	# t3 = 1
	
		li $t3, 1
		j outwar1
		
	war1false:	# t3 = 0
	
		li $t3, 0
		j outwar1
	
	outwar1:
	
	war2:
	
		beq $t1, $t6, war2true
		j war2false
	
	war2true:
	
		li $t4, 1
		j outwar2
	
	war2false:
	
		li $t4, 0
		j outwar2
	
	outwar2:
	
	and $t5, $t4, $t3
	
	war3:
	
	bne $t5, $t6, outwar3
	
		add $t2, $t2, $t6
		li $t1, 0
	
	outwar3:
	
	war4:
	
	ble $t0, $t7, outwar4
	
	li $t1 1
	
	outwar4:
	
		add $s0, $s0, $t6
		j loop	
		
error:

li $v0, 4
la $a0, noFile
syscall
j end2


end:

bne $t1, $t6, print
add $t2, $t2, $t6

print:

li $v0, 4
la $a0, result
syscall
li $v0, 1
move $a0, $t2
syscall
j end2

end2: 

move $v0, $t2
