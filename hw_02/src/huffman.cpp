#include <cstring>
#include <queue>
#include "huffman.h"
#include "huffman_util.h"

using namespace HuffmanProcessor;
using namespace HuffmanTools;

const size_t BYTE_SIZE = 1 << 3;

std::vector<uint8_t> FileReadWriter::readFile(std::string filename) {
    std::ifstream in;
    in.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    in.open(filename);

    std::vector<uint8_t> ret;

    auto it = std::istreambuf_iterator<char>(in);
    while (it != std::istreambuf_iterator<char>()) {
        ret.push_back(*it);
        it++;
    }

    in.close();
    return ret;
}

void FileReadWriter::writeToFile(std::string filename, std::vector<uint8_t> &mas) {
    std::ofstream out;
    out.exceptions(std::ofstream::failbit | std::ofstream::badbit);
    out.open(filename);

    for (uint8_t i : mas) {
        out.write((char *) &i, sizeof(uint8_t));
    }
}

HuffmanNode::HuffmanNode(float initSum, int initByteNum) : left_son(nullptr), right_son(nullptr), freqSum(initSum), byteNum(initByteNum) {}

HuffmanNode::~HuffmanNode() {
    if (isLeaf()) return;
    if (left_son) {
        delete left_son;
    }
    if (right_son) {
        delete right_son;
    }
}

bool HuffmanNode::isLeaf() {
    return left_son == right_son && !left_son;
}

HuffmanNode *HuffmanNode::nxt(uint8_t type) {
    return type ? left_son : right_son;
}

bool HuffmanComparator::operator()(const HuffmanNode *left, const HuffmanNode *right) {
    if (left->freqSum != right->freqSum) {
        return left->freqSum > right->freqSum;
    }
    return left->byteNum > right->byteNum;
}

HuffmanBuilder::HuffmanBuilder(std::array<float, BYTES> freq) {
    std::priority_queue<HuffmanNode *, std::vector<HuffmanNode *>, HuffmanComparator> nodes;

    for (int i = 0; i < BYTES; ++i) {
        if (freq[i] > 0) {
            nodes.push(new HuffmanNode(freq[i], i));
        }
    }

    if (!nodes.size()) return;
    if (nodes.size() == 1) {
        root = new HuffmanNode(BYTE_SIZE, BYTE_SIZE);
        root->left_son = nodes.top();
        return;
    }

    while (nodes.size() > 1) {
        auto first_node = nodes.top();
        nodes.pop();
        auto second_node = nodes.top();
        nodes.pop();
        auto mergeNode = new HuffmanNode(first_node->freqSum + second_node->freqSum, std::max(first_node->byteNum, second_node->byteNum));
        mergeNode->left_son = first_node;
        mergeNode->right_son = second_node;
        nodes.push(mergeNode);
    }

    root = nodes.top();
}

HuffmanBuilder::~HuffmanBuilder() {
    if (root != nullptr) {
        delete root;
    }
}

Table HuffmanBuilder::getTable() {
    Table ret;
    if (root != nullptr) {
        std::bitset<BYTES> init;
        put_codes(root, init, 0, ret);
    }
    return ret;
}

void HuffmanBuilder::put_codes(HuffmanNode *node, std::bitset<BYTES> &cur_code, uint8_t length, Table &out) {
    if (node == nullptr) return;
    if (node->isLeaf()) {
        out.codes[node->byteNum] = code(cur_code, length);
        return;
    }
    cur_code.set(length);
    put_codes(node->left_son, cur_code, length + 1, out);
    cur_code.reset(length);
    put_codes(node->right_son, cur_code, length + 1, out);
}

HuffmanNode *HuffmanBuilder::get_root() const {
    return root;
}

std::vector<uint8_t> HuffmanArchiver::process(const std::vector<uint8_t> &symbols) {
    std::array<float, BYTES> freq{};
    for (uint8_t c : symbols) {
        freq[c]++;
    }

    float volume = symbols.size();
    std::vector<uint8_t> ret;
    for (float &i : freq) {
        i /= volume;
        uint8_t temp[sizeof(float)];
        std::memcpy(temp, &i, sizeof(float));
        for (size_t bt = 0; bt < sizeof(float); ++bt) {
            ret.push_back(temp[bt]);
        }
    }

    HuffmanBuilder hb(freq);
    auto table = hb.getTable();

    uint8_t sumOfLength = 0;
    for (uint8_t c : symbols) {
        sumOfLength += table.codes[c].length;
    }
    ret.push_back((BYTE_SIZE - sumOfLength % BYTE_SIZE) % BYTE_SIZE);

    uint8_t mask = 0, shift = 0;
    for (uint8_t c : symbols) {
        for (size_t j = 0; j < table.codes[c].length; j += BYTE_SIZE) {
            size_t sub_code_size = std::min(BYTE_SIZE, table.codes[c].length - j);
            add_symbol(mask, shift, table.codes[c].sub_code(j, j + sub_code_size), sub_code_size, ret);
        }
    }

    if (shift > 0) {
        ret.push_back(mask);
    }
    return ret;
}

void HuffmanArchiver::add_symbol(uint8_t &mask, uint8_t &shift, uint8_t code, uint8_t length, std::vector<uint8_t> &dat) {
    uint8_t rem = BYTE_SIZE - shift;
    if (rem >= length) {
        mask ^= (code << shift);
        shift += length;
        return;
    }
    uint8_t sep = (1 << rem) - 1;
    mask ^= ((code & sep) << shift);
    dat.push_back(mask);
    shift = length - rem;
    mask = ((code & (~sep)) >> rem);
}

std::vector<uint8_t> HuffmanUnArchiver::process(const std::vector<uint8_t> &symbols) {
    std::array<float, BYTES> freq{};

    size_t id = 0;
    for (float &i : freq) {
        uint8_t bs[] = {symbols[id], symbols[id + 1], symbols[id + 2], symbols[id + 3]};
        memcpy(&i, &bs, sizeof(float));
        id += sizeof(float);
    }

    HuffmanBuilder hb(freq);
    uint8_t rem = symbols[id++];

    std::vector<uint8_t> ret;
    auto cur_node = hb.get_root();
    while (id < symbols.size()) {
        size_t lim = ((int) id == (int) symbols.size() - 1) ? BYTE_SIZE - rem : BYTE_SIZE;
        for (size_t j = 0; j < lim; ++j) {
            cur_node = cur_node->nxt((symbols[id] >> j) & 1);
            if (cur_node->isLeaf()) {
                ret.push_back(cur_node->byteNum);
                cur_node = hb.get_root();
            }
        }
        id++;
    }

    return ret;
}

Processor *Processor::getProcessorByType(std::string type) {
    if (type == "-u") return new HuffmanUnArchiver();
    return new HuffmanArchiver();
}

code::code(std::bitset<BYTES> &init_dat, size_t init_len) : _dat(init_dat), length(init_len) {}

uint8_t code::sub_code(size_t l, size_t r) {
    uint8_t ret = 0;
    for (size_t i = l; i < r; ++i) {
        ret ^= (_dat.test(i) << (i - l));
    }
    return ret;
}
