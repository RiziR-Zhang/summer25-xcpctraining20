#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;

#define DEBUG
#define Rpl(i,a,b) for(int i = (a); i < (b); ++i)
#define Rep(i,a,b) for(int i = (a); i <= (b); ++i)
typedef long long LL;
typedef pair<int,int> pii;
//constexpr int mN = ;
inline int rn(int v){
    return ((rand() + 1) * (rand() + 1) + rand()) % v;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    freopen("1001.in","w",stdout);
    srand(20250725);
    int n = 500000, k = 50;
    Rep(i, 1, k){
        cout<<rn(1e9)<<' ';
    }
    cout<<endl;
    Rep(i, 1, n){
        cout<<rn(1e9)<<' ';
    }
    cout<<endl;
    fclose(stdout);
    return 0;
}
