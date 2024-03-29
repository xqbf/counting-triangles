#include "commonfunctions.h"
#include "temporal_graph.h"
#include <unordered_map>
class measureindex{
    public:
        int n,m,tmax,factor;
        std::unordered_map<int,std::vector<int> > *mp;// check time by vertice
        //std::set<std::pair<int,int>> *ed;//enumerate neighbour by time
        std::vector<int> *ed;
        double expectation;
        long double variance;
        measureindex(){}
        measureindex(TemporalGraph *Graph);
        ~measureindex();
};
void measure(measureindex * Index, TemporalGraph *Graph, char * query_file, char * output_file);