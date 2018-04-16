LD A 15      ;;Init Load array {15,63,7,255,1,127,3,31}
LD &0 A
LD A 63
LD &1 A
LD A 7
LD &2 A
LD B &0
ADD C A B
LD D C
