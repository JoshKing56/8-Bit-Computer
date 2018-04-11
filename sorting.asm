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
LD A 0          ;;Start
LD &15 A
LD C 0
LD D 1
LD A *C
LD B *D
GR A B A        ;;Swap
PCU NoSwap      ;;TODO: Fill
JNZ A Noswap    ;;TODO: Fill
LD A *D
LD B *C
LD &C A
LD &D B
LD A 1
LD &19 A
EQ A D 30       ;;EOArray
PCU Esc         ;;TODO: Fill
JNZ A Esc       ;;TODO: Fill
LD C D
ADD D D 1
LD A *C
LD B *D
PCU Swap        ;;TODO: Fill
PCU Swap        ;;TODO: Fill
LD A &19
PCU Start       ;;TODO: Fill
JNZ A Start     ;;TODO: Fill
