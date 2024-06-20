#include"kdtree.h"

bool kdindex::cmp(mode a,mode b){
    if(a.te!=b.te){return a.te<b.te;}
    if(a.ts!=b.ts){return a.ts<b.ts;}
    return a.delta<b.delta;
}



void kdindex::pushup(int rt){
    for(int i=0;i<3;i++){
        tree[rt].mxpos[i]=std::max(std::max(tree[tree[rt].ls].mxpos[i],tree[tree[rt].rs].mxpos[i]),tree[rt].mxpos[i]);
        tree[rt].mnpos[i]=std::min(std::min(tree[tree[rt].ls].mnpos[i],tree[tree[rt].rs].mnpos[i]),tree[rt].mnpos[i]);
    }
    tree[rt].tot+=tree[tree[rt].ls].tot+tree[tree[rt].rs].tot;
}

void kdindex::build(int &rt,int l,int r,int dep){
    if(l>r){rt = 0;return ;}
    cnt++;
    //std::cerr<<cnt<<' '<<l<<' '<<r<<' '<<' '<<num<<'\n';
    rt=cnt;
    static int opt=dep%3;
    int mid=(l+r)>>1;
    std::nth_element(a+l,a+mid,a+r+1,[&](mode a,mode b){
        if(opt==0)
            return a.ts<b.ts;
        else if(opt==1)
            return a.te<b.te;
        else
            return a.delta<b.delta;
    });
    tree[rt].val=tree[rt].tot=a[mid].val;
    tree[rt].pos[0]=tree[rt].mxpos[0]=tree[rt].mnpos[0]=a[mid].ts;
    tree[rt].pos[1]=tree[rt].mxpos[1]=tree[rt].mnpos[1]=a[mid].te;
    tree[rt].pos[2]=tree[rt].mxpos[2]=tree[rt].mnpos[2]=a[mid].delta;
    build(tree[rt].ls,l,mid-1,dep+1);build(tree[rt].rs,mid+1,r,dep+1);
    pushup(rt);
    //std::cerr<<rt<<' '<<tree[rt].tot<<'\n'<<tree[rt].mnpos[0]<<' '<<tree[rt].mxpos[0]<<'\n'<<tree[rt].mnpos[1]<<' '<<tree[rt].mxpos[1]<<'\n'<<tree[rt].mnpos[2]<<' '<<tree[rt].mxpos[2]<<"\n\n";
}
long long kdindex::solve(int ts,int te,int delta){
    return query(1,ts,tmax,0,te,0,delta);
}
long long kdindex::query(int rt,int ts1,int ts2,int te1,int te2,int delta1,int delta2){
    if(!rt)return 0;
    if(ts1<=tree[rt].mnpos[0] && tree[rt].mxpos[0]<=ts2){
        if(te1<=tree[rt].mnpos[1] && tree[rt].mxpos[1]<=te2){
            if(delta1<=tree[rt].mnpos[2] && tree[rt].mxpos[2] <=delta2){
                return tree[rt].tot;
            }
        }
    }
    int lson=tree[rt].ls;
    int rson=tree[rt].rs;
    int lflag=1,rflag=1;
    if(tree[lson].mnpos[0]>ts2||tree[lson].mxpos[0]<ts1){
        lflag=0;
    }
    else if(tree[lson].mnpos[1]>te2||tree[lson].mxpos[1]<te1) lflag=0;
    else if(tree[lson].mnpos[2]>delta2||tree[lson].mxpos[2]<delta1)lflag=0;

    if(tree[rson].mnpos[0]>ts2||tree[rson].mxpos[0]<ts1){
        rflag=0;
    }
    else if(tree[rson].mnpos[1]>te2||tree[rson].mxpos[1]<te1)rflag=0;
    else if(tree[rson].mnpos[2]>delta2||tree[rson].mxpos[2]<delta1)rflag=0;
    long long ans=0;
    if(lflag){
        ans+=query(lson,ts1,ts2,te1,te2,delta1,delta2);
    }
    if(rflag){
        ans+=query(rson,ts1,ts2,te1,te2,delta1,delta2);
    }
    if(ts1<= tree[rt].pos[0] && tree[rt].pos[0]<=ts2 && te1<= tree[rt].pos[1] && tree[rt].pos[1]<=te2 && delta1<= tree[rt].pos[2] && tree[rt].pos[2]<=delta2)ans+=tree[rt].val;
    return ans;
}

