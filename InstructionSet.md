# Instruction Set Draft 2#

## Key ##
* WREG: Register to write to
* RREG: Register to read from
* CONST: Binary constant (8 bits)
* CONST6: Binary constant (6 bits)
* RAM: RAM address in 8 bits

## Registers ##

Substitute appropreate register everywhere you see WREG (write register) and RREG (read register)

Register | WREG (Write) | RREG (Read) 
--- | ---- | ---
A | 0001 | 010
B | 0010 | 001
C | 0100 | 011
D | 1000 | 100

## Commands ## 
Command | Binary | Description
------- | ---------------------------------- | ---- 
MOV [WREG] [RREG] | 000 000 [WREG] [RREG] 000 000 00000000 | Move contents of B to A
LD [WREG] RAM | 000 000 [WREG] [RREG] 000 000 00000000 | Move contents of B to A

