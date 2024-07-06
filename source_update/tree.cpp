#include "tree.h"
#include <cmath>

bool treeindex::cmp(mode a,mode b){
    if(a.te==b.te)return a.ts<b.ts;
    return a.te<b.te;
}

void treeindex::tree::update(int rt,int l,int r,int pos1,int pos2,short node_value){
    if(rt==1){
        if(tr[rt].pos.size()==tr[rt].pos.capacity()){
            tr[rt].pos.reserve(tr[rt].pos.size()*1.1);
        }
        tr[rt].pos.emplace_back(pos2);
    }
    if(l==r){
        total+=5;
        //tr[rt].pos.push_back(pos2);
        if(tr[rt].node_value.size()==tr[rt].node_value.capacity()){
            tr[rt].node_value.reserve(tr[rt].node_value.size()*1.1);
        }
        tr[rt].node_value.emplace_back(node_value);
        return ;
    }
    int mid=(l+r)>>1;
    if(pos1<=mid){
        if(tr[rt].node_value.size()==tr[rt].node_value.capacity()){
            tr[rt].node_value.reserve(tr[rt].node_value.size()*1.1);
            tr[rt].from.reserve(tr[rt].from.size()*1.1);
        }
        tr[rt].from.emplace_back(0);
        tr[rt].node_value.emplace_back(node_value);
        long long sz = tr[rt].from.size()-1;
        if((sz+1)%lgt == 0){
            long long sum = 0, from_sum = 0;
            if(sz/lgt>0){
                sum = tr[rt].chunk_sum[sz/lgt-1];
                from_sum = tr[rt].from_table[sz/lgt-1];
            }
            for(long long i=(sz/lgt)*lgt;i<=sz;i++){
                sum=sum+tr[rt].node_value[i];
                from_sum+= (tr[rt].from[i]==1?1:0);
            }
            if(tr[rt].chunk_sum.size()==tr[rt].chunk_sum.capacity()){
                tr[rt].chunk_sum.reserve(tr[rt].chunk_sum.size()*1.1);
                tr[rt].from_table.reserve(tr[rt].from_table.size()*1.1);
            }   
            tr[rt].chunk_sum.emplace_back(sum);
            tr[rt].from_table.emplace_back(from_sum);
        }
        update(rt<<1,l,mid,pos1,pos2,node_value);
    }
    else{
        if(tr[rt].node_value.size()==tr[rt].node_value.capacity()){
            tr[rt].node_value.reserve(tr[rt].node_value.size()*1.1);
            tr[rt].from.reserve(tr[rt].from.size()*1.1);
        }
        tr[rt].from.emplace_back(1);
        tr[rt].node_value.emplace_back(node_value);
        long long sz = tr[rt].from.size()-1;
        if((sz+1)%lgt == 0){
            long long sum = 0, from_sum = 0;
            if(sz/lgt>0){
                sum = tr[rt].chunk_sum[sz/lgt-1];
                from_sum = tr[rt].from_table[sz/lgt-1];
            }
            for(long long i=(sz/lgt)*lgt;i<=sz;i++){
                sum=sum+tr[rt].node_value[i];
                from_sum+= (tr[rt].from[i]==1?1:0);
            }
            if(tr[rt].chunk_sum.size()==tr[rt].chunk_sum.capacity()){
                tr[rt].chunk_sum.reserve(tr[rt].chunk_sum.size()*1.1);
                tr[rt].from_table.reserve(tr[rt].from_table.size()*1.1);
            } 
            tr[rt].chunk_sum.emplace_back(sum);
            tr[rt].from_table.emplace_back(from_sum);
        }
        update(rt<<1|1,mid+1,r,pos1,pos2,node_value);
    }
}

