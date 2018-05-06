#include "includes.h"

using namespace std;
int main(int argc, char** argv)
{
   // read list of nodes
   Nodes locations;
   locations.loadFile(argv[1]);
   locations.printNodes();
   std::string targetNodeIP = argv[2];

   // create commands to send
   // perfsonar task rtt --source 123.123.123.123 --dest 456.456.456.456
   std::string command = "perfsonar task rtt --source " + targetNodeIP
      + " --dest " + locations.nodes.front().ip;
   //std::cout << command << std::endl;

   // send commands to perfsonar
   FILE* pipe = popen(command.c_str(), "r");

   // collect results and parse
   pclose(pipe);

   // find the lowest RTT

   // return result

   return 0;
}