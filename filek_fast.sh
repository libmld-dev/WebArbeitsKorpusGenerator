#!/bin/bash

echo "Prepare text for TreeTagger..."
./preanna $1 web_split.txt
echo "Done!"
echo "Run TreeTagger..."
which wine
./bin/tree-tagger -lemma -token ./lib/german.par ./web_split.txt ./korp.txt
echo "Done!"
echo "Transform result into csv..."
./anna korp.txt korp.csv
echo "Done!"
echo "Saving metadata..."
echo $1 > meta.txt
echo "Done!"
echo "Merging metadata..."
./postanna korp.csv korpm.csv meta.txt
echo "Done!"
