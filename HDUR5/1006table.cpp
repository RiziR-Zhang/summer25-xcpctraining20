#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<cassert>
using namespace std;

#define DEBUG
#define Rpl(i,a,b) for(int i = (a); i < (b); ++i)
#define Rep(i,a,b) for(int i = (a); i <= (b); ++i)
typedef long long LL;
typedef pair<int,int> pii;
constexpr int mN = 23;
inline void addEdge(int u, int v){

}
int SG[1 << mN];
void solve(int n){
    int U = (1 << n) - 1;
    Rep(S, 0, U){
        Rpl(i, 0, n){
            if((i > 0 && (S & (1 << (i - 1))) == 0)
            || (i + 1 < n && (S & (1 << (i + 1))) == 0)){
                int nx = S;
                if(i > 0) nx |= 1 << (i - 1);
                nx |= 1 << i;
                if(i + 1 < n) nx |= 1 << (i + 1);
                addEdge(nx, S);
            }
        }
    }
    SG[U] = 0;
    vector<int> que(1, U);
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    Rep(i, 2, 10){
        solve(i);
    }
    return 0;
}
