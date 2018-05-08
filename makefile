geolocate: bin/nodes.o cpp/includes.h cpp/geo.cpp ; g++ -std=c++11 -g bin/nodes.o cpp/geo.cpp -o geolocate

bin/nodes.o: headers/nodes.h cpp/nodes.cpp ; g++ -std=c++11 -c -g cpp/nodes.cpp -o bin/nodes.o

