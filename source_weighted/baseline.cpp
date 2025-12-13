#include "baseline.h"

inline int baseline::find(int u,int v,int delta){
    int l=0,r=g[delta][u].size()-1,ans=-1;
    while(l<=r){
        int mid=(l+r)>>1;
        if(g[delta][u][mid].v>=v){
            ans=mid;
            r=mid-1;
        }
        else{l=mid+1;}
    }
    if(ans==-1)return ans;
    if(g[delta][u][ans].v==v)return ans;
    return -1; 
}

long long baseline::count(int u,int v,int w,int ts,int te,int delta){
    // std::cerr<<u<<' '<<v<<' '<<w<<' '<<ts<<' '<<te<<' '<<delta<<'\n';
    int l1=find(u,v,delta);
    int l2=find(v,w,delta);
    int l3=find(u,w,delta);
    
    if(l1==-1||l2==-1||l3==-1)return 0;
    // std::cerr<<g2[u][l1].ts<<' '<<g2[v][l2].ts<<' '<<g2[u][l3].ts<<'\n';
    while(g[delta][u][l1].v==v&&g[delta][u][l1].te<ts)l1++;
    while(g[delta][v][l2].v==w&&g[delta][v][l2].te<ts)l2++;
    while(g[delta][u][l3].v==w&&g[delta][u][l3].te<ts)l3++;
    
    long long ans=0;
    while(g[delta][u][l1].v==v&&g[delta][v][l2].v==w&&g[delta][u][l3].v==w&&g[delta][u][l1].ts<=te&&g[delta][v][l2].ts<=te&&g[delta][u][l3].ts<=te){
        // std::cerr<<g[delta][u][l1].ts<<' '<<g[delta][v][l2].ts<<' '<<g[delta][u][l3].ts<<'\n';
        if(g[delta][u][l1].ts<= g[delta][v][l2].ts && g[delta][u][l1].ts<=g[delta][u][l3].ts){// (u,v) smallest
            int l=l2,r=g[delta][v].size()-1,ans_vw=l2-1;
            while(l<=r){
                int mid=(l+r)>>1;
                if(g[delta][v][mid].ts<=g[delta][u][l1].ts+delta&& g[delta][v][mid].v==w){
                    ans_vw=mid;l=mid+1;
                }
                else r=mid-1;
            }
            int ans_uw=l3-1;
            l=l3,r=g[delta][u].size()-1;
            while(l<=r){
                int mid=(l+r)>>1;
                if(g[delta][u][mid].ts<=g[delta][u][l1].ts+delta&& g[delta][u][mid].v==w){
                    ans_uw=mid;l=mid+1;
                }
                else r=mid-1;
            }
            //if((ans_uw-l3+1)*(ans_vw-l2+1)>0) std::cerr<<u<<' '<<v<<' '<<w<<"?\n";
            ans=ans+(ans_uw-l3+1)*(ans_vw-l2+1);
            l1++;
        }
        else if(g[delta][v][l2].ts<g[delta][u][l1].ts && g[delta][v][l2].ts<=g[delta][u][l3].ts){ // (v,w) smallest
            int l=l1,r=g[delta][u].size()-1,ans_uv=l1-1;
            while(l<=r){
                int mid=(l+r)>>1;
                if(g[delta][u][mid].ts<=g[delta][v][l2].ts+delta&& g[delta][u][mid].v==v){
                    ans_uv=mid;l=mid+1;
                }
                else r=mid-1;
            }
            int ans_uw=l3-1;
            l=l3,r=g[delta][u].size()-1;
            while(l<=r){
                int mid=(l+r)>>1;
                if((g[delta][u][mid].ts<=g[delta][v][l2].ts+delta)&& (g[delta][u][mid].v==w)){
                    ans_uw=mid;l=mid+1;
                }
                else r=mid-1;
            }
            //if(u==1&&v==2&&w==4)
            //if((ans_uw-l3+1)*(ans_uv-l1+1)>0) std::cerr<<u<<' '<<v<<' '<<w<<"??\n";
            ans=ans+(ans_uw-l3+1)*(ans_uv-l1+1);
            l2++;
        }
        else{// (u,w) smallest
        //std::cerr<<"??\n";
            int l=l1,r=g[delta][u].size()-1,ans_uv=l1-1;
            while(l<=r){
                int mid=(l+r)>>1;
                if((g[delta][u][mid].ts<=g[delta][u][l3].ts+delta) && (g[delta][u][mid].v==v)){
                    ans_uv=mid;l=mid+1;
                }
                else r=mid-1;
            }

            l=l2,r=g[delta][v].size()-1; 
            int ans_vw=l2-1;
            while(l<=r){
                int mid=(l+r)>>1;
                if((g[delta][v][mid].ts<=g[delta][u][l3].ts+delta)&&(g[delta][v][mid].v==w)){
                    ans_vw=mid;l=mid+1;
                }
                else r=mid-1;
            }
            if(u==1&&v==2&&w==4){
                // for(auto p:g[delta][u]) std::cerr<<p.v<<' '<<p.ts<<'\n';
                // for(auto p:g[delta][v]) std::cerr<<p.v<<' '<<p.ts<<'\n';
                // for(auto p:g[delta][w]) std::cerr<<p.v<<' '<<p.ts<<'\n';
                // std::cerr<<ans_vw<<' '<<g[delta][v][ans_vw].ts<<' '<<g[delta][u][ans_uv].ts<<' '<<ans_uv<<'\n';
            }
            // if((ans_vw-l2+1)*(ans_uv-l1+1)>0) std::cerr<<u<<' '<<v<<' '<<w<<"???\n";
            ans=ans+(ans_vw-l2+1)*(ans_uv-l1+1);
            l3++;
        }
    }
    // std::cerr<<u<<' '<<v<<' '<<w<<' '<<ts<<' '<<te<<' '<<delta<<" ans: "<<ans<<'\n';
    return ans;
}

