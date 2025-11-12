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
constexpr int mN = 1000005;
int n, a[mN], b[mN], ans[mN], recrk[mN];
struct BIT{
    int tr[mN], len;
    void init(int Len){
        len = Len;
        Rep(i, 1, len) tr[i] = 0;
    }
    inline int lowbit(int x){return x & (-x);}
    void insert(int x){
        while(x <= len){
            tr[x]++;
            x += lowbit(x);
        }
    }
    int pre(int x){
        int s = 0;
        while(x){
            s += tr[x];
            x -= lowbit(x);
        }
        return s;
    }
}bit;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tsk;
    cin>>tsk;
    while(tsk--){
        cin>>n;
        Rep(i, 1, n){
            cin>>a[i];
            recrk[a[i]] = i;
        }
        Rep(i, 1, n){
            cin>>b[i];
//            b[i] = recrk[b[i]];
        }
/*        Rep(i, 1, n){
            cout<<b[i]<<' ';
        }
        cout<<endl;*/
        bit.init(n);
        Rep(i, 1, n){
            ans[b[i]] = (i - 1) + (recrk[b[i]] - 1) - bit.pre(recrk[b[i]]);
//            ans[a[i]] = i - 1 + b[i] - 1 - bit.pre(b[i]);
            bit.insert(recrk[b[i]]);
        }
        Rep(i, 1, n){
            cout<<ans[i]<<" ";
        }
        cout<<endl;
    }
    return 0;
}
