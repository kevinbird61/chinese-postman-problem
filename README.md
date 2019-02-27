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

## Description of Program

1. If current graph is Eulerian ?
    * Yes:  Find one of Eularian path/trail (shortest path) can solve chinese postman problem.
    * No:   Goto next phase.
2. If not Eulerian:
    * Find all `odd` degree points, then using these points into a `complete graph`.
    * Mapping those `new` edges of complete graph back to origin graph. (It will be some new edges)
    * Now we have Eulerian, back to Step 1.
3. After finding an Eulerian path/trail, if there have any `new` edges in this path/trail, then replace it with an alternative path in original graph. (Using `fake-mininet` API to give these `new` edges a "tag", and if detect this special tag, then replace it with an alternative.)
