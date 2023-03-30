#ifndef _SPLAY_NODE_HPP_
#define _SPLAY_NODE_HPP_

#include <iostream>
#include "SoccerTeam.hpp"

class SplayNode
{
private:
  SoccerTeam _val;
  SplayNode *_left;
  SplayNode *_right;
public:
  SplayNode(SoccerTeam val)
    : _val(val), _left(nullptr), _right(nullptr) {}

  std::ostream& print(std::ostream &os) const;

  const SoccerTeam value() const {return _val;}
  SoccerTeam& value() {return _val;}

  const SplayNode* left() const {return _left;}
  SplayNode* & left() {return _left;}

  const SplayNode* right() const {return _right;}
  SplayNode* & right() {return _right;}

  bool isLeaf() const { return !_left&&!_right; }
  
  SplayNode* insert(SoccerTeam newVal, SplayNode *intoSubTree);

  //  SplayNode* remove(int existingVal, SplayNode *fromSubTree);

  SplayNode* lookup(SoccerTeam val, SplayNode *subTree);
  int visited(SoccerTeam val, SplayNode *root);//nodes visited (I know it could be implemented using with the lookup function but I found this simpler)
  friend std::ostream& operator<<(std::ostream &os, const SplayNode &n);
};


#endif
