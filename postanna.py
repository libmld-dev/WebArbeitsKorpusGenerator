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

# remove newlines and ---
metadata = metadata.replace("\n", "")
metadata = metadata.replace("---", "")

# append metadata to each entry
for l in lines:
    print(l + ",\"" + metadata + "\"", file=fout)

# print newline
print("", file=fout)
