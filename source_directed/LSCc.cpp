#include "LSCc.h"
#include <math.h>
bool LSCcindex::cmp(mode a,mode b){
    if(a.te==b.te)return a.ts<b.ts;
    return a.te<b.te;
}

bool LSCcindex::cmp2(node a,node b){
    return a.pos<b.pos;
}

inline int LSCcindex::find(int u,int p){
    
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

LSCcindex::LSCcindex(TemporalGraph *Graph){
    n=Graph->n;
    m=Graph->m;
    tmax=Graph->tmax;
    factor=RAND_MAX*1;
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
            ed[u].push_back(v);
            //ed2[v].push_back(u);
        }
    }
    for(int i=0;i<n;i++){
        std::sort(ed[i].begin(),ed[i].end());
        ed[i].erase(std::unique(ed[i].begin(),ed[i].end()), ed[i].end());
        beta[i].resize(ed[i].size());
        /*std::sort(ed2[i].begin(),ed2[i].end());
        ed2[i].erase(std::unique(ed2[i].begin(),ed2[i].end()), ed2[i].end());*/
    }
    int id,p,l1,l2;
    long long cnt=0;
    for(int t=0;t<=tmax;t++){
        std::vector<std::pair<int, int>>::iterator it;
        for (it = Graph->temporal_edge[t].begin(); it != Graph->temporal_edge[t].end(); it++) {
            int u=(*it).first;
            int v=(*it).second;
            if(u==v)continue;
            //if(ed[u].size()<ed[v].size())std::swap(u,v);
            for(int i1=0;i1<ed[v].size();++i1){
                p=ed[v][i1];
                if(beta[v][i1].size()==0)continue;
                id=find(p,u);
                if(id!=-1){
                    if(beta[p][id].size()==0)continue;
                        cnt++;
                        l1=0,l2=0;
                    for(int i=0;i<beta[p][id].size();i++){
                        while(beta[v][i1][l2]<beta[p][id][i]&&l2<beta[v][i1].size()){
                            l2++;
                        }
                        if(beta[v][i1].size()==l2)break;
                        //std::cerr<<u<<' '<<v<<' '<<p<<' '<<tmp2.size()-l2<<std::endl;
                        if(rand()<factor)
                        alfa.push_back(mode(beta[p][id][i],t,beta[v][i1].size()-l2));
                    }
                    for(int i=0;i<beta[v][i1].size();i++){
                        while(beta[p][id][l1]<=beta[v][i1][i]&&l1<beta[p][id].size()){
                            l1++;
                        }
                        if(beta[p][id].size()==l1)break;
                        //std::cerr<<u<<' '<<v<<' '<<p<<' '<<tmp1.size()-l1<<std::endl;
                        if(rand()<factor)
                        alfa.push_back(mode(beta[v][i1][i],t,beta[p][id].size()-l1));
                    }
                    
                }
            }
            id=find(u,v);
            beta[u][id].push_back(t);
            /*id=find(v,u);
            beta[v][id].push_back(t);*/
        }
        if((t+1)%10000 == 0)
        putProcess(double(t+1) / (tmax+1), (clock()-start_time)/CLOCKS_PER_SEC);
        Graph->temporal_edge[t].clear();
        std::vector<std::pair<int, int>>().swap(Graph->temporal_edge[t]);
    }
    std::cout<<"Number of static triangles: "<<cnt<<'\n';
    //delete [] mp;
    delete [] ed;
    delete [] beta;
    delete Graph;
    std::cout << "Fetching total: " << timeFormatting((clock()-start_time)/CLOCKS_PER_SEC).str() << std::endl<<std::endl;
    int period_time = clock();
    long long szt=log(tmax+1)/log(2)+1;
    //tree.push_back((node)(0,0,0));
    sort(alfa.begin(),alfa.end(),cmp);
    std::vector<mode> beta2;beta2.clear();
    
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
            beta2.push_back(current);
            current=alfa[i];
        }
    }
    beta2.push_back(current);
    std::swap(alfa,beta2);
    beta2.clear();
    std::vector<mode>().swap(beta2);
    std::cout<<"Number of C-points: "<<alfa.size()<<std::endl;
    /*for(int i=0;i<alfa.size();i++){
        std::cerr<<alfa[i].ts<<' '<<alfa[i].te<<' '<<alfa[i].val<<'\n';
    }*/


    len=std::max(1,(int)sqrt(tmax));
    len2=std::max(1,(int)sqrt(len));
    mat1=new long long* [(tmax+1)/len+2];
    mat2=new long long* [(tmax+1)/len+2];
    for(int i=0;i<=(tmax+1)/len;i++){
        mat1[i]=new long long[(tmax+1)/len+2];
        mat2[i]=new long long[(tmax+1)/len+2];
        for(int j=0;j<=len;j++)mat1[i][j]=mat2[i][j]=0;
    }
    index1=new std::vector<node> [tmax+1];
    chunk1=new std::vector<node> [(tmax+1)/len2+1];
    index2=new std::vector<node> [tmax+1];
    chunk2=new std::vector<node> [(tmax+1)/len2+1];
    rindex1=new std::vector<node> [tmax+1];
    rchunk1=new std::vector<node> [(tmax+1)/len2+1];
    rindex2=new std::vector<node> [tmax+1];
    rchunk2=new std::vector<node> [(tmax+1)/len2+1];
    //std::cerr<<len<<' '<<len2<<'\n';
    long long sum=0;
    for(int i=0;i<alfa.size();i++){
        //std::cerr<<alfa[i].ts<<' '<<alfa[i].te<<' '<<alfa[i].val<<'\n';
        int delta=alfa[i].te-alfa[i].ts;
        sum=sum+alfa[i].val;
        mat1[alfa[i].ts/len][alfa[i].te/len]+=alfa[i].val;// O(1) big matrix
        mat2[delta/len][alfa[i].te/len]+=alfa[i].val;
        //std::cerr<<"??\n";
        index1[alfa[i].ts].push_back(node(alfa[i].te,-1,alfa[i].val));// {row, ts}
        chunk1[alfa[i].ts/len2].push_back(node(alfa[i].te,-1,alfa[i].val));// chunk for {row,ts}
        //std::cerr<<"???\n";
        index2[delta].push_back(node(alfa[i].te,-1,alfa[i].val));// {row,delta}
        chunk2[delta/len2].push_back(node(alfa[i].te,-1,alfa[i].val));// chunk for {row,delta}
        //std::cerr<<"???\n";
        rindex1[alfa[i].te].push_back(node(alfa[i].ts,-1,alfa[i].val));// {column, ts}
        rchunk1[alfa[i].te/len2].push_back(node(alfa[i].ts,-1,alfa[i].val));//chunk for {column, ts}
        //std::cerr<<"???\n";
        rindex2[alfa[i].te].push_back(node(delta,-1,alfa[i].val));// {column, delta}
        rchunk2[alfa[i].te/len2].push_back(node(delta,-1,alfa[i].val));//chunk for {column, delta}
        //std::cerr<<"???\n";
    }
    //std::cerr<<sum<<'\n';
    //std::cerr<<"???\n";
    for(int i=0;i<=tmax/len;i++){
        for(int j=0;j<=tmax/len;j++){
            if(i>0){
                mat1[i][j]+=mat1[i-1][j];
                mat2[i][j]+=mat2[i-1][j];
            }
            if(j>0){
                mat1[i][j]+=mat1[i][j-1];
                mat2[i][j]+=mat2[i][j-1];
            }
            if(i>0 && j>0){
                mat1[i][j]-=mat1[i-1][j-1];
                mat2[i][j]-=mat2[i-1][j-1];
            }
        }
    }
    //std::cerr<<"????\n";
    for(int i=0;i<=tmax;i++){
        int sz=index1[i].size();
        int fd=0;
        for(int j=1;j<sz;j++){
            index1[i][j].presum+=index1[i][j-1].presum;
        }
        if(i+1<=tmax)
        for(int j=0;j<sz;j++){
            while(fd<index1[i+1].size()&&index1[i+1][fd].pos<=index1[i][j].pos ){fd++;}
            index1[i][j].next=fd-1;
        }
    }
    //std::cerr<<"?????\n";
    for(int i=0;i<=tmax;i++){
        int sz=index2[i].size();
        int fd=0;
        for(int j=1;j<sz;j++){
            index2[i][j].presum+=index2[i][j-1].presum;
        }
        if(i+1<=tmax)
        for(int j=0;j<sz;j++){
            while(fd<index2[i+1].size()&&index2[i+1][fd].pos<=index2[i][j].pos ){fd++;}
            index2[i][j].next=fd-1;
        }
    }
    //std::cerr<<"??????\n";
    for(int i=0;i<=tmax;i++){
        if(!rindex1[i].empty())
        std::sort(rindex1[i].begin(),rindex1[i].end(),cmp2);
        if(!rindex2[i].empty())
        std::sort(rindex2[i].begin(),rindex2[i].end(),cmp2);
        int sz=rindex1[i].size();
        for(int j=1;j<sz;j++){
            rindex1[i][j].presum+=rindex1[i][j-1].presum;
        }
        sz=rindex2[i].size();
        for(int j=1;j<sz;j++){
            rindex2[i][j].presum+=rindex2[i][j-1].presum;
        }
    }
    for(int i=0;i<tmax;i++){
        int fd=0;
        int sz=rindex1[i].size();
        for(int j=0;j<sz;j++){
            while(fd<rindex1[i+1].size()&&rindex1[i+1][fd].pos<=rindex1[i][j].pos)fd++;
            rindex1[i][j].next=fd-1;
        }
    }
    for(int i=0;i<tmax;i++){
        int fd=0;
        int sz=rindex2[i].size();
        for(int j=0;j<sz;j++){
            while(fd<rindex2[i+1].size()&&rindex2[i+1][fd].pos<=rindex2[i][j].pos)fd++;
            rindex2[i][j].next=fd-1;
        }
    }
    for(int i=0;i<=tmax/len2;i++){
        if(!chunk1[i].empty()){
            std::sort(chunk1[i].begin(),chunk1[i].end(),cmp2);
            int sz=chunk1[i].size();
            for(int j=1;j<sz;j++){
                chunk1[i][j].presum+=chunk1[i][j-1].presum;
            }
        }
        if(!chunk2[i].empty()){
            std::sort(chunk2[i].begin(),chunk2[i].end(),cmp2);
            int sz=chunk2[i].size();
            for(int j=1;j<sz;j++){
                chunk2[i][j].presum+=chunk2[i][j-1].presum;
            }
        }
        if(!rchunk1[i].empty()){
            std::sort(rchunk1[i].begin(),rchunk1[i].end(),cmp2);
            int sz=rchunk1[i].size();
            for(int j=1;j<sz;j++){
                rchunk1[i][j].presum+=rchunk1[i][j-1].presum;
            }
        }
        if(!rchunk2[i].empty()){
            std::sort(rchunk2[i].begin(),rchunk2[i].end(),cmp2);
            int sz=rchunk2[i].size();
            for(int j=1;j<sz;j++){
                rchunk2[i][j].presum+=rchunk2[i][j-1].presum;
            }
        }
    }
    //std::cerr<<"???????\n";
    for(int i=0;i<tmax/len2;i++){
        int fd=0;
        int sz=chunk1[i].size();
        for(int j=0;j<sz;j++){
            while(fd<chunk1[i+1].size()&&chunk1[i+1][fd].pos<=chunk1[i][j].pos)fd++;
            chunk1[i][j].next=fd-1;
        }
    }
    for(int i=0;i<tmax/len2;i++){
        int fd=0;
        int sz=chunk2[i].size();
        for(int j=0;j<sz;j++){
            while(fd<chunk2[i+1].size()&&chunk2[i+1][fd].pos<=chunk2[i][j].pos)fd++;
            chunk2[i][j].next=fd-1;
        }
    }
    //std::cerr<<"????????\n";
    for(int i=0;i<tmax/len2;i++){
        int fd=0;
        int sz=rchunk1[i].size();
        for(int j=0;j<sz;j++){
            while(fd<rchunk1[i+1].size()&&rchunk1[i+1][fd].pos<=rchunk1[i][j].pos)fd++;
            rchunk1[i][j].next=fd-1;
        }
    }
    for(int i=0;i<tmax/len2;i++){
        int fd=0;
        int sz=rchunk2[i].size();
        for(int j=0;j<sz;j++){
            while(fd<rchunk2[i+1].size()&&rchunk2[i+1][fd].pos<=rchunk2[i][j].pos)fd++;
            rchunk2[i][j].next=fd-1;
        }
    }
    std::cout << "Indexing total: " << timeFormatting((clock()-start_time)/CLOCKS_PER_SEC).str()<<std::endl;
    //std::cout << "Indexing size: " <<  alfa.size()*8ll*16+32ll*(len+2)*(len+2)<<"bytes"<< std::endl<<std::endl;
}

