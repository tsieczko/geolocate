#include "includes.h"

Node::Node()
{
   region = "default";
   location = "default";
   ip = "default";
   rtt = 10e20;
}

Node::Node(const Node& in)
{
   region = in.region;
   location = in.location;
   ip = in.ip;
   rtt = in.rtt;
}

Node::~Node()
{}

void Node::printNode()
{
   std::cout << "Region:\t\t" << region << std::endl;
   std::cout << "Location:\t" << location << std::endl;
   std::cout << "IP:\t\t" << ip << std::endl;
   std::cout << "RTT:\t\t" << rtt << " ms" << std::endl;
}

Nodes::Nodes()
{}

Nodes::Nodes(const Nodes& in)
{
   nodes = in.nodes;
}

Nodes::~Nodes()
{}

void Nodes::loadFile(std::string fileName)
{
   std::fstream file;
   file.open(fileName, std::fstream::in);
   if (!file.is_open())
   {
      std::cerr << "Error reading input file" << std::endl;
   }
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