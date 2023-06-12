#include "commonfunctions.h"
#include "temporal_graph.h"
#include<unordered_map>

class treeindex{
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
        treeindex(){}
        treeindex(TemporalGraph *Graph);
        ~treeindex();
        void directmodify(int direction, long long fa, int pos,int val,int l,int r);
        void modify(long long pre,long long &cur,int l,int r);
        int query(long long cur,int l,int r,int x,int y);
        int solve(int ts,int te);
        struct node{
            unsigned int ls1,rs1;
            char ls2,rs2;
            int sum;
            node(unsigned int _ls1=0, char _ls2=0, unsigned int _rs1=0, char _rs2=0, int _sum=0){
                ls1=_ls1;
                ls2=_ls2;
                rs1=_rs1;
                rs2=_rs2;
                sum=_sum;
            }
        };
        static bool cmp(mode a,mode b);
        std::vector<node> tree;
        //node* tree;
        long long *rt;
        long long cnt=0;
};

void tree(treeindex *Index, TemporalGraph *Graph, char* query_file, char* output_file);