long long LSCcindex::brute1(int ts1,int ts2,int te1,int te2){
	if(te1>te2)return 0; 
    long long ans = 0;
    if(ts2-ts1<=2*len){//chunk1
        te1--;
        int id1=ts1/len2;
        int id2=ts2/len2;
        if(id1+2>id2){
             int l=0,r=index1[ts1].size()-1;
            int pos=-1;
            while(l<=r){
                int mid=(l+r)>>1;
                if(index1[ts1][mid].pos<=te1){
                    pos=mid;l=mid+1;
                }
                else{
                    r=mid-1;
                }
            }
            if(pos!=-1){
                ans-=index1[ts1][pos].presum;
                pos=index1[ts1][pos].next;
            }
            if(pos==-1){
                pos=0;
            }
            for(int i=ts1+1;i<=ts2;i++){
                while(pos<index1[i].size()&&index1[i][pos].pos<=ts1){
                    pos++;
                }
                pos--;
                if(pos!=-1){
                    ans-=index1[i][pos].presum;
                    pos=index1[i][pos].next;
                }
                if(pos==-1){
                    pos=0;
                }
            }

            l=0,r=index1[ts1].size()-1;
            pos=-1;
            while(l<=r){
                int mid=(l+r)>>1;
                if(index1[ts1][mid].pos<=te2){
                    pos=mid;l=mid+1;
                }
                else{
                    r=mid-1;
                }
            }
            if(pos!=-1){
                ans+=index1[ts1][pos].presum;
                pos=index1[ts1][pos].next;
            }
            if(pos==-1){
                pos=0;
            }
            for(int i=ts1+1;i<=ts2;i++){
                while(pos<index1[i].size()&&index1[i][pos].pos<=te2){
                    pos++;
                }
                pos--;
                if(pos!=-1){
                    ans+=index1[i][pos].presum;
                    pos=index1[i][pos].next;
                }
                if(pos==-1){
                    pos=0;
                }
            }
            return ans;
        }
        int pos=-1;
        int l=0,r=chunk1[id1+1].size()-1;
        while(l<=r){
            int mid=(l+r)>>1;
            if(chunk1[id1+1][mid].pos<=te1){
                pos=mid;
                l=mid+1;
            }
            else r=mid-1;
        }
        if(pos!=-1){
            ans-=chunk1[id1+1][pos].presum;
            pos=chunk1[id1+1][pos].next;
        }
        if(pos==-1){
            pos=0;
        }
        for(int i=id1+2;i<id2;i++){
            while(pos<chunk1[i].size()&&chunk1[i][pos].pos<=te1){
                pos++;
            }
            pos--;
            if(pos!=-1){
                ans-=chunk1[i][pos].presum;
                pos=chunk1[i][pos].next;
            }
            if(pos==-1)pos=0;
        }



        pos=-1;
        l=0,r=index1[ts1].size()-1;
        while(l<=r){
            int mid=(l+r)>>1;
            if(index1[ts1][mid].pos<=te1){
                pos=mid;
                l=mid+1;
            }
            else r=mid-1;
        }
        if(pos!=-1){
            ans-=index1[ts1][pos].presum;
            pos=index1[ts1][pos].next;
        }
        if(pos==-1){
            pos=0;
        }
        for(int i=ts1+1;i<=(id1+1)*len2-1;i++){
            while(pos<index1[i].size()&&index1[i][pos].pos<=te1){
                pos++;
            }
            pos--;
            if(pos!=-1){
                ans-=index1[i][pos].presum;
                pos=index1[i][pos].next;
            }
            if(pos==-1)pos=0;
        }


        pos=-1;
        l=0,r=index1[id2*len2].size()-1;
        while(l<=r){
            int mid=(l+r)>>1;
            if(index1[id2*len2][mid].pos<=te1){
                pos=mid;
                l=mid+1;
            }
            else r=mid-1;
        }
        if(pos!=-1){
            ans-=index1[id2*len2][pos].presum;
            pos=index1[id2*len2][pos].next;
        }
        if(pos==-1){
            pos=0;
        }
        for(int i=id2*len2+1;i<=ts2;i++){
            while(pos<index1[i].size()&&index1[i][pos].pos<=te1){
                pos++;
            }
            pos--;
            if(pos!=-1){
                ans-=index1[i][pos].presum;
                pos=index1[i][pos].next;
            }
            if(pos==-1)pos=0;
        }

//summation
        pos=-1;
        l=0,r=chunk1[id1+1].size()-1;
        while(l<=r){
            int mid=(l+r)>>1;
            if(chunk1[id1+1][mid].pos<=te2){
                pos=mid;
                l=mid+1;
            }
            else r=mid-1;
        }
        if(pos!=-1){
            ans+=chunk1[id1+1][pos].presum;
            pos=chunk1[id1+1][pos].next;
        }
        if(pos==-1){
            pos=0;
        }
        for(int i=id1+2;i<id2;i++){
            while(pos<chunk1[i].size()&&chunk1[i][pos].pos<=te2){
                pos++;
            }
            pos--;
            if(pos!=-1){
                ans+=chunk1[i][pos].presum;
                pos=chunk1[i][pos].next;
            }
            if(pos==-1)pos=0;
        }



        pos=-1;
        l=0,r=index1[ts1].size()-1;
        while(l<=r){
            int mid=(l+r)>>1;
            if(index1[ts1][mid].pos<=te2){
                pos=mid;
                l=mid+1;
            }
            else r=mid-1;
        }
        if(pos!=-1){
            ans+=index1[ts1][pos].presum;
            pos=index1[ts1][pos].next;
        }
        if(pos==-1){
            pos=0;
        }
        for(int i=ts1+1;i<=(id1+1)*len2-1;i++){
            while(pos<index1[i].size()&&index1[i][pos].pos<=te2){
                pos++;
            }
            pos--;
            if(pos!=-1){
                ans+=index1[i][pos].presum;
                pos=index1[i][pos].next;
            }
            if(pos==-1)pos=0;
        }


        pos=-1;
        l=0,r=index1[id2*len2].size()-1;
        while(l<=r){
            int mid=(l+r)>>1;
            if(index1[id2*len2][mid].pos<=te2){
                pos=mid;
                l=mid+1;
            }
            else r=mid-1;
        }
        if(pos!=-1){
            ans+=index1[id2*len2][pos].presum;
            pos=index1[id2*len2][pos].next;
        }
        if(pos==-1){
            pos=0;
        }
        for(int i=id2*len2+1;i<=ts2;i++){
            while(pos<index1[i].size()&&index1[i][pos].pos<=te2){
                pos++;
            }
            pos--;
            if(pos!=-1){
                ans+=index1[i][pos].presum;
                pos=index1[i][pos].next;
            }
            if(pos==-1)pos=0;
        }

        return ans;
    }
    else{//rchunk1
        ts1--;
        int id1=te1/len2;
        int id2=te2/len2;
        if(id1+2>id2){
            int l=0,r=rindex1[te1].size()-1;
            int pos=-1;
            while(l<=r){
                int mid=(l+r)>>1;
                if(rindex1[te1][mid].pos<=ts1){
                    pos=mid;l=mid+1;
                }
                else{
                    r=mid-1;
                }
            }
            if(pos!=-1){
                ans-=rindex1[te1][pos].presum;
                pos=rindex1[te1][pos].next;
            }
            if(pos==-1){
                pos=0;
            }
            for(int i=te1+1;i<=te2;i++){
                while(pos<rindex1[i].size()&&rindex1[i][pos].pos<=ts1){
                    pos++;
                }
                pos--;
                if(pos!=-1){
                    ans-=rindex1[i][pos].presum;
                    pos=rindex1[i][pos].next;
                }
                if(pos==-1){
                    pos=0;
                }
            }

            l=0,r=rindex1[te1].size()-1;
            pos=-1;
            while(l<=r){
                int mid=(l+r)>>1;
                if(rindex1[te1][mid].pos<=ts2){
                    pos=mid;l=mid+1;
                }
                else{
                    r=mid-1;
                }
            }
            if(pos!=-1){
                ans+=rindex1[te1][pos].presum;
                pos=rindex1[te1][pos].next;
            }
            if(pos==-1){
                pos=0;
            }
            for(int i=te1+1;i<=te2;i++){
                while(pos<rindex1[i].size()&&rindex1[i][pos].pos<=ts2){
                    pos++;
                }
                pos--;
                if(pos!=-1){
                    ans+=rindex1[i][pos].presum;
                    pos=rindex1[i][pos].next;
                }
                if(pos==-1){
                    pos=0;
                }
            }
            return ans;
        }
        //std::cerr<<ts1<<' '<<ts2<<' '<<te1<<' '<<te2<<'\n'; 
        //std::cerr<<id1<<' '<<id2<<'\n';
        int pos=-1;
        int l=0,r=rchunk1[id1+1].size()-1;
        //std::cerr<<l<<' '<<r<<'\n';
        while(l<=r){
            int mid=(l+r)>>1;
            if(rchunk1[id1+1][mid].pos<=ts1){
                pos=mid;
                l=mid+1;
            }
            else r=mid-1;
        }
        if(pos!=-1){
            ans-=rchunk1[id1+1][pos].presum;
            pos=rchunk1[id1+1][pos].next;
        }
        if(pos==-1){
            pos=0;
        }
        for(int i=id1+2;i<id2;i++){
            while(pos<rchunk1[i].size()&&rchunk1[i][pos].pos<=ts1){
                pos++;
            }
            pos--;
            if(pos!=-1){
                ans-=rchunk1[i][pos].presum;
                pos=rchunk1[i][pos].next;
            }
            if(pos==-1)pos=0;
        }



        pos=-1;
        l=0,r=rindex1[te1].size()-1;
        //std::cerr<<l<<' '<<r<<"??\n"; 
        while(l<=r){
            int mid=(l+r)>>1;
            if(rindex1[te1][mid].pos<=ts1){
                pos=mid;
                l=mid+1;
            }
            else r=mid-1;
        }
        if(pos!=-1){
            ans-=rindex1[te1][pos].presum;
            pos=rindex1[te1][pos].next;
        }
        if(pos==-1){
            pos=0;
        }
        for(int i=te1+1;i<=(id1+1)*len2-1;i++){
            while(pos<rindex1[i].size()&&rindex1[i][pos].pos<=ts1){
                pos++;
            }
            pos--;
            if(pos!=-1){
                ans-=rindex1[i][pos].presum;
                pos=rindex1[i][pos].next;
            }
            if(pos==-1)pos=0;
        }


        pos=-1;
        //std::cerr<<id2*len2<<' '<<tmax<<'\n';
        l=0,r=rindex1[id2*len2].size()-1;
        //std::cerr<<l<<' '<<r<<"!\n";
        while(l<=r){
            int mid=(l+r)>>1;
            if(rindex1[id2*len2][mid].pos<=ts1){
                pos=mid;
                l=mid+1;
            }
            else r=mid-1;
        }
        if(pos!=-1){
            ans-=rindex1[id2*len2][pos].presum;
            pos=rindex1[id2*len2][pos].next;
        }
        if(pos==-1){
            pos=0;
        }
        for(int i=id2*len2+1;i<=te2;i++){
            while(pos<rindex1[i].size()&&rindex1[i][pos].pos<=ts1){
                pos++;
            }
            pos--;
            if(pos!=-1){
                ans-=rindex1[i][pos].presum;
                pos=rindex1[i][pos].next;
            }
            if(pos==-1)pos=0;
        }

//summation
        pos=-1;
        l=0,r=rchunk1[id1+1].size()-1;
        while(l<=r){
            int mid=(l+r)>>1;
            if(rchunk1[id1+1][mid].pos<=ts2){
                pos=mid;
                l=mid+1;
            }
            else r=mid-1;
        }
        if(pos!=-1){
            ans+=rchunk1[id1+1][pos].presum;
            pos=rchunk1[id1+1][pos].next;
        }
        if(pos==-1){
            pos=0;
        }
        for(int i=id1+2;i<id2;i++){
            while(pos<rchunk1[i].size()&&rchunk1[i][pos].pos<=ts2){
                pos++;
            }
            pos--;
            if(pos!=-1){
                ans+=rchunk1[i][pos].presum;
                pos=rchunk1[i][pos].next;
            }
            if(pos==-1)pos=0;
        }


        pos=-1;
        l=0,r=rindex1[te1].size()-1;
        while(l<=r){
            int mid=(l+r)>>1;
            if(rindex1[te1][mid].pos<=ts2){
                pos=mid;
                l=mid+1;
            }
            else r=mid-1;
        }
        if(pos!=-1){
            ans+=rindex1[te1][pos].presum;
            pos=rindex1[te1][pos].next;
        }
        if(pos==-1){
            pos=0;
        }
        for(int i=te1+1;i<=(id1+1)*len2-1;i++){
            while(pos<rindex1[i].size()&&rindex1[i][pos].pos<=ts2){
                pos++;
            }
            pos--;
            if(pos!=-1){
                ans+=rindex1[i][pos].presum;
                pos=rindex1[i][pos].next;
            }
            if(pos==-1)pos=0;
        }


        pos=-1;
        l=0,r=rindex1[id2*len2].size()-1;
        while(l<=r){
            int mid=(l+r)>>1;
            if(rindex1[id2*len2][mid].pos<=ts2){
                pos=mid;
                l=mid+1;
            }
            else r=mid-1;
        }
        if(pos!=-1){
            ans+=rindex1[id2*len2][pos].presum;
            pos=rindex1[id2*len2][pos].next;
        }
        if(pos==-1){
            pos=0;
        }
        for(int i=id2*len2+1;i<=te2;i++){
            while(pos<rindex1[i].size()&&rindex1[i][pos].pos<=ts2){
                pos++;
            }
            pos--;
            if(pos!=-1){
                ans+=rindex1[i][pos].presum;
                pos=rindex1[i][pos].next;
            }
            if(pos==-1)pos=0;
        }
        return ans;
    }
}


