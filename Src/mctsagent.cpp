
#include "../Header/MctsAgent.h"

void MctsAgent::search(int time_budget){


}

std::pair<Node, GameState> MctsAgent::select_node(){



        return std::pair<Node, GameState>(); 
}

bool MctsAgent::expand(Node parent, GameState state){


        return false;
}

int MctsAgent::roll_out(GameState state){


        return 0;
}

void MctsAgent::back_up(Node* node, int turn, int outcome){


}

std::pair<int, int> MctsAgent::best_move(){


        return std::pair<int, int>();
}

void MctsAgent::move(std::pair<int, int>){
}

void MctsAgent::set_gamestate(GameState state){
}

std::tuple<int, int, int> MctsAgent::statistics(){
    return std::tuple<int, int, int>();
}

int MctsAgent::tree_size(){
    return 0;
}
