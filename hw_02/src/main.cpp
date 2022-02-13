#include <iostream>
#include "huffman.h"

struct Parameters {
    std::string outputFile;
    std::string inputFile;
    std::string type;

    bool isCorrect() {
        return outputFile.size() != 0 && inputFile.size() != 0 && type.size() != 0;
    }
};

class BadArgumentException : public std::runtime_error {
public:
    BadArgumentException(std::string msg) : std::runtime_error(msg) {}
};

Parameters getParameters(int argc, char **argv) {
    std::vector<std::string> pars(argc - 1);
    for (int i = 1; i < argc; ++i) {
        pars[i - 1] = std::string(argv[i]);
    }

    Parameters ret;
    try {
        for (size_t i = 0; i < pars.size(); ++i) {
            if (pars[i] == "-u" || pars[i] == "-c") {
                ret.type = pars[i];
            } else if (pars[i] == "-f" || pars[i] == "--file") {
                ret.inputFile = pars.at(i + 1);
            } else if (pars[i] == "-o" || pars[i] == "--output") {
                ret.outputFile = pars.at(i + 1);
            }
        }
    } catch (...) {
        throw BadArgumentException("Not enough arguments");
    }

    if (!ret.isCorrect()) throw BadArgumentException("Not enough arguments");
    return ret;
}

int main(int argc, char **argv) {
    try {
        auto pars = getParameters(argc, argv);
        FileReadWriter fl;
        auto dat = fl.readFile(pars.inputFile);
        auto processor = HuffmanProcessor::Processor::getProcessorByType(pars.type);
        auto res = processor->process(dat);
        fl.writeToFile(pars.outputFile, res);

        // print stat
        if (pars.type == "-u") {
            std::cout << dat.size() - DOP_SIZE << std::endl;
            std::cout << res.size() << std::endl;
            std::cout << DOP_SIZE << std::endl;
        } else {
            std::cout << dat.size() << std::endl;
            std::cout << res.size() - DOP_SIZE << std::endl;
            std::cout << DOP_SIZE << std::endl;
        }

        delete processor;
    } catch (const BadArgumentException &e) {
        std::cout << e.what() << "\n";
    }

    return 0;
}

