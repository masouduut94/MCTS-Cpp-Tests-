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
        Node node = Node(this->root);
        Node* nodeptr = &node;

        //      stop if we find reach a leaf node
        while (nodeptr->has_children()) {
                //      Descend to the maximum value node, break ties at random
                nodeptr = nodeptr->best_move(true);
                std::pair<int, int> move = nodeptr->get_move();
                state.play(move);

                //     if some child node has not been explored select it before expanding \
                        other children
                if (nodeptr->get_N() == 0) {
                        return std::make_pair(nodeptr, state);
                }
                if (this->expand(nodeptr, state)) {
                        nodeptr = nodeptr->best_move(true);
                        state.play(nodeptr->get_move());
                }
        }
        return std::make_pair(nodeptr, state);
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
        /*
        Simulate an entirely random game from the passed state and return the winning
        player.

        Args:
            state: game state

        Returns:
            int: winner of the game
        */

        std::vector<Cell> moves = state.get_moves();
        while (state.winner() == PLAYERS["none"]) {
                Cell move = *select_randomly(moves.begin(), moves.end());
                state.play(move);
                moves.erase(std::find(moves.begin(), moves.end(), move));  // TODO: Optimize this part.!!!!
        }

        return state.winner();
}

void MctsAgent::back_up(Node* node, int turn, int outcome){
        /*
        Update the node statistics on the path from the passed node to root to reflect
        the outcome of a randomly simulated playout.

        Args:
            node:
            turn: winner turn
            outcome: outcome of the rollout

        Returns:
            object:
        */
        int reward = (turn == outcome) ? 0 : 1;
        Node* nodeptr = new Node(*node);

        while (nodeptr != NULL) {
                nodeptr->update_reward(reward);
                nodeptr = nodeptr->get_parent();
                reward = (reward == 0) ? 1 : 0;
        }
}

std::pair<bool, std::pair<int, int>> MctsAgent::best_move(){
        /*
        Return the best move after analysis of the root children simulations.
        The node with the most number of simulations has the most proof available
        to indicate the best move.        
        */

        if (this->rootstate.winner() != PLAYERS["none"]) {
                std::pair<bool, std::pair<int, int>> output = { false, {-100, -100} };
                return output;
        }

        std::pair<int, int> output = this->root.best_move(false)->get_move();

        return std::make_pair(true, output);
}

void MctsAgent::move(std::pair<int, int> move){
        
        /*
        1 - Disconnect the child from parent
        2 - Pop out the child from old root children.
        3 - Delete the other children and free the memory.
        4 - Rewrite a self-destruction method that can remove its children properly.
        5 - Play the move in rootstate and replace it.

        */ 
        
        std::pair<bool, Node*> result = this->root.find_child(move);



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
