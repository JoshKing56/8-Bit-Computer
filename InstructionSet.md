# Instruction Set Draft #

---

Command Number | Command | Argument | Argument | Argument | Description
--- | ---- | --- | -------- | ------- | -----------|
1   |  LD  |    A     | Constant |         | Loads constant to A (register)
2   |  LD  |    A     |    B     |         | Loads B to A (registers)
3   |  LD  |   RAM    |    B     |         | Loads B (register) to RAM
4   |  LD  |    A     |   RAM    |         | Loads RAM to A (Register)
5   |  LD  |    A     |  Input   |         | Loads register to input
6   |  ADD |    A     |    B     |    C    | Adds B to A and stores in C
7   |  ADD |    A     | Constant |    C    | Adds Constant to A and stores in C
8   |  SUB |    A     |    B     |    C    | Subtracts A from B (B-A) and stores in C
9   |  SUB |    A     | Constant |    C    | Subtracts Constant from A and stores in C
10  |  AND |    A     |    B     |    C    | ANDs A and B and stores in C
11  |  AND |    A     | Constant |    C    | ANDs A and Constant and stores in C
12  |  OR  |    A     |    B     |    C    | ORs A and B and stores in C
13  |  OR  |    A     | Constant |    C    | ORs A and Constant and stores in C
14  |  GR  |    A     |    B     |    C    | Checks if B is greater than A (B>A), stores in C
15  |  GR  |    A     | Constant |    C    | Checks if constant is greater than A (Const>A), stores in C
16  |  GEQ |    A     |    B     |    C    | Checks if B is greater than or equal to A (B>A), stores in C
17  |  GEQ |    A     | Constant |    C    | Checks if B is greater than or equal to constant (Const>A), stores in C
18  |  EQ  |    A     |    B     |    C    | Checks if B=0, store in C
19  |  EQ  |    A     | Constant |    C    | Checks if A=Constant, store in C
20  |  JZ  |    A     |    0     | ADDRESS | Jumps to Address if A=0
21  |  PCL | Constant |          |         | Loads constant to PC and jumps (Lower byte)
22  |  PCU | Constant |          |         | Loads constant to PC and jumps (Lower byte)
23  |  LDI |          |          |         | Loads interrupt to PC and jumps
24  |  NOP |          |          |         | No Operation
