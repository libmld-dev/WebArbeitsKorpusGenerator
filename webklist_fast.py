#!/bin/python3
import sys
import subprocess

# open input
fin = open(sys.argv[1], "r")
lines_in = [line.rstrip() for line in fin]

# split by whitespace and print
for l in lines_in:
    if not l:
        continue
    print("Doing " + l + "...")
    subprocess.run(["./webk_fast.sh", l])
