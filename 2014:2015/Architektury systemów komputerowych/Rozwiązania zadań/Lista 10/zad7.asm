.macro seb (%rd, %rs)	# to proste - wystarczy przesunąć w lewo o 24 a potem cofnąć w prawo 
	sll %rd,%rs, 24	
	sra %rd, %rd, 24
.end_macro

# dodatkowe makro, napisałem by nie pisać dwa razy tego samego - przesuwa bity
# wyzerowuje pierwsze p bitów 
.macro shiftv (%rd) (%rs) (%p)	
	srlv %rd %rs %p 
	sllv %rd %rd %p 
	sub %rd %rs %rd
.end_macro
.macro shift (%rd) (%rs) (%p)	
	srl %rd %rs %p 
	sll %rd %rd %p 
	sub %rd %rs %rd
.end_macro

#ext rd, rs, p, s: Extract s bits from rs from position p and put into rd

.macro ext (%rd) (%rs) (%p) (%s)
	addi $at $zero %p
	addi $at $at %s
	shiftv %rd %rs $at
	srl %rd %rd %s
.end_macro

# ins rd, rs, p, s: Insert first s bits of rs into rd, from position p
# robię tak że rd to jest wartość której przypisuje

.macro ins (%rd) (%rs) (%p) (%s) # to samo co ext tylko s i p zamienione miejscem
	shift %rd %rs %s
	sll %rd %rd %p
.end_macro

#addi $t1 $zero 0x11223344
#ext $t2 $t1 8 8

addi $t1 $zero 0x0000000a
addi $t2 $zero 0x000000e7
ins $t1 $t2 4 8
