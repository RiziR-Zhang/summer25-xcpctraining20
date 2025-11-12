#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;

//#define DEBUG
//#define FILE
#define Rpl(i,a,b) for(int i = (a); i < (b); ++i)
#define Rep(i,a,b) for(int i = (a); i <= (b); ++i)
typedef long long LL;
typedef pair<int,int> pii;
constexpr int mN = 3005, Sigma = 17, INF = 0x3f3f3f3f;
int n, beg, w[Sigma + 4], req[mN];
char s[mN];
inline bool inSet(int S, int bit){
    return (S & (1 << bit));
}
void solve(){
    int ext = (beg + 1) / 2;
    Rpl(i, 1, n){
        int l = i, r = i + 1;
        req[i] = 0;
        if(i - ext + 1 < 1 || i + ext > n) continue;
        for(;l >= 1 && r <= n; --l, ++r){
            if(s[l] == s[r]){
                req[i] = 0;
                break;
            }
            req[i] |= 1 << (min(s[l] - 'a', s[r] - 'a'));
            if(r - l + 1 >= beg) break;
        }
    }

    int U = (1<<17) - 1, ans = INF;
    for(int S = 0; S <= U; ++S){
        bool flag = 1;
        for(int i = 1; i < n && flag; ++i){
            flag &= (req[i] == 0) || ((req[i] & S) != 0);
        }
        if(flag){
            int sum = 0;
            Rep(c, 1, Sigma){
                if(inSet(S, c - 1)) sum += w[c];
            }
            ans = min(ans, sum);
        }
    }
    if(ans == INF)
        cout<<-1<<endl;
    else
        cout<<ans<<endl;
}
int main()
{
#ifdef FILE
freopen("1003.in","r",stdin);
//freopen("1003.out","w",stdout);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tsk;
    cin>>tsk;
    while(tsk--){
        cin>>n;
        cin>>(s + 1);
        Rep(i, 1, Sigma) cin>>w[i];
        cin>>beg;
        solve();
    }
#ifdef FILE
fclose(stdin);
//fclose(stdout);
#endif
    return 0;
}
/*10240*/