#include "commonfunctions.h"
#include "temporal_graph.h"

class baseline{
    public:
    int n,tmax;
    struct edge{
        int ts,te,v;
        edge(int t1=0,int t2=0,int v1=0){
            ts=t1;te=t2;v=v1;
        }
    };
    struct relation{
        int u,v,w;
        relation(int u1=0,int v1=0,int w1=0){
            u=u1;v=v1;w=w1;
        }
    };
    static bool cmp(edge a,edge b);
    std::vector<relation> alfa;
    std::vector<int> *ed;
    std::set<int> *s;
    std::vector<edge> **g;
    int *vis;
    baseline(){}
    baseline(TemporalGraph *Graph);
    ~baseline();
    long long solve(int ts,int te,int delta); 
    long long count(int u,int v,int w,int ts,int te,int delta);
    inline int find(int u,int v,int delta);
};

void base(baseline* Index, TemporalGraph *Graph, char* query_file, char* output_file);