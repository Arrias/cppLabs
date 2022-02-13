#ifndef HW_02_HUFFMAN_UTIL_H
#define HW_02_HUFFMAN_UTIL_H

const int BYTES = 1 << 8;

namespace HuffmanTools {

    struct HuffmanNode {
        HuffmanNode *left_son, *right_son;
        float freqSum;
        int byteNum;

        HuffmanNode(float initSum, int initByteNum);

        HuffmanNode *nxt(uint8_t type);

        bool isLeaf();

        ~HuffmanNode();
    };

    struct HuffmanComparator {
        bool operator()(const HuffmanNode *left, const HuffmanNode *right);
    };

    struct code {
        std::bitset<BYTES> _dat{};
        size_t length{};

        code(std::bitset<BYTES> &init_dat, size_t init_len);

        uint8_t sub_code(size_t l, size_t r);

        code() = default;
    };

    struct Table {
        std::array<code, BYTES> codes{};
    };

    class HuffmanBuilder {
    public:
        HuffmanBuilder(std::array<float, BYTES> freq);

        ~HuffmanBuilder();

        Table getTable(); // public wrapper of ::put_codes

        HuffmanNode *get_root() const;

    private:
        HuffmanNode *root{};

        void put_codes(HuffmanNode *node, std::bitset<BYTES> &code, uint8_t length, Table &out);
    };
};

#endif //HW_02_HUFFMAN_UTIL_H