inline int kdindex::find(int u,int p){
    
    int l=0,r=ed[u].size()-1,ans=-1;
    if(r-l+1<=40){
        /*for(int i=0;i<=r;i+=8){
            if(ed[u][i]>p)return -1;
            if(ed[u][i]==p)return i;
            if(i+1<=r && ed[u][i+1]==p)return i+1;
            if(i+2<=r && ed[u][i+2]==p)return i+2;
            if(i+3<=r && ed[u][i+3]==p)return i+3;
            if(i+4<=r && ed[u][i+4]==p)return i+4;
            if(i+5<=r && ed[u][i+5]==p)return i+5;
            if(i+6<=r && ed[u][i+6]==p)return i+6;
            if(i+7<=r && ed[u][i+7]==p)return i+7;
        }*/
        for(int i=0;i<=r;i+=4){
            if(ed[u][i]>=p){
            if(ed[u][i]>p)return -1;
            if(ed[u][i]==p)return i;}
            if(i+1<=r&&ed[u][i+1]>=p){
            if(ed[u][i+1]>p)return -1;
            if(ed[u][i+1]==p)return i+1;}
            if(i+2<=r&&ed[u][i+2]>=p){
            if(ed[u][i+2]>p)return -1;
            if(ed[u][i+2]==p)return i+2;}
            if(i+3<=r&&ed[u][i+3]>=p){
            if(ed[u][i+3]>p)return -1;
            if(ed[u][i+3]==p)return i+3;}
        }
        return -1;
    }
    /*else{
        std::unordered_map<int,int>::iterator iter;
        iter=pt[u].find(p);
        if(iter!=pt[u].end())
        return (*iter).second;
        else
        return -1;
    }*/
    while(l<=r){
        int mid=(l+r)>>1;
        if(ed[u][mid]<=p){
            ans=mid;
            l=mid+1;
        }
        else{
            r=mid-1;
        }
    }
    if(ed[u][ans]==p)
    return ans;
    else
    return -1;
}

