#
#
# Usage:
#
#         python3 Compiler.py [filename.asm]
#


import sys
import re

#Global Variables
REGISTERS = ["A", "B", "C", "D"]
WRITE = ["1000","0100","0010","0001"]
READ = ["010", "001", "011", "100"] #Order is A, B, C, D
SOURCELINES = []

LABELTABLE = [];

#Boolean to control what gets printed
LINENUM = True
SOURCE = True
BINARY = True
HEX = True

#main methods
def main(): #Main method
    file = getFileName() #gets file name from args
    allCommands = openFile(file) #opens the file
    
    binaryStrings = [] #creates new array to hold binary values
    for command in allCommands:
        binaryStrings.append(returnBinary(command))#populates binaryStrings

    consolePrint(binaryStrings)

    writeHex(binaryStrings)

    return 0;

def getFileName(): #Returns filename from args. TODO: Should add more checks
    if (len(sys.argv)!=2):# If the input isn't "python compiler.py [filename]"
        print("Error 1")
        return 0;
    else:
        return sys.argv[1]
def openFile(filename): # Opens "filename" as a file
    linearray = [] #Creates new array of command arrays
    sourceFile = open(filename, "r")
    for line in sourceFile:
        line = line.split(";",1)[0] #removes all comments
        populateSourceArray(line) #output only command and not comments
        #line = line.replace("\t","TAB ")
        linearray.append(line.upper().split()) #Ensures all the lines are upper case, then splits by space
    sourceFile.close()
    return linearray

def populateSourceArray(line):
    appendstring = ""
    linecommand = line.split()
    for i in linecommand:
        appendstring = appendstring + i + " "
    SOURCELINES.append(appendstring)
def returnBinary(commandLine):
    opcode = commandLine[0]
    operands = commandLine[1:len(commandLine)] # rest of the array
    returnstring = ""

    if (opcode=="LD"):
        returnstring = ld(operands)
    elif (opcode=="CLR"):
        returnstring = clr(operands)
    elif (opcode=="JNZ"):
        returnstring = jnz(operands)
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

def consolePrint(binaryStrings):
    x=0 #For counting lines
    print("Output: ")
    for i in binaryStrings:
        printstring = ""
        if (LINENUM and x<10):
            printstring += str(x) + " |\t"
        elif (LINENUM and x>=10):
            printstring += str(x) + "|\t"
        if (SOURCE):
             printstring += SOURCELINES[x] + "\t| "
        if (BINARY):
             printstring += i + "\t| "
        if(HEX):
            printstring +=  toHex(i.replace(" ",""))

        print(printstring)
        x+=1
def printBinary(binaryStrings):
    x=0
    print("Binary: ")
    for i in binaryStrings:
        printstring = ""
        if (LINENUM and x<10):
            printstring = str(x) + " | " + i
        elif (LINENUM and x>=10):
            printstring = str(x) + "| " + i
        else:
            printstring = i
        print(printstring)
        x+=1
def printHex(binaryStrings):
    x=0
    print("Hex: ")
    for i in binaryStrings:
        printstring = ""
        if (LINENUM and x<10):
            printstring = str(x) + " | " + toHex(i.replace(" ",""))
        elif (LINENUM and x>=10):
            printstring = str(x) + "| " + toHex(i.replace(" ",""))
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
        file.write(toHex(i.replace(" ","")) + "\n")
        x+=1
    file.close()

#Support functions
def toHex(binary): #Converts binary number to Hex
    unformatted = hex(int(str(binary),2)) #Converts number to base 2, then turns into hex
    unformatted = unformatted[2:len(unformatted)] #Chops off the first two characters, '0x'
    while (len(unformatted)<6):
        unformatted = "0" + unformatted
    return str(unformatted)
def toBinary(decimalstring): #Converts decimal into binary
    decimal=int(decimalstring)
    if (decimal<0): decimal=decimal+256 #This takes into account negative numbers
    unformatted = bin(decimal)
    unformatted = unformatted[2:len(unformatted)] #Chops off the first two characters, '0b'
    while (len(unformatted)<8):
        unformatted = "0" + unformatted
    return str(unformatted)
def toBinarySixLong(decimalstring):
    decimal=int(decimalstring)
    if (decimal<0): decimal=decimal+256 #This takes into account negative numbers
    unformatted = bin(int(decimal))
    unformatted = unformatted[2:len(unformatted)] #Chops off the first two characters, '0b'
    while (len(unformatted)<6):
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

