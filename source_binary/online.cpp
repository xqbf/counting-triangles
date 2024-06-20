#include "online.h"


bool onlineindex::cmp(node a,node b){
    if(a.degree==b.degree)return a.id<b.id;
    return a.degree>b.degree;
}






/*long long onlineindex::search(TemporalGraph *Graph, int ts,int te,int delta){
    for(int i=0;i<n;i++){
        //mp[i].clear();
        alfa[i].clear();
        ed[i].clear();
        //pt[i].clear();
    }
    //std::cerr<<"?\n";
    long long ans=0,tmp;
    int u,v,l1,l2,i,id,p,flag;
    std::vector<int> tmp1,tmp2;
    int cnt=0;
    for(int t=ts;t<=te;t++){
        std::vector<std::pair<int, int>>::iterator it;
        for (it = Graph->temporal_edge[t].begin(); it != Graph->temporal_edge[t].end(); it++) {
            u=(*it).first;
            v=(*it).second;
            ed[u].push_back(v);
            ed[v].push_back(u);
        }
    }
    //tmp1.clear();
    for(int i=0;i<n;i++){
        std::sort(ed[i].begin(),ed[i].end());
        ed[i].erase(std::unique(ed[i].begin(),ed[i].end()), ed[i].end());
        //std::cerr<<i<<' '<<ed[i].size()<<'\n';
        //std::cerr<<i<<": ";
        alfa[i].resize(ed[i].size());
        // if(ed[i].size()>150){
        //     for(int j=0;j<ed[i].size();j++){
        //         pt[i][ed[i][j]]=j;
        //     }
        // }
        //std::cerr<<'\n';
    }
    for(int t=ts;t<=te;t++){
        //  if(t%10000==0){
        //      std::cerr<<t<<' '<<cnt<<'\n';
        //  }
        std::vector<std::pair<int, int>>::iterator it;
        for (it = Graph->temporal_edge[t].begin(); it != Graph->temporal_edge[t].end(); it++) {
            u=(*it).first;
            v=(*it).second;
            if(ed[u].size()<ed[v].size())std::swap(u,v);
            if(ed[v].size()==1)continue;
            for(int i1=0;i1<ed[v].size();++i1){
                p=ed[v][i1];
                if(alfa[v][i1].size()==0)continue;
                id=find(u,p);
                if(id!=-1){
                    if(alfa[u][id].size()==0)continue;
                    cnt++;
                    //tmp1=alfa[u][id];
                    //tmp2=alfa[v][i1];
                    l1=alfa[u][id].size()-1,l2=alfa[v][i1].size()-1;
                    flag=1;
                    while(l1>=0 && l2>=0){
                        if(alfa[u][id][l1]>=alfa[v][i1][l2]){
                            if(t-alfa[u][id][l1]<=delta){
                                ans=ans+(alfa[v][i1].size()-l2-1);
                            }
                            else{
                                flag=0;break;
                            }
                            l1--;
                        }
                        else{
                            if(t-alfa[v][i1][l2]<=delta){
                                ans=ans+(alfa[u][id].size()-l1-1);
                            }
                            else{
                                flag=0;break;
                            }
                            l2--;
                        }
                        if(flag){
                            while(l1>=0){
                                if(t-alfa[u][id][l1]<=delta){
                                    ans=ans+(alfa[v][i1].size()-l2-1);
                                }
                                else break;
                                l1--;
                            }
                            while(l2>=0){
                                if(t-alfa[v][i1][l2]<=delta){
                                    ans=ans+(alfa[u][id].size()-l1-1);
                                }
                                else break;
                                l2--;
                            }
                        }
                    }
                }
            }
            id=find(u,v);
            alfa[u][id].push_back(t);
            id=find(v,u);
            alfa[v][id].push_back(t);
        }
    }
    std::cerr<<cnt<<'\n';
    return ans;
}*/

