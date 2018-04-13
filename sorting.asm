CLR
LD A 15      ;;Init Load array {15,63,7,255,1,127,3,31}
LD &0 A
LD A 63
LD &1 A
LD A 7
LD &2 A
LD A 255
LD &3 A
LD A 1
LD &4 A
LD A 127
LD &5 A
LD A 3
LD &6 A
LD A 31
LD &7 A         ;;Done loading
LD A 0          ;;NotSorted
LD &15 A
LD C 0
LD D 1
LD A &C         ;;NextPair
LD B &D
GR A B A
PCU 0           ;;Jump to NoSwap
JNZ A 32        ;;Jump to NoSwap
LD A &D
LD B &C
LD &C A
LD &D B
LD A 1
LD &15 A
EQ A D 7        ;;NoSwap
PCU 0           ;;Jump to EOArray
JNZ A 39        ;;Jump to EOArray
LD C D
ADD D D 1
PCU 0           ;;Jump to NextPair
PCL 21          ;;Jump to NextPair
LD A &15        ;;EOArray
PCU 0           ;;Jump Not Sorted
JNZ A 17        ;;Jump Not Sorted
PCU 0
PCL 43 ;;Jump to self
