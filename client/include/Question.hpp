/*
** question.h for ZAPPY in /home/julien/rendu/PSU_2015_zappy/client
**
** Made by julien
** Login   <julien@epitech.net>
**
** Started on  Tue Jun 14 13:55:57 2016 julien
// Last update Sat Jun 25 21:28:53 2016 julien
*/

#ifndef QUESTION_H_
# define QUESTION_H_

# include "Player.hpp"

class Question
{
 private:
 public:
  Question();
  ~Question();
  /* int	operator(); */
  bool	isEnoughFood(const Player::PlayerStat &stat);
  bool	Look(const Player::PlayerStat &stat);

  bool	Food(const Player::PlayerStat &stat);

  bool	Anyone(const Player::PlayerStat &stat);
  bool	Turn(const Player::PlayerStat &stat);
  bool	canEvolve(const Player::PlayerStat &stat);
  bool	EnoughPlayerNbr(const Player::PlayerStat &stat);
  bool	TooMuchPlayerNbr(const Player::PlayerStat &stat);
  bool	AnyoneEvolve(const Player::PlayerStat &stat);
  bool	Evolve(const Player::PlayerStat &stat);
  bool	EnoughRessources(const Player::PlayerStat &stat);
  bool  PickRessources(const Player::PlayerStat &stat);
  bool  PerfectRessourcesNbr(const Player::PlayerStat &stat);
  bool  NeedMe(const Player::PlayerStat &stat);
};

typedef bool (Question::* question)(const Player::PlayerStat &);

#endif /* !QUESTION_H_ */
