## THIS IS A WIP, DON'T RUN

# Usage:
#
#         python3 Compiler.py [filename.asm]
#


import sys

#Global Variables
REGISTERS = ["A", "B", "C", "D"]
WRITE = ["1000","0100","0010","0001"]
READ = ["010", "001", "011", "100"] #Order is A, B, C, D

#Boolean to control if line numbers are printed
LINENUM = False

#main methods
def main(): #Main method
    file = getFileName() #gets file name from args
    allCommands = openFile(file) #opens the file

    binaryStrings = [] #creates new array to hold binary values
    for command in allCommands:
        binaryStrings.append(returnBinary(command))#populates binaryStrings

    print("\n")
    printBinary(binaryStrings)
    print("\n")
    printHex(binaryStrings)
    writeHex(binaryStrings)

    return 0;

def getFileName(): #Returns filename from args. TODO: Should add more checks
    if (len(sys.argv)!=2):# If the input isn't "python compiler.py [filename]"
        print("Error 1")
        return 0;
    else:
        return sys.argv[1]
def openFile(filename): # Opens "filename" as a file
    linearray = []
    sourceFile = open(filename, "r")
    for line in sourceFile:
        linearray.append(line.upper().split()) #Ensures all the lines are upper case, then splits by space
    sourceFile.close()
    return linearray
def returnBinary(commandLine):
    opcode = commandLine[0]
    operands = commandLine[1:len(commandLine)] # rest of the array
    returnstring = ""

    if (opcode=="LD"):
        returnstring = ld(operands)
    elif (opcode=="CLR"):
        returnstring = clr(operands)
    elif (opcode=="JZ"):
        returnstring = jz(operands)
    elif (opcode=="ADD"):
        returnstring = add(operands)
    elif (opcode=="SUB"):
        returnstring = sub(operands)
    elif (opcode=="LSH"):
        returnstring = lsh(operands)
    elif (opcode=="RSH"):
        returnstring = rsh(operands)
    elif (opcode=="AND"):
        returnstring = andString(operands)
    elif (opcode=="OR"):
        returnstring = orString(operands)
    elif (opcode=="NOT"):
        returnstring = notString(operands)
    elif (opcode=="GR"):
        returnstring = gr(operands)
    elif (opcode=="GEQ"):
        returnstring = geq(operands)
    elif (opcode=="EQ"):
        returnstring = eq(operands)
    elif (opcode=="PCU"):
        returnstring = pcu(operands)
    elif (opcode=="PCL"):
        returnstring = pcl(operands)
    elif (opcode=="LDI"):
        returnstring = ldi(operands)
    elif (opcode=="NOP"):
        returnstring = nop(operands)
    elif (opcode=="OCL"):
        returnstring = ocl(operands)
    else:
        print("Error: 5")

    return returnstring
def printBinary(binaryStrings):
    x=0
    print("Binary: ")
    for i in binaryStrings:
        printstring = ""
        if (LINENUM):
            printstring = str(x) + " | " + i
        else:
            printstring = i
        print(printstring)
        x+=1
def printHex(binaryStrings):
    x=0
    print("Hex: ")
    for i in binaryStrings:
        printstring = ""
        if (LINENUM):
            printstring = str(x) + " | " + toHex(i)
        else:
            printstring = toHex(i.replace(" ",""))
        print(printstring)
        x+=1
def writeHex(binaryStrings):
    writefile = "hexOutput.hex"
    file = open(writefile,"w")
    file.write("v2.0 raw\n\n")
    x=0
    for i in binaryStrings:
        printstring = ""
        if (LINENUM):
            file.write(str(x) + " | " + toHex(i))
        else:
            file.write(toHex(i.replace(" ","")) + "\n")
        print(printstring)
        x+=1
    file.close()


#Operations
def ld(operands): #LD
    # LD always has two arguments
    returnstring = "000 " #LD XX XX

    if (operands[0] in REGISTERS): #LD [REGISTER] XX
        writeregister = matchWriteRegister(operands[0])
        if (operands[1] in REGISTERS): #LD [REGISTER] [REGISTER]
            returnstring += "000 "  #subopcode
            returnstring += writeregister + " " #writeregister
            returnstring += matchReadRegister(operands[1]) #readregister
            returnstring += " 000 " #not used
            returnstring += "00000000" #empty constant
        elif (operands[1][0:1]=="&"): #LD [REGISTER] [RAM]
            returnstring += "010 " #subopcode
            returnstring += writeregister #writeregister
            returnstring += " 000" #readregister
            returnstring += " 000 " #not used
            returnstring += toBinary(str(operands[1][1:len(operands[1])])) #RAM address
        else: #LD [REGISTER] [CONSTANT]
            returnstring += "011 " #subopcode
            returnstring += writeregister #writeregister
            returnstring += " 000" #readregister
            returnstring += " 000 " #not used
            returnstring += toBinary(operands[1]) #Constant

    elif (operands[0][0:1]=="&"):## LD RAM [REGISTER]
        returnstring += "010 0000 "
        if (operands[1] in REGISTERS):
            returnstring += matchReadRegister(operands[1])
            returnstring += " 000 "
            # returnstring += toBinary(str(operands[0][1:len(operands[0])]))
        else:
            returnstring += "Error: 4"

    return returnstring
