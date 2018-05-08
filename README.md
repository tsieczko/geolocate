# geolocate
Geolocates a target using public perfSONAR nodes.

Compares a list of nodes with known locations and geolocates a target based on RTT data between the nodes and target node.

## Input file format:

REGION "LOCATION" IP

example:
```
NA "UNR" 134.197.11.250
NA "UC Davis" 128.120.80.78
```


## Usage example:

`$ ./geolocate example_input.txt 12.34.56.78`