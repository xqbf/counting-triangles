#include "commonfunctions.h"
#include "temporal_graph.h"

class onlineindex{
    public:
        struct node{
            int id,degree;
        };
        node *point;
        int n;
        int m;
        std::unordered_set<int> *g;
        int *ps;
        onlineindex(){}
        onlineindex(TemporalGraph *Graph);
        ~onlineindex();
        int search(TemporalGraph *Graph, int ts,int te);
        static bool cmp(node a,node b);
};
void online(onlineindex * Index, TemporalGraph *Graph, char * query_file, char * output_file);