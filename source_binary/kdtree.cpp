#include"kdtree.h"

bool kdindex::cmp(mode a,mode b){
    if(a.te!=b.te){return a.te<b.te;}
    else if(a.ts!=b.ts){return a.ts<b.ts;}
    else return a.delta<b.delta;
}



void kdindex::pushup(long long rt){
    for(int i=0;i<3;i++){
        tree[rt].mxpos[i]=std::max(std::max(tree[tree[rt].ls].mxpos[i],tree[tree[rt].rs].mxpos[i]),tree[rt].mxpos[i]);
        tree[rt].mnpos[i]=std::min(std::min(tree[tree[rt].ls].mnpos[i],tree[tree[rt].rs].mnpos[i]),tree[rt].mnpos[i]);
    }
    tree[rt].tot+=tree[tree[rt].ls].tot+tree[tree[rt].rs].tot;
}

void kdindex::build(long long &rt,long long l,long long r,int dep){
    if(l>r){rt = 0;return ;}
    cnt++;
    //std::cerr<<cnt<<' '<<l<<' '<<r<<' '<<' '<<num<<'\n';
    rt=cnt;
    static int opt=dep%3;
    long long mid=(l+r)>>1;
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
long long kdindex::query(long long rt,int ts1,int ts2,int te1,int te2,int delta1,int delta2){
    if(!rt)return 0;
    if(ts1<=tree[rt].mnpos[0] && tree[rt].mxpos[0]<=ts2){
        if(te1<=tree[rt].mnpos[1] && tree[rt].mxpos[1]<=te2){
            if(delta1<=tree[rt].mnpos[2] && tree[rt].mxpos[2] <=delta2){
                return tree[rt].tot;
            }
        }
    }
    long long lson=tree[rt].ls;
    long long rson=tree[rt].rs;
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
    
    int l=0,r=ed2[u].size()-1,ans=-1;
    if(r-l+1<=50){
        for(int i=0;i<=r;i+=4){
            if(ed2[u][i]>=p){
            if(ed2[u][i]>p)return -1;
            if(ed2[u][i]==p)return i;}
            if(i+1<=r&&ed2[u][i+1]>=p){
            if(ed2[u][i+1]>p)return -1;
            if(ed2[u][i+1]==p)return i+1;}
            if(i+2<=r&&ed2[u][i+2]>=p){
            if(ed2[u][i+2]>p)return -1;
            if(ed2[u][i+2]==p)return i+2;}
            if(i+3<=r&&ed2[u][i+3]>=p){
            if(ed2[u][i+3]>p)return -1;
            if(ed2[u][i+3]==p)return i+3;}
        }
        return -1;
    }
    while(l<=r){
        int mid=(l+r)>>1;
        if(ed2[u][mid]<=p){
            ans=mid;
            l=mid+1;
        }
        else{
            r=mid-1;
        }
    }
    if(ed2[u][ans]==p)
    return ans;
    else
    return -1;
}


#define s1 alfa[u][t1]
#define s2 alfa[v][t2]
#define s3 alfa[u][t3]
void kdindex::deal(int u,int v,int w){
    int t1=find(u,v),t2=find(v,w),t3=find(u,w);
    int l1=0,l2=0,l3=0,lst=-1;
    std::vector<mode> tmp;
    tmp.clear();
    while(1){
        //std::cerr<<l1<<' '<<s1.size()<<' '<<l2<<' '<<s2.size()<<' '<<l3<<' '<<s3.size()<<'\n';
        if(l1==s1.size() &&l2==s2.size() &&l3==s3.size()){
            break;
        }
        int flag=1;
        if(l1==s1.size()){
            if(l2==s2.size()){
                flag=3;
            }
            else{
                if(l3==s3.size())flag=2;
                else{
                    if(s2[l2]<=s3[l3])flag=2;
                    else flag=3;
                }
            }
        }
        else{
            if(l2==s2.size()){
                if(l3==s3.size())flag=1;
                else{
                    if(s1[l1]<=s3[l3])flag=1;
                    else flag=3;
                }
            }
            else{
                if(l3==s3.size()){
                    if(s1[l1]<=s2[l2])flag=1;
                    else flag=2;
                }
                else{
                    if(s1[l1]<=s2[l2]&&s1[l1]<=s3[l3])flag=1;
                    else if(s2[l2]<=s3[l3])flag=2;
                    else flag=3;
                }
            }
        }
        if(flag==1){//s1
        //std::cerr<<"?\n";
            if(l2>0&&l3>0){
                int mn=std::min(s2[l2-1],s3[l3-1]);
                if(mn>lst ){
                    if(tmp.empty() || tmp[tmp.size()-1].te<s1[l1])
                    tmp.push_back(mode(mn,s1[l1],s1[l1]-mn,1));
                    else
                    tmp[tmp.size()-1]=mode(mn,s2[l1],s2[l1]-mn,1);
                    lst=mn;
                }
                
            }
            l1++;
        }
        else if(flag==2){//s2
        //std::cerr<<"??\n";
            if(l1>0&&l3>0){
                int mn=std::min(s1[l1-1],s3[l3-1]);
                if(mn>lst ){
                    if(tmp.empty() ||tmp[tmp.size()-1].te<s2[l2])
                    tmp.push_back(mode(mn,s2[l2],s2[l2]-mn,1));
                    else
                    tmp[tmp.size()-1]=mode(mn,s2[l2],s2[l2]-mn,1);
                    lst=mn;
                }
                
            }
            l2++;
        }
        else{//s3
        //std::cerr<<"???\n";
        //std::cerr<<l1<<' '<<l2<<' '<<l3<<'\n';
            if(l1>0&&l2>0){
                
                int mn=std::min(s2[l2-1],s1[l1-1]);
                if(mn>lst ){
                    if(tmp.empty() ||tmp[tmp.size()-1].te<s3[l3])
                    tmp.push_back(mode(mn,s3[l3],s3[l3]-mn,1));
                    else
                    tmp[tmp.size()-1]=mode(mn,s3[l3],s3[l3]-mn,1);
                    lst=mn;
                }
                
            }
            l3++;
        }
    }
    if(tmp.empty())return ;
    
    //std::cerr<<tmp.size()<<'\n';
    /*std::vector<mode> syr;
    syr.clear();
    for(int i=0;i<tmp.size();i++){
        int flag=1;
        for(int j=0;j<tmp.size();j++){
            if(i==j)continue;
            if(tmp[j].ts>=tmp[i].ts && tmp[j].te<=tmp[i].te){
                flag=0;break;
            }
        }
        if(flag)syr.push_back(tmp[i]);
    }
    tmp=syr;*/
    sort(tmp.begin(),tmp.end(),cmp);
    std::vector<point> deltav;
    deltav.clear();
    int cnt=0;
    int dura=5;
    for(auto p:tmp){
        int t=p.te,tmn=p.ts;
        int lst=-1;
        while(1){
            if(deltav.empty())break;
                                //std::cout<<x<<' '<<y<<' '<<z<<' '<<tmn<<' '<<t<<'\n';
                                //std::cout<<toper<<' '<<toper->ts<<' '<<toper->delta<<' '<<toper->nex<<'\n';
                                //point realtop=*toper;
            int len=deltav.size()-1;
            point realtop = deltav[len];
            if(realtop.delta>t-tmn){
                if(rand()<=factor){
                    /*if(u==0&&v==32&&w==36){
                        std::cout<<realtop.ts<<' '<<t<<' '<<realtop.delta<<"!\n";
                    }*/
                    beta.push_back(mode(realtop.ts,t,realtop.delta,-1));
                    if(realtop.delta<=dura)
                    cnt--;
                }
                    if(lst!=-1){
                        if(rand()<=factor){
                            /*if(u==0&&v==32&&w==36){
                                std::cout<<realtop.ts<<' '<<t<<' '<<lst<<"!\n";
                            }*/
                            beta.push_back(mode(realtop.ts,t,lst,1));
                            if(lst<=dura)
                            cnt++;
                        }
                    }
                    lst=realtop.delta;
                    if(len>=0){
                        deltav.pop_back();
                        len--;
                        if(len>=0)
                        realtop=deltav[len];
                        else
                        break;
                    }
                    else{
                        break;
                    }
            }
            else{
                if(rand()<=factor){
                    /*if(u==0&&v==32&&w==36){
                        std::cout<<realtop.ts<<' '<<t<<' '<<t-tmn<<"!\n";
                    }*/
                    beta.push_back(mode(realtop.ts,t,t-tmn,-1));
                    if(t-tmn<=dura)
                    cnt--;
                }
                if(lst!=-1){
                    if(rand()<=factor){
                        /*if(u==0&&v==32&&w==36){
                            std::cout<<realtop.ts<<' '<<t<<' '<<lst<<"!\n";
                        }*/
                        beta.push_back(mode(realtop.ts,t,lst,1));
                        if(lst<=dura)
                        cnt++;
                    }
                }
                break;
            }
        }
                            //std::cout<<toper<<"?\n";
        point tmper=point(tmn,t-tmn);
        deltav.push_back(tmper);
        if(rand()<=factor){
            beta.push_back(mode(tmn,t,t-tmn,1));
            if(t-tmn<=dura)
            cnt++;
        }
                        
    }

    tmp.clear();
    std::vector<mode>().swap(tmp);
    deltav.clear();
    
    std::vector<point>().swap(deltav);
    /*if(cnt>1){
        std::cout<<u<<' '<<v<<' '<<w<<' '<<cnt<<'\n';
        for(auto p:tmp){
            std::cout<<p.ts<<' '<<p.te<<' '<<p.delta<<' '<<p.val<<'\n';
        }
        for(auto t:s1){
            std::cout<<t<<' ';
        }
        std::cout<<'\n';
        for(auto t:s2){
            std::cout<<t<<' ';
        }
        std::cout<<'\n';
        for(auto t:s3){
            std::cout<<t<<' ';
        }
        std::cout<<'\n';
    }*/
}


kdindex::kdindex(TemporalGraph *Graph){
    n=Graph->n;
    m=Graph->m;
    tmax = Graph->tmax*0.2;
    srand(1);
    d= new int[n];
    factor=RAND_MAX;
    alfa=new std::vector<std::vector<int> >[n];
    ed=new std::vector<int>[n];
    ed2=new std::vector<int>[n];
    double start_time=clock();
    for(int t=0;t<=tmax;t++){
        std::vector<std::pair<int, int>>::iterator it;
        int u,v;
        for (it = Graph->temporal_edge[t].begin(); it != Graph->temporal_edge[t].end(); it++) {
            u=(*it).first;
            v=(*it).second;
            ed2[u].push_back(v);
            ed2[v].push_back(u);
            /*if(t>=0 && t<=15){
                std::cout<<u<<' '<<v<<' '<<t<<'\n';
            }*/
        }
    }
    for(int i=0;i<n;i++){
        d[i]=0;
        std::sort(ed2[i].begin(),ed2[i].end());
        ed2[i].erase(std::unique(ed2[i].begin(),ed2[i].end()), ed2[i].end());
        alfa[i].resize(ed2[i].size());
    }
    for(int i=0;i<n;i++){
        int sz=ed2[i].size();
        if(sz==1)continue;
        for(auto p:ed2[i]){
            int u=p;
            if(ed2[u].size()>sz||(ed2[u].size()==sz&&u>i)){
                ed[u].push_back(i);
                //std::cerr<<u<<' '<<i<<'\n';
                //ed2[i].push_back(u);
                d[i]++;
            }
        }
    }
    for(int t=0;t<=tmax;t++){
        std::vector<std::pair<int, int>>::iterator it;
        int u,v;
        for (it = Graph->temporal_edge[t].begin(); it != Graph->temporal_edge[t].end(); it++) {
            u=(*it).first;
            v=(*it).second;
            int id=find(u,v);
            alfa[u][id].push_back(t);
            int id2=find(v,u);
            alfa[v][id2].push_back(t);
        }
    }
    std::queue<int> q;
    for(int i=0;i<n;i++){
        if(d[i]==0){q.push(i);}
    }
    std::vector<bool> vis(n,false);
    while(!q.empty()){
        int u=q.front();q.pop();
        for(auto v:ed[u]){
            vis[v]=true;
        }
        for(auto v:ed[u]){
            for(auto w:ed[v]){
                if(vis[w]){
                    //std::cerr<<u<<' '<<v<<' '<<w<<'\n';
                    //cnt++;
                    deal(u,v,w);
                    /*if(cnt%100000==0){
                        putProcess(double(cnt)/(100000), (clock()-start_time)/CLOCKS_PER_SEC);
                    }*/
                }
            }
            d[v]--;
            if(d[v]==0)q.push(v);
        }
        for(auto v:ed[u]){
            vis[v]=false;
        }
    }
    std::cout << "Fetching total: " << timeFormatting((clock()-start_time)/CLOCKS_PER_SEC).str() << std::endl<<std::endl;
    std::cerr<<beta.size()<<'\n';
    std::sort(beta.begin(),beta.end(),cmp);
    /*
    int tmp1=0;
    for(auto p:beta){
        if(p.ts>=10 && p.te<=24 && p.delta<=5){
            std::cerr<<p.ts<<' '<<p.te<<' '<<p.delta<<' '<<p.val<<'\n';
            tmp1+=p.val;
        }
    }
    std::cerr<<tmp1<<"??\n";*/
    std::vector<mode> beta2;beta2.clear();
    mode current;
    current.ts=beta[0].ts;
    current.te=beta[0].te;
    current.delta=beta[0].delta;
    current.val=beta[0].val;
    //std::cerr<<"???\n";
    for(long long i=1;i<beta.size();i++){
        if(beta[i].ts==beta[i-1].ts && beta[i].te==beta[i-1].te && beta[i].delta==beta[i-1].delta){
            current.val+=beta[i].val;
        }
        else{
            if(current.val!=0)
            beta2.push_back(current);
            current=beta[i];
        }
    }
    beta2.push_back(current);
    //std::cerr<<"??\n";
    //std::swap(alfa,beta);
    num=beta2.size();
    std::cerr<<num<<'\n';
    a = new mode[num];
    //int tmp=0;
    for(long long i=0;i<num;i++){
        a[i]=beta2[i];
        /*if(a[i].ts>=10 && a[i].te<=24 && a[i].delta<=3){
        std::cout<<a[i].ts<<' '<<a[i].te<<' '<<a[i].delta<<' '<<a[i].val<<'\n';
        tmp+=a[i].val;
        }*/
    }
    //std::cout<<tmp<<'\n';
    beta.clear();
    std::vector<mode>().swap(beta);
    beta2.clear();
    std::vector<mode>().swap(beta2);
    std::cout<<"Number of C-points: "<<num<<'\n';
    tree =new node[num+5];
    tree[0].tot=0;
    for(int i=0;i<3;i++)
    tree[0].mnpos[i]=1e9;
    for(int i=0;i<3;i++)
    tree[0].mxpos[i]=-1e9;
    for(int i=0;i<3;i++)
    tree[0].pos[i]=-1;
    long long root=0;
    //std::cerr<<"???\n";
    build(root,0,num-1,0);
    std::cout << "Indexing total: " << timeFormatting((clock()-start_time)/CLOCKS_PER_SEC).str()<<std::endl;


}

/*kdindex::kdindex(TemporalGraph *Graph){
    n=Graph->n;
    m=Graph->m;
    tmax=Graph->tmax*0.8;
    
    srand(1);
    factor=RAND_MAX;
    mp=new std::unordered_map<int,int>[n];
    ed=new std::vector<std::pair<int,int>>[n];
    deltav.clear();
    double start_time=clock();
    int tmpcnt=0;
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
                        int tpre=std::max(t1,mp[u][v1]);
                        int x=u,y=v,z=v1;
                        if(x>y)std::swap(x,y);
                        if(x>z)std::swap(x,z);
                        if(y>z)std::swap(y,z);
                        std::pair<int,std::pair<int,int> > vs=std::pair<int,std::pair<int,int> >(x,std::pair<int,int> (y,z));
                        
                        if(tmn>time){
                        if(deltav.count(vs)){
                            //std::vector<point> toper=deltav[vs];
                            int lst=-1;
                            int tmp=10;
                            while(1){
                                if(deltav[vs].empty())break;
                                //std::cout<<x<<' '<<y<<' '<<z<<' '<<tmn<<' '<<t<<'\n';
                                //std::cout<<toper<<' '<<toper->ts<<' '<<toper->delta<<' '<<toper->nex<<'\n';
                                
                                //point realtop=*toper;
                                int len=deltav[vs].size()-1;
                                point realtop = deltav[vs][len];
                                if(realtop.delta>t-tmn){
                                    if(rand()<=factor)
                                    alfa.push_back(mode(realtop.ts,t,realtop.delta,-1));
                                    if(lst!=-1){
                                        if(rand()<=factor)
                                        alfa.push_back(mode(realtop.ts,t,lst,1));
                                    }
                                    lst=realtop.delta;
                                    if(len>0){
                                        deltav[vs].pop_back();
                                        len--;
                                        realtop=deltav[vs][len];
                                    }
                                    else{
                                        break;
                                    }
                                }
                                else{
                                    if(rand()<=factor)
                                    alfa.push_back(mode(realtop.ts,t,t-tmn,-1));
                                    if(lst!=-1){
                                        if(rand()<=factor)
                                        alfa.push_back(mode(realtop.ts,t,lst,1));
                                    }
                                    break;
                                }
                            }
                            //std::cout<<toper<<"?\n";
                            point tmper=point(tmn,t-tmn);
                            deltav[vs].push_back(tmper);
                            if(rand()<=factor)
                            alfa.push_back(mode(tmn,t,t-tmn,1));
                            }
                            else{
                                point tmper=point(tmn,t-tmn);
                                deltav[vs].push_back(tmper);
                                if(rand()<=factor)
                                alfa.push_back(mode(tmn,t,t-tmn,1));
                            }
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
                        int x=u,y=v,z=v1;
                        if(x>y)std::swap(x,y);
                        if(x>z)std::swap(x,z);
                        if(y>z)std::swap(y,z);
                        std::pair<int,std::pair<int,int> > vs=std::pair<int,std::pair<int,int> >(x,std::pair<int,int> (y,z));
                        {
                            point tmper= point(tmn,t-tmn);
                            deltav[vs].push_back(tmper);
                            if(rand()<=factor)
                            alfa.push_back(mode(tmn,t,t-tmn,1));
                        }
                    }
                }
                ed[v].push_back(std::pair<int,int>(u,t));
                ed[u].push_back(std::pair<int,int>(v,t));
                mp[u][v]=t;
                mp[v][u]=t;
            }
        }
        //std::cerr<<alfa.size()<<std::endl;
        if((t+1)%10000 == 0){
        putProcess(double(t+1) / (tmax+1), (clock()-start_time)/CLOCKS_PER_SEC);
        //std::cerr<<deltav.size()<<'\n';
        }
    }//std::cerr<<tmpcnt<<'\n';
    deltav.clear();
    for(int i=0;i<n;i++){mp[i].clear();ed[i].clear();std::vector<std::pair<int,int> >().swap(ed[i]);}
    delete[] mp;
    delete[] ed;
    std::cout << "Fetching total: " << timeFormatting((clock()-start_time)/CLOCKS_PER_SEC).str() << std::endl<<std::endl;
    
    std::sort(alfa.begin(),alfa.end(),cmp);
    std::vector<mode> beta;beta.clear();
    mode current;
    current.ts=alfa[0].ts;
    current.te=alfa[0].te;
    current.delta=alfa[0].delta;
    current.val=alfa[0].val;
    //std::cerr<<"???\n";
    for(long long i=1;i<alfa.size();i++){
        if(alfa[i].ts==alfa[i-1].ts && alfa[i].te==alfa[i-1].te && alfa[i].delta==alfa[i-1].delta){
            current.val+=alfa[i].val;
        }
        else{
            if(current.val!=0)
            beta.push_back(current);
            current=alfa[i];
        }
    }
    beta.push_back(current);
    //std::cerr<<"??\n";
    //std::swap(alfa,beta);
    num=beta.size();
    // std::cerr<<num<<'\n';
    a = new mode[num];
    for(long long i=0;i<num;i++){
        a[i]=beta[i];
    }
    beta.clear();
    std::vector<mode>().swap(beta);
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
    long long root=0;
    //std::cerr<<"???\n";
    build(root,0,num-1,0);
    std::cout << "Indexing total: " << timeFormatting((clock()-start_time)/CLOCKS_PER_SEC).str()<<std::endl;
    //std::cout << "Indexing size: " <<  56ll*cnt<<"bytes"<< std::endl<<std::endl;
}*/

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
