
$s0 = f
$s1 = g
$s2 = h
$s3 = &A[0]
$s4 = &B[0]

#g = -f + h + B[1];
sub $s7, $zero, $s0  ; $s7 = -f
add $s7, $s7, $s2    ; $s7 = -f + h
add $s1, $s7, 1($s4) ; g = $s7 + B[1]

#f = A[B[g]+1];
add  $s6, $s1, $s4   ; $s6 = &B[0] + g
lw   $s6, 0($s6)     ; $s6 = B[g]
addi $s6, $s6, 1     ; $s6 = B[g] + 1
add  $s6, $s6, $s3   ; $s6 = &A[0] + B[g] + 1
lw   $s0, 0($s6)     ; f = A[B[g]+1]
