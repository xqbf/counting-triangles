#include "online.h"


inline short onlineindex::find(int u,int p){
    int id=p%40;
    for(auto val:point[u].para[id]){
        if(ed[u][val]==p){
            return val;
        }
    }
    return -1;
}


long long onlineindex::search(TemporalGraph *Graph, int ts, int te,int delta){
    for(int i=0;i<n;i++){
        ed[i].clear();
        ed2[i].clear();
        len[i]=0;
        len2[i]=0;
        vis[i]=-1;
        ans1[i].clear();
        cnt1[i].clear();
        for(int j=0;j<40;j++)point[i].para[j].clear();
        //red[i].clear();
        triangle[i].clear();
    }
    long long ans=0;
    for(int t=ts;t<=te;t++){
        std::vector<std::pair<int, int>>::iterator it;
        int u,v;
        for (it = Graph->temporal_edge[t].begin(); it != Graph->temporal_edge[t].end(); it++) {
            u=(*it).first;
            v=(*it).second;
            ed2[u].emplace_back(v);
            ed2[v].emplace_back(u);
        }
    }
    std::vector<int>alfa;
    for(int i=0;i<n;i++){
        std::sort(ed2[i].begin(),ed2[i].end());
        ed2[i].erase(std::unique(ed2[i].begin(),ed2[i].end()), ed2[i].end());
        len2[i]=ed2[i].size();
    }
    
    for(int i=0;i<n;i++){
        int sz=len2[i];
        if(sz==1)continue;
        for(auto u:ed2[i]){
            if((len2[u]<sz)||(len2[u]==sz&&u<i)){
                ed[u].emplace_back(i);
                
                //red[i].push_back(std::pair<int,int>(u,len[u]++));
                int id=i%40;
                point[u].para[id].emplace_back(len[u]++);
            }
        }
    }

    
    for(int u=0;u<n;u++){
        cnt1[u].resize(len[u]);
        ans1[u].resize(len[u]);
        triangle[u].resize(len[u]);
        for(int j=0;j<len[u];j++){
            vis[ed[u][j]]=j;
        }
        for(int j=0;j<len[u];j++){
            int v=ed[u][j];
            for(int k=0;k<len[v];k++){
                int w=ed[v][k];
                if(vis[w]!=-1){
                    triangle[u][j].emplace_back(std::pair<short,short>(vis[w],k));
                    triangle[u][vis[w]].emplace_back(std::pair<short,short>(j,k));
                }
            }
        }
        for(int j=0;j<len[u];j++){
            vis[ed[u][j]]=-1;
        }
    }
    //std::cerr<<"test\n";


    
    for(int t=ts;t<=te;t++){
        //std::cerr<<t-delta-1<<' '<<ts<<' '<<t<<std::endl;
        std::vector<std::pair<int, int>>::iterator it;
        int u,v;
        if(t-delta-1>=ts){
            //std::cerr<<t-delta-1<<"?\n";
            int t2=t-delta-1;
            for (it = Graph->temporal_edge[t2].begin(); it != Graph->temporal_edge[t2].end(); it++) {
                u=(*it).first;
                v=(*it).second;
                if(u>v)std::swap(u,v);
                if(len2[u]>len2[v])std::swap(u,v);
                if(len2[u]==1)continue;
                int pos=find(u,v);
                    for(auto p:triangle[u][pos]){
                        int w=ed[u][p.first], id_v_w=p.second, id_u_w = p.first;
                        long long tmp = cnt1[u][id_u_w];
                        if(tmp==0)continue;
                        if((len2[v]<len2[w])||(len2[v]==len2[w] && v<w)){//v smaller than w
                            ans1[v][id_v_w]-=tmp;
                        }
                        else{//w smaller than v
                            ans1[w][id_v_w]-=tmp;
                        }
                    }
                    cnt1[u][pos]--;
                    // for(int i=0;i<len[v];i++){
                    //     vis[ed[v][i]]=i;
                    // }
                    // int pos=-1;
                    // for(int i=0;i<len[u];i++){
                    //     int w=ed[u][i];
                    //     if(v==w){
                    //         pos=i;
                    //         continue;
                    //     }
                    //     //int v1=std::min(u,w),v2=std::max(u,w);

                    //     long long tmp=cnt1[u][i];
                    //     if(tmp==0)continue;
                    //     if((len2[v]<len2[w])||(len2[v]==len2[w] && v<w)){
                    //         int id=vis[w];
                    //         if(id!=-1){
                    //             ans1[v][id]-=tmp;
                    //         }
                    //     }
                    //     else{
                    //         int id=find(w,v);
                    //         if(id!=-1){
                    //             ans1[w][id]-=tmp;
                    //         } 
                            
                    //     }
                    //     //v1 = std::min(v,w),v2=std::max(v,w);
                    //     //ans1[v1*2147483647ll+v2]-=tmp;
                    // }
                    // int id=pos;
                    // cnt1[u][pos]--;
                    // for(int p:ed[v]){
                    //     vis[p]=-1;
                    // }
                
            }
        }
        for (it = Graph->temporal_edge[t].begin(); it != Graph->temporal_edge[t].end(); it++) {
            u=(*it).first;
            v=(*it).second;
            if(u>v)std::swap(u,v);
            if(len2[u]>len2[v])std::swap(u,v);
            
                if(len2[u]==1)continue;
                
                int pos=find(u,v);
                
                    for(auto p:triangle[u][pos]){
                        int w=ed[u][p.first], id_v_w=p.second, id_u_w = p.first;
                        long long tmp = cnt1[u][id_u_w];
                        if(tmp==0)continue;
                        if((len2[v]<len2[w])||(len2[v]==len2[w] && v<w)){//v smaller than w
                            ans+=tmp*cnt1[v][id_v_w];
                            ans1[v][id_v_w]+=tmp;
                        }
                        else{//w smaller than v
                            ans+=tmp*cnt1[w][id_v_w];
                            ans1[w][id_v_w]+=tmp;
                        }
                    }
                    cnt1[u][pos]++;
                    ans+=ans1[u][pos];
            
        }
    }
    std::cerr<<ts<<' '<<te<<' '<<delta<<' '<<ans<<std::endl;
    return ans;
}


