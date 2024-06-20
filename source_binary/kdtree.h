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
    std::vector<mode> beta;
    //std::vector<point> aggregate_points;
    //std::map<std::pair<int, std::pair<int,int> >, std::vector<point> > deltav;
    mode *a;
    int n,m,tmax;
    //std::unordered_map<int,int>* mp;
    int *d;
    std::vector<int> *ed;
    std::vector<std::vector<int> > *alfa;
    std::vector<mode> P;
    std::vector<int> *ed2;
    kdindex(){};
    kdindex(TemporalGraph *Graph);
    ~kdindex();
    int find(int u,int p);
    void deal(int u,int v,int w);
    static bool cmp(mode a,mode b);
    struct node{
        long long ls,rs;
        int mxpos[3],mnpos[3],val,pos[3];
        long long tot;
    };
    void pushup(long long rt);
    void build(long long &rt,long long l,long long r,int dep);
    long long query(long long rt,int ts1,int ts2,int te1,int te2,int delta1,int delta2);
    long long solve(int ts,int te,int delta); 
    long long cnt=0,num=0;
    node *tree;
};
void kd(kdindex *Index,TemporalGraph *Graph, char* query_file, char* output_file);