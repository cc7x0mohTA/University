# A: 

# if f > 1 then
#        g = f + f;
#        f = 0;
# endif;
#        g = g + 1;

$s0 = f
$s1 = g
      addi $s3, $zero, 1    ; $s3 = 1
      slt $s2, $s0, $s3     ; $s2 = (f < 1) ? 1 : 0
      bne $s2, $s3, end     ; if(!(f < 1)) goto end;
      add $s1, $zero, $zero ; g = 0
      add $s1, $s0, $s0     ; g = f + f
      add $s0, $zero, $zero ; f = 0
end:  addi $s1, $s1, 1      ; g++

# B:

# f = 1;
# while f < 10 do
#        f = f + 1;
# endwhile

$s0 = f
      addi $s3, $zero, 1    ; $s3 = 1
      addi $s4, $zero, 10   ; $s4 = 10 ; lol mips
      addi $s0, $zero, 1    ; $s0 = 1
      slt $s2, $s0, $s4     ; $s2 = (f < 10) ? 1 : 0
      bne $s2, $s3, end     ; if(!(f < 10)) goto end
loop:
      addi $s0, $s0, 1      ; f++
      slt $s2, $s0, $s4     ; $s2 = (f < 10) ? 1 : 0
      neq $s2, $s3, loop    ; if(f < 10) goto loop
end:

# C:

# g = 0;
# for f = 1 to 10 do
#        g := g + f;

$s0 = f
$s1 = g
      addi $s4, $zero, 11   ; $s4 = 11
      add $s1, $zero, $zero ; g = 0
      addi $s0, $zero, 1    ; f = 1
loop:
      add $s1, $s1, $s0     ; g += f
      addi $s0, $s0, 1      ; f++
      slt $s2, $s0, $s4     ; $s2 = (f < 11) ? 1 : 0
      neq $s2, $s3, loop    ; if(f < 11) goto loop
end:
