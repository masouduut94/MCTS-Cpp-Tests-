#include <gtest/gtest.h>
#include <vector>
#include "Header/Node.h"


struct NodeTest : public testing::Test {
        Cell move;
        Cell ch1;
        Cell ch2;
        Cell ch3;
        Cell ch4;
        Node root;
        std::vector<Cell> moves;

        void SetUp() {
                move = { 3, 5 };
                root = { move, nullptr };
                ch1 = { 1, 2 };
                ch2 = { 3, 4 };
                ch3 = { 10, 4 };
                ch4 = { 22, 5 };

                moves = { ch1, ch2, ch3 };
                root.add_children(moves);
        }

        void TearDown() {

        }
};


TEST_F(NodeTest, FindChildNodeRelated2Move) {
        std::pair<bool, Node*> output;
        output = root.find_child(ch1);
        bool is_found = output.first;
        Cell move1 = output.second->get_move();

        ASSERT_EQ(is_found, true);
        ASSERT_EQ(ch1, move1);

        output = root.find_child(ch4);
        is_found = output.first;
        ASSERT_EQ(is_found, false);
}

// TODO: Enable Node initialization with Null parent and Null move;

// Test node value UCT


//        // Test Node value RAVE
