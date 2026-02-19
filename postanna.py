#!/bin/python3
import sys

# open input file
fin = open(sys.argv[1], "r")
lines = [line.rstrip() for line in fin]

# open output file
fout = open(sys.argv[2], "a+")

# open metadata
f = open(sys.argv[3], "r")
metadata = f.read()

# escape flag
fescape = True
if len(sys.argv) > 4:
    fescape = (int(sys.argv[4]) == 1)

# remove possible data after metadata
endm0 = metadata.find("---")
endm1 = metadata.find("---", endm0 + 3)
metadata = metadata[:endm1]

# remove newlines and ---
metadata = metadata.replace("\n", "")
metadata = metadata.replace("---", "")

# append metadata to each entry
for l in lines:
    if fescape:
        print(l + ",\"" + metadata + "\"", file=fout)
    else:
        print(l + "," + metadata, file=fout)

# print newline
print("", file=fout)
