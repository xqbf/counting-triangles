#include<bits/stdc++.h>
using namespace std;
signed main(int argc,char* argv[]){
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::ifstream fin1(argv[1]);
    std::ifstream fin2(argv[2]);
    long long x,y;
    double ans;
    int cnt;
    while(fin1>>x){
        fin2>>y;
        cnt++;
        ans+=1.0*abs(y-x)/x;
        
    }
    printf("%.6lf\n",ans/cnt);
}