#include "../cpp/includes.h"

class Node
{
public:
   Node();
   Node(const Node&);
   ~Node();

   void printNode();

public:
   std::string region;
   std::string location;
   std::string ip;
   float rtt;
};

class Nodes
{
public:
   Nodes();
   Nodes(const Nodes&);
   ~Nodes();

   void loadFile(const char*);
   void printNodes();

   std::queue<Node> nodes;
};