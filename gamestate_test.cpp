#include <vector>
#include <gtest/gtest.h>
#include "Header/GameState.h"


struct GameStateTest : public testing::Test {
        GameState state;
        std::vector <Cell> all_cells;
        Cell m1;
        Cell m2;
        Cell m3;
        // Cells to test chaining rule from Top to Bottom (white Player)
        Cell m4;
        Cell m5;
        Cell m6;

        void SetUp() {
                state.set_size(3);
                for (size_t i = 0; i <= state.get_size(); i++)
                {
                        for (size_t j = 0; j <= state.get_size(); j++)
                        {
                                Cell move(i, j);
                                all_cells.push_back(move);
                        }
                }

                // Cells to test chaining rule from Left to Right (Black Player)
                m1 = { 0, 0 };
                m2 = { 0, 1 };
                m3 = { 0, 2 };

                // Cells to test chaining rule from Top to Bottom (white Player)
                m4 = { 0, 0 };
                m5 = { 1, 0 };
                m6 = { 2, 0 };
        }
        void TearDown() {}
};


TEST_F(GameStateTest, Test_Neighbor_Cells) {
        std::vector<Cell> neighbors = state.neighbors(all_cells[0]);
        ASSERT_EQ(neighbors.size(), 2);
}


TEST_F(GameStateTest, Test_Unoccupied_Moves) {
        /**********   TEST2: GameState::get_moves()    ***********/
        // Let's play a move and check if available moves are any different.
        state.play(all_cells[0]);
        std::vector<Cell> available_moves = state.get_moves();
        ASSERT_EQ(available_moves.size(), all_cells.size() - 1);
}


TEST_F(GameStateTest, Test_Chaining_Rule) {
        // We want to test UnionFind module that whether it is detecting the connection between 2 sides for 
        // both black and white players.

        /**********   TEST3: GameState::winner    ***********/
        state.place_black(m1);
        int w = state.winner();
        ASSERT_EQ(GameMeta::PLAYERS["none"], w);

        state.place_black(m2);
        w = state.winner();
        ASSERT_EQ(GameMeta::PLAYERS["none"], w);

        state.place_black(m3);
        w = state.winner();
        ASSERT_EQ(GameMeta::PLAYERS["black"], w);

        // Check if GameState deepCopy creates a new object with no change in values.
        state.reset_board(3);
        GameState state_copy(state);

        state_copy.place_white(m4);
        state_copy.place_white(m5);
        state_copy.place_white(m6);
        ASSERT_EQ(state_copy.winner(), GameMeta::PLAYERS["white"]);
}

