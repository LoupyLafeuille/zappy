#include "Question.hpp"

extern std::map<int,std::array<int,8>>	_resourcesPerLvl;

Question::Question()
{}

Question::~Question()
{}

bool	Question::isEnoughFood(const Player::PlayerStat &stat)
{
  return stat.inventaire[Player::info::FOOD] >= 4 ? true : false;
}

bool	Question::EnoughRessources(const Player::PlayerStat &stat)
{
  for (int i = Player::info::LINEMATE; i < Player::info::SIZE; ++i)
    if (stat.view[0][i] + stat.inventaire[i] <
	_resourcesPerLvl[stat.level][i])
      return false;
  return true;
}

bool	Question::PickRessources(const Player::PlayerStat &stat)
{
  for (int i = Player::info::LINEMATE; i < Player::info::SIZE; ++i)
    if (stat.view[0][i] + stat.inventaire[i] < _resourcesPerLvl[stat.level][i] && stat.view[0][i] > 0)
      return true;
  return false;
}

bool	Question::PerfectRessourcesNbr(const Player::PlayerStat &stat)
{
  for (int i = Player::info::LINEMATE; i < Player::info::SIZE; ++i)
    if (stat.view[0][i] != _resourcesPerLvl[stat.level][i])
      return false;
  return true;
}

bool	Question::Look(const Player::PlayerStat &stat)
{
  return stat.look;
}

/*
** check case 0
*/
bool	Question::Food(const Player::PlayerStat &stat)
{
  return stat.view[0][Player::info::FOOD] > 0 ? true : false;
}

bool	Question::Anyone(const Player::PlayerStat &stat)
{
  return stat.view[0][Player::info::PLAYER] > 1 ? true : false;
}

bool	Question::EnoughPlayerNbr(const Player::PlayerStat &stat)
{
  int playerNeed;

  if (stat.level == 1)
    playerNeed = 1;
  else
    playerNeed = stat.level - (stat.level % 2 == 0 ? 0 : 1);
  return stat.view[0][Player::info::PLAYER] >= playerNeed ? true : false;// est ce quon se compte ?
}

bool	Question::TooMuchPlayerNbr(const Player::PlayerStat &stat)
{
  int playerNeed;

  if (stat.level == 1)
    playerNeed = 1;
  else
    playerNeed = stat.level - (stat.level % 2 == 0 ? 0 : 1);
  return stat.view[0][Player::info::PLAYER] > playerNeed ? true : false;// est ce quon se compte ?
}

bool	Question::Turn(const Player::PlayerStat &stat)
{
  return stat.nbrTurn == 2 ? true : false;
}

bool	Question::NeedMe(const Player::PlayerStat &stat)
{
  return stat.anyoneMyLevelEvolve;
}

bool	Question::AnyoneEvolve(const Player::PlayerStat &stat)
{
  return stat.anyoneMyLevelEvolve;
}
