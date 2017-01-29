#ifndef PARSING_HPP_
# define PARSING_HPP_

#include "json/value.h"
#include "json/json.h"
#include <fstream>
#include <iostream>
#include <map>
#include <vector>

class		Parsing
{
public:
  Parsing(const std::string &fileName = "client/Dtree.json");
  ~Parsing();

  enum		LinkEnum
    {
      NAME,
      QUESTION,
      DECISION,
      LEFT,
      RIGHT
    };

  const std::vector<std::vector<std::string> >		&getNodeMap() const;
  std::string					epurString(const std::string &str);
  void						getInfoFromFile();
  void						fillMap(int i);
  void						affMap();

private:
  std::vector<std::vector<std::string>>	nodeVec;
  const std::string			&_fileName;
  Json::Value				jsonValue;
};

#endif //PARSING_HPP_
