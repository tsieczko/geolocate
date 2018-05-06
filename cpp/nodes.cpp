#include "includes.h"

Node::Node()
{
   rtt = 10e20;
}

Node::Node(const Node&)
{

}

Node::~Node()
{

}

void Node::printNode()
{
   std::cout << "Region:\t" << region << std::endl;
   std::cout << "Location:\t" << location << std::endl;
   std::cout << "IP:\t" << ip << std::endl;
   std::cout << "RTT:\t" << rtt << " ms" << std::endl;
}

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