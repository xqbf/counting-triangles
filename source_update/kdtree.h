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
    int n,m,tmax,tim;
    std::unordered_map<int,int>* mp;
    std::unordered_map<int,int>* rep;
    std::vector<std::pair<int,int> > *ed;
    kdindex(){};
    kdindex(TemporalGraph *Graph,double length);
    ~kdindex();
    static bool cmp(mode a,mode b);
    struct node{
        long long ls,rs;
        int mxpos[3],mnpos[3],pos[3];
        short val;
        long long tot;
        node(){
            ls=0;
            rs=0;
            for(int i=0;i<3;i++)mxpos[i]=mnpos[i]=pos[i]=0;
            tot=0;
        }
    };
    void update(TemporalGraph *Graph, double pre);
    void pushup(long long rt);
    void build(long long &rt,long long l,long long r,int dep);
    long long query(long long rt,int ts1,int ts2,int te1,int te2,int delta1,int delta2);
    long long solve(int ts,int te,int delta); 
    void insert(long long &rt, mode a, long long dep);
    long long cnt=0,num=0,root=0;
    std::vector<node> tree;
};
void kd(kdindex *Index,TemporalGraph *Graph, char* query_file, char* output_file);