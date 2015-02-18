      addi $t1,    $s0,    400
LOOP: lw   $s1,    0($s0)
      add  $s2,    $s2,    $s1
      lw   $s1,    4($s0)
      add  $s2,    $s2,    $s1
      addi $s0,    $s0,    8
      bne  $t1,    $s0,    LOOP

# the same in C

# extern int32_t result;
# extern int32_t *memarray;
# int i;
# for(i = 0; i < 100; i++)
#	result += memarray[i];
