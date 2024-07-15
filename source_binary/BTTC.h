#include "commonfunctions.h"
#include "temporal_graph.h"
#include <unordered_map>
class onlineindex{
    public:
        struct node{
            int id,degree;
        };
        node *point;
        int n;
        int m;
        int tmax;
        int *d;
        //std::vector<int> *ed;
        std::unordered_map<int,int> *pt;
        std::vector<int> *ed;
        std::vector<int> *ed2;
        std::vector<std::vector<int>> *alfa;
        std::unordered_map<int,std::vector<int>> *mp;
        onlineindex(){}
        onlineindex(TemporalGraph *Graph);
        ~onlineindex();
        long long search(TemporalGraph *Graph, int ts,int te,int delta);
        int find(int u,int p);
        long long deal(int u,int v,int w,int delta);
        //int ec(int x,int y,std::vector<int> S);
        static bool cmp(node a,node b);
};
void online(onlineindex * Index, TemporalGraph *Graph, char * query_file, char * output_file);