#Operations
def ld(operands): #LD
    # LD always has two arguments
    returnstring = "000 " #LD XX XX

    if (operands[0] in REGISTERS): #LD [REGISTER] XX
        writeregister = matchWriteRegister(operands[0])
        if (operands[1][0:1]=="&"): #LD REGISTER &[SOMETHING]
            returnstring += "001 "
            if (operands[1][1:len(operands[1])] in REGISTERS): #LD [REGISTER] &[REGISTER]
                returnstring += writeregister #writeregister
                returnstring += " 000 " #not used
                returnstring += matchReadRegister(operands[1][1:len(operands[1])]) #readregister
                returnstring += " 00000000" #empty constant
            else: #LD [REGISTER] &[CONSTANT]
                returnstring += writeregister
                returnstring += " 000 000 "
                returnstring += toBinary(operands[1][1:len(operands[1])])
        else:  #LD [REGISTER] [SOMETHING]
            if(operands[1] in REGISTERS): #LD [REGISTER] [REGISTER]
                returnstring += "000 "
                returnstring += writeregister + " "
                returnstring += matchReadRegister(operands[1]) + " "
                returnstring += "000 00000000"
            else: #LD [REGISTER] [CONSTANT]
                returnstring += "011 "
                returnstring += writeregister + " "
                returnstring += "000 000 "
                returnstring += str(toBinary(operands[1]))

    else: #LD &[SOMETHING]
        if (operands[0][1:len(operands[0])] in REGISTERS): #LD &[REGISTER] [REGISTER]
            returnstring += "010 0000 "
            returnstring += matchReadRegister(operands[1]) + " "
            returnstring += matchReadRegister(operands[0][1:len(operands[0])])
            returnstring += " 00000000"
        else: #LD &[CONSTANT] [REGISTER]
            returnstring += "010 0000 "
            returnstring += matchReadRegister(operands[1])
            returnstring += " 000 "
            returnstring += toBinary(operands[0][1:len(operands[0])])

    return returnstring
def clr(operands): #CLR
    return "000 100 1111 000 000 00000000"
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
    returnstring = "010"
    wregister = matchWriteRegister(operands[0])
    rregister = matchReadRegister(operands[1])

    if (operands[2] in REGISTERS): #ADD [REGISTER] [REGISTER] [REGISTER]
        returnstring += " 010 "
        returnstring += wregister + " "
        returnstring += rregister + " "
        returnstring += matchReadRegister(operands[2])
        returnstring += " 00000000"
    else: #ADD [REGISTER] [REGISTER] [CONSTANT]
        returnstring += " 011 "
        returnstring += wregister + " "
        returnstring += rregister + " "
        returnstring += "000 "
        returnstring += toBinary(operands[2])

    return returnstring;
def notString(operands): #NOT (not is a reserved word)
    returnstring = "010"
    wregister = matchWriteRegister(operands[0])

    if (operands[1] in REGISTERS): #ADD [REGISTER] [REGISTER] [REGISTER]
        returnstring += " 100 "
        returnstring += wregister + " "
        returnstring += " 000 "
        returnstring += matchReadRegister(operands[1]) + " "
        returnstring += " 00000000"
    else: #ADD [REGISTER] [REGISTER] [CONSTANT]
        returnstring += " 101 "
        returnstring += wregister + " "
        returnstring += "000 000 "
        returnstring += toBinary(operands[1])

    return returnstring;
def gr(operands): #GR
    returnstring = "011"
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
def geq(operands): #GEQ
    returnstring = "011"
    wregister = matchWriteRegister(operands[0])
    rregister = matchReadRegister(operands[1])

    if (operands[2] in REGISTERS): #ADD [REGISTER] [REGISTER] [REGISTER]
        returnstring += " 010 "
        returnstring += wregister + " "
        returnstring += rregister + " "
        returnstring += matchReadRegister(operands[2])
        returnstring += " 00000000"
    else: #ADD [REGISTER] [REGISTER] [CONSTANT]
        returnstring += " 011 "
        returnstring += wregister + " "
        returnstring += rregister + " "
        returnstring += "000 "
        returnstring += toBinary(operands[2])

    return returnstring;
def eq(operands): #eq
    returnstring = "011"
    wregister = matchWriteRegister(operands[0])
    rregister = matchReadRegister(operands[1])

    if (operands[2] in REGISTERS): #ADD [REGISTER] [REGISTER] [REGISTER]
        returnstring += " 100 "
        returnstring += wregister + " "
        returnstring += rregister + " "
        returnstring += matchReadRegister(operands[2])
        returnstring += " 00000000"
    else: #ADD [REGISTER] [REGISTER][CONSTANT]
        returnstring += " 101 "
        returnstring += wregister + " "
        returnstring += rregister + " "
        returnstring += "000 "
        returnstring += toBinary(operands[2])

    return returnstring;
def pcu(operands): #eq
    returnstring = "100 000 0000 000 000 "
    returnstring += toBinary(operands[0])
    return returnstring;
def pcl(operands): #eq
    returnstring = "100 001 0000 000 000 "
    returnstring += toBinary(operands[0])
    return returnstring;
def ldi(operands): #eq
    return "100 010 0000 000 000 00000000"
def jnz(operands):
    returnstring = "100 011 0000 "
    returnstring += matchReadRegister(operands[0])
    returnstring += " 000 "
    returnstring += toBinary(operands[1]) + " "
    return returnstring;
def nop(operands): #eq
    return "100 100 0000 000 000 00000000"
def ocl(operands): #eq
    returnstring = "100 101 0000 "
    returnstring += toBinarySixLong(operands[0]) + " "
    returnstring += toBinary(operands[1])
    return returnstring


main()
