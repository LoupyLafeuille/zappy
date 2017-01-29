#include "Action.hpp"
#include <cstdlib>
#include <iostream>
#include <ctime>

static std::string     g_ressources[Player::info::SIZE] = { //check const
  "error in prendre or pose",
  "nourriture",
  "linemate",
  "deraumere",
  "sibur",
  "mendiane",
  "phiras",
  "thystame",
};

std::map<int,std::array<int,8>>        _resourcesPerLvl = {
  {1, std::array<int,8>({1,0,1,0,0,0,0,0})},
  {2, std::array<int,8>({2,0,1,1,1,0,0,0})},
  {3, std::array<int,8>({2,0,2,0,1,0,2,0})},
  {4, std::array<int,8>({4,0,1,1,2,0,1,0})},
  {5, std::array<int,8>({4,0,1,2,1,3,0,0})},
  {6, std::array<int,8>({6,0,1,2,3,0,1,0})},
  {7, std::array<int,8>({6,0,2,2,2,2,2,1})},
};


Action::Action()
{
  std::srand(std::time(0));
}

Action::~Action()
{}


void		Action::Look(Player::PlayerStat &stat, std::deque<std::string> &act)
{
  stat.look = true;
  act.push_back("inventaire");
  act.push_back("voir");
}

void		Action::Kick(Player::PlayerStat &stat, std::deque<std::string> &act)
{
  if (!stat.anyoneMyLevelEvolve)
    act.push_back("expulse");
  stat.look = false;
}

void		Action::PickFood(Player::PlayerStat &stat, std::deque<std::string> &act)
{
  act.push_back("prend nourriture");
  stat.look = false;
}

void		Action::Adjust(Player::PlayerStat &stat, std::deque<std::string> &act)
{
  for (int i = Player::info::LINEMATE; i < Player::info::SIZE; ++i)
    {
      if (stat.view[0][i] > _resourcesPerLvl[stat.level][i])
	{
	  act.push_back("prend ");
	  act.back() += g_ressources[i];
	  break ;
	}
      else if (stat.view[0][i] < _resourcesPerLvl[stat.level][i])
	{
	  act.push_back("pose ");
	  act.back() += g_ressources[i];
	  break ;
	}
    }
  act.push_back("voir");
  act.push_back("inventaire");
}

void		Action::Pick(Player::PlayerStat &stat, std::deque<std::string> &act)
{
  int		i;

  if (stat.view[0][Player::info::FOOD] > 0 && stat.inventaire[Player::info::FOOD] < 8)
    {
      act.push_back("prend ");
      act.back() += g_ressources[Player::info::FOOD];
    }
  else
    for (i = Player::info::LINEMATE; i < Player::info::SIZE; ++i)
      {
	if (_resourcesPerLvl[stat.level][i] - stat.inventaire[i] > 0 && stat.view[0][i] > 0)
	  {
	    act.push_back("prend ");
	    act.back() += g_ressources[i];
	    break ;
	  }
      }
  stat.look = false;
}

unsigned	Action::caseValue(const int view[Player::info::SIZE], const int inventaire[Player::info::SIZE],
				  const std::array<int, 8> need)
{
  int	cpt = 0;

  if (view[Player::info::PLAYER] > 0)
    return 0;
  for (int i = Player::info::LINEMATE; i < Player::info::SIZE; ++i)
    {
      if (inventaire[i] < need[i] && view[i] >= 0)
	cpt += (need[i] - inventaire[i] >= view[i] ? view[i] : need[i] - inventaire[i]);
    }
  return cpt;
}

void		Action::SearchForRessources(Player::PlayerStat &stat, std::deque<std::string> &act)
{
  unsigned	best = 0;
  unsigned	obj = 2;
  unsigned	size = act.size();
  unsigned	tmp;

  for (unsigned i = 0; i < size; ++i)
    {
      tmp = caseValue(stat.view[i], stat.inventaire, _resourcesPerLvl[stat.level]);
      if (tmp > best)
	{
	  best = tmp;
	  obj = i;
	}
    }
  moveToCell(obj, act);
  stat.look = false;
  stat.busy = false;
}

void		Action::moveToCell(unsigned cell,  std::deque<std::string> &act)
{
  unsigned	inc1 = 3;
  unsigned	inc2 = 2;
  unsigned	min = 1;
  unsigned	mid = 0;
  int		it;

  if (cell == 0)
    return ;
  while (cell >= min)
    {
      min += inc1;
      mid += inc2;
      inc1 += 2;
      inc2 += 2;
      act.push_back("avance");
    }
  it = mid - cell;
  if (it > 0)
    act.push_back("gauche");
  else if (it < 0)
    act.push_back("droite");
  it = it > 0 ? it : -it;
  for (; it > 0; --it)
    act.push_back("avance");
}

void		Action::Walk(Player::PlayerStat &stat, std::deque<std::string> &act)
{
  int		dir = stat.inventaire[Player::info::FOOD];
  unsigned	size = stat.view.size();
  unsigned	i;

  for (i = 0; i < size; ++i)
    {
      if (stat.view[i][Player::info::FOOD] > 0)
	break ;
    }
  if (i == size)
    {
      if (dir == 1)
	act.push_back("gauche");
      else if (dir == 2)
	act.push_back("droite");
      act.push_back("avance");
    }
  else
    {
      moveToCell(i, act);
    }
  stat.look = false;
}

void		Action::Fork(Player::PlayerStat &, std::deque<std::string> &act)
{
  act.push_back("fork");
}

void		Action::Evolve(Player::PlayerStat &stat, std::deque<std::string> &act)
{
  std::string	broadMsg;

  act.push_back(broadMsg);
  act.push_back("incantation");
  broadMsg += "broadcast [start incantation:";
  broadMsg += std::to_string(stat.evolveId);
  broadMsg += "] ";
  broadMsg += std::to_string(stat.level);
  stat.look = false;
  stat.callNbr = 0;
  stat.evolveId = 0;
}

void		Action::Join(Player::PlayerStat &stat, std::deque<std::string> &act)
{
  if (stat.view[0][Player::info::FOOD] > 0 && stat.inventaire[Player::info::FOOD] < 8)
    act.push_back("prend nourriture");
  if (stat.sound == 1 || stat.sound == 8 || stat.sound == 2)
    act.push_back("avance");
  else if (stat.sound == 4 || stat.sound == 3)
    act.push_back("gauche");
  else if (stat.sound != 0)
    act.push_back("droite");
  if (stat.sound)
    ++stat.moveNbr;
  if (stat.moveNbr > 15)
    {
      stat.moveNbr = 0;
      stat.anyoneMyLevelEvolve = false;
      stat.evolveId = 0;
    }
  stat.look = false;

}

void		Action::Call(Player::PlayerStat &stat, std::deque<std::string> &act)
{
  std::string	broadMsg;

  // ++stat.callNbr;
  if (stat.callNbr > 60)
    {
      stat.evolveId = 0;
      stat.callNbr = 0;
      stat.evolveId = 0;
      act.push_back("avance");
      act.push_back("fork");
    }
  if (!stat.evolveId)
    stat.evolveId = rand() % 10000;
  broadMsg += "broadcast [pre incantation:";
  broadMsg += std::to_string(stat.evolveId);
  broadMsg += "] ";
  broadMsg += std::to_string(stat.level);
  act.push_back(broadMsg);
  stat.busy = true;
  stat.look = false;
}
