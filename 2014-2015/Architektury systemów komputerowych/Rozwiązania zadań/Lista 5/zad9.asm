# A :

$t0 = 8
$zero = 0
$t1 = 9
$s3 = 19

add $d, $s, $t
000000 sssss ttttt ddddd 00000100000 
add $t0, $t0, $zero
000000 01000 00000 01000 00000100000

lw $t, offset($s)
100011 sssss ttttt iiiiiiii iiiiiiii 
lw $t1, 4($s3)
100011 10011 01001 00000000 00000100

# B :

0xAE0BFFFC = 10101110000010111111111111111100
sw $t, offset($s)
101011 sssss ttttt iiiiiiii iiiiiiii 
101011 10000 01011 11111111 11111100
sw $t3, -4($s0)

0x8D08FFC0 = 10001101000010001111111111000000
lw $t, offset($s)
100011 sssss ttttt iiiiiiii iiiiiiii
100011 01000 01000 11111111 11000000
lw $t0, -64($t0)


