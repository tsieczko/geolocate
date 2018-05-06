#include "includes.h"

using namespace std;
int main(int argc, char** argv)
{
   // read list of nodes
   Nodes locations;
   locations.loadFile(argv[1]);
   locations.printNodes();
   std::string targetNodeIP = argv[2];
   Node closestNode;

   if (!locations.nodes.empty())
   //if (0)
   {
      // create commands to send to perfsonar pscheduler
      // pscheduler task rtt --source 123.123.123.123 --dest 456.456.456.456
      std::string command = "pscheduler task rtt --source " + targetNodeIP
         + " --dest " + locations.nodes.front().ip;
      std::cout << "\nSending command: " << command << std::endl;

      // send commands to perfSONAR
      FILE* pipe = popen(command.c_str(), "r");
      char buffer[1000]={0};
      string response;
      while (fscanf(pipe, "%s", buffer) != EOF)
      {
         response = response + buffer + " ";
      }
      cout << response << endl;
      pclose(pipe);

      // parse results
      //string regextest = "asdflkjadslj2 21234 RTT Min/Mean/Max/StdDev = 1.23/4.56/7.89/10.12 sklls 1234";
      regex pattern("RTT Min/Mean/Max/StdDev = [0-9]*.[0-9]*/[0-9]*.[0-9]*/[0-9]*.[0-9]*/[0-9]*.[0-9]*");
      std::smatch m;
      cout << regex_search(response, m, pattern) << endl;
      cout << m.str() << endl;
      string extractedRTT = m.str();
      //cout << extractedRTT[25] << endl;
      string RTTmin, RTTmean, RTTmax, RTTstddev;
      int i = 26;
      // get RTTmin
      while (extractedRTT[i] != '/')
      {
         RTTmin += extractedRTT[i++];
      }
      i++;
      //cout << RTTmin << endl;
      // get RTTmean
      while (extractedRTT[i] != '/')
      {
         RTTmean += extractedRTT[i++];
      }
      i++;
      //cout << RTTmean << endl;
      // get RTTmax
      while (extractedRTT[i] != '/')
      {
         RTTmax += extractedRTT[i++];
      }
      i++;
      //cout << RTTmax << endl;
      // get RTTstddev
      while (i < extractedRTT.length())
      {
         RTTstddev += extractedRTT[i++];
      }
      //cout << RTTstddev << endl;

      // find the lowest RTT
      if (atof(RTTmean.c_str()) < closestNode.rtt)
      {
         closestNode = locations.nodes.front();
         closestNode.rtt = atof(RTTmean.c_str());
      }

      locations.nodes.pop();
   }

   // return result
   cout << "\nThe closest node is: " << endl;
   closestNode.printNode();

   return 0;
}