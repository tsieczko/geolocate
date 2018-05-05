#include <fstream>
#include <iostream>
#include <stdio.h>

using namespace std;
int main(int argc, char** argv)
{
   FILE* pipe = popen("ls /", "r");
   char buffer[100]={0};
   string response;
   //fscanf(pipe, "% s", buffer);
   //fgets(buffer, 100, pipe);
   //fgets(buffer, 100, pipe);
   //printf("%s", buffer);
   while (fscanf(pipe, "%s", buffer) != EOF)
   {
      response = response + buffer + " ";
   }
   for (int i=0; i<100; i++)
      printf("%c", buffer[i]);
   printf("\n");
   cout << response << endl;
   pclose(pipe);
   return 0;
}