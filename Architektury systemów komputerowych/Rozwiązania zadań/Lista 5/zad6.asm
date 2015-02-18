#C = A*A
#A > 0
#X = 1
#I - iterator
#B - tymczasowa wartość 

      SBN B B 10   ; C = 0
10:   SBN I I 20   ; I = 0
20:   SBN Z Z 30   ; Z = 0
30:   SBN Z A 40   ; Z = -A
40:   SBN I Z 50   ; I = 0 - -A = A
50:   SBN I X loop ; I = A - 1 (bo odliczamy do -1, nie 0)
loop: SBN B A 80   ; B -= A
80:   SBN I X end  ; if(I-- < 0) goto end
      SBN P P 90   ; P = 0
90:   SBN P X loop ; goto loop
end:  SBN C C 100  ; C = 0
100:  SBN C B 110  ; C = A*A