long long LSCcindex::query1(int ts1,int ts2,int te1,int te2){
    long long ans = 0;
    if(ts2/len!=ts1/len && te2/len!=te1/len){
        if(ts2/len>=1 && te2/len>=1){
            ans=mat1[ts2/len-1][te2/len-1];
            if((ts1)/len>=0){
                ans-=mat1[(ts1)/len][te2/len-1];
            }
            if((te1)/len>=0){
                ans-=mat1[ts2/len-1][(te1)/len];
            }
            if((ts1)/len>=0 && (te1)/len>=0){
                ans+=mat1[(ts1)/len][(te1)/len];
            }
        }
        //std::cerr<<ts1<<' '<<ts2<<' '<<te1<<' '<<te2<<' '<<len<<'\n';
    int es1=(ts1/len+1)*len-1;
    int et1=(te1/len+1)*len-1;
    int es2=(ts2/len)*len;
    int et2=(te2/len)*len;
    ans+=brute1(ts1,ts2,te1,et1);
    ans+=brute1(ts1,ts2,et2,te2);
    ans+=brute1(ts1,es1,et1+1,et2-1);
    ans+=brute1(es2,ts2,et1+1,et2-1);
    return ans;
    }
    //std::cerr<<"??\n";
    return brute1(ts1,ts2,te1,te2);
}