/*long long onlineindex::search(TemporalGraph *Graph, int ts,int te,int delta){
    for(int i=0;i<n;i++){
        mp[i].clear();
        //alfa[i].clear();
        ed[i].clear();
    }
    //std::cerr<<"?\n";
    long long ans=0,tmp;
    int u,v,l1,l2,i,id,p;
    std::vector<int> tmp1,tmp2;
    int cnt=0;
    for(int t=ts;t<=te;t++){
        if(t%10000==0){
            std::cerr<<t<<' '<<cnt<<'\n';
        }
        std::vector<std::pair<int, int>>::iterator it;
        for (it = Graph->temporal_edge[t].begin(); it != Graph->temporal_edge[t].end(); it++) {
            
            u=(*it).first;
            v=(*it).second;
            if(ed[u].size()<ed[v].size())std::swap(u,v);
            for(auto p:ed[v]){
                if(mp[u].count(p)){
                    cnt++;
                    tmp=0;
                    tmp1=mp[u][p];
                    tmp2=mp[v][p];
                    l1=0,l2=0;
                    for(i=0;i<tmp1.size();i++){
                        if(t-tmp1[i]<=delta)break;
                    }
                    for(;i<tmp1.size();i++){
                        while(tmp2[l2]<tmp1[i]&&l2<tmp2.size()){
                            l2++;
                        }
                        if(tmp2.size()==l2)break;
                        ans+=tmp2.size()-l2;
                    }
                    for(i=0;i<tmp2.size();i++){
                        if(t-tmp2[i]<=delta)break;
                    }
                    for(;i<tmp2.size();i++){
                        while(tmp1[l1]<=tmp2[i]&&l1<tmp1.size()){
                            l1++;
                        }
                        if(tmp1.size()==l1)break;
                        ans+=tmp1.size()-l1;
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
                tmp1.clear();tmp2.clear();
                tmp1.push_back(t);
                tmp2.push_back(t);
                mp[u][v]=tmp1;
                mp[v][u]=tmp2;
            }

        }
        //std::cerr<<alfa.size()<<std::endl;
    }
    std::cerr<<cnt<<'\n';
    return ans;
}*/




