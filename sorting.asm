CLR
LD A 6      ;;Init Load array {6, 99, 36, 66, 24, 30, 46, 26, 86, 54, 75}
LD &0 A
LD A 99
LD &1 A
LD A 36
LD &2 A
LD A 66
LD &3 A
LD A 24
LD &4 A
LD A 30
LD &5 A
LD A 46
LD &6 A
LD A 26
LD &7 A
LD A 86
LD &8 A
LD A 54
LD &9 A
LD A 75
LD &10 A        ;;Done loading
LD C 0
LD D 1
LD A 0          ;;NotSorted
LD &15 A
LD A &C         ;;NextPair
LD B &D
GR A B A
PCU 0      ;;Jump to NoSwap
JNZ A 38    ;;Jump to NoSwap
LD A &D
LD B &C
LD &C A
LD &D B
LD A 1
LD &15 A
EQ A D 10       ;;NoSwap
PCU 0           ;;Jump to EOArray
JNZ A 45        ;;Jump to EOArray
LD C D
ADD D D 1
PCU 0           ;;Jump to NextPair
PCL 27          ;;Jump to NextPair
LD A &15        ;;EOArray
PCU 0           ;;Jump Not Sorted
JNZ A 25        ;;Jump Not Sorted
PCU 0
PCL 49 ;;Jump to self
