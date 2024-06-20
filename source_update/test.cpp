#include<bits/stdc++.h>
using namespace std;
const int maxn=155;
struct node{
    int x,y,z,val;
    node(int x1=0,int y1=0,int z1=0,int val1=0){
        x=x1;y=y1;z=z1;val=val1;
    }
}a[maxn];
bool cmp(node a,node b){
    if(a.x!=b.x)return a.x<b.x;
    if(a.y!=b.y)return a.y<b.y;
    if(a.z!=b.z)return a.z<b.z;
    return a.val<b.val;
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    freopen("test.in","r",stdin);
    freopen("test.out","w",stdout);
    int x,y,z,val;
    int cnt=0;
    while(cin>>x>>y>>z>>val){
        a[++cnt]=node(x,y,z,val);
    }
    sort(a+1,a+1+cnt,cmp);
    for(int i=1;i<=cnt;i++){
        printf("%d %d %d %d\n",a[i].x,a[i].y,a[i].z,a[i].val);
    }
    return 0;
}
