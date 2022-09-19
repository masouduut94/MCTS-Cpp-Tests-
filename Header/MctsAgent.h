#include "GameState.h"
#include "Node.h"
#include "utils.h"

using namespace GameMeta;

#pragma once
class MctsAgent{
private:
        GameState rootstate;
        Node* root; // TODO: Replace it with dynamic memory.
        float run_time=0;
        int num_rollouts=0;
        int node_count=0;

public:
        MctsAgent() {
                this->root = new Node();
                this->rootstate = GameState()
        };
        MctsAgent(GameState state);
        void search(int time_budget);
        std::pair<Node*, GameState> select_node();
        bool expand(Node* parent, GameState state);
        int roll_out(GameState state);
        void back_up(Node* node, int turn, int outcome);
        std::pair<bool, std::pair<int, int>> best_move();
        void move(std::pair<int, int>);
        void set_gamestate(GameState state);
        std::tuple<int, int, int> statistics();
        int tree_size();


};

