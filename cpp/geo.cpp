#include "includes.h"

using namespace std;
int main(int argc, char** argv)
{
   // read list of nodes
   Nodes locations;
   locations.loadFile(argv[1]);
   //locations.printNodes();
   std::string targetNodeIP = argv[2];

   while (!locations.nodes.empty())
   {
      // create commands to send
      // perfsonar task rtt --source 123.123.123.123 --dest 456.456.456.456
      std::string command = "pscheduler task rtt --source " + targetNodeIP
         + " --dest " + locations.nodes.front().ip;
      std::cout << "Sending command: " << command << std::endl;

      // send commands to perfsonar
      FILE* pipe = popen(command.c_str(), "r");
      char buffer[1000]={0};
      string response;
      while (fscanf(pipe, "%s", buffer) != EOF)
      {
         response = response + buffer + " ";
      }
      for (int i=0; i<100; i++)
         printf("%c", buffer[i]);
      printf("\n");
      cout << response << endl;



      // collect results and parse
      pclose(pipe);

      // find the lowest RTT

      locations.nodes.pop();
   }

   // return result

   return 0;
}