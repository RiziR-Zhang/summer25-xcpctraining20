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
constexpr int mN = 105;
constexpr LL mdN = 998244353;
int n, k;
LL a[mN], num[mN], sym[mN], sum;
void chk(){
    LL res = num[1];
    Rep(i, 2, n){
        if(sym[i] == 1){
            res = (res + num[i]) % mdN;
        }else if(sym[i] == 2){
            res = (res * num[i]) % mdN;
        }else if(sym[i] == 3){
            res = (res | num[i]) % mdN;
        }else if(sym[i] == 4){
            res = (res & num[i]) % mdN;
        }else
            res = (res ^ num[i]) % mdN;
    }
    sum = (sum + res) % mdN;
}
void dfs(int t){
    Rep(i, 1, k){
        num[t] = a[i];
        if(t < n){
            Rep(op, 1, 5){
                sym[t + 1] = op;
                dfs(t + 1);
            }
        }else{
            chk();
        }
    }
}
LL qp(LL p, LL q){
    LL pw = 1;
    while(q){
        if(q & 1) pw = pw * p % mdN;
        p = p * p % mdN;
        q >>= 1;
    }
    return pw;
}
void solve(){
    sum = 0;
    cin>>n>>k;
    Rep(i, 1, k){
        cin>>a[i];
    }
    dfs(1);
    cout<<sum * qp(k, (mdN - 2) * n) % mdN * qp(5, (mdN - 2) * (n - 1)) % mdN<<endl;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tsk;
    cin>>tsk;
    while(tsk--){
        solve();
        // ALLClear();
    }
    return 0;
}
