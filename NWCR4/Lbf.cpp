#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;

//#define DEBUG
#define FILE
#define Rpl(i,a,b) for(int i = (a); i < (b); ++i)
#define Rep(i,a,b) for(int i = (a); i <= (b); ++i)
typedef long long LL;
typedef pair<int,int> pii;
//constexpr int mN = ;
int a[200005], b[200005];
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
#ifdef FILE
freopen("L.in","r",stdin);
freopen("Lbf.out","w",stdout);
#endif
    int n, q;
    cin>>n>>q;
#ifdef DEBUG
q = 1;
#endif
    Rep(i, 1, n){
        cin>>a[i];
    }
    int x, y;
    Rep(i, 1, q){
        cin>>x>>y;
        y = n + 1 - y;
        memcpy(b + 1, a + 1, sizeof(int) * (n + 1));
        int x0 = x;
        int j = 1;
        for(; j <= n && b[j] <= x; ++j);
        if(b[j] <= x){
            cout<<0<<endl;
            continue;
        }
        for(; j <= y; ++j){
            x = (x + b[j] + 1) / 2;
#ifdef DEBUG
cout<<j<<": "<<x<<endl;
#endif
        }
        cout<<x - x0<<endl;
    }
#ifdef FILE
fclose(stdin);fclose(stdout);
#endif

    return 0;
}
