#ifndef _SPLAY_TREE_HPP_
#define _SPLAY_TREE_HPP_

#include <iostream>

#include "SplayNode.hpp"

class SplayTree
{
private:
  SplayNode *_root;
public:
  SplayTree(): _root(nullptr) {}

  std::ostream& display(std::ostream &os) const;

  void insert(SoccerTeam newVal) {if (!_root) _root=new SplayNode(newVal); else _root=_root->insert(newVal, _root);} 

  void remove(SoccerTeam val);// {_root=_root->remove(val, _root);}

  void lookup(SoccerTeam val) {_root=_root->lookup(val, _root); 
  				if(_root->value() == val) 
  					std::cout << "Found: " << *_root << std::endl;
  				else 
  					std::cout << "Element " << val.name() << " not found."<<std::endl;}
   int visited2(SoccerTeam val);						
};

#endif
