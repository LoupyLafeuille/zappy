//
// tree.cpp for zappy in /home/julien/rendu/PSU_2015_zappy/client/src
//
// Made by julien
// Login   <julien@epitech.net>
//
// Started on  Thu Jun  9 18:26:11 2016 julien
// Last update Sun Jun 26 16:28:44 2016 julien
//

#include "Tree.hpp"

static std::map<std::string, action> actionTab = {
  {"NULL", NULL},
  {"Look", &Action::Look},
  {"Kick", &Action::Kick},
  {"PickFood", &Action::PickFood},
  {"Pick", &Action::Pick},
  {"Adjust", &Action::Adjust},
  {"Walk", &Action::Walk},
  {"Fork", &Action::Fork},
  {"SearchForRessources", &Action::SearchForRessources},
  {"Kick", &Action::Kick},
  {"Evolve", &Action::Evolve},
  {"Join", &Action::Join},
  {"Call", &Action::Call},
};

static std::map<std::string, question> questionTab = {
  {"NULL", NULL},
  {"isEnoughFood?", &Question::isEnoughFood},
  {"Look?", &Question::Look},
  {"Food?", &Question::Food},
  {"PerfectRessourcesNbr?", &Question::PerfectRessourcesNbr},
  {"PickRessources?", &Question::PickRessources},
  {"EnoughPlayerNbr?", &Question::EnoughPlayerNbr},
  {"TooMuchPlayerNbr?", &Question::TooMuchPlayerNbr},
  {"EnoughRessources?", &Question::EnoughRessources},
  {"NeedMe?", &Question::NeedMe},
};

Dtree::Dtree(Player &player)
  : player(player), myQuestions() // &Question::canEvolve
{
  Parsing parse("./client/Dtree.json");

  initTree(parse.getNodeMap());
}

void	Dtree::initTree(const std::vector<std::vector<std::string> > &link)
{
  nodes["NULL"] = NULL;
  for (auto idx : link)
    {
      nodes[idx[Parsing::NAME]] = new Node(questionTab[idx[Parsing::QUESTION]],
					   actionTab[idx[Parsing::DECISION]], NULL, NULL);
    }
  for (auto idx : link)
    {
      nodes[idx[Parsing::NAME]]->left = nodes[idx[Parsing::LEFT]];
      nodes[idx[Parsing::NAME]]->right = nodes[idx[Parsing::RIGHT]];
    }
  root = nodes["Look?"];
}

Dtree::~Dtree()
{}

action	Dtree::takeDecision()
{
  return browseTree(root);
}

action	Dtree::browseTree(Node *node)
{
  if (node->act)
    return node->act;
  if ((myQuestions.*node->q)(player.getPlayerStat()))
    return browseTree(node->right);
  else
    return browseTree(node->left);
}
