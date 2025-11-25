#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

static const std::vector<std::string> tokenfilter = {"VVFIN", "VVIMP", "VVIZU", "VVINF", "VVPP"};
static const std::vector<std::string> sentenceEnd = {".", "!", "?", "*"};

int main(int argc, char *argv[])
{
    // check args
    if (argc < 3)
    {
        std::cerr << "Usage: program inputfile outputfile\n";
        return 1;
    }

    // open input file
    std::ifstream fin(argv[1]);
    if (!fin)
    {
        std::cerr << "Error opening input file\n";
        return 1;
    }

    // open output file
    std::ofstream fout(argv[2]);
    if (!fout)
    {
        std::cerr << "Error opening output file\n";
        return 1;
    }

    // read lines and store them in a vector
    std::vector<std::string> lines_in;
    std::string line;
    while (std::getline(fin, line))
    {
        lines_in.push_back(line);
    }
    fin.close();

    // flags for analysis
    bool inSentence = false;
    std::string currToken = "None";
    int currTokenIndex = 0;
    int targetTokenIndex = 0;
    bool restartSentence = false;

    // output
    std::string lines_out;

    // iterators
    size_t currSentenceStart = 0;
    size_t i = 0;
    const size_t line_count = lines_in.size();

    while (i < line_count)
    {
        // print status
        std::cout << "Processing line " << i << " of " << line_count << "\r" << std::flush;

        // get line and its tags
        const std::string l = lines_in[i];
        std::vector<std::string> d;
        d.resize(3);
        std::stringstream ss(l);
        std::string item;
        while (std::getline(ss, item, '\t'))
        {
            d.push_back(item);
        }

        // detect sentence end case 1: token is only sentence terminator
        bool isSentenceEndTokenOnly = false;
        for (const auto &se : sentenceEnd)
        {
            if (d[0] == se)
            {
                isSentenceEndTokenOnly = true;
                break;
            }
        }
        if (isSentenceEndTokenOnly)
        {
            lines_out += d[0] + "\",\"" + currToken + "\"\n";

            currToken = "None";
            inSentence = false;

            if (restartSentence)
            {
                currTokenIndex = 0;
                i = currSentenceStart;
                ++targetTokenIndex;
                restartSentence = false;
                continue;
            }

            ++i;
            currSentenceStart = i;
            targetTokenIndex = 0;
            currTokenIndex = 0;
            restartSentence = false;
            continue;
        }

        // if we are not in a sentence => start with new cell
        if (!inSentence)
        {
            lines_out += "\"";
        }

        // check if d[1] in tokenfilter
        bool d1_in_tokenfilter = false;
        for (const auto &tf : tokenfilter)
        {
            if (d[1] == tf)
            {
                d1_in_tokenfilter = true;
                break;
            }
        }

        if (!d1_in_tokenfilter)
        {
            if (inSentence)
            {
                lines_out += " ";
            }
            lines_out += d[0];
            inSentence = true;

            // detect sentence end case 2: sentence terminator is part of token
            bool sentenceEndFound = false;
            for (const auto &e : sentenceEnd)
            {
                if (d[0].find(e) != std::string::npos)
                {
                    lines_out += "\",\"" + currToken + "\"\n";

                    currToken = "None";
                    inSentence = false;

                    if (restartSentence)
                    {
                        currTokenIndex = 0;
                        i = currSentenceStart;
                        ++targetTokenIndex;
                        restartSentence = false;
                        sentenceEndFound = true;
                        break;
                    }

                    currSentenceStart = i;
                    targetTokenIndex = 0;
                    currTokenIndex = 0;
                    restartSentence = false;
                    sentenceEndFound = true;
                    break;
                }
            }
            if (sentenceEndFound)
            {
                ++i;
                continue;
            }
        }
        else
        {
            // detect untargeted token as ordinary word
            if (currTokenIndex != targetTokenIndex)
            {
                if (currTokenIndex > targetTokenIndex)
                {
                    restartSentence = true;
                }
                if (inSentence)
                {
                    lines_out += " ";
                }
                lines_out += d[0];
                ++currTokenIndex;
                ++i;
                inSentence = true;
                continue;
            }

            lines_out += "\",\"" + d[0] + "\",";
            currToken = d[1];
            ++currTokenIndex;
            inSentence = false;
        }

        ++i;
    }


    // has the file ended without sentence termination and a token in pipeline?
    if (currToken != "None")
    {
        lines_out += " \",\"" + currToken + "\"\n";
    }

    // newline after status print when finished
    std::cout << std::endl;

    // filter out sentences without specified token and print result to file
    std::stringstream ss_out(lines_out);
    std::string out_line;
    while (std::getline(ss_out, out_line))
    {
        for (const auto &token : tokenfilter)
        {
            if (out_line.find(token) != std::string::npos)
            {
                fout << out_line << "\n";
                break;
            }
        }
    }

    // close file
    fout.close();

    return 0;
}
