.data
rozmiar: .word 11
wektor: .word 213, 224, 235, 246, 257, 268, 279, 290, 301, 

312, 323
suma1: .word 0
suma2: .word 0
stala: .word 26
roznica: .word 0
iloczyn: .word 0




.text

main:
	LW R1, rozmiar(r0)
	addi R2, R0, wektor
	addi R3, R0, 0 
	addi R4, R0, 0
			
loop_suma1:
	BEQZ R1, loop_suma1_finish
	lw R5, 0(R2)
	add R4, R4, R5
	addi R2, R2, 4
	sub R1, R1, 1
	j loop_suma1

loop_suma1_finish:
	sw suma1, R4 

	addi R1, R0, 11
	addi R2, R0, wektor
	addi R3, R0, 0 
	addi R4, R0, 0
	LW R6, stala(R0)
loop_suma2:
	BEQZ R1, loop_suma2_finish
	LW R5, 0(R2)
	add R5, R5, R6
	SW 0(R2), R5
	add R13, R13, R5
	addi R2, R2, 4
	sub R1, R1, 1
	j loop_suma2	


loop_suma2_finish:
	SW suma2, R13 
	sub R13, R13, R4
	SW roznica, R13
	
	


trap 0
