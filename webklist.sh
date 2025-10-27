#!/bin/bash

# trafilatura --crawl "https://example.org" > $1

# process list of links
while IFS= read -r line; do
    echo "Doing $line..."
    ./webk.sh "$line"
done < $1
