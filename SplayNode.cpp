#include "SplayNode.hpp"

#include <iostream>

using namespace std;
extern void helper(ostream &os, const SplayNode* node);

/*
int getHeight(const SplayNode *node)
{
  if (node==nullptr)
    return 0;
  else
    return node->height();
}
*/


SplayNode* rotateWithLeftChild(SplayNode *k2)
{
  SplayNode *k1 = k2->left();
  k2->left() = k1->right();  // Y
  k1->right() = k2;
  //k2->height() = 1+ max(getHeight(k2->left()), getHeight(k2->right()) );
  //k1->height() = 1+ max(getHeight(k1->left()), getHeight(k2) );
  return k1;
}

SplayNode* rotateWithRightChild(SplayNode *k2)
{
  SplayNode *k1 = k2->right();
  k2->right() = k1->left();  // Y
  k1->left() = k2;
  //k2->height() = 1+ max(getHeight(k2->left()), getHeight(k2->right()) );
  //k1->height() = 1+ max(getHeight(k1->right()), getHeight(k2) );
  return k1;
}

SplayNode* doubleWithLeftChild(SplayNode *k3)
{
   SplayNode *k1 = k3->left();
   k3->left() = rotateWithRightChild( k1 );
   return rotateWithLeftChild( k3 );
}

SplayNode* doubleWithRightChild(SplayNode *k3)
{
   SplayNode *k1 = k3->right();
   k3->right() = rotateWithLeftChild( k1 );
   return rotateWithRightChild( k3 );
}



SplayNode*
SplayNode::insert(SoccerTeam val, SplayNode *intoSubTree)
{
  if (intoSubTree==nullptr)
    return new SplayNode(val);
  else if (val < intoSubTree->_val)
    {
      intoSubTree->_left=insert(val, intoSubTree->_left);

      /*
      int leftHeight=intoSubTree->_left->_height;
      int rightHeight=0;
      if (intoSubTree->_right!=nullptr)
	rightHeight=intoSubTree->_right->_height;
      
      if (leftHeight-rightHeight==2)
	{
	  if (val < intoSubTree->left()->value() )
	    {
	      intoSubTree = rotateWithLeftChild(intoSubTree); //case 1
	    }
	  else
            intoSubTree = doubleWithLeftChild(intoSubTree); // case 2
	}
      */
    }
  else if (val > intoSubTree->_val)
    {
      intoSubTree->_right=insert(val, intoSubTree->_right);

      /*
      int rightHeight=intoSubTree->_right->_height;
      int leftHeight=0;
      if (intoSubTree->_left!=nullptr)
	leftHeight=intoSubTree->_left->_height;
      if (rightHeight - leftHeight ==2)
	{
	  if (val > intoSubTree->right()->value() )
	    {
	      intoSubTree = rotateWithRightChild(intoSubTree); //case 4
	    }
	  else
	    intoSubTree = doubleWithRightChild(intoSubTree); // case 3
	}
      */
    }
  else // equal
    ;

  /*
  intoSubTree->height() = 1+max( getHeight(intoSubTree->left()),
				 getHeight(intoSubTree->right()) );
  */
  return intoSubTree;
}


extern void helper(ostream &os, const SplayNode* node);
int visited = 0;
SplayNode*
SplayNode::lookup(SoccerTeam val, SplayNode *subTree)
{
  if (subTree==nullptr)
    return nullptr;

  
  if (subTree->_val == val)
    	return subTree;

  // check left child
  if (val<subTree->_val)
    {
      if (!subTree->left())
	return subTree;
      // LL case
      if (val < subTree->left()->_val)
	{
	  // recursively bring val to root of left-left
	  subTree->left()->left()=lookup( val, subTree->left()->left() );
	  
	  // now rotate the current root right
	  subTree=rotateWithLeftChild(subTree);
	  
	  //note: second rotation is below (common for LL and LR case)
	}
      else if  (val > subTree->left()->_val)
	{
	  // recursively bring val to root of left-right
	  subTree->left()->right()=lookup( val, subTree->left()->right() );
	  
	  // if exists, do first step of RL (second is below)
	  if (subTree->left()->right())
	    subTree->left() = rotateWithRightChild(subTree->left());
	}
      
      if (!subTree->left())
      {
	return subTree;
       }
      else
      {
	return rotateWithLeftChild(subTree);
      }
    }
  // check right child
  else // val>subTree->value()
    {
      if (!subTree->right())
      {
	return subTree;
	}
      
      // RR case
      if (val > subTree->right()->_val)
	{
	  // recursively bring val to root of right-right
	  subTree->right()->right()=lookup( val, subTree->right()->right() );
	  
	  // now rotate the current root left
	  subTree=rotateWithRightChild(subTree);
	  
	  //note: second rotation is below (common for LL and LR case)
	}
      else if  (val < subTree->right()->_val)
	{
	  // recursively bring val to root of right-left
	  subTree->right()->left()=lookup( val, subTree->right()->left() );
	  
	  // if exists, do first step of LR (second is below)
	  if (subTree->right()->left())
	  {
	    subTree->right() = rotateWithLeftChild(subTree->right());
	  }
	}
      
      if (!subTree->right())
      {
	return subTree;
      }
      else
      {
	return rotateWithRightChild(subTree);
      }
    }
}
int
SplayNode::visited(SoccerTeam val, SplayNode *root) 
{
  		if (root->value() == val) //if the value node equals the Team we are looking
      		{
           		return 1; //RETURN 1
       	}
    		else if (root->value() < val) //else if it is smaller go to the right
       	{ 
           		return 1 + visited(val, root->right()); //add one and repeat recursively
       	}
       	else if (root->value() > val)//else if it is bigger go to the left
         	{
             		return 1 + visited(val, root->left()); //add one and repeat recursively
         	}
         	return 0;

} 
ostream&
SplayNode::print(ostream &os) const
{
  os << _val;//<< "(" << getHeight(_left) << "<->" << getHeight(_right) << ')';
  return os;
}

ostream& operator<<(ostream &os, const SplayNode &n)
{
  return n.print(os);
}
