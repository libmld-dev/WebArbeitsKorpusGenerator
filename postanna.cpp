#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <sstream>

int main(int argc, char *argv[])
{
    // check args
    if (argc < 4)
    {
        std::cerr << "Usage: " << argv[0] << " input_file output_file metadata_file\n";
        return 1;
    }

    // open input file
    std::ifstream fin(argv[1]);
    if (!fin)
    {
        std::cerr << "Error opening input file\n";
        return 1;
    }

    // open output file in append mode
    std::ofstream fout(argv[2], std::ios::app);
    if (!fout)
    {
        std::cerr << "Error opening output file\n";
        return 1;
    }

    // open metadata file
    std::ifstream fmeta(argv[3]);
    if (!fmeta)
    {
        std::cerr << "Error opening metadata file\n";
        return 1;
    }

    // read metadata to string
    std::stringstream buffer;
    buffer << fmeta.rdbuf();
    std::string metadata = buffer.str();
    fmeta.close();

    // remove "---" from metadata string
    const std::string dashes = "---";
    size_t pos = std::string::npos;
    while ((pos = metadata.find(dashes)) != std::string::npos)
    {
        metadata.erase(pos, dashes.length());
    }

    // remove newline from metadata string
    metadata.erase(std::remove(metadata.begin(), metadata.end(), '\n'), metadata.cend());

    // append metadata to each entry
    std::string line;
    while (std::getline(fin, line))
    {
        fout << line << ",\"" << metadata << "\"" << std::endl;
    }

    // print newline
    fout << std::endl;

    // close files
    fin.close();
    fout.close();

    return 0;
}
