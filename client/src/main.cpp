#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "Network.hpp"

int		main(int ac, char **av)
{
  if (ac != 7)
    {
      std::cout << "Usage: " << av[0] << " -n squad_name -p port -h hostname" << std::endl;
      return (1);
    }

  try {
    Network	network(ac, av);

    if (network.connexionToServer() == -1)
      return (1);
  }
  catch (std::exception &except)
    {
      std::cerr << except.what() << std::endl;
      return (1);
    }
  return (0);
}
