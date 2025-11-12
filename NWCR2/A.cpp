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
constexpr int mN = 500005;
constexpr LL mdN = 998244353;
int n, a[mN];
LL f[mN][2], c[mN][2];
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tsk;
    cin>>tsk;
    while(tsk--){
        cin>>n;
        f[0][0] = f[0][1] = 0;
        c[0][0] = 1;
        c[0][1] = 0;
        Rep(i, 1, n){
            cin>>a[i];
            if(a[i] == 0 || a[i] == -1){
                c[i][0] = (c[i - 1][0] + c[i - 1][1]) % mdN;
                f[i][0] = (f[i - 1][0] + f[i - 1][1]) % mdN;
            }else{
                c[i][0] = 0;
                f[i][0] = 0;
            }
            if(a[i] == 1 || a[i] == -1){
                c[i][1] = (c[i - 1][0] + c[i - 1][1]) % mdN;
                f[i][1] = (f[i - 1][0] + f[i - 1][1] + c[i - 1][0]) % mdN;
            }else{
                c[i][1] = 0;
                f[i][1] = 0;
            }
        }
        cout<<(f[n][0] + f[n][1]) % mdN<<endl;
    }
    return 0;
}
