#include <cstring>
#include <string>
#include <sstream>
#include <deque>
#include "Action.hpp"
#include "Network.hpp"

Network::Network(int ac, char **av) : _player(), _tree(_player), co(false)
{
  for (int i = 0; i < ac; i++) {
    if (av[i][0] == '-')
      _args.insert(std::make_pair(av[i],av[i + 1]));
  }
  resources = getTabResources();
  value = 0;
  voir = true;
  nbBuff = 1;
}

Network::~Network()
{
}

const std::map<std::string, std::string>	&Network::getArgs() const
{
  return (_args);
}

void			Network::showArgs()
{
  for (std::map<std::string,std::string>::iterator it=_args.begin(); it != _args.end(); it++) {
    std::cout << "premier element => " << it->first << "  deuxieme elememt => " << it->second << std::endl;
  }
}

std::vector<std::string>		Network::getTabResources()
{
  resources.push_back("joueur");
  resources.push_back("nourriture");
  resources.push_back("linemate");
  resources.push_back("deraumere");
  resources.push_back("sibur");
  resources.push_back("mendiane");
  resources.push_back("phiras");
  resources.push_back("thystame");

  return (resources);
}

std::string		Network::epurResources(const std::string &str)
{
  std::string		newString;

  for (unsigned int i = 0; i < str.size(); i++)
    {
      if (str[i] != '{' && str[i] != '}')
	newString += str[i];
    }
  return (newString);
}

void			Network::fillPlayerStat(int value, int cell)
{
  ++_player.getPlayerStat().view[cell][value];
}

int			Network::checkCompResources(const std::string &tok)
{
  for (unsigned int i = 0; i < resources.size(); i++)
    {
      if (tok == resources[i])
	return (i);
    }
  return (-1);
}

void			Network::sortingResources(const std::string &str, int cell)
{
  int			value;
  std::stringstream	stream(str);
  std::string		tok;

  while (getline(stream, tok, ' '))
    {
      if ((value = checkCompResources(epurResources(tok))) != -1)
	fillPlayerStat(value, cell);
    }
}

void			Network::voirCommand(const std::string &str)
{
  std::stringstream	stream(str);
  std::string		tok;
  int			cell = 0;
  unsigned int			i = 0;
  Player::PlayerStat	&ps =  _player.getPlayerStat();

  voir = true;
  while (getline(stream, tok, ','))
    {
      if (i >= ps.view.size())
	{
	  int	*tab = new int[8];
	  ps.view.push_back(tab);
	}
      ps.view[i][0] = 0;
      ps.view[i][1] = 0;
      ps.view[i][2] = 0;
      ps.view[i][3] = 0;
      ps.view[i][4] = 0;
      ps.view[i][5] = 0;
      ps.view[i][6] = 0;
      ps.view[i][7] = 0;
      sortingResources(tok, cell);
      ++cell;
      ++i;
    }
}

void			Network::sortingInventaire(const std::string &str)
{
  int			value;
  std::stringstream	stream(str);
  std::string		tok;
  std::vector<std::string>	vec;
  std::string		resName;
  std::string		resNbr;

  while (getline(stream, tok, ' '))
    vec.push_back(tok);
  if (vec[0].size() != 0)
    {
      resName = vec[0];
      resNbr = vec[1];
    }
  else if (vec[0].size() == 0)
    {
      resName = vec[1];
      resNbr = vec[2];
    }
  if ((value = checkCompResources(epurResources(resName))) != -1)
    _player.getPlayerStat().inventaire[value] = atoi(resNbr.c_str());
}

void			Network::inventaireCommand(const std::string &str)
{
  std::stringstream	stream(str);
  std::string		tok;

  voir = true;
  while (getline(stream, tok, ','))
    sortingInventaire(tok);
}

bool			Network::isNumber(const std::string &str)
{
  for (unsigned int i = 0; i < str.size(); i++)
    if (str[i] >= '0' && str[i] <= '9')
      return (true);
  return (false);
}

void			Network::checkCommand(const std::string &str)
{
  if (isNumber(str) == true)
    inventaireCommand(str);
  else
    voirCommand(str);
}

void		Network::preIncantation(const std::string &flag, const std::string &all)
{
  unsigned int	value;
  std::string	nb;

  value = all.find("]");
  if (flag == "pre incantation")
    {
      for (int i = 0; value < all.size(); i++)
	{
	  nb.insert(i, 1, all[value]);
	  value++;
	}
      if ((unsigned)atoi(nb.c_str()) == _player.getPlayerStat().level)
	_player.getPlayerStat().anyoneMyLevelEvolve = true;
    }
}

