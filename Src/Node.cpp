
#include "../Header/Node.h"
#include <iostream>
// ###################################### UCT Node Methods


Node::Node(Node &sample) {
        // DeepCopy function.
        this->parent = sample.parent;
        this->Q = sample.Q;
        this->N = sample.N;
        this->N_RAVE = sample.N_RAVE;
        this->Q_RAVE = sample.Q_RAVE;
        this->OUTCOME = sample.OUTCOME;
        this->children = sample.children;
}

Node::Node(std::pair<int, int> inp_move, Node* parent_inp) {
        this->cell = inp_move;
        this->parent = parent_inp;
        this->Q = 0;
        this->N = 0;
        this->N_RAVE = 0;
        this->Q_RAVE = 0;
        this->children = {};
}

void Node::add_children(std::vector<Cell> list_of_children)
{
        for (std::pair<int, int> item : list_of_children) {
                Node* node = new Node(item, this);
                this->children.push_back(node);
        }
}

void Node::remove_children()
{
        // TODO: TEST THIS
        for (Node* child : this->children) {
                delete child;
        }
}

void Node::display_children()
{
        if (this->children.empty()) {
                return;
        }
        for (Node* ch : this->children) {
                printf("{Cell: '%c-%i'}", ch->get_move_char());
        }
}

double Node::value(const float explore_const, int rave_const) {
        /*
        Description:
                Returns the RAVE + UCT value of node in MCTS algorithm.

        Note:
                If you consider using UCT, just pass -1 for RAVE_CONST.

        */
        if (this->get_move().first == NULL) return NULL;
        else if (N == 0) return GameMeta::INF;
        else {
                double alpha = 0;
                double AMAF = 0.0;
                double UCT = (this->Q / this->N) + (double)(explore_const * (sqrt(log10(static_cast<double>(this->parent->N) / this->N))));
                double explore = sqrt(log10(static_cast<double>(this->parent->N) / this->N));
                if (rave_const > 0) {
                        alpha = std::max(0.0, (static_cast<double>(rave_const - this->N) / rave_const));
                        if (this->N_RAVE != 0) {
                                AMAF = static_cast<double>(this->Q_RAVE / this->N_RAVE);
                        }
                }
                return static_cast<double>((1 - alpha) * UCT + alpha * AMAF);
        }
}

std::pair<char, int> Node::get_move_char() {
        auto a = this->cell;
        char ch = GameMeta::mapper[a.first];
        return std::pair<char, int>(ch, a.second);
}

std::pair<bool, Node*>  Node::find_child(std::pair<int, int> move) {
        /*  Returns the child which constructed for input move.

        */
        bool flag_found = false;
        Node* value = nullptr;
        for (Node* child : this->children) {
                if ((child->get_move() == move)) {
                        flag_found = true;
                        value = child;
                        break;
                }
        }
        return std::make_pair(flag_found, value);
}

Node* Node::best_move(bool by_value) {
        /*  Returns the best child between all existing children nodes based on their
        *    corresponding values or N
        *   Args:
        *       by_value(bool): if set true, the returned node has the maximum value between other nodes,
        *                                 else, the returned node has the maximum number of simulations.

        */
        Node* max;
        std::vector<Node*> temp;
        if (by_value) {
                auto max = *std::max_element(this->children.begin(), this->children.end(),
                        [](Node* a, Node* b) {
                                return a->value() < b->value();
                        });
                for (Node* node : this->children) {
                        if (node->value() == max->value()) {
                                temp.emplace_back(node);
                        }
                }
                auto result = *select_randomly(temp.begin(), temp.end());
                return result;
        }
        else
        {
                auto max = *std::max_element(this->children.begin(), this->children.end(),
                        [](Node* a, Node* b) {
                                return a->get_N() < b->get_N();
                        });

                for (Node* node : this->children) {
                        if (node->get_N() == max->get_N()) {
                                temp.emplace_back(node);
                        }
                }

                auto result = *select_randomly(temp.begin(), temp.end());
                return result;
        }
}

