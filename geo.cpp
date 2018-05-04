#include <fstream>
#include <iostream>
#include <stdio.h>

using namespace std;
int main(int argc, char** argv)
{
   FILE* pipe = popen("ls /", "r");
   char buffer[100]={0};
   //fscanf(pipe, "% s", buffer);
   fgets(buffer, 100, pipe);
   //printf("%s", buffer);
   for (int i=0; i<100; i++)
      printf("%c", buffer[i]);
   pclose(pipe);
   return 0;
}