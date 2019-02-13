# Chinese Postman Problem
Project of Course - Graph Theory (EE6622E) in National Cheng Kung University.

## Build & Run

```sh
# Clone
$ git clone --recursive https://github.com/kevinbird61/chinese-postman-problem.git
# Build the library first
$ cd fake-mininet/ && make lib && cd ..
# Copy the libfakemn.a to root
$ cp fake-mininet/libfakemn.a .
# Build the code 
$ make
# Run 
$ ./main.out
```

## Concepts we need

* Graph (Edge, Vertex) - chapter 1
* Distance - chapter 2
* Matching - chapter 3
* Connectivities - chapter 4
* Dijkstra
* Eulerian circuit
