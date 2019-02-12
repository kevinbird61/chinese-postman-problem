#include <algorithm>
#include <iostream>
#include <unistd.h>
#include <queue>
#include <map>
#include "network_manager.h"
#include "gplot.h"
#include "path.h"

NetworkManager *nm = new NetworkManager();

int main(int argc, char** argv){

    nm->add_switch("a");
    nm->add_switch("d");
    nm->add_switch("b");
    nm->add_switch("c");
    nm->add_switch("e");

    nm->connect("a", "b");
    nm->connect("b", "c");
    nm->connect("c", "a");
    nm->connect("c", "d");
    nm->connect("d", "e");
    nm->connect("e", "b");
    nm->connect("e", "c");

    

    return 0;
}