#include "online.h"


bool onlineindex::cmp(node a,node b){
    if(a.degree==b.degree)return a.id<b.id;
    return a.degree>b.degree;
}

int onlineindex::search(TemporalGraph *Graph, int ts,int te){
    for(int i=0;i<n;i++){
        point[i].id=i;
        point[i].degree=0;
        g[i].clear();
    }
    for(int t=ts;t<=te;t++){
        //std::cerr<<t<<'\n';
        for(auto iter=Graph->temporal_edge[t].begin();iter!=Graph->temporal_edge[t].end();iter++){
            int u=(*iter).first;
            int v=(*iter).second;
            //std::cerr<<u<<' '<<v<<'\n';
            if(g[u].find(v)!=g[u].end())continue;
            g[u].insert(v);
            g[v].insert(u);
            point[u].degree++;
            point[v].degree++;
        }
    }
    /*for(int t=ts;t<=te;t++){
        //std::cerr<<t<<'\n';
        for(auto iter=Graph->temporal_edge[t].begin();iter!=Graph->temporal_edge[t].end();iter++){
            int u=(*iter).first;
            int v=(*iter).second;
            //std::cerr<<u<<' '<<v<<'\n';
            if(point[u].degree>point[v].degree){
                if(g[u].find(v)!=g[u].end())continue;
                g[u].insert(v);
            }
            else{
                if(g[v].find(u)!=g[v].end())continue;
                g[v].insert(u);
            }
        }
    }*/
    std::sort(point,point+n,cmp);
    
    for(int i=0;i<n;i++)ps[point[i].id]=i;
    //std::cerr<<"???";
    int ans=0;
    for(int i=0;i<n;i++){
        int u=point[i].id;
        auto iter=g[u].begin();
        for(;iter!=g[u].end();iter++){
            int v=*iter;
            //std::cerr<<v<<' '<<u<<'\n';
            if(ps[v]<i)continue;
            auto k=g[v].begin();
            for(;k!=g[v].end();k++){
                if(ps[*k]<ps[v])continue;
                if(g[u].find(*k)!=g[u].end()){
                    //std::cerr<<u<<' '<<v<<' '<<*k<<'\n';
                    ans++;
                }
            }
        }
    }
    //std::cerr<<ans<<'\n';
    return ans;
}

onlineindex::onlineindex(TemporalGraph *Graph){
    n=Graph->n;
    //std::cerr<<n<<std::endl;
    point = new node[n];
    ps = new int[n];
    g = new std::unordered_set<int> [n]();
    for(int i=0;i<n;i++){
        point[i].id=i;
        point[i].degree=0;
        g[i].clear();
    }

}

onlineindex::~onlineindex(){
    delete [] ps;
    delete [] g;
    delete [] point;
}
void online(onlineindex *Index, TemporalGraph *Graph, char * query_file, char * output_file){
    int ts, te;
    int query_num = 0;
    std::ifstream fin(query_file);
    std::ofstream fout(output_file);
    
    while(fin >> ts >> te){
        ++query_num;
    }

    fin=std::ifstream(query_file);

    int i=0;
    double start_time=clock();
    while(fin >> ts >> te){
        //std::cerr<<ts<<' '<<te;
        fout<<Index->search(Graph, ts , te)<<std::endl;
        putProcess(double(++i) / query_num, (clock()-start_time)/CLOCKS_PER_SEC);
    }
    std::cout << "Average: " << timeFormatting((clock()-start_time)/CLOCKS_PER_SEC / query_num).str() << std::endl;
}