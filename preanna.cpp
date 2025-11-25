#include <iostream>
#include <fstream>
#include <sstream>

int main(int argc, char *argv[])
{
    // check args
    if (argc < 3)
    {
        std::cerr << "Usage: " << argv[0] << " input_file output_file\n";
        return 1;
    }

    // open input file
    std::ifstream fin(argv[1]);
    if (!fin)
    {
        std::cerr << "Error opening input file.\n";
        return 1;
    }

    // open output file
    std::ofstream fot(argv[2]);
    if (!fot)
    {
        std::cerr << "Error opening output file.\n";
        return 1;
    }

    // iter lines
    std::string line;
    while (std::getline(fin, line))
    {
        // get tokens split by whitespace
        std::istringstream iss(line);
        std::string token;
        while (iss >> token)
        {
            // print each token in a new line
            fot << token << "\n";
        }
    }

    // close files
    fin.close();
    fot.close();

    return 0;
}
