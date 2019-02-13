#include <algorithm>
#include <iostream>
#include <unistd.h>
#include <queue>
#include <map>
#include "network_manager.h"
#include "gplot.h"
#include "path.h"

using namespace std;

NetworkManager *nm = new NetworkManager();
map<string, vector<Edge *>> ef, eb;

vector<Edge *> route, existed;
int finish(); 
int dfs(string src, string sink);

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

    // build the edges belong to vertex 
    Edge *elist = nm->elist;
    while(elist!=NULL){
        ef[elist->head->name].push_back(elist);
        eb[elist->tail->name].push_back(elist);
        elist=elist->next;
    }

    // find odd degree vertices
    Vertex *vlist = nm->get_all_nodes();
    vector<Vertex *> odds;
    while(vlist!=NULL){
        int degree = ef[vlist->name].size()+eb[vlist->name].size();
        // odd degree
        if(degree%2!=0){
            cout << vlist->name <<", degree: " << degree << endl;
            odds.push_back(vlist);
        }
        vlist=vlist->next;
    }

    // form a complete graph among odds
    for(int i=0;i<odds.size();i++){
        for(int j=0;j<odds.size();j++){
            if(nm->connected_d(odds[i]->name, odds[j]->name) && odds[i]->name != odds[j]->name){
                // not connect, create new link to these 2 point
                nm->connect(odds[i]->name, odds[j]->name);
                ef[odds[i]->name].push_back(nm->get_edge(odds[i]->name, odds[j]->name));
                eb[odds[j]->name].push_back(nm->get_edge(odds[i]->name, odds[j]->name));
                cout << "New link: " << odds[i]->name << "->" << odds[j]->name << endl;
            }
        }
    }

    // run 
    dfs("a", "a");

    for(int i=0;i<route.size();i++){
        cout << route[i]->head->name << "--->" << route[i]->tail->name << endl;
    }

    /*
    Path *path = new Path();
    path->append(nm->elist);
    //path->find_paths("b", "e");
    //path->debug();
    path->find_paths("e", "b");
    path->debug();
    */

    return 0;
}

int dfs(string src, string sink)
{
    // traversal
    for(int i=0;i<ef[src].size();i++){
        // cout << "Current: " << ef[src].at(i)->head->name << "->" << ef[src].at(i)->tail->name << endl;
        // check the edge is already existed or not
        if(find(route.begin(), route.end(), ef[src].at(i))==route.end()){
            route.push_back(ef[src].at(i));
            // if found the sink
            if(ef[src].at(i)->tail->name==sink){
                // check if traverse all 
                /*for(int i=0;i<route.size();i++){
                    cout << route[i]->head->name << "--->" << route[i]->tail->name << endl;
                }*/
                if(!finish()){
                    // cout << "NOT END" << endl;
                    route.pop_back();
                    // go to next 
                    continue;
                }
                //cout << "END" << endl;
                return 0; // END
            }
            cout << ef[src].at(i)->head->name << "->" << ef[src].at(i)->tail->name << endl;
            // if END, then return; else: keep going
            if(dfs(ef[src].at(i)->tail->name, sink)){
                // pop out the error one
                //cout << "SRC: " << src << ". POP, and continue..." << endl;
                route.pop_back();
            } else {
                // END
                //cout << "SRC: " << src << ". END, return..." << endl;
                return 0; // END, return 
            }
        }
    }
}

int finish()
{
    Edge *elist = nm->elist;
    while(elist!=NULL){
        // cout << elist->head->name << "=>" << elist->tail->name << ". Compare: " << (find(route.begin(), route.end(), elist)==route.end()) << endl;
        if(find(route.begin(), route.end(), elist)==route.end()){
            // not found in route 
            return 0;
        }
        elist = elist->next;
    }
    return 1;
}