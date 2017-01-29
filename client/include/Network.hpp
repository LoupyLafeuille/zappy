#ifndef NETWORK_HPP_
# define NETWORK_HPP_

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <map>

#include "Player.hpp"
#include "Tree.hpp"

class		Network
{
public:
  Network(int ac, char **av);
  ~Network();

  const std::map<std::string,std::string>	&getArgs() const;
  void						showArgs();
  int						connexionToServer();
  int						loop();
  void						initFD(fd_set *readfds, fd_set *writefds);
  bool						checkFD(fd_set *readfds, fd_set *writefds);
  bool						parseAnswer(const std::string &str);
  void						voirCommand(const std::string &str);
  void						sortingResources(const std::string &str, int cell);
  void						sortingInventaire(const std::string &str);
  void						fillPlayerStat(int value, int cell);
  std::vector<std::string>			getTabResources();
  int						checkCompResources(const std::string &tok);
  std::string					epurResources(const std::string &str);
  void						checkCommand(const std::string &str);
  bool						isNumber(const std::string &str);
  void						inventaireCommand(const std::string &str);
  void						checkBroadcast(const std::string &str);
  void						preIncantation(const std::string &flag, const std::string &str);
  bool						checkBackLine();
private:
  Player					_player;
  Dtree						_tree;
  bool						co;
  std::map<std::string,std::string>		_args;
  std::vector<std::string>			resources;
  int						fdSocket;
  int						port;
  Parsing					*_parsing;
  std::string					buff;
  unsigned int						value;
  bool						voir;
  bool						inventaire;
  int						nbBuff;
  std::deque<std::string>			queue;
  std::string					buffer;
};

#endif //NETWORK_HPP_