long long LSCcindex::brute2(int ts1,int ts2,int te1,int te2){
	if(te1>te2)return 0;
    //std::cerr<<ts1<<' '<<ts2<<' '<<te1<<' '<<te2<<'\n';
    long long ans = 0;
    if(ts2-ts1<=2*len){//chunk2
    te1--;
        int id1=ts1/len2;
        int id2=ts2/len2;
        
        if(id1+2>id2){
            int l=0,r=index2[ts1].size()-1;
            int pos=-1;
            while(l<=r){
                int mid=(l+r)>>1;
                if(index2[ts1][mid].pos<=te1){
                    pos=mid;l=mid+1;
                }
                else{
                    r=mid-1;
                }
            }
            if(pos!=-1){
                ans-=index2[ts1][pos].presum;
                pos=index2[ts1][pos].next;
            }
            if(pos==-1){
                pos=0;
            }
            for(int i=ts1+1;i<=ts2;i++){
                while(pos<index2[i].size()&&index2[i][pos].pos<=te1){
                    pos++;
                }
                pos--;
                if(pos!=-1){
                    ans-=index2[i][pos].presum;
                    pos=index2[i][pos].next;
                }
                if(pos==-1){
                    pos=0;
                }
            }

            l=0,r=index2[ts1].size()-1;
            pos=-1;
            while(l<=r){
                int mid=(l+r)>>1;
                if(index2[ts1][mid].pos<=te2){
                    pos=mid;l=mid+1;
                }
                else{
                    r=mid-1;
                }
            }
            if(pos!=-1){
                ans+=index2[ts1][pos].presum;
                pos=index2[ts1][pos].next;
            }
            if(pos==-1){
                pos=0;
            }
            //std::cerr<<ans<<'\n';
            for(int i=ts1+1;i<=ts2;i++){
                while(pos<index2[i].size()&&index2[i][pos].pos<=te2){
                    pos++;
                }
                pos--;
                if(pos!=-1){
                    //std::cerr<<i<<' '<<pos<<' '<<index2[i][pos].pos<<' '<<index2[i][pos].presum<<'\n';
                    ans+=index2[i][pos].presum;
                    pos=index2[i][pos].next;
                }
                if(pos==-1){
                    pos=0;
                }
            }
            //std::cerr<<ans<<'\n';
            return ans;
        }
        int pos=-1;
        int l=0,r=chunk2[id1+1].size()-1;
        while(l<=r){
            int mid=(l+r)>>1;
            if(chunk2[id1+1][mid].pos<=te1){
                pos=mid;
                l=mid+1;
            }
            else r=mid-1;
        }
        if(pos!=-1){
            ans-=chunk2[id1+1][pos].presum;
            pos=chunk2[id1+1][pos].next;
        }
        if(pos==-1){
            pos=0;
        }
        for(int i=id1+2;i<id2;i++){
            while(pos<chunk2[i].size()&&chunk2[i][pos].pos<=te1){
                pos++;
            }
            pos--;
            if(pos!=-1){
                ans-=chunk2[i][pos].presum;
                pos=chunk2[i][pos].next;
            }
            if(pos==-1)pos=0;
        }



        pos=-1;
        l=0,r=index2[ts1].size()-1;
        while(l<=r){
            int mid=(l+r)>>1;
            if(index2[ts1][mid].pos<=te1){
                pos=mid;
                l=mid+1;
            }
            else r=mid-1;
        }
        if(pos!=-1){
            ans-=index2[ts1][pos].presum;
            pos=index2[ts1][pos].next;
        }
        if(pos==-1){
            pos=0;
        }
        for(int i=ts1+1;i<=(id1+1)*len2-1;i++){
            while(pos<index2[i].size()&&index2[i][pos].pos<=te1){
                pos++;
            }
            pos--;
            if(pos!=-1){
                ans-=index2[i][pos].presum;
                pos=index2[i][pos].next;
            }
            if(pos==-1)pos=0;
        }


        pos=-1;
        l=0,r=index2[id2*len2].size()-1;
        while(l<=r){
            int mid=(l+r)>>1;
            if(index2[id2*len2][mid].pos<=te1){
                pos=mid;
                l=mid+1;
            }
            else r=mid-1;
        }
        if(pos!=-1){
            ans-=index2[id2*len2][pos].presum;
            pos=index2[id2*len2][pos].next;
        }
        if(pos==-1){
            pos=0;
        }
        for(int i=id2*len2+1;i<=ts2;i++){
            while(pos<index2[i].size()&&index2[i][pos].pos<=te1){
                pos++;
            }
            pos--;
            if(pos!=-1){
                ans-=index2[i][pos].presum;
                pos=index2[i][pos].next;
            }
            if(pos==-1)pos=0;
        }
        //std::cerr<<ans<<'\n';
//summation
        pos=-1;
        l=0,r=chunk2[id1+1].size()-1;
        while(l<=r){
            int mid=(l+r)>>1;
            if(chunk2[id1+1][mid].pos<=te2){
                pos=mid;
                l=mid+1;
            }
            else r=mid-1;
        }
        if(pos!=-1){
            //std::cerr<<id1+1<<' '<<chunk2[id1+1][pos].pos<<' '<<chunk2[id1+1][pos].presum<<'\n';
            ans+=chunk2[id1+1][pos].presum;
            pos=chunk2[id1+1][pos].next;
        }
        if(pos==-1){
            pos=0;
        }
        for(int i=id1+2;i<id2;i++){
            while(pos<chunk2[i].size()&&chunk2[i][pos].pos<=te2){
                pos++;
            }
            pos--;
            if(pos!=-1){
                //std::cerr<<i<<' '<<chunk2[i][pos].pos<<' '<<chunk2[i][pos].presum<<'\n';
                ans+=chunk2[i][pos].presum;
                pos=chunk2[i][pos].next;
            }
            if(pos==-1)pos=0;
        }



        pos=-1;
        l=0,r=index2[ts1].size()-1;
        while(l<=r){
            int mid=(l+r)>>1;
            if(index2[ts1][mid].pos<=te2){
                pos=mid;
                l=mid+1;
            }
            else r=mid-1;
        }
        if(pos!=-1){
            //std::cerr<<ts1<<' '<<index2[ts1][pos].pos<<' '<<index2[ts1][pos].presum<<"?\n";
            ans+=index2[ts1][pos].presum;
            pos=index2[ts1][pos].next;
        }
        if(pos==-1){
            pos=0;
        }
        for(int i=ts1+1;i<=(id1+1)*len2-1;i++){
            while(pos<index2[i].size()&&index2[i][pos].pos<=te2){
                pos++;
            }
            pos--;
            if(pos!=-1){
                //std::cerr<<i<<' '<<index2[i][pos].pos<<' '<<index2[i][pos].presum<<"?\n";
                ans+=index2[i][pos].presum;
                pos=index2[i][pos].next;
            }
            if(pos==-1)pos=0;
        }


        pos=-1;
        l=0,r=index2[id2*len2].size()-1;
        while(l<=r){
            int mid=(l+r)>>1;
            if(index2[id2*len2][mid].pos<=te2){
                pos=mid;
                l=mid+1;
            }
            else r=mid-1;
        }
        if(pos!=-1){
            //std::cerr<<id2*len2<<' '<<index2[id2*len2][pos].pos<<' '<<index2[id2*len2][pos].presum<<"!\n";
            ans+=index2[id2*len2][pos].presum;
            pos=index2[id2*len2][pos].next;
        }
        if(pos==-1){
            pos=0;
        }
        for(int i=id2*len2+1;i<=ts2;i++){
            while(pos<index2[i].size()&&index2[i][pos].pos<=te2){
                pos++;
            }
            pos--;
            if(pos!=-1){
                //std::cerr<<i<<' '<<index2[i][pos].pos<<' '<<index2[i][pos].presum<<"!\n";
                ans+=index2[i][pos].presum;
                pos=index2[i][pos].next;
            }
            if(pos==-1)pos=0;
        }
        //std::cerr<<ans<<'\n';
        return ans;
    }
    else{//rchunk2
    ts1--;
        int id1=te1/len2;
        int id2=te2/len2;
        if(id1+2>id2){
            int l=0,r=rindex2[te1].size()-1;
            int pos=-1;
            while(l<=r){
                int mid=(l+r)>>1;
                if(rindex2[te1][mid].pos<=ts1){
                    pos=mid;l=mid+1;
                }
                else{
                    r=mid-1;
                }
            }
            if(pos!=-1){
                ans-=rindex2[te1][pos].presum;
                pos=rindex2[te1][pos].next;
            }
            if(pos==-1){
                pos=0;
            }
            for(int i=te1+1;i<=te2;i++){
                while(pos<rindex2[i].size()&&rindex2[i][pos].pos<=ts1){
                    pos++;
                }
                pos--;
                if(pos!=-1){
                    ans-=rindex2[i][pos].presum;
                    pos=rindex2[i][pos].next;
                }
                if(pos==-1){
                    pos=0;
                }
            }

            l=0,r=rindex2[te1].size()-1;
            pos=-1;
            while(l<=r){
                int mid=(l+r)>>1;
                if(rindex2[te1][mid].pos<=ts2){
                    pos=mid;l=mid+1;
                }
                else{
                    r=mid-1;
                }
            }
            if(pos!=-1){
                ans+=rindex2[te1][pos].presum;
                pos=rindex2[te1][pos].next;
            }
            if(pos==-1){
                pos=0;
            }
            for(int i=te1+1;i<=te2;i++){
                while(pos<rindex2[i].size()&&rindex2[i][pos].pos<=ts2){
                    pos++;
                }
                pos--;
                if(pos!=-1){
                    ans+=rindex2[i][pos].presum;
                    pos=rindex2[i][pos].next;
                }
                if(pos==-1){
                    pos=0;
                }
            }
            return ans;
        }
        
        int pos=-1;
        int l=0,r=rchunk2[id1+1].size()-1;
        while(l<=r){
            int mid=(l+r)>>1;
            if(rchunk2[id1+1][mid].pos<=ts1){
                pos=mid;
                l=mid+1;
            }
            else r=mid-1;
        }
        if(pos!=-1){
            ans-=rchunk2[id1+1][pos].presum;
            pos=rchunk2[id1+1][pos].next;
        }
        if(pos==-1){
            pos=0;
        }
        for(int i=id1+2;i<id2;i++){
            while(pos<rchunk2[i].size()&&rchunk2[i][pos].pos<=ts1){
                pos++;
            }
            pos--;
            if(pos!=-1){
                ans-=rchunk2[i][pos].presum;
                pos=rchunk2[i][pos].next;
            }
            if(pos==-1)pos=0;
        }



        pos=-1;
        l=0,r=rindex2[te1].size()-1;
        while(l<=r){
            int mid=(l+r)>>1;
            if(rindex2[te1][mid].pos<=ts1){
                pos=mid;
                l=mid+1;
            }
            else r=mid-1;
        }
        if(pos!=-1){
            ans-=rindex2[te1][pos].presum;
            pos=rindex2[te1][pos].next;
        }
        if(pos==-1){
            pos=0;
        }
        for(int i=te1+1;i<=(id1+1)*len2-1;i++){
            while(pos<rindex2[i].size()&&rindex2[i][pos].pos<=ts1){
                pos++;
            }
            pos--;
            if(pos!=-1){
                ans-=rindex2[i][pos].presum;
                pos=rindex2[i][pos].next;
            }
            if(pos==-1)pos=0;
        }


        pos=-1;
        l=0,r=rindex2[id2*len2].size()-1;
        while(l<=r){
            int mid=(l+r)>>1;
            if(rindex2[id2*len2][mid].pos<=ts1){
                pos=mid;
                l=mid+1;
            }
            else r=mid-1;
        }
        if(pos!=-1){
            ans-=rindex2[id2*len2][pos].presum;
            pos=rindex2[id2*len2][pos].next;
        }
        if(pos==-1){
            pos=0;
        }
        for(int i=id2*len2+1;i<=te2;i++){
            while(pos<rindex2[i].size()&&rindex2[i][pos].pos<=ts1){
                pos++;
            }
            pos--;
            if(pos!=-1){
                ans-=rindex2[i][pos].presum;
                pos=rindex2[i][pos].next;
            }
            if(pos==-1)pos=0;
        }

//summation
        pos=-1;
        l=0,r=rchunk2[id1+1].size()-1;
        while(l<=r){
            int mid=(l+r)>>1;
            if(rchunk2[id1+1][mid].pos<=ts2){
                pos=mid;
                l=mid+1;
            }
            else r=mid-1;
        }
        if(pos!=-1){
            ans+=rchunk2[id1+1][pos].presum;
            pos=rchunk2[id1+1][pos].next;
        }
        if(pos==-1){
            pos=0;
        }
        for(int i=id1+2;i<id2;i++){
            while(pos<rchunk2[i].size()&&rchunk2[i][pos].pos<=ts2){
                pos++;
            }
            pos--;
            if(pos!=-1){
                ans+=rchunk2[i][pos].presum;
                pos=rchunk2[i][pos].next;
            }
            if(pos==-1)pos=0;
        }


        pos=-1;
        l=0,r=rindex2[te1].size()-1;
        while(l<=r){
            int mid=(l+r)>>1;
            if(rindex2[te1][mid].pos<=ts2){
                pos=mid;
                l=mid+1;
            }
            else r=mid-1;
        }
        if(pos!=-1){
            ans+=rindex2[te1][pos].presum;
            pos=rindex2[te1][pos].next;
        }
        if(pos==-1){
            pos=0;
        }
        for(int i=te1+1;i<=(id1+1)*len2-1;i++){
            while(pos<rindex2[i].size()&&rindex2[i][pos].pos<=ts2){
                pos++;
            }
            pos--;
            if(pos!=-1){
                ans+=rindex2[i][pos].presum;
                pos=rindex2[i][pos].next;
            }
            if(pos==-1)pos=0;
        }


        pos=-1;
        l=0,r=rindex2[id2*len2].size()-1;
        while(l<=r){
            int mid=(l+r)>>1;
            if(rindex2[id2*len2][mid].pos<=ts2){
                pos=mid;
                l=mid+1;
            }
            else r=mid-1;
        }
        if(pos!=-1){
            ans+=rindex2[id2*len2][pos].presum;
            pos=rindex2[id2*len2][pos].next;
        }
        if(pos==-1){
            pos=0;
        }
        for(int i=id2*len2+1;i<=te2;i++){
            while(pos<rindex2[i].size()&&rindex2[i][pos].pos<=ts2){
                pos++;
            }
            pos--;
            if(pos!=-1){
                ans+=rindex2[i][pos].presum;
                pos=rindex2[i][pos].next;
            }
            if(pos==-1)pos=0;
        }
        return ans;
    }
}


