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
typedef unsigned long long uLL;
typedef pair<int,int> pii;
constexpr int mN = 51, mB = 60;
int n;
uLL a[mN];
struct LinearBase{
    uLL b[mB];
    LinearBase(){
        memset(b, 0, sizeof(b));
    }
    void insert(uLL x){
        for(int w = mB - 1; w >= 0; --w){
            if(x & (1ull << w)){
                if(b[w]){
                    x ^= b[w];
                    if(x == 0) break;
                }else{
                    b[w] = x;
                    break;
                }
            }
        }
    }
    uLL conMax(){
        uLL res = 0;
        for(int w = mB - 1; w >= 0; --w){
            if((res ^ b[w]) > res) res ^= b[w];
        }
        return res;
    }
    void merge(const LinearBase& rhs){
        for(int w = 0; w < mB; ++w){
            if(rhs.b[w])
                insert(rhs.b[w]);
        }
    }
};
vector<LinearBase> lnb[2][mN];
void buildbase(){
    Rep(t, 0, 1){
        Rpl(i, 0, n){
            lnb[t][i].assign(n - i, LinearBase());
            Rpl(j, i, n){
                if(j != i){
                    lnb[t][i][j - i] = lnb[t][i][j - i - 1];
                }
                if((j & 1) == t)
                    lnb[t][i][j - i].insert(a[j]);
            }
        }
    }
}
uLL ans;
int sep[mN >> 1], k;
void process(){
    LinearBase todobase;
    Rep(t, 0, 1){
        for(int i = 1, stut = t; i <= k; ++i, stut ^= 1){
            int l = max(sep[i - 1] + 1, 0), r = min(sep[i] - 1, n - 1);
            todobase.merge(lnb[stut][l][r - l]);
        }
        ans = max(ans, todobase.conMax());
        todobase = LinearBase();
    }
}
void search(int x = -2){
    if(x > n){
        process();
        return;
    }
    for(int i = x + 3; i - 2 < n; i += 2){
        sep[++k] = i;
        search(i);
        --k;
    }
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tsk;
    cin>>tsk;
    while(tsk--){
        cin>>n;
        Rpl(i, 0, n){
            cin>>a[i];
        }
        buildbase();
        sep[0] = -1;
        ans = 0;
        search(-1);
        cout<<ans<<endl;
    }
    return 0;
}
