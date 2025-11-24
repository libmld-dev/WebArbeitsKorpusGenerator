#!/bin/bash

echo "Fetch data with trafilatura..."
trafilatura -u "$1" --no-tables > web.txt
echo "Done!"
echo "Prepare text for TreeTagger..."
./preanna.py web.txt web_split.txt
echo "Done!"
echo "Run TreeTagger..."
which wine
if [ $? = 0 ]; then
    wine ./bin/tree-tagger.exe -lemma -token ./lib/german.par ./web_split.txt ./korp.txt
else
    ./bin/tree-tagger.exe -lemma -token ./lib/german.par ./web_split.txt ./korp.txt
fi
echo "Done!"
echo "Transform result into csv..."
./anna.py korp.txt korp.csv
echo "Done!"
echo "Fetching metadata..."
trafilatura -u "$1" --with-metadata --no-tables | head -n 8 > meta.txt
echo "Done!"
echo "Merging metadata..."
./postanna.py korp.csv korpm.csv meta.txt
echo "Done!"

