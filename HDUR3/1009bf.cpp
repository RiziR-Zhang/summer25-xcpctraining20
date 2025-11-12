#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;

// #define FILE
#define DEBUG
#define Rpl(i,a,b) for(int i = (a); i < (b); ++i)
#define Rep(i,a,b) for(int i = (a); i <= (b); ++i)
typedef long long LL;
typedef pair<int,int> pii;
constexpr int mN = 15, mM = 15;
constexpr LL mdN = 1e9 + 7, inv10 = (mdN * 7 + 1) / 10;
int n, m, a[mN], cnt;
bool col[mN];
struct Seg{
    int l, r;
}seg[mM];
void chk(){
    bool fgall = 1;
    Rep(i, 1, m){
        bool fgsing = 0;
        Rep(j, seg[i].l, seg[i].r){
            fgsing |= col[j];
        }
        fgall &= fgsing;
    }
    cnt += fgall;
}
void dfs(int k){
    if(k > n){
        chk();
        return;
    }
    Rep(i, 1, 10){
        col[k] = (i <= a[k]);
        dfs(k + 1);
    }
}
int main()
{
#ifdef FILE
freopen("1009.in","r",stdin);
freopen("1009bf.out","w",stdout);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tsk;
    cin>>tsk;
    while(tsk--){
        cin>>n>>m;
        LL pre = 1;
        Rep(i, 1, n){
            cin>>a[i];
            pre = pre * inv10 % mdN;
        }
        Rep(i, 1, m){
            cin>>seg[i].l>>seg[i].r;
        }
        cnt = 0;
        dfs(1);
        // cout<<cnt<<endl;
        cout<<pre * cnt % mdN<<endl;
    }
#ifdef FILE
fclose(stdin);fclose(stdout);
#endif
    return 0;
}