inline int onlineindex::find(int u,int p){
    
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
long long onlineindex::deal(int u,int v,int w,int delta){
    //mp[u][v],mp[v][w],mp[w][u]
    int t1=find(u,v),t2=find(v,w),t3=find(u,w);
    //std::vector<int> s1=alfa[u][t1];
    //std::vector<int> s2=alfa[v][t2];
    //std::vector<int> s3=alfa[u][t3];
    std::vector<int> s4;
    std::vector<int> s5;
    std::vector<int> s6;
    s4.resize(s1.size()+s2.size());
    s5.resize(s1.size()+s2.size()+s3.size());
    s6.resize(s1.size()+s2.size()+s3.size());
    long long ans=0;
    int l1=0,l2=0,l=0;
    while(l1<s1.size()&&l2<s2.size()){
        if(s1[l1]<=s2[l2]){
            s4[l]=s1[l1];
            l1++;l++;
        }
        else{
            s4[l]=s2[l2]+tmax+1;
            l2++;l++;
        }
    }
    while(l1<s1.size()){
        s4[l]=s1[l1];
        l++;l1++;
    }
    while(l2<s2.size()){
        s4[l]=s2[l2]+tmax+1;
        l++;l2++;
    }
    int l3=0,l4=0;
    l=0;
    long long a=0,b=0,c=0;
    int pre=0;
    while(l3<s3.size()&&l4<s4.size()){
        int p=s4[l4];
        if(s4[l4]>tmax)p-=tmax+1;
        if(s3[l3]<p){
            c++;
            s5[l]=s3[l3];
            s6[l]=3;
            l++;
            l3++;
        }
        else{
            if(s4[l4]>tmax){
                a++;
                s6[l]=1;
            }
            else{
                b++;
                s6[l]=2;
            }
            s5[l]=p;
            l4++;
            l++;
        }
        while(s5[l-1]-s5[pre]>delta){
            switch (s6[pre])
            {
            case 1:
                a--;
                break;
            case 2:
                b--;
                break;
            case 3:
                c--;
                break;
            }
            pre++;
        }
        switch (s6[l-1])
        {
            case 1:
            //std::cerr<<u<<' '<<v<<' '<<w<<'\n';
            //std::cerr<<"val: "<<b*c<<'\n';
                ans=ans+b*c;
                break;
            case 2:
            //std::cerr<<u<<' '<<v<<' '<<w<<'\n';
            //std::cerr<<"val: "<<a*c<<'\n';
                ans=ans+a*c;
                break;
            case 3:
            //std::cerr<<u<<' '<<v<<' '<<w<<'\n';
            //std::cerr<<"val: "<<a*b<<'\n';
                ans=ans+a*b;
                break;
        }
        if(ans>0){
            s5.clear();
            s6.clear();
            s4.clear();
            std:: vector<int>().swap(s5);
            std:: vector<int>().swap(s6);
            std:: vector<int>().swap(s4);
            return true;
        }
    }
    while(l3<s3.size()){
        c++;
        s5[l]=s3[l3];
        s6[l]=3;
        l++;
        l3++;
        while(s5[l-1]-s5[pre]>delta){
            switch (s6[pre])
            {
            case 1:
                a--;
                break;
            case 2:
                b--;
                break;
            case 3:
                c--;
                break;
            }
            pre++;
        }
        switch (s6[l-1])
        {
            case 1:
            //std::cerr<<u<<' '<<v<<' '<<w<<'\n';
            //std::cerr<<"val: "<<b*c<<'\n';
                ans=ans+b*c;
                break;
            case 2:
            //std::cerr<<u<<' '<<v<<' '<<w<<'\n';
            //std::cerr<<"val: "<<a*c<<'\n';
                ans=ans+a*c;
                break;
            case 3:
            //std::cerr<<u<<' '<<v<<' '<<w<<'\n';
            //std::cerr<<"val: "<<a*b<<'\n';
                ans=ans+a*b;
                break;
        }
        if(ans>0){
            s5.clear();
            s6.clear();
            s4.clear();
            std:: vector<int>().swap(s5);
            std:: vector<int>().swap(s6);
            std:: vector<int>().swap(s4);
            return true;
        }
    }
    while(l4<s4.size()){
        int p=s4[l4];
        if(s4[l4]>tmax)p-=tmax+1;
        if(s4[l4]>tmax){
                a++;
                s6[l]=1;
            }
            else{
                b++;
                s6[l]=2;
            }
            s5[l]=p;
            l4++;
            l++;
        while(s5[l-1]-s5[pre]>delta){
            switch (s6[pre])
            {
            case 1:
                a--;
                break;
            case 2:
                b--;
                break;
            case 3:
                c--;
                break;
            }
            pre++;
        }
        switch (s6[l-1])
        {
            case 1:
            //std::cerr<<u<<' '<<v<<' '<<w<<'\n';
            //std::cerr<<"val: "<<b*c<<'\n';
                ans=ans+b*c;
                break;
            case 2:
            //std::cerr<<u<<' '<<v<<' '<<w<<'\n';
            //std::cerr<<"val: "<<a*c<<'\n';
                ans=ans+a*c;
                break;
            case 3:
            //std::cerr<<u<<' '<<v<<' '<<w<<'\n';
            //std::cerr<<"val: "<<a*b<<'\n';
                ans=ans+a*b;
                break;
        }
        if(ans>0){
            s5.clear();
            s6.clear();
            s4.clear();
            std:: vector<int>().swap(s5);
            std:: vector<int>().swap(s6);
            std:: vector<int>().swap(s4);
            return true;
        }
    }
    //std::cerr<<u<<' '<<v<<' '<<w<<'\n';
    //std::cerr<<"val: "<<a<<' '<<b<<' '<<c<<'\n';
    s5.clear();
    s6.clear();
    s4.clear();
    std:: vector<int>().swap(s5);
    std:: vector<int>().swap(s6);
    std:: vector<int>().swap(s4);
    return ans>0;
}

long long onlineindex::search(TemporalGraph *Graph, int ts, int te,int delta){
    for(int i=0;i<n;i++){
        alfa[i].clear();
        ed[i].clear();
        ed2[i].clear();
        d[i]=0;
    }
    for(int t=ts;t<=te;t++){
        std::vector<std::pair<int, int>>::iterator it;
        int u,v;
        for (it = Graph->temporal_edge[t].begin(); it != Graph->temporal_edge[t].end(); it++) {
            u=(*it).first;
            v=(*it).second;
            ed2[u].push_back(v);
            ed2[v].push_back(u);
        }
    }
    //std::cerr<<"??\n";
    for(int i=0;i<n;i++){
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
    for(int t=ts;t<=te;t++){
        std::vector<std::pair<int, int>>::iterator it;
        int u,v;
        for (it = Graph->temporal_edge[t].begin(); it != Graph->temporal_edge[t].end(); it++) {
            u=(*it).first;
            v=(*it).second;
            int id=find(u,v);
            alfa[u][id].push_back(t);
            id=find(v,u);
            alfa[v][id].push_back(t);
            //mp[u][v].push_back(t);
            //mp[v][u].push_back(t);
        }
    }
    //std::cerr<<"??\n";
    std::queue<int> q;
    for(int i=0;i<n;i++){
        if(d[i]==0){q.push(i);}
    }
    long long ans=0;
    int cnt=0;
    std::vector<bool> vis(n,false);
    while(!q.empty()){
        int u=q.front();q.pop();
        for(auto v:ed[u]){
            vis[v]=true;
        }
        for(auto v:ed[u]){
            for(auto w:ed[v]){
                if(vis[w]){
                    cnt++;
                    ans+=deal(u,v,w,delta);
                }
            }
            d[v]--;
            if(d[v]==0)q.push(v);
        }
        for(auto v:ed[u]){
            vis[v]=false;
        }
    }
    //std::cerr<<cnt<<'\n';
    return ans;
}


onlineindex::onlineindex(TemporalGraph *Graph){
    n=Graph->n;
    //std::cerr<<n<<std::endl;
    tmax=Graph->tmax;
    //point = new node[n];
    d = new int[n];
    ed = new std::vector<int> [n]();
    ed2 = new std::vector<int> [n]();
    alfa = new std::vector<std::vector<int> > [n]();
    //pt = new std::unordered_map<int,int> [n]();
    //mp = new std::unordered_map<int, std::vector<int> > [n]();
    //ed2 = new std::set<int> [n]();
    //alfa = new element[n];
    //mp = new std::unordered_map<int,std::vector<int> > [n]();
    /*for(int i=0;i<n;i++){
        point[i].id=i;
        point[i].degree=0;
        mp[i].clear();
        ed[i].clear();
    }*/

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