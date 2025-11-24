#!/bin/python3
import sys

# open in and out file
fin = open(sys.argv[1], "r")
lines_in = [line.rstrip() for line in fin]
fout = open(sys.argv[2], "w+")

# filter for tokens
tokenfilter = ["VVFIN", "VVIMP", "VVIZU", "VVINF", "VVPP"]

# mark end of sentence
sentenceEnd = [".", "!", "?", "*"]

# flags for parsing
inSentence = False
currToken = "None"
currTokenIndex = 0
targetTokenIndex = 0
restartSentence = False

# (pre) output string
lines_out = ""

# iter variables
currSentenceStart = 0
i = 0
line_count = len(lines_in)
while i < line_count:
    # print status
    print("Processing line ", i , " of ", line_count, end='\r')

    # get line and its tags
    l = lines_in[i]
    d = l.split("\t")

    # detect sentence end case 1: token is only sentence terminator
    if d[0] in sentenceEnd:
        lines_out += (d[0] + "\"" + "," + "\"" + currToken + "\"" + "\n")

        # reset state
        currToken = "None"
        inSentence = False

        # check of restart
        if restartSentence:
            currTokenIndex = 0
            i = currSentenceStart
            targetTokenIndex = targetTokenIndex + 1
            restartSentence = False
            continue

        # end sentence
        i = i + 1
        currSentenceStart = i
        targetTokenIndex = 0
        currTokenIndex = 0
        restartSentence = False
        continue

    # if we are not in a sentence => start with new cell
    if not inSentence:
        lines_out += "\""

    if not d[1] in tokenfilter:
        # print leading whitespace in sentence
        if inSentence:
            lines_out += " "

        # store word
        lines_out += d[0]
        inSentence = True

        # detect sentence end case 2: sentence terminator is part of token
        for e in sentenceEnd:
            if e in d[0]:
                lines_out += "\"," + "\"" + currToken + "\"" + "\n"

                # reset state
                currToken = "None"
                inSentence = False

                # check of restart
                if restartSentence:
                    currTokenIndex = 0
                    i = currSentenceStart
                    targetTokenIndex = targetTokenIndex + 1
                    restartSentence = False
                    break

                # end sentence
                currSentenceStart = i
                targetTokenIndex = 0
                currTokenIndex = 0
                restartSentence = False
                break
    else:
        # detect untargeted token as ordinary word
        if currTokenIndex != targetTokenIndex:

            # found new target token
            if currTokenIndex > targetTokenIndex:
                restartSentence = True

            # store as ordinary word
            if inSentence:
                lines_out += " "

            lines_out += d[0]
            currTokenIndex = currTokenIndex + 1
            i = i + 1
            inSentence = True
            continue

        # store word and end cell
        lines_out += "\"," + "\"" + d[0] + "\"" + ","
        currToken = d[1]
        currTokenIndex = currTokenIndex + 1
        inSentence = False

    # inc i
    i = i + 1

# newline after status print when finished
print()

# filter out not sentences without specified token and print result to file
lines_out_filtered = lines_out.split("\n")
for l in lines_out_filtered:
    for token in tokenfilter:
        if token in l:
            print(l, file=fout)