onlineindex::onlineindex(TemporalGraph *Graph){
    n=Graph->n;
    tmax=Graph->tmax;
    vis = new int[n];
    d = new int[n];
    ed = new std::vector<int> [n]();
    ed2 = new std::vector<int> [n]();
    cnt1 = new std::vector<int > [n]();
    ans1 = new std::vector<long long>[n]();
    //red = new std::vector<std::pair<int,int> > [n]();
    triangle = new std::vector<std::vector<std::pair<short,short> > > [n]();
    point = new node[n];
    len2 = new int[n];
    len = new short[n];
    for(int i=0;i<n;i++)len2[i]=0;
    for(int t=0;t<=tmax;t++){
        std::vector<std::pair<int, int>>::iterator it;
        for (it = Graph->temporal_edge[t].begin(); it != Graph->temporal_edge[t].end(); it++) 
        {
            int u=(*it).first,v=(*it).second;
            len2[u]++;len2[v]++;
        }
    }
    for(int i=0;i<n;i++){
        ed2[i].resize(len2[i]);
        len2[i]=0;
    }
}

onlineindex::~onlineindex(){
    delete [] d;
    delete [] ed2;
    delete [] ed;
    delete [] alfa;
    //delete [] point;
    //delete [] alfa;
}
void online(onlineindex *Index, TemporalGraph *Graph, char * query_file, char * output_file){
    int ts, te,delta;
    int query_num = 0;
    std::ifstream fin(query_file);
    std::ofstream fout(output_file);
    
    while(fin >> ts >> te >> delta){
        ++query_num;
    }

    fin=std::ifstream(query_file);

    int i=0;
    double start_time=clock();
    while(fin >> ts >> te >> delta){
        //std::cerr<<ts<<' '<<te;
        fout<<Index->search(Graph, ts , te,delta)<<std::endl;
        putProcess(double(++i) / query_num, (clock()-start_time)/CLOCKS_PER_SEC);
    }
    std::cout << "Average: " << timeFormatting((clock()-start_time)/CLOCKS_PER_SEC / query_num).str() << std::endl;
}