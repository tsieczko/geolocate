#include "includes.h"

using namespace std;
int main(int argc, char** argv)
{
   // read list of nodes
   Nodes locations;
   locations.loadFile(argv[1]);
   //locations.printNodes();
   std::string targetNodeIP = argv[2];
   Node closestNode;

   while (!locations.nodes.empty())
   {
      // create commands to send to perfsonar pscheduler
      // pscheduler task rtt --source 123.123.123.123 --dest 456.456.456.456
      std::string command = "pscheduler task rtt --source " + locations.nodes.front().ip + " --dest " + targetNodeIP;
      cout << "\n-Current Node-" << endl;
      cout << "Region:\t\t" << locations.nodes.front().region << endl;
      cout << "Location:\t" << locations.nodes.front().location << endl;
      cout << "IP:\t\t" << locations.nodes.front().ip << endl;
      cout << "\nSending command: " << command << endl;

      // send commands to perfSONAR
      FILE* pipe = popen(command.c_str(), "r");
      char buffer[1000]={0};
      string response;
      while (fscanf(pipe, "%s", buffer) != EOF)
      {
         response = response + buffer + " ";
      }
      //cout << response << endl;
      pclose(pipe);

      // parse results
      regex pattern("RTT Min/Mean/Max/StdDev = [0-9]*.[0-9]*/[0-9]*.[0-9]*/[0-9]*.[0-9]*/[0-9]*.[0-9]*");
      std::smatch m;
      //cout << regex_search(response, m, pattern) << endl;
      regex_search(response, m, pattern);
      cout << m.str() << endl;
      string extractedRTT = m.str();
      //cout << extractedRTT[25] << endl;
      string RTTmin, RTTmean, RTTmax, RTTstddev;
      int i = 26;
      // get RTTmin
      while (extractedRTT[i] != '/' | i>100)
      {
         RTTmin += extractedRTT[i++];
      }
      i++;
      // get RTTmean
      while (extractedRTT[i] != '/')
      {
         RTTmean += extractedRTT[i++];
      }
      i++;
      // get RTTmax
      while (extractedRTT[i] != '/')
      {
         RTTmax += extractedRTT[i++];
      }
      i++;
      // get RTTstddev
      while (i < extractedRTT.length())
      {
         RTTstddev += extractedRTT[i++];
      }

      // find the lowest RTT
      if (atof(RTTmean.c_str()) < closestNode.rtt)
      {
         closestNode = locations.nodes.front();
         closestNode.rtt = atof(RTTmean.c_str());
      }

      locations.nodes.pop();
   }

   // return result
   cout << "\nThe closest node to " << targetNodeIP << " is: " << endl;
   closestNode.printNode();

   return 0;
}