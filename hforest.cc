// Eriksen Liu

#include "hforest.hh"
#include <algorithm>

// helper function for make_heap to perform a descending order of values
bool compare_trees(HTree::tree_ptr_t t1, HTree::tree_ptr_t t2) {
    return t1->get_value() > t2->get_value();
}

// to get the size of the forest
int HForest::size()
{
    return forest_vector.size();
}

// add trees into the forest
void HForest::add_tree(HTree::tree_ptr_t tree)
{
    forest_vector.push_back(tree);  // simply add one pointer point to the tree into the forest _vector using push_back function
    return;
}


// return the pointer point to the root with lowest value in the forest, and remove it from the forest
HTree::tree_ptr_t HForest::pop_tree()
{  
    // if there is no tree in the forest, then there is no tree to pop, so return nullptr
    if (HForest::size() == 0)
    {
        return nullptr;
    }
    // if there are trees in the forest...
    else
    {
        // make the trees have descending order of values (tree_ptr with lowest value will be the first place in the vector now)
        make_heap(forest_vector.begin(), forest_vector.end(), compare_trees);
        
        // make result eqauls to the first element of the forest_vectore in order to return the tree_ptr
        HTree::tree_ptr_t result = forest_vector.front();

        // erase the first element of the vector using erase()
        forest_vector.erase(forest_vector.begin());

        // return the result
        return result;
    }
}

