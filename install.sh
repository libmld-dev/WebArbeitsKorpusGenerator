#!/bin/bash

# install required packages
sudo apt update
sudo apt install -y curl python3 pipx gzip poppler-utils

# install trafilatura
pipx ensurepath
pipx install trafilatura[all]

# download TreeTagger files
curl --output tree-tagger-linux-3.2.5.tar.gz https://www.cis.uni-muenchen.de/~schmid/tools/TreeTagger/data/tree-tagger-linux-3.2.5.tar.gz
curl --output tagger-scripts.tar.gz https://www.cis.uni-muenchen.de/~schmid/tools/TreeTagger/data/tagger-scripts.tar.gz
curl --output german.par.gz https://www.cis.uni-muenchen.de/~schmid/tools/TreeTagger/data/german.par.gz
curl --output install-tagger.sh https://www.cis.uni-muenchen.de/~schmid/tools/TreeTagger/data/install-tagger.sh

# install TreeTagger
chmod +x *.sh
./install-tagger.sh

# remove tmp TreeTagger stuff
rm *.gz install-tagger.sh

# make python files executable in case the are not
chmod +x *.py
