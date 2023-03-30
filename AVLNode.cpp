#include "AVLNode.hpp"

#include <iostream>

using namespace std;

AVLNode* rotateWithLeftChild(AVLNode *k2);
AVLNode* rotateWithRightChild(AVLNode *k2);

int getHeight(AVLNode *n)
{
  if (!n) // (n==NULL)
    {
      return 0;
    }
  else
    {
      return n->height();
    }
}

std::ostream&
AVLNode::print(std::ostream &os) const
{
  os << _val
     << " (" << getHeight(_left) << "<->" << getHeight(_right) << ")";
  return os;
}


AVLNode* rotateWithLeftChild(AVLNode *k2)
{
  AVLNode *k1 = k2->left();
  k2->left() = k1->right(); // Y
  k1->right() =  k2;

  k2->height() = 1 + max (getHeight(k2->left()), getHeight(k2->right()) );
  k1->height() = 1 + max (getHeight(k1->left()), getHeight(k2) );

  return k1;
}

AVLNode* doubleWithLeftChild(AVLNode *k3)
{
  AVLNode *k1 = k3->left();
  k3->left() = rotateWithRightChild(k1);
  return rotateWithLeftChild(k3);
}

AVLNode* rotateWithRightChild(AVLNode *k2)
{
  AVLNode *k1 = k2->right();
  k2->right() = k1->left(); // Y
  k1->left() =  k2;

  k2->height() = 1 + max (getHeight(k2->left()), getHeight(k2->right()) );
  k1->height() = 1 + max (getHeight(k1->right()), getHeight(k2) );

  return k1;
}

AVLNode* doubleWithRightChild(AVLNode *k3)
{
  AVLNode *k1 = k3->right();
  k3->right() = rotateWithLeftChild(k1);
  return rotateWithRightChild(k3);
}



AVLNode*
AVLNode::insert(SoccerTeam newVal, AVLNode *intoSubTree)
{
  if (intoSubTree==nullptr)
    {
      AVLNode *newRoot = new AVLNode(newVal);
      return newRoot;
    }

  else if (newVal < intoSubTree->_val)
    {
      intoSubTree->_left=insert(newVal, intoSubTree->_left);

      // update _height for AVL manipulations
      int leftHeight = getHeight(intoSubTree->_left);

      int rightHeight = getHeight(intoSubTree->_right);

      // might need AVL rotations
      if (leftHeight-rightHeight==2) // imbalance in left
	{
	  // is this a left-left imbalance?
	  if (newVal < intoSubTree->_left->_val )
	    {
	      intoSubTree=rotateWithLeftChild(intoSubTree);
	    }
	  // or is it a left-rght imabalance?
	  else
	    {
	      intoSubTree=doubleWithLeftChild(intoSubTree);
	    }
	}
    }
  else if (newVal > intoSubTree->_val)
    {
      intoSubTree->_right=insert(newVal, intoSubTree->_right);

      // update _height for AVL manipulations
      int leftHeight = getHeight(intoSubTree->_left);

      int rightHeight = getHeight(intoSubTree->_right);

      // might need AVL rotations
      if (rightHeight-leftHeight==2) // imbalance in right
	{
	  // is this a right-right imbalance?
	  if (newVal >  intoSubTree->_right->_val )
	    {
	      intoSubTree=rotateWithRightChild(intoSubTree);
	    }
	  // or is it a right-left imabalance?
	  else
	    {
	      intoSubTree=doubleWithRightChild(intoSubTree);
	    }
	}
    }
  else // node value already in tree (==)
    {
    }

  intoSubTree->height() = 1 + max(getHeight(intoSubTree->left()),
				  getHeight(intoSubTree->right()) ); 

  return intoSubTree;
}

AVLNode*
AVLNode::remove(SoccerTeam existingVal, AVLNode *fromSubTree)
{
  if (!fromSubTree)
    return nullptr;

  if (existingVal < fromSubTree->_val)
    {
      fromSubTree->left() = remove(existingVal, fromSubTree->left() );
    }
  else if (existingVal > fromSubTree->_val)
    {
      fromSubTree->right() = remove(existingVal, fromSubTree->right() );
    }
  else // this is the node I want to remove!
    {
      if (fromSubTree->isLeaf())  // 0 children
	{
	  fromSubTree=nullptr;
	}
      else if (fromSubTree->left() && fromSubTree->right() ) // 2 children
	{
	  AVLNode *toDel = fromSubTree->left();
	  while(toDel->right()!=nullptr)
	    {
	      toDel = toDel->right();
	    }

	  SoccerTeam valueToMove = toDel->value();

	  fromSubTree->left()=remove(valueToMove, fromSubTree->left());
	  fromSubTree->value() = valueToMove;
	}
      else // 1 child
	{
	  if (fromSubTree->left() )
	    fromSubTree = fromSubTree->left();
	  else // onlyhave right child
	    fromSubTree = fromSubTree->right();
	}
      
    }

  if (!fromSubTree)
    return nullptr;
  
  // rebalance now if needed
  int balance = getHeight(fromSubTree->left()) -
                getHeight(fromSubTree->right()) ;

  // is the left subtree of height more than 2 bigger than right subtree
  if (balance==2)
    {
      int subBalance = getHeight(fromSubTree->left()->left()) -
	               getHeight(fromSubTree->left()->right());

      // left-left issue
      if (subBalance >= 0)
	{
	  fromSubTree = rotateWithLeftChild(fromSubTree);
	}
      else // left-right issue
	{
	  fromSubTree = doubleWithLeftChild(fromSubTree);
	}
    }
  
  // is the right subtree of height more than 2 bigger than left subtree
  if (balance==-2)
    {
      int subBalance = getHeight(fromSubTree->right()->left()) -
	               getHeight(fromSubTree->right()->right());

      // right-right issue
      if (subBalance < 0)
	{
	  fromSubTree = rotateWithRightChild(fromSubTree);
	}
      else // left-right issue
	{
	  fromSubTree = doubleWithRightChild(fromSubTree);
	}
    }

  fromSubTree->_height = 1 + max( getHeight(fromSubTree->left()) ,
				  getHeight(fromSubTree->right()) );
  
  return fromSubTree;
}
int //store the number of nodes visited during a look up
AVLNode::visited(SoccerTeam val, AVLNode *root) 
{
 	if (root->value() == val) //if the value of the current node is the same as the value searched 
      	{
           	return 1; //return 1
        }
    	else if (root->value() < val) //if it is smaller go right
        { 
           	return 1 + visited(val, root->right()); //add one and keep looking up
        }
        else if (root->value() > val)//if it is bigger go left
        {
             	return 1 + visited(val, root->left()); //add one and keep looking up
        }
   
   return 0;

}
ostream& operator<<(ostream &os, const AVLNode &n)
{
  return n.print(os);
}
