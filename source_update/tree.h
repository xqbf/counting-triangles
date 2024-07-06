#include "commonfunctions.h"
#include "temporal_graph.h"
#include<unordered_map>
#include<bitset>
class treeindex{
    public:
        struct mode{
            int ts,te,val;
            mode(int _ts=0,int _te=0,int _val=0){ts=_ts;te=_te;val=_val;}
        };
        std::vector<mode> alfa;
        std::vector<mode> alfa2;
        int n,m,tmax,lgu,factor,tim;
        std::unordered_map<int,std::vector<int> > *mp;// check time by vertice
        //std::set<std::pair<int,int>> *ed;//enumerate neighbour by time
        std::vector<int> *ed;
        std::vector<std::vector<int>> *beta;
        int Find(int u,int p);
        treeindex(){}
        treeindex(TemporalGraph *Graph,double length);
        void update(TemporalGraph *Graph, double pre);
        ~treeindex();
        long long solve(int ts,int te,int delta);
        struct node{
            std::vector<long long> chunk_sum;
            std::vector<short> node_value;
            std::vector<bool> from;
            std::vector<int> pos;
            std::vector<unsigned int> from_table;
        };
        
        static bool cmp(mode a,mode b);
        long long cnt=0;
        struct tree{
            node* tr;
            int lgt;
            long long total = 0;
            long long find(int pos);
            void build(int rt,int l,int r);
            void insert(int rt,int l,int r,int pos1,int pos2,short node_value);
            long long query(int rt,int l,int r,int x,int y,long long p);
            void update(int rt,int l,int r,int pos1,int pos2,short node_value);
        }tree1,tree2;
};

void tree(treeindex *Index, TemporalGraph *Graph, char* query_file, char* output_file);