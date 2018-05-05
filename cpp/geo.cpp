#include "includes.h"

using namespace std;
int main(int argc, char** argv)
{
   // read list of nodes
   Nodes locations;
   locations.loadFile(argv[1]);
   locations.printNodes();
   // send commands to perfsonar

   // find the lowest RTT

   // return result

   return 0;
}