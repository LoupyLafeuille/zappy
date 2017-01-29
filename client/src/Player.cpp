#include "Player.hpp"

Player::Player()
{
  _playerStat.ressourceNeed[0] = 1;
  _playerStat.ressourceNeed[1] = 0;
  _playerStat.ressourceNeed[2] = 1;
  _playerStat.ressourceNeed[3] = 0;
  _playerStat.ressourceNeed[4] = 0;
  _playerStat.ressourceNeed[5] = 0;
  _playerStat.ressourceNeed[6] = 0;
  _playerStat.ressourceNeed[7] = 0;
  _playerStat.inventaire[0] = 0;
  _playerStat.inventaire[1] = 10;
  _playerStat.inventaire[2] = 0;
  _playerStat.inventaire[3] = 0;
  _playerStat.inventaire[4] = 0;
  _playerStat.inventaire[5] = 0;
  _playerStat.inventaire[6] = 0;
  _playerStat.inventaire[7] = 0;
}

Player::~Player()
{

}

Player::PlayerStat		&Player::getPlayerStat()
{
  return (_playerStat);
}