void treeindex::tree::insert(int rt,int l,int r,int pos1,int pos2,short node_value){
    if(l==r){
        total+=5;
        tr[rt].pos.emplace_back(pos2);
        tr[rt].node_value.emplace_back(node_value);
        return ;
    }
    int mid=(l+r)>>1;
    if(pos1<=mid)insert(rt<<1,l,mid,pos1,pos2,node_value);
    else insert(rt<<1|1,mid+1,r,pos1,pos2,node_value);
    return ;
}
long long treeindex::tree::query(int rt,int l,int r,int x,int y,long long p){
    //std::cerr<<rt<<' '<<l<<' '<<r<<' '<<x<<' '<<y<<' '<<p<<' '<<tr[rt].chunk_sum.size()<<'\n';
    if(x<=l && r<=y){
        long long ans=0;
        long long t=p/lgt-1;
        if(l==r){
            for(long long i=0;i<=p;i++)ans+=tr[rt].node_value[i];
            return ans;
        }
        if(t>=0)
        ans=tr[rt].chunk_sum[t];
        //std::cerr<<(t+1)*lgt<<' '<<p<<' '<<tr[rt].node_value.size()<<std::endl;
        for(long long i=(t+1)*lgt;i<=p;i++)ans+=tr[rt].node_value[i];
        //std::cerr<<ans<<'\n';
        return ans;
    }
    int mid=(l+r)>>1;
    long long ans=0;
    long long pl=0,pr=0;
    long long t=p/lgt-1;
    //std::cerr<<t<<' '<<tr[rt].from_table.size()<<"???\n";
    if(t!=-1){
        pr=tr[rt].from_table[t];
        pl=(t+1)*lgt-pr;
    }
    
    
    for(long long i=(t+1)*lgt;i<=p;i++){
        if(tr[rt].from[i]==1)pr++;
        else pl++;
    }
    //std::cerr<<"???\n";
    if(x<=mid && pl>=1)ans+=query(rt<<1,l,mid,x,y,pl-1);
    if(y>mid && pr>=1)ans+=query(rt<<1|1,mid+1,r,x,y,pr-1);
    return ans;
}

void treeindex::tree::build(int rt, int l, int r){// [l,r]: ts 
    //std::cout<<l<<' '<<r<<"\n";
    if(l==r){
        if(tr[rt].pos.empty())return ;
        int len = tr[rt].pos.size();
        tr[rt].pos.resize(len);
        len = tr[rt].node_value.size();
        tr[rt].node_value.resize(len);
        return ;
    }
    int mid=(l+r)>>1;
    build(rt<<1,l,mid);
    build(rt<<1|1,mid+1,r);
    if(tr[rt<<1].pos.empty() && tr[rt<<1|1].pos.empty())return ;
    tr[rt].pos.resize(tr[rt<<1].pos.size()+tr[rt<<1|1].pos.size());
    tr[rt].from.resize(tr[rt].pos.size());
    tr[rt].node_value.resize(tr[rt].pos.size());
    total+=tr[rt].pos.size()*6.125;
    unsigned int lson=0,rson=0,len=0;
    while(lson<tr[rt<<1].pos.size() && rson<tr[rt<<1|1].pos.size()){
        if(tr[rt<<1].pos[lson]<=tr[rt<<1|1].pos[rson]){
            tr[rt].pos[len]=tr[rt<<1].pos[lson];
            tr[rt].from[len]=0;
            tr[rt].node_value[len]=tr[rt<<1].node_value[lson];
            lson++;len++;
        }
        else{
            tr[rt].pos[len]=tr[rt<<1|1].pos[rson];
            tr[rt].from[len]=1;
            tr[rt].node_value[len]=tr[rt<<1|1].node_value[rson];
            rson++;len++;
        }
    }
    while(lson<tr[rt<<1].pos.size()){
        tr[rt].pos[len]=tr[rt<<1].pos[lson];
        tr[rt].from[len]=0;
        tr[rt].node_value[len]=tr[rt<<1].node_value[lson];
        lson++;len++;
    }
    while(rson<tr[rt<<1|1].pos.size()){
        tr[rt].pos[len]=tr[rt<<1|1].pos[rson];
        tr[rt].from[len]=1;
        tr[rt].node_value[len]=tr[rt<<1|1].node_value[rson];
        rson++;len++;
    }
    if(!tr[rt<<1].pos.empty()){
        total-=tr[rt<<1].pos.size()*4ll;
        tr[rt<<1].pos.clear();
        std::vector<int>().swap(tr[rt<<1].pos);
    }
    if(!tr[rt<<1|1].pos.empty()){
        total-=tr[rt<<1|1].pos.size()*4ll;
        tr[rt<<1|1].pos.clear();
        std::vector<int>().swap(tr[rt<<1|1].pos);
    }
    long long sum=0;
    //std::cout<<rt<<' '<<l<<' '<<r<<' '<<tr[rt].from.size()<<' '<<tr[rt].node_value.size()<<'\n';
    len=0;
    for(unsigned int i=0;i<tr[rt].from.size();i++){
        sum=sum+tr[rt].node_value[i];
        len=len+(tr[rt].from[i]==1? 1:0);
        if(i>0 && (i+1)%lgt == 0){
            tr[rt].chunk_sum.push_back(sum);
            tr[rt].from_table.push_back(len);
        }
    }
    total+=tr[rt].chunk_sum.size()*12ll;
}

