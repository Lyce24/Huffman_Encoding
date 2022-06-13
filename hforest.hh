// Eriksen Liu

#pragma once
#include "htree.hh"
#include <list>
#include <vector>
#include <memory>

using namespace std;

class HForest
{

public:
      std::vector<HTree::tree_ptr_t> forest_vector; // create a vector space to store trees

      HForest() = default; // nothing to do here
      ~HForest() = default;

      // claim the functions needed
      int size();
      void add_tree(HTree::tree_ptr_t tree);
      HTree::tree_ptr_t pop_tree();
};
