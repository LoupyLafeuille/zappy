#ifndef PLAYER_HPP_
# define PLAYER_HPP_

# include <iostream>
# include <map>
# include <vector>

class		Player
{
  public:

  enum		info
    {
      PLAYER = 0,
      FOOD,
      LINEMATE,
      DERAUMERE,
      SIBUR,
      MENDIANE,
      PHIRAS,
      THYSTAME,
      SIZE,
    };
  struct	PlayerStat
  {
    public:
    bool	look;
    unsigned	nbrTurn;
    unsigned	level;
    bool	anyoneMyLevelEvolve;
    unsigned	teamNbr;
    unsigned	maxTeamNbr;
    bool	busy;
    unsigned	sound;
    unsigned	evolveId;
    unsigned	moveNbr;
    unsigned	callNbr;
    int		ressourceNeed[info::SIZE];
    int		inventaire[info::SIZE];
    std::vector<int*> view;
    public:
    PlayerStat()
      : look(false), nbrTurn(1), level(1), anyoneMyLevelEvolve(false),
	teamNbr(1), maxTeamNbr(1), busy(false), sound(0), evolveId(0), moveNbr(0), callNbr(0) {}
	~PlayerStat()
    {
      view.clear();
    }
  };


public:
  Player();
  ~Player();

  Player::PlayerStat		&getPlayerStat();

private:
  PlayerStat		_playerStat;
};

#endif //PLAYER_HPP_
