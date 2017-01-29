/*
** tree.h for zappy in /home/julien/rendu/PSU_2015_zappy/client/src
**
** Made by julien
** Login   <julien@epitech.net>
**
** Started on  Thu Jun  9 18:26:13 2016 julien
// Last update Sat Jun 18 16:45:31 2016 julien
*/

#ifndef TREE_H_
# define TREE_H_

# include "Player.hpp"
# include "Question.hpp"
# include "Action.hpp"
# include "Parsing.hpp"

// typedef	void	(BTree::*BTreefct)(const &Player::PlayerStat);

class	Dtree
{
  public :



struct	Node
{
  public:
  question	q;
  action	act;
  Node		*left;
  Node		*right;

  Node(question q, action act, Node *left, Node *right)
    : q(q), act(act), left(left), right(right)
  {}
  ~Node();

};

 private:
  Player	&player;
  Question	myQuestions;
  Node		*root;
  void destroyTree(Node *leaf);
  std::map<std::string, Node *> nodes;
 public:
  Dtree(Player &player);
  ~Dtree();
  void	initTree(const std::vector<std::vector<std::string> > &);
  void	addNode();
  action takeDecision();
  action browseTree(Node *);
};

#endif /* !TREE_H_ */
