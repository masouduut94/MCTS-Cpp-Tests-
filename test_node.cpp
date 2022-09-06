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

struct NodeValueTest : public testing::Test {
        Cell move;
        Cell ch1;
        Cell ch2;
        Cell ch3;
        Cell ch4;
        Node root;
        std::vector<Cell> moves;

        void SetUp() {
                // Enable Node initialization with Null parentand Null move;
                move = { NULL, NULL };
                root = { move, nullptr };
                for (int i = 0; i <= 2; i++)
                {
                        for (size_t j = 0; j <= 2; j++)
                        {
                                std::pair <int, int> move = { i, j };
                                moves.push_back(move);
                        }
                }

                root.add_children(moves);

        }

        void TearDown() {

        }
};


TEST_F(NodeValueTest, TestIfBestMoveReturnsTheCorrectMove) 
// Test Node::best_move
{

        std::pair<bool, Node*> result;
        bool flag;
        Node* node;
        for (std::pair<int, int> move : moves)
        {
                result = root.find_child(move);
                flag = result.first;
                ASSERT_TRUE(flag);
                node = result.second;

                if (
                       node->get_move() == std::make_pair(0, 0) || 
                       node->get_move() == std::make_pair(0, 1) ||
                       node->get_move() == std::make_pair(0, 2) ||
                       node->get_move() == std::make_pair(1, 0) ||
                       node->get_move() == std::make_pair(1, 1)
                        )
                {
                        for (size_t i = 0; i < 4; i++)
                        {
                                node->win();
                        }
                }
                else if (
                        node->get_move() == std::make_pair(2, 1) ||
                        node->get_move() == std::make_pair(2, 2) ||
                        node->get_move() == std::make_pair(1, 2)
                        )
                {
                        for (size_t i = 0; i < 3; i++)
                        {
                                node->win();
                        }
                        node->loss();
                }

                else if  (node->get_move() == std::make_pair(2, 0) )
                {
                        for (size_t i = 0; i < 20; i++)
                        {
                                node->win();
                        }
                }
        }
        // Let's see if the (2, 0) move is going to be selected as the best move according to number of simulations.
        Node* best = root.best_move(false);
        move = best->get_move();
        int N = best->get_N();
        ASSERT_EQ(N, 20);
        ASSERT_EQ(move, std::make_pair(2, 0));

}

