#include<bits/stdc++.h>
using namespace std;
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    srand(time(0));
    freopen("graph.txt","w",stdout);
    int n=45,m=500,t=30;
    for(int i=1;i<=m;i++){
        printf("%d %d %d\n",rand()*rand()%n,rand()*rand()%n,rand()*rand()%t);
    }
}