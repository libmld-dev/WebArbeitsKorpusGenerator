#!/bin/bash

make -j3
echo "Fetch data with trafilatura..."
trafilatura --config-file settings.cfg -u "$1" --no-tables > web.txt
echo "Done!"
echo "Prepare text for TreeTagger..."
./preanna web.txt web_split.txt
echo "Done!"
echo "Run TreeTagger..."
which wine
./bin/tree-tagger -lemma -token ./lib/german.par ./web_split.txt ./korp.txt
echo "Done!"
echo "Transform result into csv..."
./anna korp.txt korp.csv
echo "Done!"
echo "Fetching metadata..."
trafilatura --config-file settings.cfg -u "$1" --with-metadata --no-tables | head -n 8 > meta.txt
echo "Done!"
echo "Merging metadata..."
./postanna korp.csv korpm.csv meta.txt
echo "Done!"
