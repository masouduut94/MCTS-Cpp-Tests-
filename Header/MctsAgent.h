#include "GameState.h"
#include "Node.h"

#pragma once
class MctsAgent
{
private:
        GameState rootstate;
        Node root;

public:
        void search(int time_budget) {};
        std::pair<Node, GameState> select_node() {};
        bool expand(Node parent, GameState state) {};
        int roll_out(GameState state) {};
        void back_up(Node* node, int turn, int outcome) {};
        std::pair <int, int> best_move() {};
        void move(std::pair<int, int>) {};
        void set_gamestate(GameState state) {};
        std::tuple<int, int, int> statistics() {};
        int tree_size(){}


};

