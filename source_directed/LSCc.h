#include "commonfunctions.h"
#include "temporal_graph.h"
#include<unordered_map>

class LSCcindex{
    public:
    struct mode{
        int ts,te,val;
        mode(int _ts=0,int _te=0,int _val=0){ts=_ts;te=_te;val=_val;}
    };
    std::vector<mode> alfa;
    int n,m,tmax,len,len2,factor;
    std::unordered_map<int,std::vector<int> > *mp;
    std::vector<int> *ed;
    //std::vector<int> *ed2;
    std::vector<std::vector<int>> *beta;
    LSCcindex(){}
    LSCcindex(TemporalGraph *Graph);
    ~LSCcindex();
    int find(int u,int p);
    long long solve(int ts,int te,int delta);
    long long query1(int ts1,int ts2,int te1,int te2);
    long long brute1(int ts1,int ts2,int te1,int te2);
    long long query2(int ts1,int ts2,int te1,int te2);
    long long brute2(int ts1,int ts2,int te1,int te2);
    static bool cmp(mode a,mode b);
    long long** mat1;
    long long** mat2;
    struct node{
        int presum;
        int pos,next;
        node(int _pos,int _next,int _presum){pos=_pos;next=_next; presum=_presum;}
    };
    static bool cmp2(node a,node b);
    std::vector<node> *index1, *chunk1;
    std::vector<node> *index2, *chunk2;
    std::vector<node> *rindex1, *rchunk1;
    std::vector<node> *rindex2, *rchunk2;
};

void LSCc(LSCcindex *Index,TemporalGraph *Graph, char* query_file, char* output_file);