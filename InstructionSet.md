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
MOV WREG RREG | Move contents of RREG to WREG | 000 000 [WREG] [RREG] 000 000 00000000
LD WREG RAM | Move contents of specified RAM block to RREG | 000 001 [WREG] [RREG] 000 000 00000000
SR RAM RREG | Store contents of RREG to specified RAM block | 000 010 0000 [RREG] 000 000 [RAM]
LD WREG CONST | Loads a constant to WWREG | 000 011 WREG 000 000 000 [CONST]
