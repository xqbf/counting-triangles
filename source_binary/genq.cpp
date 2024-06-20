#include<bits/stdc++.h>
using namespace std;
inline long long rande(){
    return 1ll*rand()*rand();
}
signed main(int argc,char* argv[]){
    cin.tie(0);
    freopen("graph.txt","r",stdin);
    //freopen("query.txt","w",stdout);
    int u,v,t=0,tmax=0;
    while(cin>>u>>v>>t){tmax=max(tmax,t);}
    std::cerr<<RAND_MAX<<std::endl;
    
    if(argv[1][0]=='E'){
    	string name("query.txt");
    	ofstream fout(name.c_str());
    	int q=10000;
    	for(int i=1;i<=q;i++){
    		int l=0.8*tmax/q*i;
    		int r=l+0.2*tmax,delta=0.1*(r-l);
    		fout<<l<<' '<<r<<' '<<delta<<'\n';
    	}
    }
	 
    if(argv[1][0]=='C'){
        string name("query.txt");
        ofstream fout(name.c_str());
        int q=10000;
        while(q--){
            int l=(rande())%(tmax+1);
            while(l+0.8*tmax>tmax)l=(rande())%(tmax+1);
            int r=(l+0.8*tmax),delta=0.1*(r-l);
            //printf("%d %d %d\n",l,r,delta);
            fout<<l<<' '<<r<<' '<<delta<<'\n';
        }
    }
    if(argv[1][0]=='A'){
        string name("query2.txt");
        ofstream fout(name.c_str());
        int q=100;
        while(q--){
            int l=(rande())%(tmax+1);
            while(l+0.2*tmax>tmax)l=(rande())%(tmax+1);
            int r=(l+0.2*tmax),delta=0.1*(r-l);
            //printf("%d %d %d\n",l,r,delta);
            fout<<l<<' '<<r<<' '<<delta<<'\n';
        }
        name="query4.txt"s;
        fout=ofstream(name.c_str());
        q=100;
        while(q--){
            int l=(rande())%(tmax+1);
            while(l+0.4*tmax>tmax)l=(rande())%(tmax+1);
            int r=(l+0.4*tmax),delta=0.1*(r-l);
            //printf("%d %d %d\n",l,r,delta);
            fout<<l<<' '<<r<<' '<<delta<<'\n';
        }
        name="query6.txt"s;
        fout=ofstream(name.c_str());
        q=100;
        while(q--){
            int l=(rande())%(tmax+1);
            while(l+0.6*tmax>tmax)l=(rande())%(tmax+1);
            int r=(l+0.6*tmax),delta=0.1*(r-l);
            //printf("%d %d %d\n",l,r,delta);
            fout<<l<<' '<<r<<' '<<delta<<'\n';
        }
        name="query8.txt"s;
        fout=ofstream(name.c_str());
        q=100;
        while(q--){
            int l=(rande())%(tmax+1);
            while(l+0.8*tmax>tmax)l=(rande())%(tmax+1);
            int r=(l+0.8*tmax),delta=0.1*(r-l);
            //printf("%d %d %d\n",l,r,delta);
            fout<<l<<' '<<r<<' '<<delta<<'\n';
        }
        name="query10.txt"s;
        fout=ofstream(name.c_str());
        q=100;
        while(q--){
            int l=0;
            int r=tmax,delta=0.1*(r-l);
            fout<<l<<' '<<r<<' '<<delta<<'\n';
        }
    }

    if(argv[1][0]=='B'){
        string name("queryd1.txt");
        ofstream fout(name.c_str());
        int q=100;
        while(q--){
            int l=0;
            int r=tmax,delta=0.1*(r-l);
            //printf("%d %d %d\n",l,r,delta);
            fout<<l<<' '<<r<<' '<<delta<<'\n';
        }
        name="queryd3.txt"s;
        fout=ofstream(name.c_str());
        q=100;
        while(q--){
            int l=0;
            int r=tmax,delta=0.3*(r-l);
            //printf("%d %d %d\n",l,r,delta);
            fout<<l<<' '<<r<<' '<<delta<<'\n';
        }
        name="queryd5.txt"s;
        fout=ofstream(name.c_str());
        q=100;
        while(q--){
            int l=0;
            int r=tmax,delta=0.5*(r-l);
            //printf("%d %d %d\n",l,r,delta);
            fout<<l<<' '<<r<<' '<<delta<<'\n';
        }
        name="queryd7.txt"s;
        fout=ofstream(name.c_str());
        q=100;
        while(q--){
            int l=0;
            int r=tmax,delta=0.7*(r-l);
            //printf("%d %d %d\n",l,r,delta);
            fout<<l<<' '<<r<<' '<<delta<<'\n';
        }
        name="queryd9.txt"s;
        fout=ofstream(name.c_str());
        q=100;
        while(q--){
            int l=0;
            int r=tmax,delta=0.9*(r-l);
            //printf("%d %d %d\n",l,r,delta);
            fout<<l<<' '<<r<<' '<<delta<<'\n';
        }
    }

    if(argv[1][0]=='D'){
        string name("queryf1.txt");
        ofstream fout(name.c_str());
        int q=10;
        while(q--){
            int l=0;
            int r=tmax,delta=0.1*(r-l);
            //printf("%d %d %d\n",l,r,delta);
            fout<<l<<' '<<r<<' '<<delta<<'\n';
        }
        name="queryf3.txt"s;
        fout=ofstream(name.c_str());
        q=10;
        while(q--){
            int l=0;
            int r=tmax,delta=0.3*(r-l);
            //printf("%d %d %d\n",l,r,delta);
            fout<<l<<' '<<r<<' '<<delta<<'\n';
        }
        name="queryf5.txt"s;
        fout=ofstream(name.c_str());
        q=10;
        while(q--){
            int l=0;
            int r=tmax,delta=0.5*(r-l);
            //printf("%d %d %d\n",l,r,delta);
            fout<<l<<' '<<r<<' '<<delta<<'\n';
        }
        name="queryf7.txt"s;
        fout=ofstream(name.c_str());
        q=10;
        while(q--){
            int l=0;
            int r=tmax,delta=0.7*(r-l);
            //printf("%d %d %d\n",l,r,delta);
            fout<<l<<' '<<r<<' '<<delta<<'\n';
        }
        name="queryf9.txt"s;
        fout=ofstream(name.c_str());
        q=10;
        while(q--){
            int l=0;
            int r=tmax,delta=0.9*(r-l);
            //printf("%d %d %d\n",l,r,delta);
            fout<<l<<' '<<r<<' '<<delta<<'\n';
        }
    }

	
	
    if(argv[1][0]=='0'){
        int q=10000;
        while(q--){
            int l=(rande())%(tmax+1),r=(rande())%(tmax+1),delta=(rande())%(tmax+1);
            if(l>r)swap(l,r);
            printf("%d %d %d\n",l,r,delta);
        }
    }
    if(argv[1][0]=='4'){
        int q=10000;
        while(q--){
            int l=(rande())%(tmax+1);
            while(l+0.4*tmax>tmax)l=(rande())%(tmax+1);
            int r=(l+0.4*tmax),delta=0.1*(r-l);
            printf("%d %d %d\n",l,r,delta);
        }
    }
    if(argv[1][0]=='2'){
        int q=10000;
        while(q--){
            int l=(rande())%(tmax+1);
            while(l+0.2*tmax>tmax)l=(rande())%(tmax+1);
            int r=(l+0.2*tmax),delta=0.1*(r-l);
            printf("%d %d %d\n",l,r,delta);
        }
    }
    if(argv[1][0]=='6'){
        int q=10000;
        while(q--){
            
            int l=(rande())%(tmax+1);
            while(l+0.6*tmax>tmax)l=(rande())%(tmax+1);
            int r=(l+0.6*tmax),delta=0.1*(r-l);
            printf("%d %d %d\n",l,r,delta);
        }
    }
    if(argv[1][0]=='8'){
         string name("query2.txt");
        ofstream fout(name.c_str());
        name="query8.txt"s;
        fout=ofstream(name.c_str());
        int q=10000;
        while(q--){
            
            int l=(rande())%(tmax+1);
            while(l+0.8*tmax>tmax)l=(rande())%(tmax+1);
            int r=(l+0.8*tmax),delta=0.1*(r-l);
            fout<<l<<' '<<r<<' '<<delta<<'\n';
        }
    }
    if(argv[1][0]=='x'){
        int q=10000;
        while(q--){
            int l=0;
            int r=tmax,delta=0.1*(r-l);
            printf("%d %d %d\n",l,r,delta);
        }
    }
    return 0;
}
