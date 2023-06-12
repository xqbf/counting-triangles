#include "commonfunctions.h"
#include "temporal_graph.h"
#include<unordered_map>

class arrayindex{
    public:
        struct mode{
            int ts,te,val;
            mode(int _ts=0,int _te=0,int _val=0){ts=_ts;te=_te;val=_val;}
        };
        std::vector<mode> alfa;
        int n,m,tmax;
        std::unordered_map<int,int> *mp;// check time by vertice
        //std::set<std::pair<int,int>> *ed;//enumerate neighbour by time
        std::vector<std::pair<int,int> > *ed;
        arrayindex(){}
        arrayindex(TemporalGraph *Graph);
        ~arrayindex();
        int solve(int ts,int te);
        struct node{
            int ts,presum;
            node(int _ts = 0, int _presum=0){ts=_ts;presum=_presum;}
        };
        static bool cmp(node a,node b);
        std::vector<node> *arraylist;
};

void array(arrayindex *Index, TemporalGraph *Graph, char* query_file, char* output_file);