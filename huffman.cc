// Eriksen Liu

#include "huffman.hh"
#include <iostream>

// method to combine two leaves to become a branch
HTree::tree_ptr_t combine_leaf(int key, int val, HTree::tree_ptr_t left, HTree::tree_ptr_t right)
{
    auto leaf = make_shared<HTree>(key, val, left, right); // make a branch connecting two leaves
    return leaf;                                           // return this branch
}

// constructor of huffman - initialize the frequency table
Huffman::Huffman()
{
    // from 1st - 255th position, initialize to 0
    for (int i = 0; i < Huffman::ALPHABET_SIZE - 1; i++)
        Huffman::frequency_table.push_back(0);
    // add 256th position with frequency of 1 as eof
    Huffman::frequency_table.push_back(1);
    return;
}

// method to make a huffman tree
HTree::tree_ptr_t Huffman::create_tree()
{
    // initialize trees of every node with regarding to frequency table into the forest
    for (int i = 0; i < Huffman::ALPHABET_SIZE; i++)
    {
        HTree::tree_ptr_t leaf = combine_leaf(i, Huffman::frequency_table[i], nullptr, nullptr);
        Huffman::huffman_forest.add_tree(leaf);
    }

    // if there is more than 1 tree in the forest, then combine the branches with lowest value with a new branch
    while (Huffman::huffman_forest.size() != 1)
    {
        // pop the branch with lowest value twice, record their ptr and make a branch connecting them.
        HTree::tree_ptr_t leaf1 = Huffman::huffman_forest.pop_tree();
        int value1 = leaf1->get_value();
        HTree::tree_ptr_t leaf2 = Huffman::huffman_forest.pop_tree();
        int value2 = leaf2->get_value();
        int value = value1 + value2;
        // add the new tree into the forest with negative key
        HTree::tree_ptr_t leaf3 = combine_leaf(-1, value, leaf1, leaf2);
        Huffman::huffman_forest.add_tree(leaf3);
    }
    // pop the tree in the forest for the next usage.
    auto result = Huffman::huffman_forest.pop_tree();
    // return the huffman tree
    return result;
}

Huffman::bits_t Huffman::encode(int symbol)
{
    // firstly, create a huffman tree
    HTree::tree_ptr_t tree = create_tree();
    // find the path to symbol
    auto path = tree->path_to(symbol);
    Huffman::bits_t result;
    auto path_front = (*(path)).begin();

    // converting the path into boolean value and adding them into result
    for (path_front; path_front != (*(path)).end(); path_front++)
    {
        if (*path_front == HTree::Direction::LEFT)
        {
            result.push_back(0);
        }
        else
        {
            result.push_back(1);
        }
    }

    // update the frequency for this symbol in the frequency table
    Huffman::frequency_table[symbol]++;
    // return the path as vectors of boolean values
    return result;
}

int Huffman::decode(bool bits)
{
    // if the bit is the first one of the bits
    if (Huffman::huffman_forest.size() == 0)
    {
        // create the huffman tree
        HTree::tree_ptr_t tree = create_tree();

        // find the symbol
        if (bits == 0)
        {
            // go the left leaf
            auto left = Huffman::huffman_forest.forest_vector.front()->get_child(HTree::Direction::LEFT);
            // get the key is negative (branch of other leaves)
            if (left->get_key() < 0)
            {
                // pop the huffman tree
                Huffman::huffman_forest.pop_tree();
                // focusing on the left branch (left be the only tree in the forest)
                Huffman::huffman_forest.add_tree(left);
                return -1;
            }
            // if the key of left branch is greater of equal to 0 (a symbol)
            else
            {
                // get the key to return
                auto result = left->get_key();
                // clear the forest
                huffman_forest.pop_tree();
                // update the frequency_table
                Huffman::frequency_table[result]++;
                return result;
            }
        }
        // same logic as bits == 0;
        else
        {
            auto right = Huffman::huffman_forest.forest_vector.front()->get_child(HTree::Direction::RIGHT);
            if (right->get_key() < 0)
            {
                Huffman::huffman_forest.pop_tree();
                Huffman::huffman_forest.add_tree(right);
                return -1;
            }
            else
            {
                auto result = right->get_key();
                huffman_forest.pop_tree();
                Huffman::frequency_table[result]++;
                return result;
            }
        }
    }
    // if not the first bit of bits
    else
    {
        // still same logic as before (if branch -> pop the original tree and go to subtree; if leaf -> return key and update frequency table)
        if (bits == 0)
        {
            auto left = Huffman::huffman_forest.forest_vector.front()->get_child(HTree::Direction::LEFT);
            if (left->get_key() < 0)
            {
                Huffman::huffman_forest.pop_tree();
                Huffman::huffman_forest.add_tree(left);
                return -1;
            }
            else
            {
                auto result = left->get_key();
                huffman_forest.pop_tree();
                Huffman::frequency_table[result]++;
                return result;
            }
        }
        else
        {
            auto right = Huffman::huffman_forest.forest_vector.front()->get_child(HTree::Direction::RIGHT);
            if (right->get_key() < 0)
            {
                Huffman::huffman_forest.pop_tree();
                Huffman::huffman_forest.add_tree(right);
                return -1;
            }
            else
            {
                auto result = right->get_key();
                huffman_forest.pop_tree();
                Huffman::frequency_table[result]++;
                return result;
            }
        }
    }
    // return some integer
    return -1;
}
