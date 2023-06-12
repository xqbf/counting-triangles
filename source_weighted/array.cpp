#include "array.h"
#include <cmath>

bool arrayindex::cmp(node a,node b){
    return a.ts>b.ts;
}

arrayindex::arrayindex(TemporalGraph* Graph){
    n=Graph->n;
    m=Graph->m;
    tmax=Graph->tmax;
    mp=new std::unordered_map<int,std::vector<int> >[n];
    ed=new std::vector<int>[n];
    double start_time=clock();
    for(int t=0;t<=tmax;t++){
        std::vector<std::pair<int, int>>::iterator it;
        for (it = Graph->temporal_edge[t].begin(); it != Graph->temporal_edge[t].end(); it++) {
            int u=(*it).first;
            int v=(*it).second;
            if(ed[u].size()<ed[v].size())std::swap(u,v);
            for(auto p:ed[v]){
                if(mp[u].count(p)){
                    long long tmp=0;
                    std::vector<int> tmp1=mp[u][p];
                    std::vector<int> tmp2=mp[v][p];
                    int l1=0,l2=0;
                    for(int i=0;i<tmp1.size();i++){
                        while(tmp2[l2]<tmp1[i]&&l2<tmp2.size()){
                            l2++;
                        }
                        if(tmp2.size()==l2)break;
                        //std::cerr<<u<<' '<<v<<' '<<p<<' '<<tmp2.size()-l2<<std::endl;
                        alfa.push_back(mode(tmp1[i],t,tmp2.size()-l2));
                    }
                    for(int i=0;i<tmp2.size();i++){
                        while(tmp1[l1]<=tmp2[i]&&l1<tmp1.size()){
                            l1++;
                        }
                        if(tmp1.size()==l1)break;
                        //std::cerr<<u<<' '<<v<<' '<<p<<' '<<tmp1.size()-l1<<std::endl;
                        alfa.push_back(mode(tmp2[i],t,tmp1.size()-l1));
                    }
                    
                }
            }
            if(mp[u].count(v)){
                mp[u][v].push_back(t);
                mp[v][u].push_back(t);
            }
            else{
                ed[u].push_back(v);
                ed[v].push_back(u);
                std::vector<int> tmp1,tmp2;
                tmp1.clear();tmp2.clear();
                tmp1.push_back(t);tmp2.push_back(t);
                mp[u][v]=tmp1;
                mp[v][u]=tmp2;
            }
        }
        //std::cerr<<alfa.size()<<std::endl;
        if((t+1)%10000 == 0)
        putProcess(double(t+1) / (tmax+1), (clock()-start_time)/CLOCKS_PER_SEC);
    }
    std::cout << "Fetching total: " << timeFormatting((clock()-start_time)/CLOCKS_PER_SEC).str() << std::endl<<std::endl;
    arraylist = new std::vector<node> [tmax+1];
    for(int i=0;i<alfa.size();i++){
        //std::cout<<alfa[i].ts<<' '<<alfa[i].te<<' '<<alfa[i].val<<std::endl;
        arraylist[alfa[i].te].push_back(node(alfa[i].ts,alfa[i].val));
    }
    int sum=0;
    for(int i=0;i<=tmax;i++){
        sort(arraylist[i].begin(),arraylist[i].end(),cmp);
        for(int j=1;j<arraylist[i].size();j++){
            arraylist[i][j].presum+=arraylist[i][j-1].presum;
        }
        sum+=arraylist[i].size();
    }
    std::cout << "Indexing total: " << timeFormatting((clock()-start_time)/CLOCKS_PER_SEC).str() << std::endl;
    std::cout << "Indexing size: " <<  8ll*sum<<"bytes"<< std::endl<<std::endl;
}


int arrayindex::solve(int ts,int te){
    int ans=0;
    for(int i=ts;i<=te;i++){
        if(arraylist[i].empty())continue;
        int l=0,r=arraylist[i].size()-1,pos=-1;
        while(l<=r){
            int mid=(l+r)>>1;
            if(arraylist[i][mid].ts>=ts){
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

void array(arrayindex *Index, TemporalGraph *Graph, char* query_file, char* output_file){
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