#include "includes.h"

Nodes::Nodes()
{}

Nodes::Nodes(const Nodes&)
{}

Nodes::~Nodes()
{}

void Nodes::loadFile(const char* fileName)
{
   std::fstream file;
   file.open(fileName, std::fstream::in);
   char temp[100] = {0};
   while (1)
   {
      Node currentNode;

      file >> currentNode.region;
      if (file.eof()) break;
      //std::cout << "Region: " << currentNode.region << std::endl;

      file.ignore(100, '"');
      file.get(temp, 100, '"');
      currentNode.location = temp;
      //std::cout << "Location: " << currentNode.location << std::endl;

      file.ignore(100, ' ');
      file >> currentNode.ip;
      //std::cout << "IP: " << currentNode.ip << std::endl;

      nodes.push(currentNode);
   }
   file.close();
}

void Nodes::printNodes()
{
   std::queue<Node> temp = nodes;
   while (!temp.empty())
   {
      std::cout << "Region: " << temp.front().region << std::endl;
      std::cout << "Location: " << temp.front().location << std::endl;
      std::cout << "IP: " << temp.front().ip << std::endl;
      temp.pop();
   }
}