#include "AVLTree.hpp"

#include <iostream>

using namespace std;

void
AVLTree::insert(SoccerTeam newVal)
{
  if (!_root)
    _root = new AVLNode(newVal);
  _root = _root->insert(newVal, _root);
}

void
AVLTree::remove(SoccerTeam toDel)
{
  if (!_root)
    return;
  else
    {
      _root = _root->remove(toDel, _root);
    }
}




int depth;

void helper(ostream &os, AVLNode *node)
{
  if (!node) return;

  depth++;
  helper(os, node->right());
  depth--;

  for (int i=0; i<depth; i++)
    os << "    ";
  
  node->print(os);
  os << endl;

  depth++;
  helper(os, node->left());
  depth--;
  
}

int
AVLTree::visited2(SoccerTeam val)
{
  if (!_root)//if there is no root
    return 0;
  else
    {
      return _root->visited(val, _root);//start at the root of the tree
    }
}

ostream& 
AVLTree::display(ostream &os) const
{
  depth=0;
  helper(os, _root);
  return os; 
}
