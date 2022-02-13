#ifndef HW_02_HUFFMAN_H
#define HW_02_HUFFMAN_H

#include <string>
#include <array>
#include <fstream>
#include <vector>
#include <bitset>
#include <cstdint>

const size_t DOP_SIZE = (1 << 10) + 1;

namespace HuffmanProcessor {
    class Processor {
    public:
        static Processor *getProcessorByType(std::string type);

        virtual std::vector<uint8_t> process(const std::vector<uint8_t> &symbols) = 0;

        virtual ~Processor() = default;
    };

    class HuffmanArchiver : public Processor {
    public:
        virtual std::vector<uint8_t> process(const std::vector<uint8_t> &symbols) override;

        void add_symbol(uint8_t &mask, uint8_t &shift, uint8_t code, uint8_t length, std::vector<uint8_t> &dat);
    };

    class HuffmanUnArchiver : public Processor {
    public:
        virtual std::vector<uint8_t> process(const std::vector<uint8_t> &symbols) override;
    };

}

class FileReadWriter {
public:
    std::vector<uint8_t> readFile(std::string filename);

    void writeToFile(std::string filename, std::vector<uint8_t> &mas);
};

#endif //HW_02_HUFFMAN_H
