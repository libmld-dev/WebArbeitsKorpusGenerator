# WebArbeitsKorpusGenerator
Entwickelt von 
- Marcel Lütke Dreimann (marcel.luetkedreimann@uos.de)
- Anna-Lena Randermann (anna-lena.randermann@uibk.ac.at).

## Anforderungen und Installation
- Linux (Ubuntu/Debian) oder Windows WSL (Ubuntu/Debian)
- Installation: `./install.sh`

## Verwendung
Erstellen eines Webarbeitskorpus: `./webk.sh <Link>`  
Anschließend befindet sich in *korpm.csv* der Arbeitskorpus. Eine mehrfache Ausführung von *webk* fügt die neuen Daten am Ende der Tabelle von *korpm.csv* hinzu.

Erstellen eines Webarbeitskorpus aus mehreren Links: `./webklist.py <Liste.txt>`  
Anschließend wird *webk* für jeden Link aus *Liste.txt* ausgeführt. Die Links sollten durch Zeilenumbrüche getrennt sein.

Löschen von temporären Dateien: `./clean.sh`  
Löscht alle temporären Dateien. *korpm.csv* bleibt bestehen.


## Verwendete 3rd Party Software

### Trafilatura
https://github.com/adbar/trafilatura

Barbaresi, Adrien. "Trafilatura: A web scraping library and command-line tool for text discovery and extraction." Proceedings of the 59th Annual Meeting of the Association for Computational Linguistics and the 11th International Joint Conference on Natural Language Processing: System Demonstrations. 2021.

### TreeTagger
https://www.cis.uni-muenchen.de/~schmid/tools/TreeTagger/

Schmid, Helmut. "Probabilistic part-of-speech tagging using decision trees." New methods in language processing. Routledge, 2013.
