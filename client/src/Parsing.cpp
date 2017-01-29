#include <stdio.h>
#include <string.h>
#include <openssl/md5.h>
#include "Parsing.hpp"

Parsing::Parsing(const std::string &fileName) : _fileName(fileName)
{
  getInfoFromFile();
}

Parsing::~Parsing()
{
}

const std::vector<std::vector<std::string>>		&Parsing::getNodeMap() const
{
  return (nodeVec);
}

std::string		Parsing::epurString(const std::string &str)
{
  std::string		newString;

  for (unsigned int i = 0; i < str.size(); i++)
    {
      if (str[i] != '"' && str[i] != '\n')
	newString += str[i];
    }
  return (newString);
}

void			Parsing::fillMap(int i)
{
  Json::FastWriter	fast;
  std::vector<std::string>		link;
  std::string				str = fast.write(jsonValue["nodes"][i]["name"]);

  link.push_back(epurString(fast.write(jsonValue["nodes"][i]["name"])));
  link.push_back(epurString(fast.write(jsonValue["nodes"][i]["question"])));
  link.push_back(epurString(fast.write(jsonValue["nodes"][i]["decision"])));
  link.push_back(epurString(fast.write(jsonValue["nodes"][i]["left"])));
  link.push_back(epurString(fast.write(jsonValue["nodes"][i]["right"])));

  nodeVec.push_back(link);
}

void			Parsing::getInfoFromFile()
{
  std::ifstream		jsonFile(_fileName, std::ifstream::binary);
  unsigned char		c[MD5_DIGEST_LENGTH];
  FILE			*inFile = fopen(_fileName.c_str(), "rb");
  MD5_CTX		mdContext;
  int			bytes;
  char			data[1024];
  // char			buff[1024];
  char			buff[1024];

  std::string		str;

  if (inFile == NULL)
    {
      throw std::runtime_error("Can't open file");
    }
  MD5_Init(&mdContext);
  while ((bytes = fread (data, 1, 1024, inFile)) != 0)
    MD5_Update (&mdContext, data, bytes);
  MD5_Final (c,&mdContext);
  for(int i = 0; i < MD5_DIGEST_LENGTH; i++) {
    sprintf(buff, "%02x", c[i]);
    str += buff;
  }
  if (str != "ca4d2914800606f27fa9a8df12b3be95")
    {
      throw std::runtime_error("Error on the Dtree.json file");
    }
  fclose (inFile);
  jsonFile >> jsonValue;
  for (int i = 0; i < 20; i++)
    fillMap(i);
}
