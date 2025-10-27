#!/bin/python3
import sys

# open input
fin = open(sys.argv[1], "r")
lines_in = [line.rstrip() for line in fin]

# create output
fot = open(sys.argv[2], "w+")

# split by whitespace and print
for l in lines_in:
    d = l.split()
    for t in d:
        print(t, file=fot)