long long treeindex::tree::find(int pos){
    long long l=0,r=tr[1].pos.size()-1,ans=-1;
    while(l<=r){
        long long mid=(l+r)>>1;
        if(tr[1].pos[mid]<=pos){
            ans=mid;
            l=mid+1;
        }
        else r=mid-1;
    }
    return ans;
}
inline int treeindex::Find(int u,int p){
    
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
long long treeindex::solve(int ts,int te,int delta){
    if(te-ts>=delta){
    long long pos2_te,pos1_delta,pos2_delta;
    pos2_te=tree2.find(te);
    pos1_delta=tree1.find(ts+delta);
    pos2_delta=tree2.find(ts+delta);
    if(pos2_te==-1 || pos1_delta ==-1||pos2_delta==-1)return 0;
    //std::cerr<<pos2_te<<' '<<pos1_delta<<' '<<pos2_delta<<std::endl;
    //std::cerr<<tree2.query(1,0,tmax,0,delta,pos2_te)<<"????\n";
    //std::cerr<<' '<<tree1.query(1,0,tmax,ts,tmax,pos1_delta)<<' '<<tree2.query(1,0,tmax,0,delta,pos2_delta)<<"!!\n";
    long long ans=tree2.query(1,0,tmax,0,delta,pos2_te)+tree1.query(1,0,tmax,ts,tmax,pos1_delta)-tree2.query(1,0,tmax,0,delta,pos2_delta);
    return ans;
    }
    else{
        long long pos1_te;
        pos1_te=tree1.find(te);
        if(pos1_te==-1)return 0;
        //std::cerr<<pos1_te<<'\n';
        return tree1.query(1,0,tmax,ts,tmax,pos1_te);
    }
}

treeindex::treeindex(TemporalGraph* Graph,double length){
    n=Graph->n;
    m=Graph->m;
    tmax=Graph->tmax;
    tim = tmax*length;
    factor=RAND_MAX;
    //mp=new std::unordered_map<int,std::vector<int> >[n];
    ed=new std::vector<int>[n];
    beta = new std::vector<std::vector<int> > [n]();
    double start_time=clock();
    srand(1);
    for(int t=0;t<=tmax;t++){
        std::vector<std::pair<int, int>>::iterator it;
        for (it = Graph->temporal_edge[t].begin(); it != Graph->temporal_edge[t].end(); it++) {
            int u=(*it).first;
            int v=(*it).second;
            if(u==v)continue;
            ed[u].emplace_back(v);
            ed[v].emplace_back(u);
        }
    }
    for(int i=0;i<n;i++){
        std::sort(ed[i].begin(),ed[i].end());
        ed[i].erase(std::unique(ed[i].begin(),ed[i].end()), ed[i].end());
        //std::cerr<<i<<' '<<ed[i].size()<<'\n';
        //std::cerr<<i<<": ";
        beta[i].resize(ed[i].size());
    }
    int id,p,l1,l2;
    for(int t=0;t<=tim;t++){
        std::vector<std::pair<int, int>>::iterator it;
        for (it = Graph->temporal_edge[t].begin(); it != Graph->temporal_edge[t].end(); it++) {
            int u=(*it).first;
            int v=(*it).second;
            if(u==v)continue;
            if(ed[u].size()<ed[v].size())std::swap(u,v);


            for(int i1=0;i1<ed[v].size();++i1){
                p=ed[v][i1];
                if(beta[v][i1].size()==0)continue;
                id=Find(u,p);
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
                        alfa.emplace_back(mode(beta[u][id][i],t,beta[v][i1].size()-l2));
                    }
                    for(int i=0;i<beta[v][i1].size();i++){
                        while(beta[u][id][l1]<=beta[v][i1][i]&&l1<beta[u][id].size()){
                            l1++;
                        }
                        if(beta[u][id].size()==l1)break;
                        //std::cerr<<u<<' '<<v<<' '<<p<<' '<<tmp1.size()-l1<<std::endl;
                        if(rand()<=factor)
                        alfa.emplace_back(mode(beta[v][i1][i],t,beta[u][id].size()-l1));
                    }
                    
                }
            }
            id=Find(u,v);
            beta[u][id].emplace_back(t);
            id=Find(v,u);
            beta[v][id].emplace_back(t);
        }
        //std::cerr<<alfa.size()<<std::endl;
        if((t+1)%10000 == 0)
        putProcess(double(t+1) / (tmax+1), (clock()-start_time)/CLOCKS_PER_SEC);
        Graph->temporal_edge[t].clear();
        std::vector<std::pair<int, int>>().swap(Graph->temporal_edge[t]);
    }
    std::cout<<"Number of static triangles: "<<cnt<<'\n';
    //delete [] mp;
    //delete [] ed;
    //delete [] beta;
    //delete Graph;
    std::cout << "Fetching"<< length*100<<"\%"<<": " << timeFormatting((clock()-start_time)/CLOCKS_PER_SEC).str() << std::endl<<std::endl;
    
    //std::cerr<<cnt<<'\n';
    //delete [] mp;
    //delete [] ed;
    //delete [] beta;
    //delete Graph;
    //std::cout << "Fetching total: " << timeFormatting((clock()-start_time)/CLOCKS_PER_SEC).str() << std::endl<<std::endl;
    int period_time = clock();
    long long szt=log(tmax+1)/log(2)+1;
    //tree.push_back((node)(0,0,0));
    sort(alfa.begin(),alfa.end(),cmp);
    std::vector<mode> beta2;beta2.clear();
    tree1.tr = new node[(tmax+5)<<2];
    tree2.tr = new node[(tmax+5)<<2];
    tree1.lgt = log(tmax)*4;
    tree2.lgt=tree1.lgt;
    //std::cerr<<tree1.lgt<<std::endl;
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
            beta2.emplace_back(current);
            current=alfa[i];
        }
    }
    beta2.emplace_back(current);
    std::swap(alfa,beta2);
    beta2.clear();
    std::vector<mode>().swap(beta2);
    //std::cerr<<alfa.size()<<std::endl;
    long long sum =0;
    for(int i=0;i<alfa.size();i++){
        tree1.insert(1,0,tmax,alfa[i].ts,alfa[i].te,alfa[i].val);
        tree2.insert(1,0,tmax,alfa[i].te-alfa[i].ts,alfa[i].te,alfa[i].val);
        sum=sum+alfa[i].val;
        //std::cerr<<alfa[i].ts<<' '<<alfa[i].te<<' '<<alfa[i].val<<'\n';
    }
    std::cout<<"Number of C-points: "<<alfa.size()<<std::endl;
    std::cerr<<sum;
    alfa.clear();
    std::vector<mode>().swap(alfa);
    //std::cerr<<"Let's go!\n";
    tree1.build(1,0,tmax);
    //std::cerr<<"Tree1 ok.\n";
    tree2.build(1,0,tmax);
    //std::cerr<<tree1.total<<' '<<tree2.total<<'\n';
    std::cout << "Indexing"<< length*100<<"\%"<<": " << timeFormatting((clock()-start_time)/CLOCKS_PER_SEC).str() << std::endl<<std::endl;
    //std::cout << "Indexing size: " <<  tree1.total+tree2.total<<"bytes"<< std::endl<<std::endl;
}