bool baseline::cmp(edge a ,edge b){
    if(a.v!=b.v)return a.v<b.v;
    return a.ts<b.ts;
}

long long baseline::solve(int ts,int te,int delta){
    long long ans=0;
    for(auto R: alfa){
        ans += count(R.u,R.v,R.w,ts+delta,te,delta);
        // std::cerr<<R.u<<' '<<R.v<<' '<<R.w<<' '<<ts+delta<<' '<<te<<' '<<delta<<" ans: "<<ans<<'\n';
    }
    return ans;
}

baseline::baseline(TemporalGraph *Graph){
    n = Graph -> n;
    tmax = Graph -> tmax;
    ed = new std::vector<int> [n];
    s = new std::set<int> [n];
    g = new std::vector<edge>* [tmax+1];
    vis = new int[n];
    std::set<int> num={(int)(0.1*tmax),(int)(0.3*tmax),(int)(0.5*tmax),(int)(0.7*tmax),(int)(0.9*tmax),(int)(0.2*tmax*0.1),(int)(0.4*tmax*0.1),(int)(0.6*tmax*0.1),(int)(0.8*tmax*0.1)};
    // std::cerr<<num.size()<<std::endl;
    // for(int delta=0;delta<=tmax;delta++){
    for(auto delta:num){
        g[delta]=new std::vector<edge> [n];
    }
    double start_time=clock();
    for(int t=0;t<=tmax;t++){
        std::vector<std::pair<int,int>>::iterator it;
        for(it = Graph->temporal_edge[t].begin(); it!=Graph->temporal_edge[t].end();it++){
            int u=(*it).first, v=(*it).second;
            if(u==v)continue;
            s[u].insert(v);
            s[v].insert(u);
            for(auto delta:num){
                g[delta][u].push_back(edge(t,t+delta,v));
                g[delta][v].push_back(edge(t,t+delta,u));
           }
        }
        // if(t%10==0){
        //     std::cout << "Processed time " << t << "/" << tmax << " in " << timeFormatting((clock()-start_time)/CLOCKS_PER_SEC).str() << std::endl;
        // }
    }
    
    for(int u=0;u<n;u++){
        ed[u].assign(s[u].begin(),s[u].end());
    }
    for(int u=0;u<n;u++){
        for(auto v:ed[u]){
            vis[v]=1;
        }
        for(auto v:ed[u]){
            for(auto w:ed[v]){
                if(vis[w]){
                    if(u<v&&v<w){
                    alfa.push_back(relation(u,v,w));
                    // std::cerr<<u<<' '<<v<<' '<<w<<'\n';
                    }
                }
            }
        }
        for(auto v:ed[u])vis[v]=0;
    }
    std::cerr<<alfa.size()<<" triangles in total\n";
        // for(int u=0;u<n;u++){
        //     sort(g2[u].begin(),g2[u].end(),cmp);
        // }
        for(auto delta:num){
            for(int u=0;u<n;u++)sort(g[delta][u].begin(),g[delta][u].end(),cmp);
        }
    std::cout << "Building index total: " << timeFormatting((clock()-start_time)/CLOCKS_PER_SEC).str() << std::endl<<std::endl;
}


void base(baseline *Index, TemporalGraph *Graph, char* query_file, char* output_file){
    int ts, te,delta;
    int query_num = 0;
    std::ifstream fin(query_file);
    std::ofstream fout(output_file);
    
    while(fin >> ts >> te >> delta){
        ++query_num;
    }

    fin=std::ifstream(query_file);

    double start_time=clock();
    int tmp=0;
    while(fin >> ts >> te>>delta){
        //std::cerr<<ts<<' '<<te<<' '<<delta<<"????\n";
        
        // std::cerr<<ts<<' '<<te<<' '<<delta<<"????\n";
        fout<<(long long)(Index->solve(ts , te, delta))<<std::endl;
        tmp++;
        if(tmp%1 == 0)
        putProcess(double(tmp) / query_num, (clock()-start_time)/CLOCKS_PER_SEC);
    }
    std::cout << "Average: " << timeFormatting((clock()-start_time)/CLOCKS_PER_SEC / query_num).str() << std::endl;
}
