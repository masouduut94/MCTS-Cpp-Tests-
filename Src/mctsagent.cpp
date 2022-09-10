
#include "../Header/MctsAgent.h"

MctsAgent::MctsAgent(GameState state){
        std::pair<int, int> move = { -1, -1 };
        this->root = Node(move, nullptr);
        /*
            To check if a ptr is null or not.
            int* ptr = nullptr;
    
            if (!ptr){
                cout << "OK";
            }
        */
        this->rootstate = state;
        this->run_time = 0;
        this->node_count = 0;
        this->num_rollouts = 0;
}

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
        this->rootstate = state;
        Cell move = { -1, -1 };
        this->root.remove_children();
        this->root = Node(move, nullptr);

}

std::tuple<int, int, int> MctsAgent::statistics(){
    return std::tuple<int, int, int>();
}

int MctsAgent::tree_size(){
    return 0;
}
