#include "commonfunctions.h"
#include "temporal_graph.h"
#include<unordered_map>

class chunkindex{
    public:
        struct mode{
            int ts,te,val;
            mode(int _ts=0,int _te=0,int _val=0){ts=_ts;te=_te;val=_val;}
        };
        std::vector<mode> alfa;
        int n,m,tmax,len;
        std::unordered_map<int,std::vector<int> > *mp;// check time by vertice
        //std::set<std::pair<int,int>> *ed;//enumerate neighbour by time
        std::vector<int> *ed;
        chunkindex(){}
        chunkindex(TemporalGraph *Graph);
        ~chunkindex();
        int solve(int ts,int te);
        int second_solve(int bar, int ts,int te);
        struct node{
            int ts,presum;
            node(int _ts = 0, int _presum=0){ts=_ts;presum=_presum;}
        };
        static bool cmp(node a,node b);
        static bool cmp2(mode a,mode b);
        std::vector<node> *arraylist;
        std::vector<node> *chunklist;
};

void chunk(chunkindex *Index, TemporalGraph *Graph, char* query_file, char* output_file);