#include "tree.h"
#include <cmath>

bool treeindex::cmp(mode a,mode b){
    if(a.te==b.te)return a.ts<b.ts;
    return a.te<b.te;
}

void treeindex::directmodify(int direction, long long fa,int pos,int val,int l,int r){
    //std::cerr<<pos<<' '<<l<<' '<<r<<std::endl;
    long long cur = 0;
    if(direction ==0){
        long long ls=tree[fa].ls2;
        ls<<=32;ls+=tree[fa].ls1;
        if(ls== 0){
            cur=++cnt;
            tree.push_back(node(0,0,0,0,0));
            tree[cur].ls1=0;
            tree[cur].rs1=0;
            tree[cur].ls2=0;
            tree[cur].rs2=0;
            tree[cur].sum=0;
            tree[fa].ls1=cur&((1ll<<32)-1);
            tree[fa].ls2=int(cur>>32);
        }
        else{
            cur=ls;
        }
    }
    else{
        long long rs=(tree[fa].rs2);
        rs<<=32; rs+=tree[fa].rs1;
        if(rs==0){
            cur=++cnt;
            tree.push_back(node(0,0,0,0,0));
            tree[cur].ls1=0;
            tree[cur].rs1=0;
            tree[cur].ls2=0;
            tree[cur].rs2=0;
            tree[cur].sum=0;
            tree[fa].rs1=cur&((1ll<<32)-1);
            tree[fa].rs2=int(cur>>32);
        }
        else{
            cur=rs;
        }
    }
    if(l==r){
        tree[cur].sum+=val;
        return ;
    }
    int mid=(l+r)>>1;
    if(pos<=mid)directmodify(0,cur,pos,val,l,mid);
    else directmodify(1,cur,pos,val,mid+1,r);
    long long ls=int(tree[cur].ls2);
    ls<<=32;ls+=tree[cur].ls1;
    long long rs=int(tree[cur].rs2);
    rs<<=32; rs+=tree[cur].rs1;
    tree[cur].sum=tree[ls].sum+tree[rs].sum;
    //std::cerr<<cur<<' '<<l<<' '<<r<<' '<<tree[cur].sum<<std::endl;
}


void treeindex::modify(long long pre,long long &cur,int l,int r){
    if(!cur){
        cur=++cnt;
        tree.push_back(node(0,0,0,0,0));
        tree[cur].ls1=tree[pre].ls1;
        tree[cur].rs1=tree[pre].rs1;
        tree[cur].ls2=tree[pre].ls2;
        tree[cur].rs2=tree[pre].rs2;
        tree[cur].sum=tree[pre].sum;
        return ;
    }
    if(!pre){
        return ;
    }
    if(l==r){
        tree[cur].sum+=tree[pre].sum;
        return ;
    }
    int mid=(l+r)>>1;
    long long rs=int(tree[cur].rs2);
    rs<<=32; rs+=tree[cur].rs1;
    long long ls=int(tree[cur].ls2);
    ls<<=32;ls+=tree[cur].ls1;
    long long prer=int(tree[pre].rs2);
    prer<<=32;prer+=tree[pre].rs1;
    
    long long prel=int(tree[pre].ls2);
    prel<<=32;prel+=tree[pre].ls1;
    if(ls!=0)
    modify(prel,ls,l,mid);
    else{
        tree[cur].ls1=tree[pre].ls1;
        tree[cur].ls2=tree[pre].ls2;
    }
    if(rs!=0){
        modify(prer,rs,mid+1,r);
    }
    else{
        tree[cur].rs1=tree[pre].rs1;
        tree[cur].rs2=tree[pre].rs2;
    }
    rs=int(tree[cur].rs2);
    rs<<=32; rs+=tree[cur].rs1;
    ls=int(tree[cur].ls2);
    ls<<=32;ls+=tree[cur].ls1;
    tree[cur].sum=tree[ls].sum+tree[rs].sum;
}

