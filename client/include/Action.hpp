/*
** Action.h for zappi in /home/julien/rendu/PSU_2015_zappy/client
**
** Made by julien
** Login   <julien@epitech.net>
**
** Started on  Tue Jun 14 16:08:56 2016 julien
// Last update Sat Jun 25 15:39:36 2016 julien
*/

#ifndef ACTION_H_
# define ACTION_H_

# include <deque>
# include "Player.hpp"

class Action
{
  private:

  public:
  Action();
  ~Action();
  void Look(Player::PlayerStat &, std::deque<std::string> &);
  void Adjust(Player::PlayerStat &, std::deque<std::string> &);
  void Kick(Player::PlayerStat &, std::deque<std::string> &);
  void Pick(Player::PlayerStat &, std::deque<std::string> &);
  void PickFood(Player::PlayerStat &stat, std::deque<std::string> &act);
  void Walk(Player::PlayerStat &, std::deque<std::string> &);
  void Fork(Player::PlayerStat &, std::deque<std::string> &);
  void Evolve(Player::PlayerStat &, std::deque<std::string> &);
  void Join(Player::PlayerStat &, std::deque<std::string> &);
  void SearchForRessources(Player::PlayerStat &stat, std::deque<std::string> &act);
  unsigned caseValue(const int info[Player::info::SIZE], const int inventaire[Player::info::SIZE],
		     const std::array<int, 8> need);
  void Call(Player::PlayerStat &stat, std::deque<std::string> &act);
  void  moveToCell(unsigned cell,  std::deque<std::string> &act);
};

typedef void (Action:: *action)(Player::PlayerStat &, std::deque<std::string> &);

#endif /* !ACTION_H_ */
