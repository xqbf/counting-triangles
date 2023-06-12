#include<bits/stdc++.h>
using namespace std;
signed main(int argc,char* argv[]){
    srand(time(0));
    cin.tie(0);
    freopen("graph.txt","r",stdin);
    freopen("query.txt","w",stdout);
    int u,v,t=0,tmax=0;
    while(cin>>u>>v>>t){tmax=max(tmax,t);}
    std::cerr<<RAND_MAX<<std::endl;
    if(argv[1][0]=='0'){
        int q=10000;
        while(q--){
            int l=(rand())%(tmax+1),r=(rand())%(tmax+1);
            if(l>r)swap(l,r);
            printf("%d %d\n",l,r);
        }
    }
    if(argv[1][0]=='1'){
        int q=10000;
        while(q--){
            int l=(rand())%(tmax+1);
            while(l+0.1*tmax>tmax)l=(rand())%(tmax+1);
            int r=(l+0.1*tmax);
            printf("%d %d\n",l,r);
        }
    }
    if(argv[1][0]=='2'){
        int q=10000;
        while(q--){
            int l=(rand())%(tmax+1);
            while(l+0.2*tmax>tmax)l=(rand())%(tmax+1);
            int r=(l+0.2*tmax);
            printf("%d %d\n",l,r);
        }
    }
    if(argv[1][0]=='3'){
        int q=10000;
        while(q--){
            
            int l=(rand())%(tmax+1);
            while(l+0.3*tmax>tmax)l=(rand())%(tmax+1);
            int r=(l+0.3*tmax);
            printf("%d %d\n",l,r);
        }
    }
    return 0;
}
