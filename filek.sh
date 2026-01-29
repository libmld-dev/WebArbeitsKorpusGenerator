#!/bin/bash

echo "Prepare text for TreeTagger..."
if [[ $1 == *.pdf ]]
then
    pdftotext $1 pdf.txt
    iconv -f utf-8 -t utf-8 -c pdf.txt > text.txt
    rm pdf.txt
else
    cp $1 text.txt
fi
./preanna.py text.txt web_split.txt
echo "Done!"
echo "Run TreeTagger..."
which wine
./bin/tree-tagger -lemma -token ./lib/german.par ./web_split.txt ./korp.txt
echo "Done!"
echo "Transform result into csv..."
./anna.py korp.txt korp.csv
echo "Done!"
echo "Saving metadata..."
echo $1 > meta.txt
echo "Done!"
echo "Merging metadata..."
./postanna.py korp.csv korpm.csv meta.txt
echo "Done!"
