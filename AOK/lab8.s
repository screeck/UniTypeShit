.data
T: .space 1040
TB: .space 840
Suma: .double 0.0
Rozmiar: .word 105
Skladnik: .double 1550
nr: .double 13
ulamek: .double 0.55
one: .double 1.0
stala: .double 5.2

.text
addi r1, r0, T       
addi r2, r0, 130     
addi r3, r0, 0       
ld f2, Skladnik
ld f4, ulamek
ld f8, nr
ld f10, one

addd f6, f2, f4      
addd f6, f6, f8      

loop_T_start:
    beqz r2, loop_T_end
    sd 0(r1), f6
    addd f6, f6, f10
    addi r1, r1, 8
    subi r2, r2, 1
    j loop_T_start

loop_T_end:

addi r1, r0, T       
addi r2, r0, TB      
lw r3, Rozmiar       
ld f14, stala

loop_TB_start:
    beqz r3, loop_TB_end
    ; T[i]
	ld f2, 0(r1)
	; TB[i]
	;ld f4, 0(r2)
	; T[i+1]
	ld f6, 8(r1)
	; T[i+2]
	ld f8, 16(r1)
	; T[i+3]
	ld f10, 24(r1)
	; T[i+4]
	ld f12, 32(r1)
	; T[i+5]
	ld f24, 40(r1)
	; T[i+6]
	ld f22, 48(r1)

	multd f16, f2, f14  
 
    	multd f16, f16, f6
	multd f16, f16, f22
	addd f18, f8, f10
	addd f18, f18, f12
	subd f16, f16, f18
	divd f16, f16, f24
	addd f20, f20, f16
	sd 0(r2), f16
	addi r1, r1, #8
	addi r2, r2, #8
	subi r3, r3, #1
    	j loop_TB_start

loop_TB_end:

	sd Suma, f20

trap 0
