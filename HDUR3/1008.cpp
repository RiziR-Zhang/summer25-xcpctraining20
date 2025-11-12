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
int n, a[mN];
char s[mN];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tsk;
    cin>>tsk;
    while(tsk--){
        cin>>n>>s;
        bool flag = (s[n - 1] != s[0]);
        for(int i = 1; i < n && flag; ++i){
            flag &= (s[i] != s[i - 1]);
        }
        if(flag){
            cout<<0<<endl;
            continue;
        }
        int pos = 0;
        Rpl(i, 0, n) a[i] = s[i] - '0';
        for(int i = 0; i < n; ++i){
            if(a[i] == (i % 2)){
                pos = i;
                break;
            }
        }
        int c1 = 0;
        for(int j = 0; j < n; ++j){
            int now = (pos + j) % n, nx = (now + 1) % n;
            if(a[now] != (now & 1)){
                if(a[now] != a[nx]){
                    swap(a[now], a[nx]);
                }else{
                    a[now] = !a[now];
                }
                ++c1;
            }
        }

        int c2 = 0;
        Rpl(i, 0, n) a[i] = s[i] - '0';
        for(int i = 0; i < n; ++i){
            if(a[i] != (i & 1)){
                pos = i;
                break;
            }
        }
        for(int j = 0; j < n; ++j){
            int now = (pos + j) % n, nx = (now + 1) % n;
            if(a[now] == (now & 1)){
                if(a[now] != a[nx]){
                    swap(a[now], a[nx]);
                }else{
                    a[now] = !a[now];
                }
                ++c2;
            }
        }

        cout<<min(c1, c2)<<endl;

    }
    return 0;
}
