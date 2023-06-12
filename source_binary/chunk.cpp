#include "chunk.h"
#include <cmath>

bool chunkindex::cmp(node a,node b){
    return a.ts>b.ts;
}

bool chunkindex::cmp2(mode a,mode b){
    if(a.te==b.te)return a.ts<b.ts;
    return a.te<b.te;
}

chunkindex::chunkindex(TemporalGraph* Graph){
    n=Graph->n;
    m=Graph->m;
    tmax=Graph->tmax;
    mp=new std::unordered_map<int,int>[n];
    ed=new std::vector<std::pair<int,int>>[n];
    double start_time=clock();
    for(int t=0;t<=tmax;t++){
        std::vector<std::pair<int, int>>::iterator it;
        for (it = Graph->temporal_edge[t].begin(); it != Graph->temporal_edge[t].end(); it++) {
            int u=(*it).first;
            int v=(*it).second;
            if(mp[u].count(v)){//already connected before
                int time=mp[u][v];
                ed[v].push_back(std::pair<int,int>(u,t));
                ed[u].push_back(std::pair<int,int>(v,t));
                int du=ed[u].size();
                int dv=ed[v].size();
                if(du<dv){
                    std::swap(u,v);
                    std::swap(du,dv);
                }
                std::unordered_map<int,int> vis;
                vis.clear();
                for(int i=dv-1;i>=0;i--){
                    std::pair<int,int> p=ed[v][i];
                    int t1=p.second,v1=p.first;
                    if(t1<=time){
                        break;
                    }
                    if(vis.count(v1))continue;
                    vis[v1]=1;
                    if(mp[u].count(v1)){
                        //std::cerr<<u<<' '<<v<<' '<<v1<<std::endl;
                        //std::cerr<<t<<' '<<t1<<' '<<mp[u][v1]<<std::endl;
                        int tmn=std::min(std::min(t,t1),mp[u][v1]);
                        if(tmn>time){
                            alfa.push_back(mode(time,t,-1));
                            alfa.push_back(mode(tmn,t,1));
                        }
                    }
                }
                //std::cerr<<u<<' '<<v<<' '<<t<<'\n';
                mp[u][v]=t;
                mp[v][u]=t;
            }
            else{//not connected before
                int time=t;
                int du=ed[u].size();
                int dv=ed[v].size();
                if(du<dv){
                    std::swap(u,v);
                    std::swap(du,dv);
                }
                std::unordered_map<int,int> vis;
                vis.clear();
                for(int i=dv-1;i>=0;i--){
                    std::pair<int,int> p=ed[v][i];
                    int t1=p.second;
                    int v1=p.first;
                    if(vis.count(v1))continue;
                    vis[v1]=1;
                    if(mp[u].count(v1)){
                        int tmn=std::min(std::min(t,t1),mp[u][v1]);
                        alfa.push_back(mode(tmn,t,1));
                    }
                }
                ed[v].push_back(std::pair<int,int>(u,t));
                ed[u].push_back(std::pair<int,int>(v,t));
                mp[u][v]=t;
                mp[v][u]=t;
            }
        }
        if((t+1)%10000 == 0)
        putProcess(double(t+1) / (tmax+1), (clock()-start_time)/CLOCKS_PER_SEC);
    }
    std::cout << "Fetching total: " << timeFormatting((clock()-start_time)/CLOCKS_PER_SEC).str() << std::endl<<std::endl;
    sort(alfa.begin(),alfa.end(),cmp2);
    std::vector<mode> beta;beta.clear();
    mode current;
    current.ts=alfa[0].ts;
    current.te=alfa[0].te;
    current.val=alfa[0].val;
    for(int i=1;i<alfa.size();i++){
        if(alfa[i].ts==alfa[i-1].ts && alfa[i].te==alfa[i-1].te){
            current.val+=alfa[i].val;
        }
        else{
            if(current.val!=0)
            beta.push_back(current);
            current=alfa[i];
        }
    }
    beta.push_back(current);
    std::swap(alfa,beta);
    beta.clear();
    arraylist = new std::vector<node> [tmax+1];
    len=std::sqrt(tmax+1);
    chunklist = new std::vector<node> [len+5];
    for(int i=0;i<alfa.size();i++){
        arraylist[alfa[i].te].push_back(node(alfa[i].ts,alfa[i].val));
        chunklist[alfa[i].te/len].push_back(node(alfa[i].ts,alfa[i].val));
    }
    long long sum=0;
    for(int i=0;i<=tmax;i++){
        sort(arraylist[i].begin(),arraylist[i].end(),cmp);
        for(int j=1;j<arraylist[i].size();j++){
            arraylist[i][j].presum+=arraylist[i][j-1].presum;
        }
        sum+=arraylist[i].size();
    }
    for(int i=0;i<=tmax;i+=len){
        sort(chunklist[i/len].begin(),chunklist[i/len].end(),cmp);
        for(int j=1;j<chunklist[i/len].size();j++){
            chunklist[i/len][j].presum+=chunklist[i/len][j-1].presum;
        }
        sum+=chunklist[i/len].size();
    }
    std::cout << "Indexing total: " << timeFormatting((clock()-start_time)/CLOCKS_PER_SEC).str() <<std::endl;
    std::cout << "Indexing size: " <<  8ll*sum<<"bytes"<< std::endl<<std::endl;
}

int chunkindex::second_solve(int bar, int ts,int te){
    //std::cerr<<ts<<' '<<te<<"?\n";
    int ans=0;
    for(int i=ts;i<=te;i++){
        int l=0,r=arraylist[i].size()-1,pos=-1;
        while(l<=r){
            int mid=(l+r)>>1;
            if(arraylist[i][mid].ts>=bar){
                pos=mid;
                l=mid+1;
            }
            else r=mid-1;
        }
        if(pos!=-1){
            ans+=arraylist[i][pos].presum;
            //std::cerr<<i<<' '<<arraylist[i][pos].presum<<'\n';
        }
    }
    return ans;
}


int chunkindex::solve(int ts,int te){
    int ans=0;
    int lb=ts/len, rb=te/len;
    if(lb==rb || rb==lb+1){
        return second_solve(ts,ts,te);
    }
    for(int i=lb+1;i<rb;i++){
        int l=0,r=chunklist[i].size()-1,pos=-1;
        while(l<=r){
            int mid=(l+r)>>1;
            if(chunklist[i][mid].ts>=ts){
                pos=mid;
                l=mid+1;
            }
            else r=mid-1;
        }
        if(pos!=-1){
            ans+=chunklist[i][pos].presum;
            //std::cerr<<i*len<<' '<<(i+1)*len-1<<' '<<chunklist[i][pos].presum<<'\n';
        }
    }
    ans+=second_solve(ts,ts,len*(lb+1)-1);
    ans+=second_solve(ts,len*rb,te);
    return ans;
}

void chunk(chunkindex *Index, TemporalGraph *Graph, char* query_file, char* output_file){
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
    int tmp=0;
    while(fin >> ts >> te){
        //std::cerr<<ts<<' '<<te;
        fout<<Index->solve(ts , te)<<std::endl;
        tmp++;
        if(tmp%100 == 0)
        putProcess(double(++i) / query_num, (clock()-start_time)/CLOCKS_PER_SEC);
    }
    std::cout << "Average: " << timeFormatting((clock()-start_time)/CLOCKS_PER_SEC / query_num).str() << std::endl;
}