// Eriksen Liu

/*
 * HTree: a class to represent a tree node with two values: a key
 * and a value.
 */

#include "htree.hh"


// Return an optional list of directions from root to a node of a given key.
// If key not contained in this tree, returns nullptr

// construction method, give parameters in the private sector values
HTree::HTree(key_t key,
             value_t value,
             tree_ptr_t left,
             tree_ptr_t right)
:key_(key), value_(value), left_(left), right_(right)
{}

// Return key in current node
HTree::key_t
HTree::get_key() const
{
  return key_;
}

// Return value in current node
HTree::value_t
HTree::get_value() const
{
  return value_;
}

// Return the child of this node indicated by dir.
// If the child is nullptr (current node is a leaf), returns nullptr.
HTree::tree_ptr_t
HTree::get_child(Direction dir) const
{
  // if go to left
  if (dir == Direction::LEFT)
  {
    // if there is no left branch return nullptr
    if (!left_)
    {
      return nullptr;
    }
    // else, go to left branch
    else
    {
      return left_;
    }
  }
  // similar logics for the right side
  else
  {
    if (!right_)
    {
      return nullptr;
    }
    else
    {
      return right_;
    }
  }
  // since there are only two possible situations here, so we don't need to consider other situations such as direction != left or right.
}

// Return an optional list of directions from root to a node of a given key.
// If key not contained in this tree, returns nullptr
HTree::possible_path_t
HTree::path_to(key_t key) const
{
  possible_path_t empty_list (new path_t()); //new path_t() - make a empty list in the heap, and make path a pointer points to it

  // if the key of the current branch equal to the key passing, then return a pointer points to an empty list in the heap
  if (key_ == key)
  {
    return empty_list;
  }

  // recursive case  
  else
  {
    // if left branch exists, go to left sub-tree 
    if (left_ != nullptr)
    { 
      // make left_case a pointer which point to the result of the left sub-tree
      auto left_case = left_->path_to(key);

      // if left_case is not nullptr, which means the key is in the left sub-tree
      if (left_case != nullptr)
        {
          // push a LEFT at the beginning of the list, and return the pointer to this list
          left_case -> push_front(Direction::LEFT);
          return left_case;
        }
      // else, go to check right branch
    }
    // similar for right side
    if (right_!= nullptr)
    {  
      auto right_case = right_->path_to(key);
      if (right_case != nullptr)
      {
        right_case -> push_front(Direction::RIGHT);
        return right_case;
      }
      // if both left_case and right_case are nullptr, then return nullptr, meanning the key is not found below this node
      else
      {
        return nullptr;
      }
    }
    // if both the right branch and left branch are nullptr, then return nullptr
    else
    {
      return nullptr;
    }
  // if the node doesn't exist, then return nullptr
  return nullptr;
  }  
}
