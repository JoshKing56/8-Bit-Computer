## THIS IS A WIP, DON'T RUN

import sys

#Global Variables
REGISTERS = ["A", "B", "C", "D"]
WRITE = ["1000","0100","0010","0001"]
READ = ["010", "001", "011", "100"] #Order is A, B, C, D

def toHex(binary):
    unformatted = hex(int(str(binary),2)) #Converts number to base 2, then turns into hex
    return unformatted[2:len(unformatted)-1] #Chops off the first two characters, '0x'

def openFile(filename):
    linearray = []
    sourceFile = open(filename, "r")
    for line in sourceFile:
        linearray.append(line.upper().split()) #Ensures all the lines are upper case, then splits by space
    sourceFile.close()
    return linearray

def getFileName(): #Should add more checks
    if (len(sys.argv)!=2):# If the input isn't "python compiler.py [filename]"
        print("Error 1")
        return 0;
    else:
        return sys.argv[1]

def ld(operands):#LD always has two arguments
    # print(str(operands))
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
            returnstring += str(operands[1][1:len(operands[1])]) #RAM address


        else: #LD [REGISTER] [CONST]
            returnstring += "000 " + writeregister + " " + matchReadRegister(operands[1]) + " 000 000000000"

    elif (operands[0][0:1]=="&"):## LD RAM [REGISTER]
        returnstring += "010 0000 "
        if (operands[1] in REGISTERS):
            returnstring += matchReadRegister(operands[1])
            returnstring += " 000 "
            returnstring += str(operands[0][1:len(operands[0])])
        else:
            returnstring += "Error: 4"

    return returnstring

def matchWriteRegister(register):
    if (register=="A"): return WRITE[0]
    if (register=="B"): return WRITE[1]
    if (register=="C"): return WRITE[2]
    if (register=="D"): return WRITE[3]
    else: return "Error: 2"

def matchReadRegister(register):
    if (register=="A"): return READ[0]
    if (register=="B"): return READ[1]
    if (register=="C"): return READ[2]
    if (register=="D"): return READ[3]
    else: return "Error: 3"

def returnBinary(commandLine):
    opcode = commandLine[0]
    operands = commandLine[1:len(commandLine)] # rest of the array
    returnstring = ""

    if (opcode=="LD"):
        returnstring = ld(operands)
    else:
        print("Not LD")

    return returnstring

def main():
    file = getFileName() #gets file name from args
    allCommands = openFile(file) #opens the file

    binaryStrings = [] #creates new array to hold binary values
    for command in allCommands:
        binaryStrings.append(returnBinary(command))#populates binaryStrings

    x=0
    for i in binaryStrings: print(i)


    return 0;


main()
