.data
TA: .space 560
TB: .space 520
Suma: .double 0


.text

addi R1, R0, 140
addi R2, R0, TA
addi R3, R0, 2200

TA_loop:
	BEQZ R1, TA_loop_finish
	LW R5, 0(r2)
	addi R5, R3, 13
	SW 0(R2), R5
	addi R3, R3, 1
	addi R2, R2, 4
	sub R1, R1, 1
	j TA_loop

TA_loop_finish:

addi R1, R0, 130
addi R2, R0, TA
addi R3, R0, TB
addi R4, R0, 6
addi R13, R0, 0
TB_loop:
	BEQZ R1, TB_loop_finish
	
	addi R5, R2, 20
	addi R6, R2, 8
	addi R7, R2, 4
	LW R14, 0(R5)
	LW R15, 0(R6)
	LW R16, 0(R7)
	add R8, R14, R15
	add R9, R8, R16
	
	mult R10, R9, R4
	
	add R13, R13, R10	

	SW 0(R3), R10
	addi R3, R3, 4
	addi R2, R2, 4
	sub R1, R1, 1
	j TB_loop

TB_loop_finish:

	SD Suma, R13
	

trap 0
