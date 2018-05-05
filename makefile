geo.exec: bin/nodes.o cpp/includes.h cpp/geo.cpp ; g++ -g bin/nodes.o cpp/geo.cpp -o geo.exec

bin/nodes.o: headers/nodes.h cpp/nodes.cpp ; g++ -c -g cpp/nodes.cpp -o bin/nodes.o

