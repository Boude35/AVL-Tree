#include "SplayTree.hpp"

using namespace std;


int depth2=0;

void
SplayTree::remove(SoccerTeam val)
{
  // move node to remove to top, splaying along the way
  lookup(val);

  SplayTree TL;
  TL._root = _root->left();
  SplayTree TR;
  TR._root = _root->right();

  if (TL._root==nullptr)
    {
      _root=TR._root;
    }
  else
    {
      // find max node in TL
      SplayNode *maxNode=TL._root;
      while(maxNode->right()!=nullptr)
	maxNode=maxNode->right();

      // move maxNode to root ot TL
      TL.lookup(maxNode->value());

      // make TR right child of TL
      TL._root->right()=TR._root;

      _root=TL._root; 
    }
}
int
SplayTree::visited2(SoccerTeam val)
{
  if (!_root)// if there is no root
    return 0;
  else
    {
      return _root->visited(val, _root);//return the value of nodes visited starting at the root
    }
}

void helper(ostream &os, const SplayNode* node)
{
  if (!node) return;

  depth2++;
  helper(os, node->right());
  depth2--;

  for (int i=0; i< depth2; i++)
    os << "    ";


  os << *node << endl;

  depth2++;
  helper(os, node->left());
  depth2--;
}

ostream&
SplayTree::display(ostream &os) const
{
  depth2=0;
  helper(os, _root);
  return os;
}
