# WebArbeitsKorpusGenerator
Entwickelt von 
- Marcel Lütke Dreimann (marcel.luetkedreimann@uos.de)
- Anna-Lena Randermann (anna-lena.randermann@uibk.ac.at).

## Anforderungen und Installation
- Linux (Ubuntu/Debian) oder Windows WSL (Ubuntu/Debian)
- Installation: `./install.sh`
- Installation (C++ Port, optional): `./install_cpp.sh`

## Verwendung
Erstellen eines Webarbeitskorpus: `./webk.sh <Link>`  
Anschließend befindet sich in *korpm.csv* der Arbeitskorpus. Eine mehrfache Ausführung von *webk* fügt die neuen Daten am Ende der Tabelle von *korpm.csv* hinzu.

Erstellen eines Webarbeitskorpus aus mehreren Links: `./webklist.py <Liste.txt>`  
Anschließend wird *webk* für jeden Link aus *Liste.txt* ausgeführt. Die Links sollten durch Zeilenumbrüche getrennt sein.

Löschen von temporären Dateien: `./clean.sh`  
Löscht alle temporären Dateien. *korpm.csv* bleibt bestehen.

## C++ Port für mehr Performance
Bei großen Datenmengen oder komplexen Instanzen kann die Verarbeiten mehr Zeit beanspruchen. Der C++ Port kann ist in diesem Fall die Verabeitung beschleunigen.
Dafür muss die Software mittels `./install_cpp.sh` eingerichtet werden. Anschließend lässt sich `./webk_fast.sh <Link>` bzw. `./webklist_fast.py <Liste.txt>` verwenden.

## Verwendete 3rd Party Software

### Trafilatura
https://github.com/adbar/trafilatura

Barbaresi, Adrien. "Trafilatura: A web scraping library and command-line tool for text discovery and extraction." Proceedings of the 59th Annual Meeting of the Association for Computational Linguistics and the 11th International Joint Conference on Natural Language Processing: System Demonstrations. 2021.

### TreeTagger
https://www.cis.uni-muenchen.de/~schmid/tools/TreeTagger/

Schmid, Helmut. "Probabilistic part-of-speech tagging using decision trees." New methods in language processing. Routledge, 2013.
