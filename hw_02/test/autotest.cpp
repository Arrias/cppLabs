#include "doctest.h"
#include "huffman.h"
#include "huffman_util.h"

using namespace HuffmanTools;
using namespace HuffmanProcessor;

int main() {
    doctest::Context context;
    context.run();
}

//================ HuffmanNode Test ===================

TEST_CASE("HuffmanNode::nxt") {
    HuffmanNode *ord = new HuffmanNode(13.0, 14);
    CHECK(ord->nxt(0) == nullptr);
    CHECK(ord->nxt(1) == nullptr);
    HuffmanNode *left_son = new HuffmanNode(15.0, 13);
    ord->left_son = left_son;
    CHECK(ord->nxt(1) == left_son);
    CHECK(ord->nxt(0) == nullptr);
    HuffmanNode *right_son = new HuffmanNode(239.0, 239);
    ord->right_son = right_son;
    CHECK(ord->nxt(0) == right_son);
    std::swap(ord->left_son, ord->right_son);
    CHECK(ord->nxt(1) == right_son);
    CHECK(ord->nxt(0) == left_son);
    delete ord;
}

TEST_CASE("HuffmanNode::isLeaf") {
    HuffmanNode *leaf = new HuffmanNode(239.0, 239);
    CHECK(leaf->isLeaf() == true);
    leaf->left_son = new HuffmanNode(1717.0, 17);
    CHECK(leaf->isLeaf() == false);
    CHECK(leaf->left_son->isLeaf() == true);
    delete leaf;
}

TEST_CASE("HuffmanNode:HuffmanNode") {
    HuffmanNode new_node = HuffmanNode(15, 15);
    CHECK(new_node.byteNum == 15);
    CHECK(new_node.freqSum == 15);
}

//===================== HuffmanComparator =================

TEST_CASE("HuffmanComparator") {
    HuffmanNode *left = new HuffmanNode(13, 14);
    HuffmanComparator cmp;
    CHECK(!cmp(left, left));
    HuffmanNode *right = new HuffmanNode(125, 4234);
    CHECK(!cmp(left, right));
    CHECK(cmp(right, left));
    delete left;
    delete right;
}

//===================== code =================

TEST_CASE("code::sub_code") {
    std::bitset<BYTES> dat;
    dat.set(1);
    dat.set(5);
    dat.set(15);
    dat.set(17);
    dat.set(100);
    dat.set(101);
    dat.set(102);
    code new_code = code(dat, BYTES);
    CHECK(new_code.sub_code(0, 2) == 2);
    CHECK(new_code.sub_code(0, 1) == 0);
    CHECK(new_code.sub_code(0, 8) == 34);
    CHECK(new_code.sub_code(10, 18) == 160);
    CHECK(new_code.sub_code(15, 16) == 1);
    CHECK(new_code.sub_code(100, 103) == 7);
}

//===================== HuffmanBuilder =================

TEST_CASE("HuffmanBuilder::get_root") {
    std::array<float, BYTES> freq{};
    SUBCASE("t1") {
        freq[0] = 0.1;
        freq[1] = 0.1;
        freq[2] = 0.1;
        freq[3] = 0.1;
        HuffmanBuilder hb = HuffmanBuilder(freq);
        auto rt = hb.get_root();
        // check tree structure
        CHECK(rt->left_son->left_son->byteNum == 0);
        CHECK(rt->left_son->right_son->byteNum == 1);
        CHECK(rt->right_son->left_son->byteNum == 2);
        CHECK(rt->right_son->right_son->byteNum == 3);
        CHECK(rt->freqSum == 0.4f);
        CHECK(rt->left_son->freqSum == 0.2f);
        CHECK(rt->left_son->left_son->isLeaf());
        CHECK(rt->right_son->left_son->isLeaf());
    }
    SUBCASE("t2") {
        freq[0] = 0.1;
        freq[1] = 0.2;
        freq[2] = 0.3;
        freq[3] = 0.5;
        freq[4] = 0.8;
        freq[5] = 1.3;
        HuffmanBuilder hb = HuffmanBuilder(freq);
        auto rb = hb.get_root();
        // check tree structure
        CHECK(rb->left_son->freqSum == 1.3f);
        CHECK(rb->left_son->isLeaf());
        CHECK(rb->right_son->left_son->freqSum == 0.8f);
        CHECK(rb->right_son->left_son->isLeaf());
        CHECK(rb->right_son->right_son->freqSum == 1.1f);
        CHECK(rb->right_son->right_son->left_son->isLeaf());
        CHECK(rb->right_son->right_son->right_son->freqSum == 0.6f);
        CHECK(rb->right_son->right_son->right_son->right_son->isLeaf());
    }
}

TEST_CASE("HuffmanBuilder::getTable") {
    std::array<float, BYTES> freq{};
    SUBCASE("t1") {
        freq[0] = 0.1;
        freq[1] = 0.1;
        freq[2] = 0.1;
        freq[3] = 0.1;
        HuffmanBuilder hb = HuffmanBuilder(freq);
        auto tb = hb.getTable();

        // check lengths
        CHECK(tb.codes[0].length == 2);
        CHECK(tb.codes[1].length == 2);
        CHECK(tb.codes[2].length == 2);
        CHECK(tb.codes[3].length == 2);

        // check codes
        CHECK(tb.codes[0]._dat.to_ulong() == 3);
        CHECK(tb.codes[1]._dat.to_ulong() == 1);
        CHECK(tb.codes[2]._dat.to_ulong() == 2);
        CHECK(tb.codes[3]._dat.to_ulong() == 0);
    }
    SUBCASE("t2") {
        freq[0] = 0.1;
        freq[1] = 0.2;
        freq[2] = 0.3;
        freq[3] = 0.5;
        freq[4] = 0.8;
        freq[5] = 1.3;
        HuffmanBuilder hb = HuffmanBuilder(freq);
        auto tb = hb.getTable();

        // check lengths
        CHECK(tb.codes[0].length == 5);
        CHECK(tb.codes[1].length == 5);
        CHECK(tb.codes[2].length == 4);
        CHECK(tb.codes[3].length == 3);
        CHECK(tb.codes[4].length == 2);
        CHECK(tb.codes[5].length == 1);

        // check codes
        CHECK(tb.codes[0]._dat.to_ulong() == 24);
        CHECK(tb.codes[1]._dat.to_ulong() == 8);
        CHECK(tb.codes[2]._dat.to_ulong() == 0);
        CHECK(tb.codes[3]._dat.to_ulong() == 4);
        CHECK(tb.codes[4]._dat.to_ulong() == 2);
        CHECK(tb.codes[5]._dat.to_ulong() == 1);
    }
}