def clr(operands): #CLR
    return "000 100 0000 000 000 00000000"
def add(operands): #ADD
    returnstring = "001"
    wregister = matchWriteRegister(operands[0])
    rregister = matchReadRegister(operands[1])

    if (operands[2] in REGISTERS): #ADD [REGISTER] [REGISTER] [REGISTER]
        returnstring += " 000 "
        returnstring += wregister + " "
        returnstring += rregister + " "
        returnstring += matchReadRegister(operands[2])
        returnstring += " 00000000"
    else: #ADD [REGISTER] [REGISTER] [CONSTANT]
        returnstring += " 001 "
        returnstring += wregister + " "
        returnstring += rregister + " "
        returnstring += "000 "
        returnstring += toBinary(operands[2])

    return returnstring;
def sub(operands): #SUB
    returnstring = "001"
    wregister = matchWriteRegister(operands[0])
    rregister = matchReadRegister(operands[1])

    if (operands[2] in REGISTERS): #SUB [REGISTER] [REGISTER] [REGISTER]
        returnstring += " 010 "
        returnstring += wregister + " "
        returnstring += rregister + " "
        returnstring += matchReadRegister(operands[2])
        returnstring += " 00000000"
    else: #SUB [REGISTER] [REGISTER] [CONSTANT]
        returnstring += " 011 "
        returnstring += wregister + " "
        returnstring += rregister + " "
        returnstring += "000 "
        returnstring += toBinary(operands[2])

    return returnstring;
def lsh(operands): #LSH
    returnstring = "001 100 "
    returnstring += matchWriteRegister(operands[0]) + " "
    returnstring += matchReadRegister(operands[1])
    returnstring += " 000 00000000"
    return returnstring
def rsh(operands): #RSH
    returnstring = "001 101 "
    returnstring += matchWriteRegister(operands[0]) + " "
    returnstring += matchReadRegister(operands[1])
    returnstring += " 000 00000000"
    return returnstring
def andString(operands): #AND (and is a reserved word)
    returnstring = "010"
    wregister = matchWriteRegister(operands[0])
    rregister = matchReadRegister(operands[1])

    if (operands[2] in REGISTERS): #ADD [REGISTER] [REGISTER] [REGISTER]
        returnstring += " 000 "
        returnstring += wregister + " "
        returnstring += rregister + " "
        returnstring += matchReadRegister(operands[2])
        returnstring += " 00000000"
    else: #ADD [REGISTER] [REGISTER] [CONSTANT]
        returnstring += " 001 "
        returnstring += wregister + " "
        returnstring += rregister + " "
        returnstring += "000 "
        returnstring += toBinary(operands[2])

    return returnstring;
def orString(operands): #OR (or is a reserved word)
    return "empty";
def notString(operands): #NOT (not is a reserved word)
    return "empty";
def gr(operands): #GR
    return "empty";
def geq(operands): #GEQ
    return "empty";
def eq(operands): #eq
    return "empty";
def pcu(operands): #eq
    return "empty";
def pcl(operands): #eq
    return "empty";
def ldi(operands): #eq
    return "empty";
def jz(operands):
    return 0; #JZ
def nop(operands): #eq
    return "empty";
def ocl(operands): #eq
    return "empty";

#Support functions
def toHex(binary): #Converts binary number to Hex
    unformatted = hex(int(str(binary),2)) #Converts number to base 2, then turns into hex
    unformatted = unformatted[2:len(unformatted)-1] #Chops off the first two characters, '0x'
    while (len(unformatted)<6):
        unformatted = "0" + unformatted
    return str(unformatted)
def toBinary(decimal): #Converts decimal into binary
    unformatted = bin(int(decimal))
    unformatted = unformatted[2:len(unformatted)-1] #Chops off the first two characters, '0b'
    while (len(unformatted)<8):
        unformatted = "0" + unformatted
    return str(unformatted)

def matchWriteRegister(register): #Returns binary for register write
    if (register=="A"): return WRITE[0]
    if (register=="B"): return WRITE[1]
    if (register=="C"): return WRITE[2]
    if (register=="D"): return WRITE[3]
    else: return "Error: 2"
def matchReadRegister(register): #Returns binary for register read
    if (register=="A"): return READ[0]
    if (register=="B"): return READ[1]
    if (register=="C"): return READ[2]
    if (register=="D"): return READ[3]
    else: return "Error: 3"

main()
