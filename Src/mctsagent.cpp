#include "../Header/MctsAgent.h"

using namespace GameMeta;

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

std::pair<Node*, GameState> MctsAgent::select_node(){
        /* 
        Select a node in the tree to preform a single simulation from.
        */


        //     copy the root state and root node because we want \
                to traverse the tree from root to leaf node.
        GameState state = this->rootstate;   
        Node node(this->root);

        //      stop if we find reach a leaf node
        while (node.has_children()) {
                //      Descend to the maximum value node, break ties at random
                Node* node = this->root.best_move(true);
                std::pair<int, int> move = node->get_move();
                state.play(move);

                //     if some child node has not been explored select it before expanding \
                        other children
                if (node->get_N() == 0) {
                        return std::make_pair(node, state);
                }
                if (this->expand(node, state)) {
                        node = node->best_move(true);
                        state.play(node->get_move()); 
                }


        }


        return std::pair<Node*, GameState>(); 
}

bool MctsAgent::expand(Node* parent, GameState state){
        /*
        Generate the children of the input "parent" node based on the available
        moves in the input gamestate and add them to the tree.

        Args:
                parent (Node*): The node that is supposed to be expanded.
                State (GameState): The game state of the `parent` node, that 
                        is used to generate the available moves.

        Returns:
                bool: returns false If node is leaf (the game has ended).
        
        */

        std::vector <Cell> children = {};
        if (state.winner() != PLAYERS["none"]){
                return false;
        }

        for (Cell cell : state.get_moves()) {
                children.emplace_back(cell);
        }

        parent->add_children(children);
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