void treeindex::update(TemporalGraph *Graph, double pre){
    double start_time=clock();
    int tpre= pre*tmax+1;
    if(tpre>tmax)return ;
    int edgenum = 0;
    int id,p,l1,l2;
    long long cnt=0;
    for(int t=tpre;t<=tmax;t++){
        std::vector<std::pair<int, int>>::iterator it;
        for (it = Graph->temporal_edge[t].begin(); it != Graph->temporal_edge[t].end(); it++) {
            edgenum++;
            int u=(*it).first;
            int v=(*it).second;
            if(u==v)continue;
            if(ed[u].size()<ed[v].size())std::swap(u,v);
            for(int i1=0;i1<ed[v].size();++i1){
                p=ed[v][i1];
                if(beta[v][i1].size()==0)continue;
                id=Find(u,p);
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
                        alfa2.push_back(mode(beta[u][id][i],t,beta[v][i1].size()-l2));
                    }
                    for(int i=0;i<beta[v][i1].size();i++){
                        while(beta[u][id][l1]<=beta[v][i1][i]&&l1<beta[u][id].size()){
                            l1++;
                        }
                        if(beta[u][id].size()==l1)break;
                        if(rand()<=factor)
                        alfa2.push_back(mode(beta[v][i1][i],t,beta[u][id].size()-l1));
                    }
                    
                }
            }
            id=Find(u,v);
            beta[u][id].push_back(t);
            id=Find(v,u);
            beta[v][id].push_back(t);
        }
        if((t+1)%10000 == 0)
        putProcess(double(t+1) / (tmax+1), (clock()-start_time)/CLOCKS_PER_SEC);
        Graph->temporal_edge[t].clear();
        std::vector<std::pair<int, int>>().swap(Graph->temporal_edge[t]);
    }
    //std::cout<<"Number of updated static triangles: "<<cnt<<'\n';
    sort(alfa2.begin(),alfa2.end(),cmp);
    std::vector<mode> beta2;beta2.clear();
    
    mode current;
    current.ts=alfa2[0].ts;
    current.te=alfa2[0].te;
    current.val=alfa2[0].val;
    for(long long i=1;i<alfa2.size();i++){
        if(alfa2[i].ts==alfa2[i-1].ts && alfa2[i].te==alfa2[i-1].te){
            current.val+=alfa2[i].val;
        }
        else{
            if(current.val!=0)
            beta2.emplace_back(current);
            current=alfa2[i];
        }
    }
    beta2.emplace_back(current);
    std::swap(alfa2,beta2);
    beta2.clear();
    std::vector<mode>().swap(beta2);
    std::cout << "Updated edge number: "<<edgenum<<std::endl;
    std::cout<<"Number of C-points updated: "<<alfa2.size()<<std::endl;
    double start2=clock();
    for(long long i=0;i<alfa2.size();i++){
        tree1.update(1,0,tmax,alfa2[i].ts,alfa2[i].te,alfa2[i].val);
        tree2.update(1,0,tmax,alfa2[i].te-alfa2[i].ts,alfa2[i].te,alfa2[i].val);
        if((i+1)%100000==0){
             putProcess(double(i+1) / (alfa2.size()+1), (clock()-start2)/CLOCKS_PER_SEC);
        }
    }
    std::cout << "Update time costs: " << timeFormatting((clock()-start_time)/CLOCKS_PER_SEC).str()<<std::endl;
    
}

void tree(treeindex *Index, TemporalGraph *Graph, char* query_file, char* output_file){
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
        double alfa=1.0*RAND_MAX/Index->factor;
        //std::cerr<<ts<<' '<<te<<' '<<delta<<"????\n";
        fout<<(long long)(Index->solve(ts , te, delta)*alfa)<<std::endl;
        tmp++;
        if(tmp%100 == 0)
        putProcess(double(tmp) / query_num, (clock()-start_time)/CLOCKS_PER_SEC);
    }
    std::cout << "Average: " << timeFormatting((clock()-start_time)/CLOCKS_PER_SEC / query_num).str() << std::endl;
}
