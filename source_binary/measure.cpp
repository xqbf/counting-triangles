#include "measure.h"
#include <cmath>

measureindex::measureindex(TemporalGraph* Graph){
    n=Graph->n;
    m=Graph->m;
    tmax=Graph->tmax;
    factor=RAND_MAX*0.01;
    mp=new std::unordered_map<int,std::vector<int> >[n];
    ed=new std::vector<int>[n];
    double start_time=clock();
    srand(1);
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
                        if(rand()<factor)
                        //alfa.push_back(mode(tmp1[i],t,tmp2.size()-l2));
                        expectation += 2.0*(tmax-t+1)*(tmp1[i]+1)*(tmp2.size()-l2)/(tmax+1);
                    }
                    for(int i=0;i<tmp2.size();i++){
                        while(tmp1[l1]<=tmp2[i]&&l1<tmp1.size()){
                            l1++;
                        }
                        if(tmp1.size()==l1)break;
                        //std::cerr<<u<<' '<<v<<' '<<p<<' '<<tmp1.size()-l1<<std::endl;
                        if(rand()<factor)
                        //alfa.push_back(mode(tmp2[i],t,tmp1.size()-l1));
                        expectation += 2.0*(tmax-t+1)*(tmp2[i]+1)*(tmp1.size()-l1)/(tmax+1);
                    }
                    std::vector<int>().swap(tmp1);
                    std::vector<int>().swap(tmp2);
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
                std::vector<int>().swap(tmp1);
                std::vector<int>().swap(tmp2);
            }
            if((t+1)%10000 == 0)
            putProcess(double(t+1) / (tmax+1), (clock()-start_time)/CLOCKS_PER_SEC);
        }
    }    
        //std::cerr<<alfa.size()<<std::endl;
        expectation = expectation/(tmax+2);
        mp=new std::unordered_map<int,std::vector<int> >[n];
        ed=new std::vector<int>[n];
    
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
                        if(rand()<factor)
                        //alfa.push_back(mode(tmp1[i],t,tmp2.size()-l2));
                        variance += ((tmp2.size()-l2)-expectation)*((tmp2.size()-l2)-expectation)*2.0*(tmax-t+1)*(tmp1[i]+1)/(tmax+1);
                    }
                    for(int i=0;i<tmp2.size();i++){
                        while(tmp1[l1]<=tmp2[i]&&l1<tmp1.size()){
                            l1++;
                        }
                        if(tmp1.size()==l1)break;
                        //std::cerr<<u<<' '<<v<<' '<<p<<' '<<tmp1.size()-l1<<std::endl;
                        if(rand()<factor)
                        //alfa.push_back(mode(tmp2[i],t,tmp1.size()-l1));
                        variance += (tmp1.size()-l1-expectation)*(tmp1.size()-l1-expectation)*2.0*(tmax-t+1)*(tmp2[i]+1)/(tmax+1);
                    }
                    std::vector<int>().swap(tmp1);
                    std::vector<int>().swap(tmp2);
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
                std::vector<int>().swap(tmp1);
                std::vector<int>().swap(tmp2);
            }
        }
        if((t+1)%10000 == 0)
        putProcess(double(t+1) / (tmax+1), (clock()-start_time)/CLOCKS_PER_SEC);
    } 
    variance/=(tmax+2);
    std::cout << "Fetching total: " << timeFormatting((clock()-start_time)/CLOCKS_PER_SEC).str() << std::endl<<std::endl;
    std::cout <<"Expectation: "<< expectation*RAND_MAX/factor <<' '<<"Variance: "<<variance*RAND_MAX/factor*RAND_MAX/factor<< "Standard Deviation: "<< sqrt(variance*RAND_MAX/factor*RAND_MAX/factor)<<'\n';
}