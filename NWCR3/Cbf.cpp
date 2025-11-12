#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;

#define DEBUG
#define FILE

#define Rpl(i,a,b) for(int i = (a); i < (b); ++i)
#define Rep(i,a,b) for(int i = (a); i <= (b); ++i)
typedef long long LL;
typedef pair<int,int> pii;
constexpr int mN = 105;
int n, m, a[mN];
char s[mN];
bool exs[27];
void solve(){
    int ans = 0;
    bool odd, even;
    Rep(i, 1, n){
        odd = 0, even = 0;
        Rep(j, i, n){
            if(exs[a[j]]) odd ^= 1, even ^= 1;
            else odd ^= 1, exs[a[j]] = 1;
            if(odd == 1 && even == 0) ans = max(ans, j - i + 1);
        }
        memset(exs, 0, sizeof(bool) * 26);
    }
    cout<<ans<<endl;
}
int main()
{
#ifdef FILE
    freopen("C.in", "r", stdin);
    freopen("Cbf.out", "w", stdout);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int l = 0, r = 0;
    Rep(tsk, 1, 1000){
        cin>>n>>m>>s;
        l = r + 1;
        r = r + m + 1;
#ifdef DEBUG
        if(l <= 731 && 731 <= r){
            //cout<<"Case #"<<tsk<<": "<<endl;
            Rep(i, 1, n) cout<<s[i - 1];
            cout<<endl;
        }
#endif
        Rep(i, 1, n){
            a[i] = s[i - 1] - 'a';
        }
        int idx;
        char t[3];
        solve();
        Rep(q, 1, m){
            cin>>idx>>t;
#ifdef DEBUG
            if(l <= 731 && 731 <= r){
                cout<<idx<<' '<<t<<endl;
            }
#endif
            a[idx] = t[0] - 'a';
            solve();
        }
    }
#ifdef FILE
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}
