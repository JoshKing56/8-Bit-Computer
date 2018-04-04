## THIS IS A WIP, DON'T RUN

import sys

def toHex(binary):
    temp = binary
    return hex(int(str(binary),2)) #Converts number to base 2, then turns into hex

print toHex(100001000000000000000111)
