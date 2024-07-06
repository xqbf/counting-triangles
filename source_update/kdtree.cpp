#include"kdtree.h"

bool kdindex::cmp(mode a,mode b){
    if(a.te!=b.te){return a.te<b.te;}
    if(a.ts!=b.ts){return a.ts<b.ts;}
    return a.val<b.val;
}



void kdindex::pushup(long long rt){
    for(int i=0;i<3;i++){
        tree[rt].mxpos[i]=std::max(std::max(tree[tree[rt].ls].mxpos[i],tree[tree[rt].rs].mxpos[i]),tree[rt].mxpos[i]);
        tree[rt].mnpos[i]=std::min(std::min(tree[tree[rt].ls].mnpos[i],tree[tree[rt].rs].mnpos[i]),tree[rt].mnpos[i]);
    }
    tree[rt].tot=tree[rt].val+tree[tree[rt].ls].tot+tree[tree[rt].rs].tot;
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

void kdindex::insert(long long &rt, mode a, long long dep){
    if(rt!=0){
        static int opt=dep%3;
        if(opt==0){
            if(a.ts<=tree[rt].pos[0]){
                insert(tree[rt].ls,a,dep+1);
            }
            else{
                insert(tree[rt].rs,a,dep+1);
            }
        }
        else if(opt==1){
            if(a.te<=tree[rt].pos[1]){
                insert(tree[rt].ls,a,dep+1);
            }
            else{
                insert(tree[rt].rs,a,dep+1);
            }
        }
        else{
            if(a.delta<=tree[rt].pos[2]){
                insert(tree[rt].ls,a,dep+1);
            }
            else{
                insert(tree[rt].rs,a,dep+1);
            }
        }
        pushup(rt);
        return ;
    }
    else{
        
        cnt++;
        /*if(tree.size()<=cnt+1){
            //std::cout<<tree.size()<<std::endl;
            //std::cerr<<rt<<std::endl;
            tree.resize(1.1*cnt);
            //std::cerr<<tree[cnt].val<<std::endl;
            //std::cout<<tree.size()<<' '<<rt<<std::endl;
        }*/
        rt=cnt;
        //std::cerr<<cnt<<' '<<rt<<' '<<tree.size()<<std::endl;
        tree[rt].val=tree[rt].tot=a.val;
        tree[rt].pos[0]=tree[rt].mxpos[0]=tree[rt].mnpos[0]=a.ts;
        tree[rt].pos[1]=tree[rt].mxpos[1]=tree[rt].mnpos[1]=a.te;
        tree[rt].pos[2]=tree[rt].mxpos[2]=tree[rt].mnpos[2]=a.delta;
        tree[rt].ls=0;
        tree[rt].rs=0;
        return ;
    }
}


long long kdindex::solve(int ts,int te,int delta){
    return query(1,ts,tmax,0,te,0,delta);
}
long long kdindex::query(long long rt,int ts1,int ts2,int te1,int te2,int delta1,int delta2){
    if(!rt)return 0;
    /*std::cerr<<ts1<<' '<<ts2<<std::endl;
    std::cerr<<te1<<' '<<te2<<std::endl;
    std::cerr<<delta1<<' '<<delta2<<std::endl;

    std::cerr<<tree[rt].mnpos[0]<<' '<<tree[rt].mxpos[0]<<std::endl;
    std::cerr<<tree[rt].mnpos[1]<<' '<<tree[rt].mxpos[1]<<std::endl;
    std::cerr<<tree[rt].mnpos[2]<<' '<<tree[rt].mxpos[2]<<std::endl;*/
    if(ts1<=tree[rt].mnpos[0] && tree[rt].mxpos[0]<=ts2){
        if(te1<=tree[rt].mnpos[1] && tree[rt].mxpos[1]<=te2){
            if(delta1<=tree[rt].mnpos[2] && tree[rt].mxpos[2] <=delta2){
                //std::cerr<<tree[rt].tot<<std::endl;
                return tree[rt].tot;
            }
        }
    }
    /*std::cerr<<tree[rt].mnpos[0]<<' '<<tree[rt].mxpos[0]<<std::endl;
    std::cerr<<tree[rt].mnpos[1]<<' '<<tree[rt].mxpos[1]<<std::endl;
    std::cerr<<tree[rt].mnpos[2]<<' '<<tree[rt].mxpos[2]<<std::endl;*/
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
kdindex::kdindex(TemporalGraph *Graph,double length){
    n=Graph->n;
    m=Graph->m;
    tmax=Graph->tmax;
    tim=tmax*length;
    srand(1);
    factor=RAND_MAX;
    mp=new std::unordered_map<int,int>[n];
    ed=new std::vector<std::pair<int,int>>[n];
    rep=new std::unordered_map<int,int>[n];
    for(int t=0;t<=tmax;t++){
        std::vector<std::pair<int, int>>::iterator it;
        for (it = Graph->temporal_edge[t].begin(); it != Graph->temporal_edge[t].end(); it++) {
            int u=(*it).first;
            int v=(*it).second;
            rep[u][v]++;
            rep[v][u]++;
        }
    }
    deltav.clear();
    double start_time=clock();
    int check=0;
    for(int t=0;t<=tim;t++){
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
                        int tmn=std::min(std::min(t,t1),mp[u][v1]);
                        //if(mp[u][v1]<=time)continue;
                        int tpre=std::min(t1,std::min(time,mp[u][v1]));
                        if(tpre>=tmn)continue;
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
                                    int len=deltav[vs].size()-1;
                                    point realtop = deltav[vs][len];
                                    if(realtop.delta>t-tmn){
                                        if(rand()<=factor){
                                            /*if(t<=19 && realtop.delta<=1){
                                                std::cout<<"1!\n";
                                                std::cout<<realtop.ts<<' '<<t<<' '<<realtop.delta<<' ';
                                            std::cout<<vs.first<<' '<<vs.second.first<<' '<<vs.second.second<<' '<<-1<<'\n';
                                            check--;
                                            }*/

                                        alfa.push_back(mode(realtop.ts,t,realtop.delta,-1));
                                        }
                                        if(lst!=-1){
                                            if(rand()<=factor){
                                                /*if(t<=19 && lst<=1){
                                                    std::cout<<"2!\n";
                                                    std::cout<<realtop.ts<<' '<<t<<' '<<lst<<' ';
                                                    std::cout<<vs.first<<' '<<vs.second.first<<' '<<vs.second.second<<' '<<1<<'\n';
                                                    check++;
                                                }*/
                                            alfa.push_back(mode(realtop.ts,t,lst,1));
                                            }
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
                                        if(rand()<=factor){
                                            /*if(t<=19 && t-tmn<=1){
                                                std::cout<<"3!\n";
                                                check--;
                                                std::cout<<realtop.ts<<' '<<t<<' '<<t-tmn<<' ';
                                                std::cout<<vs.first<<' '<<vs.second.first<<' '<<vs.second.second<<' '<<-1<<'\n';
                                            }*/
                                        alfa.push_back(mode(realtop.ts,t,t-tmn,-1));
                                        }
                                        if(lst!=-1){
                                            if(rand()<=factor){
                                             /*   if(t<=19 && lst<=1){
                                                    std::cout<<"4!\n";
                                                    check++;
                                                    std::cout<<realtop.ts<<' '<<t<<' '<<lst<<' ';
                                                    std::cout<<vs.first<<' '<<vs.second.first<<' '<<vs.second.second<<' '<<1<<'\n';
                                                }*/
                                            alfa.push_back(mode(realtop.ts,t,lst,1));
                                            }
                                        }
                                        break;
                                    }
                                }
                                //std::cout<<toper<<"?\n";
                                point tmper=point(tmn,t-tmn);
                                deltav[vs].push_back(tmper);
                                if(rand()<=factor){
                                    /*if(t<=19 && t-tmn<=1){
                                        std::cout<<"5!\n";
                                        check++;
                                        std::cout<<tmn<<' '<<t<<' '<<t-tmn<<' ';
                                        std::cout<<vs.first<<' '<<vs.second.first<<' '<<vs.second.second<<' '<<1<<'\n';
                                        
                                    }*/
                                    alfa.push_back(mode(tmn,t,t-tmn,1));
                                }
                            }
                            else{
                                point tmper=point(tmn,t-tmn);
                                deltav[vs].push_back(tmper);
                                if(rand()<=factor){
                                /*if(t<=19 && t-tmn<=1){
                                    std::cout<<"6!\n";
                                    check++;
                                    std::cout<<vs.first<<' '<<vs.second.first<<' '<<vs.second.second<<' '<<1<<'\n';
                                }*/
                                alfa.push_back(mode(tmn,t,t-tmn,1));
                                }
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
                            if(rep[x][y]==1 && rep[x][z]==1 && rep[y][z]==1);
                            else deltav[vs].push_back(tmper);
                            if(rand()<=factor){
                                /*if(t<=19 && t-tmn<=1){
                                    std::cout<<vs.first<<' '<<vs.second.first<<' '<<vs.second.second<<' '<<1<<'\n';
                                    check++;
                                }*/
                                
                            alfa.push_back(mode(tmn,t,t-tmn,1));
                            }
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
    }
    //std::cout<<check<<'\n';
    //deltav.clear();
    //for(int i=0;i<n;i++){mp[i].clear();ed[i].clear();std::vector<std::pair<int,int> >().swap(ed[i]);}
    //delete[] mp;
    //delete[] ed;
    std::cout << "Fetching"<< length*100<<"\%"<<": " << timeFormatting((clock()-start_time)/CLOCKS_PER_SEC).str() << std::endl<<std::endl;
    
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
    //std::cerr<<num<<'\n';
    a = new mode[num];
    for(long long i=0;i<num;i++){
        a[i]=beta[i];
    }
    beta.clear();
    std::vector<mode>().swap(beta);
    alfa.clear();
    std::vector<mode>().swap(alfa);
    std::cout<<"Number of original C-points: "<<num<<'\n';
    tree =std::vector<node>(num+5);
    tree[0].tot=0;
    for(int i=0;i<3;i++)
    tree[0].mnpos[i]=1e9;
    for(int i=0;i<3;i++)
    tree[0].mxpos[i]=-1e9;
    for(int i=0;i<3;i++)
    tree[0].pos[i]=-1;
    //std::cerr<<"???\n";
    build(root,0,num-1,0);
    /*int tot=0;
    for(int i=0;i<num;i++){
        if(a[i].ts>=0 && a[i].te<=19 &&a[i].delta<=1){
            tot+=a[i].val;
            std::cout<<a[i].ts<<' '<<a[i].te<<' '<<a[i].delta<<' '<<a[i].val<<'\n';
        }
    }
    std::cout<<tot<<'\n';*/
    std::cout << "Indexing"<< length*100<<"\%"<<": " << timeFormatting((clock()-start_time)/CLOCKS_PER_SEC).str() << std::endl<<std::endl;
    //std::cout << "Indexing size: " <<  56ll*cnt<<"bytes"<< std::endl<<std::endl;
}




void kdindex::update(TemporalGraph *Graph, double pre){
    double start_time=clock();
    int tpre= pre*tmax+1;
    int edgenum=0;
    if(tpre>tmax)return ;
    for(int t=tpre;t<=tmax;t++){
        std::vector<std::pair<int, int>>::iterator it;
        for (it = Graph->temporal_edge[t].begin(); it != Graph->temporal_edge[t].end(); it++) {
            edgenum++;
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
                            if(rep[x][y]==1 && rep[x][z]==1 && rep[y][z]==1);
                            else deltav[vs].push_back(tmper);
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
    }
    if(alfa.empty())return;
    //std::cerr<<"??\n";
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
    //std::cerr<<num<<'\n';
    a = new mode[num];
    for(long long i=0;i<num;i++){
        a[i]=beta[i];
    }
    beta.clear();
    std::vector<mode>().swap(beta);
    alfa.clear();
    std::vector<mode>().swap(alfa);
    std::cout<<"Number of updated C-points: "<<num<<'\n';
    std::cout << "Update edge number: "<<edgenum<<std::endl;
    double start2=clock();
    for (long long i=0;i<num;i++){
        //std::cout<<a[i].ts<<' '<<a[i].te<<' '<<a[i].delta<<' '<<a[i].val<<' '<<root<<' '<<tree.size()<<' '<<cnt<<std::endl;
        insert(root,a[i],0);
        if(tree.size()<=cnt+5){
            //std::cerr<<tree.size()<<std::endl;
            //std::cerr<<rt<<std::endl;
            tree.resize(1.1*cnt);
            //std::cerr<<tree[cnt].val<<std::endl;
            //std::cerr<<tree.size()<<std::endl;
        }
        //std::cerr<<i<<' '<<tree[root].tot<<' '<<root<<std::endl;
        if((i+1)%100000==0){
             putProcess(double(i+1) / (num), (clock()-start2)/CLOCKS_PER_SEC);
        }
    }
    std::cout << "Update time costs: " << timeFormatting((clock()-start_time)/CLOCKS_PER_SEC).str()<<std::endl;
    

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
