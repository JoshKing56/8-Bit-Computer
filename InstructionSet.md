# Instruction Set Draft #

---

Command Number | Command | Argument | Argument | Argument | Description
--- | ---- | --- | -------- | ------- | -----------|
1   |  LD  |    A     | Constant |         | Loads constant to A (register)
2   |  LD  |    A     |    B     |         | Loads B to A (registers)
3   |  LD  |   RAM    |    B     |         | Loads B (register) to RAM (Address)
4   |  LD  |    A     |   RAM    |         | Loads RAM (Address) to A (Register)
5   |  LD  |    A     |  Input   |         | Loads register to input
6   |  LD  |   RAM    | Constant |         | Loads constant to RAM (Address) - this is for writing to the screen
7   |  ADD |    A     |    B     |    C    | Adds B to A and stores in C
8   |  ADD |    A     | Constant |    C    | Adds Constant to A and stores in C
9   |  SUB |    A     |    B     |    C    | Subtracts A from B (B-A) and stores in C
10  |  SUB |    A     | Constant |    C    | Subtracts Constant from A and stores in C
11  |  AND |    A     |    B     |    C    | ANDs A and B and stores in C
12  |  AND |    A     | Constant |    C    | ANDs A and Constant and stores in C
13  |  OR  |    A     |    B     |    C    | ORs A and B and stores in C
14  |  OR  |    A     | Constant |    C    | ORs A and Constant and stores in C
15  |  GR  |    A     |    B     |    C    | Checks if B is greater than A (B>A), stores in C
16  |  GR  |    A     | Constant |    C    | Checks if constant is greater than A (Const>A), stores in C
17  |  GEQ |    A     |    B     |    C    | Checks if B is greater than or equal to A (B>A), stores in C
18  |  GEQ |    A     | Constant |    C    | Checks if B is greater than or equal to constant (Const>A), stores in C
19  |  EQ  |    A     |    B     |    C    | Checks if B=0, store in C
20  |  EQ  |    A     | Constant |    C    | Checks if A=Constant, store in C
21  |  JZ  |    A     |    0     | ADDRESS | Jumps to Address if A=0
22  |  PCL | Constant |          |         | Loads constant to PC and jumps (Lower byte)
23  |  PCU | Constant |          |         | Loads constant to PC and jumps (Lower byte)
24  |  LDI |          |          |         | Loads interrupt to PC and jumps
25  |  NOP |          |          |         | No Operation
26  |  POP |          |          |         | Clears screen