long long LSCcindex::query2(int ts1,int ts2,int te1,int te2){
    //bigmat: mat1[ts2/len-1][te2/len-1]-mat1[(ts1-1)/len-1][te2/len-1]-mat1[ts2/len-1][(te1-1)/len-1]+mat1[(ts1-1)/len-1][(te1-1)/len-1];
    long long ans = 0;
    //std::cerr<<ts1<<' '<<ts2<<' '<<te1<<' '<<te2<<'\n';
    //std::cerr<<ts1/len<<' '<<ts2/len<<' '<<te1/len<<' '<<te2/len<<'\n';
    if(ts2/len!=ts1/len && te2/len!=te1/len){
        if(ts2/len>=1 && te2/len>=1){
            ans=mat2[ts2/len-1][te2/len-1];
            if((ts1)/len>=0){
                ans-=mat2[(ts1)/len][te2/len-1];
            }
            if((te1)/len>=0){
                ans-=mat2[ts2/len-1][(te1)/len];
            }
            if((ts1)/len>=0 && (te1)/len>=0){
                ans+=mat2[(ts1)/len][(te1)/len];
            }
        }
    
        //std::cerr<<ts1<<' '<<ts2<<' '<<te1<<' '<<te2<<"??\n";
        //std::cerr<<ans<<'\n';
        //index i:[i*len,(i+1)*len-1]
        int es1=(ts1/len+1)*len-1;
        int et1=(te1/len+1)*len-1;
        int es2=(ts2/len)*len;
        int et2=(te2/len)*len;
        //std::cerr<<ts1<<' '<<ts2<<' '<<te1<<' '<<et1<<' '<<brute2(ts1,ts2,te1,et1)<<'\n';
        //std::cerr<<ts1<<' '<<ts2<<' '<<et2<<' '<<te2<<' '<<brute2(ts1,ts2,et2,te2)<<'\n';
        //std::cerr<<ts1<<' '<<es1<<' '<<et1+1<<' '<<et2-1<<' '<<brute2(ts1,es1,et1+1,et2-1)<<'\n';
        //std::cerr<<es2<<' '<<ts2<<' '<<et1+1<<' '<<et2-1<<' '<<brute2(es2,ts2,et1+1,et2-1)<<'\n';
        ans+=brute2(ts1,ts2,te1,et1);
        ans+=brute2(ts1,ts2,et2,te2);
        ans+=brute2(ts1,es1,et1+1,et2-1);
        ans+=brute2(es2,ts2,et1+1,et2-1);
        return ans;
    }
    return brute2(ts1,ts2,te1,te2);
}

long long LSCcindex::solve(int ts,int te,int delta){
    if(te-ts>delta){
        //std::cerr<<"?\n";
        long long tmp1=query1(ts,tmax,0,ts+delta),tmp2=query2(0,delta,ts+delta+1,te);
        //std::cout<<ts<<' '<<te<<' '<<delta<<' '<<tmp1<<' '<<tmp2<<' '<<tmp1+tmp2<<'\n';
        return tmp1+tmp2;
    }
    else{
        return query1(ts,tmax,0,te);
    }
}

void LSCc(LSCcindex *Index,TemporalGraph *Graph, char* query_file, char* output_file){
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
    int tmp=0;
    while(fin >> ts >> te>>delta){
        double alfa=1.0*RAND_MAX/Index->factor;
        //std::cerr<<ts<<' '<<te<<' '<<delta<<"????\n";
        fout<<(long long)(Index->solve(ts , te, delta)*alfa)<<std::endl;
        tmp++;
        if(tmp%100 == 0)
        putProcess(double(tmp) / query_num, (clock()-start_time)/CLOCKS_PER_SEC);
    }
    std::cout << "Average: " << timeFormatting((clock()-start_time)/CLOCKS_PER_SEC / query_num).str() << std::endl;
}