treeindex::treeindex(TemporalGraph* Graph){
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
    int period_time = clock();
    rt = new long long[tmax+1];
    long long szt=log(tmax+1)/log(2)+1;
    std::cerr<<szt<<'\n';
    for(int i=0;i<=tmax;i++)rt[i]=0;
    //tree.push_back((node)(0,0,0));
    sort(alfa.begin(),alfa.end(),cmp);
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
    std::vector<mode>().swap(beta);
    std::cerr<<alfa.size()<<std::endl;
    //std::cerr<<alfa[0].ts<<' '<<alfa[0].te<<std::endl;
    delete [] mp;
    delete [] ed;
    delete Graph;
    //tree = new node[std::max((long long)tmax,(long long)alfa.size())*szt];
    tree.push_back(node(0,0,0,0,0));
    for(int i=0;i<alfa.size();i++){
       // std::cerr<<alfa[i].ts<<' '<<alfa[i].te<<' '<<alfa[i].val<<std::endl;
        if(rt[alfa[i].te]==0){
            rt[alfa[i].te]=++cnt;
            tree.push_back((node)(0,0,0,0,0));
        }
        if(alfa[i].ts<=tmax/2)
        directmodify(0,rt[alfa[i].te],alfa[i].ts,alfa[i].val,0,tmax/2);
        else
        directmodify(1,rt[alfa[i].te],alfa[i].ts,alfa[i].val,tmax/2+1,tmax);
        long long ls=tree[rt[alfa[i].te]].ls2;
        ls<<=32;ls+=tree[rt[alfa[i].te]].ls1;
        long long rs=tree[rt[alfa[i].te]].rs2;
        rs<<=32;rs+=tree[rt[alfa[i].te]].rs1;
        tree[rt[alfa[i].te]].sum=tree[ls].sum+tree[rs].sum;
        if((i+1)%1000== 0)
        {
            putProcess(double(i+1) / (alfa.size()+1), (clock()-period_time)/CLOCKS_PER_SEC);
            //std::cerr<<i<<' '<<cnt<<' '<<tree.size()<<std::endl;
        }
    }
   // std::cerr<<tree[1].sum<<std::endl;
    //std::cerr<<cnt<<std::endl;
    //std::cerr<<"?????";
    for(int i=1;i<=tmax;i++){
        //std::cerr<<i<<' '<<cnt<<' '<<rt[i]<<' '<<tree[rt[i]].sum<<std::endl;
        modify(rt[i-1],rt[i],0,tmax);
        //std::cerr<<i<<' '<<cnt<<' '<<rt[i]<<' '<<tree[rt[i]].sum<<std::endl;
    }
    //std::cerr<<cnt<<'\n';
    std::cout << "Indexing total: " << timeFormatting((clock()-start_time)/CLOCKS_PER_SEC).str()<<std::endl;
    std::cout << "Indexing size: " <<  14ll*cnt<<"bytes"<< std::endl<<std::endl;
}


int treeindex::query(long long cur,int l,int r,int x,int y){
    //std::cerr<<cur<<' '<<l<<' '<<r<<' '<<x<<' '<<y<<' '<<tree[cur].sum<<std::endl;
    if(!cur)return 0;
    if(x<=l&&r<=y){
        return tree[cur].sum;
    }
    int mid=(l+r)>>1,ans=0;
    long long rs=int(tree[cur].rs2);
    rs<<=32; rs+=tree[cur].rs1;
    long long ls=int(tree[cur].ls2);
    ls<<=32;ls+=tree[cur].ls1;
    if(x<=mid)ans+=query(ls,l,mid,x,y);
    if(y>mid)ans+=query(rs,mid+1,r,x,y);
    return ans;
}

int treeindex::solve(int ts,int te){
    return query(rt[te],0,tmax,ts,tmax);
}

treeindex::~treeindex(){
    tree.clear();
    std::vector<node>().swap(tree);
    //delete [] mp;
    //delete [] ed;
}

void tree(treeindex *Index, TemporalGraph *Graph, char* query_file, char* output_file){
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
        //std::cerr<<ts<<' '<<te<<"????\n";
        fout<<Index->solve(ts , te)<<std::endl;
        tmp++;
        if(tmp%100 == 0)
        putProcess(double(++i) / query_num, (clock()-start_time)/CLOCKS_PER_SEC);
    }
    std::cout << "Average: " << timeFormatting((clock()-start_time)/CLOCKS_PER_SEC / query_num).str() << std::endl;
}