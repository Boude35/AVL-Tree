#ifndef _AVL_NODE_HPP_
#define _AVL_NODE_HPP_

#include <iostream>
#include "SoccerTeam.hpp"

class AVLNode
{
private:
  SoccerTeam _val;
  AVLNode *_left;
  AVLNode *_right;
  int _height;
public:
  AVLNode(SoccerTeam val):_val(val), _left(nullptr), _right(nullptr), _height(1) {}

  SoccerTeam value() const {return _val;}
  SoccerTeam& value() {return _val;}
  
  AVLNode* left() const {return _left;}
  AVLNode* &left() {return _left;}

  AVLNode* right() const {return _right;}
  AVLNode* &right() {return _right;}

  int height() const {return _height;}
  int &height()  {return _height;}

  bool isLeaf() const {return !_left && !_right;}
  
  std::ostream& print(std::ostream &os) const;
  /*{
    os << _val << " (" << _left->_height << "<->" << _right->_height << ")";
    return os;
  }
  */
  
  AVLNode* insert(SoccerTeam newVal, AVLNode *intoSubTree);
  AVLNode* remove(SoccerTeam exstingVal, AVLNode *fromSubTree); 
  int visited(SoccerTeam val, AVLNode *root); //declaration
  friend  std::ostream& operator<<(std::ostream &os, const AVLNode &n); 
};

#endif
