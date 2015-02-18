# Bartosz Bednarczyk - zad 2

# spis rejestrów
# $f1 = a
# $f2 = eps
# $f3 = x_n
# $f4 = x_(n+1)
# $f5 = 2.0

# Jak to działa?

#scanf("%d", &a);
#scanf("%d", &eps);
#xn1 = a;
#loop:
#xn = xn1;
#xn1 = xn;
#xn1 += a/xn;
#xn1 /= 2;
#pom = abs(xn-xn1);
#if(! eps <= pom) goto loop;
#printf("%d", xn1);

# Wczytujemy a

li $v0 6 # wczytaj do v0 liczbe 6 - 6 znaczy read_float
syscall	# wywolaj operacje z systemu
# teraz mamy flołta w $f0 w coproc 1
mov.s $f1 $f0	# ustawiamy $f1 na 'a'

# Wczytujemy eps i ustawiamy rejestr $f2 na eps

li $v0 6 # wczytaj do v0 liczbe 6 - 6 znaczy read_float
syscall	# wywolaj operacje z systemu
# teraz mamy flołta w $f0 w coproc 1
mov.s $f2 $f0	# ustawiamy $f1 na 'a'

mov.s $f4 $f1	# x_(n+1) = a

petla:

mov.s $f3 $f4	# xn := xn+1 (poczatkowo oba rowne a)

div.s $f5 $f1 $f3 # $f5 = a / xn 

# potrzebujemy umiec podzielic przez 2

li $t0 2	# wczytaj 2 do $t0
mtc1 $t0 $f6	# przenieś $t0 do $f6 (move to coprocessor 1)
cvt.s.w $f6 $f6	# przekonwertuj na IEEE764 - Internet Explorer Enterprise Edition 754r

add.s $f4 $f3 $f5	# f4 = xn + a/xn
div.s $f4 $f4 $f6	# xn+1 /= 2

sub.s $f7 $f3 $f4	# f6 = x_n - x_(n+1)
abs.s $f7 $f7		# f7 = abs(f7)

c.le.s $f7 $f2 # eps <= abs(x_n+1 - xn) - wynik zapisuje do flag 0
bc1f petla	# jesli nie to skocz do petlla

mov.s $f12 $f4	# zapis x_n+1 do f12  bo stamtad się wypisuje
li $v0 2	# 2 - print_float
syscall