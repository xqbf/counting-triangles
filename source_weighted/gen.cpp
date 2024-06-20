 #include<bits/stdc++.h>
 using namespace std;
 signed main(){
     ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
     //srand(time(0));
     freopen("graph.txt","w",stdout);
     int n=1000,m=200000,t=1005;
     for(int i=1;i<=m;i++){
         printf("%d %d %d\n",1ll*rand()*rand()%n,1ll*rand()*rand()%n,1ll*rand()*rand()%t);
     }
 }

// #include<bits/stdc++.h>
// using namespace std;

// signed main(){
//     ios::sync_with_stdio(0);
//     cin.tie(0);
//     freopen("graph.txt","r",stdin);
//     freopen("graph1.txt","w",stdout);
    
//     return 0;
// }
