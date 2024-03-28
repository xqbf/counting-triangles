#include "commonfunctions.h"
#include "temporal_graph.h"
#include <unordered_map>
class onlineCindex{
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
        std::vector<int> *ed3;
        std::vector<int> *back;
        std::vector<std::vector<int>> *alfa1;
        std::vector<std::vector<int>> *alfa2;
        std::unordered_map<int,std::vector<int>> *mp;
        onlineCindex(){}
        onlineCindex(TemporalGraph *Graph);
        ~onlineCindex();
        long long search(TemporalGraph *Graph, int ts,int te,int delta);
        int find(int u,int p);
        long long deal(int u,int v,int w,int delta);
        //int ec(int x,int y,std::vector<int> S);
        static bool cmp(node a,node b);
};
void onlineC(onlineCindex * Index, TemporalGraph *Graph, char * query_file, char * output_file);