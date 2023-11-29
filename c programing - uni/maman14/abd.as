; file ps.as 
.entry LIST
.extern W
MAINy:	 add 	r3, LIST
MAINy:	 add 	r3, LIST
LOOP:	 prn	 #48
; ahfjanfjanjfanj


leaf		STR, r6
sub r1, r4
bne END
cmp val1, #-6
bne END[r9]
dec K
.entry MAIN
sub LOOP[r10] ,r14
END: stop
STR: .string "abcd"afa
LIST: .data 6, -9f
.data -100
.entry K
K: .data 31
.extern val1