void		Network::checkBroadcast(const std::string &str)
{
  Player::PlayerStat &stat = _player.getPlayerStat();

  if ((str.find("[pre incantation")) != str.npos)
    {
      if ((unsigned)atoi(str.substr((str.find("]") + 2), 1).c_str()) == stat.level
	  && stat.evolveId == 0)
	{
	  stat.anyoneMyLevelEvolve = true;
	  stat.evolveId = atoi(str.substr((str.find(":") + 1), str.find("]") - str.find(":")).c_str());
	  stat.sound = str[str.find(",[pre") - 1] - '0';
	}
      else if ((unsigned)atoi(str.substr((str.find("]") + 2), 1).c_str()) == stat.level
	       && stat.evolveId ==
	       (unsigned)atoi(str.substr((str.find(":") + 1), str.find("]") - str.find(":")).c_str()))
	stat.sound = str[str.find(",[pre") - 1] - '0';
    }
  else if ((str.find("[start incantation")) != str.npos)
    {
      if ((unsigned)atoi(str.substr((str.find(":") + 1), str.find("]") - str.find(":")).c_str()) == stat.evolveId)
	{
	  stat.anyoneMyLevelEvolve = false;
	  stat.evolveId = 0;
	}
    }
}

bool		Network::parseAnswer(const std::string &str)
{
  size_t		value;
  Player::PlayerStat	&stat = _player.getPlayerStat();

  if (co == false)
    {
      if (buffer.find("BIENVENUE") == buffer.npos)
	co = true;
      if (buffer.find("ko") != buffer.npos)
	{
	  std::cerr << "Invalid Team name or Team is full" << std::endl;
	  return false;
	}
    }
  if ((value = str.find('{')) != str.npos)
    checkCommand(str.substr(value, str.find("}") - value));
  if ((value = str.find("message")) != str.npos)
    checkBroadcast(str);
  if ((value = str.find("niveau actuel")) != str.npos)
    {
      stat.level = atoi(str.substr((str.find(":") + 2)).c_str());
      stat.anyoneMyLevelEvolve = false;
      stat.evolveId = 0;
      queue.push_back("expulse");
    }
  return true;
}

void			Network::initFD(fd_set *readfds, fd_set *writefds)
{
  FD_ZERO(readfds);
  FD_ZERO(writefds);
  FD_SET(fdSocket, readfds);
  FD_SET(fdSocket, writefds);
}

bool			Network::checkBackLine()
{
  for (unsigned int i = 0; i < buffer.size(); i++)
    if (buffer[i] == '\n')
      return true;
  return false;
}

bool			Network::checkFD(fd_set *readfds, fd_set *writefds)
{
  Action		action1;
  action		func;
  char			str[4096];
  int			i = 0;

  buffer = "";
  if (FD_ISSET(fdSocket, readfds))
    {
      while (checkBackLine() != true)
	{
	  std::memset(str, 0, sizeof(str));
	  if (read(fdSocket, str, 4096) == 0)
	    return (false);
	  buffer += str;
	}
      if (buffer != "") {
	if (nbBuff > 1)
	  --nbBuff;
	if (parseAnswer(buffer) == false)
	  return false;
      }
    }
  if (FD_ISSET(fdSocket, writefds))
    {
      if (voir == true && nbBuff <= 10)
	{
	  if (queue.size() == 0)
	    {
	      func = _tree.takeDecision();
	      (action1.*func)(_player.getPlayerStat(), queue);
	    }
	  if (queue.size() > 0)
	    {
	      // for (unsigned j = 0; j < queue.size(); ++j)
	      //	{
	      //	  std::cout << "Queu : "<< j  << " : " << queue[j] << std::endl;
	      //	}
	      if (queue.front() == "voir" || queue.front() == "inventaire")
		voir = false;
	      queue.front() += '\n';
	      value = queue.front().size();
	      i = 0;
	      while (value != 0)
		{
		  if ((i = write(fdSocket, queue.front().c_str() + i, value)) == -1)
		    return (false);
		  value -= i;
		}
	      nbBuff++;
	      queue.pop_front();
	    }
	}
    }
  value = 0;
  return (true);
}

int			Network::loop()
{
  struct timeval	time;
  fd_set		readfds;
  fd_set		writefds;
  int			i = 0;
  std::string		teamName;

  teamName = _args["-n"];
  teamName += "\n";
  while (value != teamName.size())
    {
      i = write(fdSocket, teamName.c_str() + value, teamName.size());
      value += i;
    }
  value = 0;
  initFD(&readfds, &writefds);
  while (42)
    {
      time.tv_sec = 2;
      time.tv_usec = 20000;
      FD_SET(fdSocket, &readfds);
      FD_SET(fdSocket, &writefds);
      if ((select((fdSocket + 1), &readfds, &writefds, NULL, &time)) == -1)
	return (-1);
      if (checkFD(&readfds, &writefds) == false)
	return (0);
    }
  return (0);
}

int			Network::connexionToServer()
{
  struct protoent	*pe;
  struct sockaddr_in	s_in;
  std::string		ip;

  ip = _args["-h"];
  port = std::stoi(_args["-p"]);
  pe = getprotobyname("TCP");
  if (!pe)
    return (1);
  if ((fdSocket = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == -1)
    return (-1);
  s_in.sin_family = AF_INET;
  s_in.sin_port = htons(port);
  s_in.sin_addr.s_addr = inet_addr(ip.c_str());
  if (connect(fdSocket, (struct sockaddr *)&s_in, sizeof(s_in)) == -1)
    {
      if (close(fdSocket) == -1)
	return (-1);
      return (-1);
    }
  if (loop() == -1)
    {
      std::cerr << "Le connect a fail" << std::endl;
      return (-1);
    }
  if (close(fdSocket) == -1)
    return (-1);
  return (0);
}
