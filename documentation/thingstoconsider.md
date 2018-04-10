# Things to consider #

## General ##
* ***TWO'S COMPLEMENT***
  * Probably the most important change we need to work on right now
  * Hardware shouldn't be that different, except for LSH and RSH
* [Arithmatic vs Logical `LSH`/`RSH`](https://en.wikipedia.org/wiki/Bitwise_operation#Bit_shifts)
  * Probably need to implement both, considering we should switch to two's complement 
* `LDNZ`, `LDZ`, `ADDNZ`, `ADDZ`, `SUBNZ`, `SUBZ`
  * On the list of things that could be good, but not necessary 
* Command to consider `JGR`/`JGEQ`/`JEQ` [`JAL`](http://www.mrc.uidaho.edu/mrc/people/jff/digital/MIPSir.html) 
  
## Hardware ##
* RAM timing
  * Timing of loading into RAM is critical
  * Timing in general is critical

## Compiler ##
* Rename LD commands to MOV, SB for the sake of convention
  * RAM --> Register: `LD` (Load)
  * Register --> RAM: `SB` (Store)
  * Register --> Register: `MOV` (Move) 
* 3 Things to consider:
  * Directives
    * Probably not gonna use but good to look into
  * Labels
    * 
  * <details>
      <summary> Pseudoinstructions </summary>
         <p>
           [Reference](https://en.wikibooks.org/wiki/MIPS_Assembly/Pseudoinstructions)
           Essentially pseudonyms for commands
           > MIPS example: There is no actual `LD A B` command in the hardware, instead you would use `ADD A B 0` This is really confusing and hard to understand. Hence, the compiler supports something called a "Pseudoinstruction" that maps ADD A B 0 to move A B, even though "move" is not an actual command
         </p>
    </details> 
    
    
 
  
## Arduino ##
* Programming the ROM
  * Timing? 
  * Feed back from load
  * Run through ROM at end and check every command
*Uno based clock can only do 83kHz, is this fast enough
  
## Memory ## 
