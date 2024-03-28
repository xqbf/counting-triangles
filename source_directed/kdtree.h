#include "commonfunctions.h"
#include "temporal_graph.h"
#include<unordered_map>

class kdindex{
    public:
    int factor;
    struct point{
        int ts,delta;
        point(int _ts=0,int _delta=0){ts=_ts;delta=_delta;}
    };
    struct mode{
        int ts,te,delta;
        short val;
        mode(int _ts=0,int _te=0,int _delta=0,short _val=0){ts=_ts;te=_te;delta=_delta;val=_val;}
    };
    std::vector<mode> alfa;
    //std::vector<point> aggregate_points;
    std::map<std::pair<int, std::pair<int,int> >, std::vector<point> > deltav;
    mode *a;
    int n,m,tmax;
    std::unordered_map<int,int>* mp;
    std::vector<std::pair<int,int> > *ed;
    kdindex(){};
    kdindex(TemporalGraph *Graph);
    ~kdindex();
    static bool cmp(mode a,mode b);
    struct node{
        int ls,rs,mxpos[3],mnpos[3],val,pos[3];
        long long tot;
    };
    void pushup(int rt);
    void build(int &rt,int l,int r,int dep);
    long long query(int rt,int ts1,int ts2,int te1,int te2,int delta1,int delta2);
    long long solve(int ts,int te,int delta); 
    int cnt=0,num=0;
    node *tree;
};
void kd(kdindex *Index,TemporalGraph *Graph, char* query_file, char* output_file);