kdindex::kdindex(TemporalGraph *Graph){
    n=Graph->n;
    m=Graph->m;
    tmax=Graph->tmax*0.2;
    
    srand(1);
    factor=RAND_MAX;
    mp=new std::unordered_map<int,std::vector<int>>[n];
    ed=new std::vector<int>[n];
    beta = new std::vector<std::vector<int> > [n]();
    deltav.clear();
    double start_time=clock();
    for(int t=0;t<=tmax;t++){
        std::vector<std::pair<int, int>>::iterator it;
        for (it = Graph->temporal_edge[t].begin(); it != Graph->temporal_edge[t].end(); it++) {
            int u=(*it).first;
            int v=(*it).second;
            if(u==v)continue;
            ed[u].push_back(v);
            ed[v].push_back(u);
        }
    }
    for(int i=0;i<n;i++){
        //std::cerr<<"???\n";
        std::sort(ed[i].begin(),ed[i].end());
        ed[i].erase(std::unique(ed[i].begin(),ed[i].end()), ed[i].end());
        //std::cerr<<i<<' '<<ed[i].size()<<'\n';
        //std::cerr<<i<<": ";
        beta[i].resize(ed[i].size());
        /*if(ed[i].size()>150){
            for(int j=0;j<ed[i].size();j++){
                pt[i][ed[i][j]]=j;
            }
        }*/
        //std::cerr<<'\n';
    }
    int id,p,l1,l2;
    long long cnt=0;
    for(int t=0;t<=tmax;t++){
        std::vector<std::pair<int, int>>::iterator it;
        for (it = Graph->temporal_edge[t].begin(); it != Graph->temporal_edge[t].end(); it++) {
            int u=(*it).first;
            int v=(*it).second;
            if(u==v)continue;
            if(ed[u].size()<ed[v].size())std::swap(u,v);


            for(int i1=0;i1<ed[v].size();++i1){
                p=ed[v][i1];
                if(beta[v][i1].size()==0)continue;
                id=find(u,p);
                if(id!=-1){
                    if(beta[u][id].size()==0)continue;
                    cnt++;
                    
                        l1=0,l2=0;
                    for(int i=0;i<beta[u][id].size();i++){
                        while(beta[v][i1][l2]<beta[u][id][i]&&l2<beta[v][i1].size()){
                            l2++;
                        }
                        if(beta[v][i1].size()==l2)break;
                        //std::cerr<<u<<' '<<v<<' '<<p<<' '<<tmp2.size()-l2<<std::endl;
                        if(rand()<=factor)
                        alfa.push_back(mode(beta[u][id][i],t,t-beta[u][id][i],beta[v][i1].size()-l2));
                    }
                    for(int i=0;i<beta[v][i1].size();i++){
                        while(beta[u][id][l1]<=beta[v][i1][i]&&l1<beta[u][id].size()){
                            l1++;
                        }
                        if(beta[u][id].size()==l1)break;
                        //std::cerr<<u<<' '<<v<<' '<<p<<' '<<tmp1.size()-l1<<std::endl;
                        if(rand()<=factor)
                        alfa.push_back(mode(beta[v][i1][i],t,t-beta[v][i1][i],beta[u][id].size()-l1));
                    }
                    
                }
            }
            id=find(u,v);
            beta[u][id].push_back(t);
            id=find(v,u);
            beta[v][id].push_back(t);
            /*for(auto p:ed[v]){
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
                        alfa.push_back(mode(tmp1[i],t,tmp2.size()-l2));
                    }
                    for(int i=0;i<tmp2.size();i++){
                        while(tmp1[l1]<=tmp2[i]&&l1<tmp1.size()){
                            l1++;
                        }
                        if(tmp1.size()==l1)break;
                        //std::cerr<<u<<' '<<v<<' '<<p<<' '<<tmp1.size()-l1<<std::endl;
                        if(rand()<factor)
                        alfa.push_back(mode(tmp2[i],t,tmp1.size()-l1));
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
            }*/
        }
        //std::cerr<<alfa.size()<<std::endl;
        if((t+1)%10000 == 0)
        putProcess(double(t+1) / (tmax+1), (clock()-start_time)/CLOCKS_PER_SEC);
        Graph->temporal_edge[t].clear();
        std::vector<std::pair<int, int>>().swap(Graph->temporal_edge[t]);
    }
    std::cout<<"The number of static triangles: "<<cnt<<'\n';
    std::cerr<<alfa.size()<<std::endl;
    std::sort(alfa.begin(),alfa.end(),cmp);
    //std::cerr<<alfa[0].ts<<' '<<alfa[0].te<<' '<<alfa[10].ts<<' '<<alfa[10].te<<'\n';
    std::vector<mode> beta2;beta2.clear();
    mode current;
    current.ts=alfa[0].ts;
    current.te=alfa[0].te;
    current.delta=alfa[0].delta;
    current.val=alfa[0].val;
    //std::cerr<<"???\n";
    for(int i=1;i<alfa.size();i++){
        if(alfa[i].ts==alfa[i-1].ts && alfa[i].te==alfa[i-1].te){
            current.val+=alfa[i].val;
        }
        else{
            if(current.val!=0)
            beta2.push_back(current);
            current=alfa[i];
        }
    }
    beta2.push_back(current);
    std::cerr<<beta2.size()<<'\n';
    //std::cerr<<"??\n";
    //std::swap(alfa,beta);
    num=beta2.size();
    // std::cerr<<num<<'\n';
    a = new mode[num];
    for(int i=0;i<num;i++){
        a[i]=beta2[i];
    }
    beta2.clear();
    std::vector<mode>().swap(beta2);
    alfa.clear();
    std::vector<mode>().swap(alfa);
    std::cout<<"Number of C-points: "<<num<<'\n';
    tree =new node[num+5];
    tree[0].tot=0;
    for(int i=0;i<3;i++)
    tree[0].mnpos[i]=1e9;
    for(int i=0;i<3;i++)
    tree[0].mxpos[i]=-1e9;
    for(int i=0;i<3;i++)
    tree[0].pos[i]=-1;
    int root=0;
    //std::cerr<<"???\n";
    build(root,0,num-1,0);
    std::cout << "Indexing total: " << timeFormatting((clock()-start_time)/CLOCKS_PER_SEC).str()<<std::endl;
    //std::cout << "Indexing size: " <<  56ll*cnt<<"bytes"<< std::endl<<std::endl;
}

void kd(kdindex *Index,TemporalGraph *Graph, char* query_file, char* output_file){
    int ts, te,delta;
    int query_num = 0;
    std::ifstream fin(query_file);
    std::ofstream fout;
    fout.open(output_file);
    while(fin >> ts >> te >>delta){
        ++query_num;
    }

    fin=std::ifstream(query_file);

    int i=0;
    double start_time=clock();
    int tmp=0;
    while(fin >> ts >> te>>delta){
        //std::cerr<<ts<<' '<<te<<"????\n";
        double alfa=1.0*RAND_MAX/Index->factor;
        //std::cerr<<ts<<' '<<te<<' '<<delta<<"????\n";
        fout<<(long long)(Index->solve(ts , te, delta)*alfa)<<std::endl;
        //fout<<Index->solve(ts , te, delta)*RAND_MAX/Index->factor<<std::endl;
        tmp++;
        if(tmp%100 == 0)
        putProcess(double(++i) / query_num *100, (clock()-start_time)/CLOCKS_PER_SEC);
    }
    std::cout << "Average: " << timeFormatting((clock()-start_time)/CLOCKS_PER_SEC / query_num).str() << std::endl;
}
